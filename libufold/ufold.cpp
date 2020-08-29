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
#include "ufold/Separators.hpp"

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

                    case SeparatorType::Space:
                    insert:
                        if ((i == in.cbegin()) or (*(i - 1) != *i))
                            out.insert({ distance(in, i), sep });

                        break;
                }
            }

            return out;
        }

        [[gnu::const]]
        constexpr formats_t countBits(const Formats format) noexcept
        {
            formats_t count = 0;

            for ( auto f = format & Formats::mask_Alignment
                ; f != 0
                ; f >>= 1
                )
            {
                count += f & 1;
            }

            return count;
        }

        [[gnu::const]]
        Separators::const_iterator getMiddle(const Separators& sep)
        {
            auto out = sep.cbegin();

            for ( Separators::size_type i = 0
                ; i != sep.size() / 2
                ; ++i
                )
            {
                ++out;
            }

            return out;
        }
    }

    // `std::out_of_range` cannot be thrown
    string fold(string str, const width_t width)
    try {
        using future_t = std::future<string::reverse_iterator>;

        const auto size = str.size();

        if (size <= width)
            return str;

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

    string align(string str, const Formats format, const width_t width, const width_t max)
    try {
        width_t spaces = width - str.size();

        if (spaces < 0) {
            throw std::invalid_argument( "`str` ("
                                       + std::to_string(str.size())
                                       + ") is too small: it must be "
                                         "larger than `width` ("
                                       + std::to_string(width)
                                       + "). See "
                                         "`ufold::fold()` to fold this "
                                         "`ufold::string` if necessary."
                                       );
        } else if (spaces == 0) {
            return str;
        }

        const auto sep = scanSeparators(str, format);

        const formats_t n = countBits(format);
        const bool left = format & Formats::FillFromLeft;
        const bool center = format & Formats::FillFromCenter;
        const bool right = format & Formats::FillFromRight;

        for (formats_t offset = 0, i = 0; spaces != 0; ++i) {
            width_t index;

            if (  (i % (n + 1) == 0 and center)
               or (i % n == 0 and !center)
               )
            {
                ++offset;
            }

            if (left and (  (center and (i % n == n - 2))
                         or (!center and (i % n == n - 1))
                         )
               )
            {
                index = (sep.cbegin() + offset)->first;
            } else if (center and (i % n == n - 1)) {
                if ( const auto middle = getMiddle(sep)
                   ; (left and !right) or (   (i % (n + 1) == n)
                                          and (left == right)
                                          )
                   )
                {
                    index = (middle - offset)->first;
                } else {
                    index = (middle + offset)->first;
                }
            } else if (right and (i % n == 0)) {
                index = (sep.cend() + offset)->first;
            }

            for (auto m = max; m != 0; --m) {
                str.insert(index, 1, str[index]);
                --spaces;
            }
        }

        return str;
    } catch (...) { ufold_rethrow; }
}
