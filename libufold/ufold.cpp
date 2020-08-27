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
#include "ufold/Formats.hpp"

namespace ufold
{
    using namespace core;

    namespace
    {
        [[gnu::const]]
        Separators scanSeparators(const string_view in, const Formats format)
        {
            Separators out;

            for (auto i = in.cbegin(); i != in.cend(); ++i) {
                switch (const auto sep = getSeparatorTypeOf(*i); sep) {
                    case SeparatorType::Capital:
                        if (format & Formats::PreferCapital)
                            goto insert;

                        break;

                    case SeparatorType::Punctuation:
                        if (format & Formats::PreferPunctuation)
                            goto insert;

                        break;

                    default:
                    insert:
                        out.insert({ distance(in, i), sep });
                        break;
                }
            }

            return out;
        }
    }

    // `std::out_of_range` cannot be thrown
    string fold(string str, const width_t width)
    try {
        if (const auto size = str.size(); size > width) {
            using future_t = std::future<string::reverse_iterator>;

            auto futures = make_vector<future_t>((size % width) + 1);

            for (auto i = str.begin(); (i += width) < (str.end() - 1); ) {
                futures.push_back(
                    async_find_if( std::execution::par_unseq
                                 , std::make_reverse_iterator(i)
                                 , str.rbegin()
                                 , &isSeparator
                                 )
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

    string_vec split(const string_view in)
    try {
        using namespace std::execution;

        string_vec out;

        for ( auto first = in.cbegin(), last = first
            ; last != in.cend()
            ;)
        {
            last = std::find(par_unseq, last, in.cend(), L'\n');
            out.push_back(string(first, last));
            first = ++last;
        }

        return out;
    } catch (...) { ufold_rethrow; }

    string_view cleanOut(string_view str)
    try {
        using namespace std::execution;

        const auto value = str.front();

        if ( const auto iter =
                find_first_not_of(par_unseq, str.cbegin(), str.cend(), value)
           ; iter != str.cend()
           )
        {
            str.remove_prefix(distance(str, iter));
        }

        if ( const auto iter =
                find_first_not_of(par_unseq, str.crbegin(), str.crend(), value)
           ; iter != str.crend()
           )
        {
            str.remove_suffix(distance(str, iter));
        }

        return str;
    } catch (...) { ufold_rethrow; }
}
