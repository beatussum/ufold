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

namespace ufold
{
    using namespace core;

    namespace
    {
        void push_backsv(stringv_vec& vec, const string_view::const_iterator first, const string_view::const_iterator last)
        {
            vec.push_back(
                string_view(first, distance(first, last))
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
               ; sep != bad_enum<SeparatorType>()
               )
            {
                out.insert({ distance(in, i), sep });
            }
        }

        return out;
    } catch (...) { ufold_rethrow; }

    stringv_vec split(const string_view in)
    try {
        using namespace std::execution;

        stringv_vec out;

        string_view::const_iterator first;
        for ( auto last = first = in.cbegin()
            ; (last = std::find(par, last, in.cend(), '\n')) != in.cend()
            ;)
        {
            push_backsv(out, first, last - 1);
            ++first = last;
        }

        push_backsv(out, first, in.cend());

        return out;
    } catch (...) { ufold_rethrow; }

    string_view cleanOut(string_view str)
    try {
        const auto value = str.front();

        if ( const auto iter =
                find_first_not_of(str.cbegin(), str.cend(), value)
           ; iter != str.cend()
           )
        {
            str.remove_prefix(distance(str, iter));
        }

        if ( const auto iter =
                find_first_not_of(str.crbegin(), str.crend(), value)
           ; iter != str.crend()
           )
        {
            str.remove_suffix(distance(str, iter));
        }

        return str;
    } catch (...) { ufold_rethrow; }
}
