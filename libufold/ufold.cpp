/*
 * Copyright (C) 2020 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software:  you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published  by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be  useful,
 * but WITHOUT ANY WARRANTY;   without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>.
 */


#include "ufold/ufold.hpp"

#include <cwctype>

namespace ufold
{
    using namespace core;

    namespace
    {
        [[gnu::const]]
        constexpr bool isSpace(const char_t c) noexcept
        {
            switch (c) {
                case L' ':      // SPACE
                case L'\u2000': // EN QUAD
                case L'\u2001': // EM QUAD
                case L'\u2002': // EN SPACE
                case L'\u2003': // EM SPACE
                case L'\u2004': // THREE-PER-EM-SPACE
                case L'\u2005': // FOUR-PER-EM-SPACE
                case L'\u2006': // SIX-PER-EM-SPACE
                case L'\u2007': // FIGURE SPACE
                case L'\u2008': // PUNCTUATION SPACE
                case L'\u2009': // THIN SPACE
                case L'\u200A': // HAIR SPACE
                case L'\u202F': // NARROW NO-BREAK SPACE
                case L'\u205F': // MEDIUM MATHEMATICAL SPACE
                case L'\u3000': // IDEOGRAPHIC SPACE
                    return true;
                default:
                    return false;
            }
        }

        [[gnu::const]]
        constexpr bool isSeparator(const char_t c) noexcept
        {
            switch (c) {
                case L'-':      // HYPHEN-MINUS
                case L'\u00AD': // SOFT HYPHEN
                case L'\u2010': // HYPHEN
                case L'\u2E3A': // TWO-EM DASH
                case L'\u2E3B': // THREE-EM DASH
                    return true;
                default:
                    return isSpace(c);
            }
        }

        [[gnu::const]]
        constexpr bool isPunctuationMark(const char_t c) noexcept
        {
            switch (c) {
                case L',':
                case L';':
                case L':':
                case L'?':
                case L'!':
                case L'\u203D': // INTERROBANG
                case L'(':
                case L')':
                case L'"':
                case L'\'':
                case L'`':
                case L'\u2018': // LEFT SINGLE QUOTATION MARK
                case L'\u2019': // RIGHT SINGLE QUOTATION MARK
                case L'\u201A': // SINGLE LOW-9 QUOTATION MARK
                case L'\u201B': // SINGLE HIGH-REVERSED-9 QUOTATION MARK
                case L'\u201C': // LEFT SINGLE QUOTATION MARK
                case L'\u201D': // RIGHT SINGLE QUOTATION MARK
                case L'\u201E': // DOUBLE LOW-9 QUOTATION MARK
                case L'\u201F': // DOUBLE HIGH-REVERSED-9 QUOTATION MARK
                case L'\u2039': // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
                case L'\u203A': // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
                case L'\u00AB': // DOUBLE LEFT-POINTING ANGLE QUOTATION MARK
                case L'\u00BB': // DOUBLE RIGHT-POINTING ANGLE QUOTATION MARK
                    return true;
                default:
                    return false;
            }
        }

        [[gnu::const]]
        constexpr SeparatorType getSeparatorTypeOf(const char_t c) noexcept
        {
            if (std::iswupper(c)) {
                return SeparatorType::Capital;
            } else if (isPunctuationMark(c)) {
                return SeparatorType::Punctuation;
            } else if (isSpace(c)) {
                return SeparatorType::Space;
            } else {
                return ufold_bad_enum(SeparatorType);
            }
        }

        void push_backsv(stringv_vec& vec, const string::const_iterator first, const string::const_iterator last)
        {
            vec.push_back(
                string_view(&*first, distance(first, last))
            );
        }
    }

    // `std::out_of_range` cannot be thrown
    string fold(string str, const string::size_type width)
    try {
        if (const auto size = str.size(); size > width) {
            using future_t = std::future<string::reverse_iterator>;

            auto futures = make_vector<future_t>((size % width) + 1);

            for (auto i = str.begin(); (i += width) < str.end(); ) {
                futures.push_back(
                    async_find_if(std::make_reverse_iterator(i),
                                  str.rbegin(),
                                  &isSeparator)
                );
            }

            for (auto& i : futures) {
                if ( const auto iter = i.get().base()
                   ; isSpace(*iter)
                   )
                {
                    *iter = L'\n';
                } else {
                    str.insert(iter, L'\n');
                }
            }
        }

        return str;
    } catch (...) { ufold_rethrow; }

    Separators scanSeparators(const string_view in)
    try {
        Separators out;

        for (auto i = in.cbegin(); i <= in.cend(); ++i) {
            if ( const auto sep = getSeparatorTypeOf(*i)
               ; sep != ufold_bad_enum(SeparatorType)
               )
            {
                out.insert({ distance(in, i), sep });
            }
        }

        return out;
    } catch (...) { ufold_rethrow; }

    stringv_vec split(const string& in)
    try {
        using namespace std::execution;

        stringv_vec ret;

        string::const_iterator first;
        for ( auto last = first = in.cbegin()
            ; (last = std::find(par, last, in.cend(), '\n')) != in.cend()
            ;)
        {
            push_backsv(ret, first, last - 1);
            ++first = last;
        }

        push_backsv(ret, first, in.cend());

        return ret;
    } catch (...) { ufold_rethrow; }

    string_view cleanOut(string_view str)
    try {
        const auto value = str.front();

        if (const auto iter =
                find_first_not_of(str.cbegin(), str.cend(), value)
           ; iter != str.cend())
        {
            str.remove_prefix(distance(str, iter));
        }

        if (const auto iter =
                find_first_not_of(str.crbegin(), str.crend(), value)
           ; iter != str.crend())
        {
            str.remove_suffix(distance(str, iter));
        }

        return str;
    } catch (...) { ufold_rethrow; }
}
