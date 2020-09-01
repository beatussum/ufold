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
#include "ufold/SeparatorSearcher.hpp"

namespace ufold
{
    using namespace core;

    namespace
    {
        [[gnu::const]]
        std::shared_ptr<Separators> scanSeparators(const string_view in, const Formats format)
        {
            auto out = std::make_shared<Separators>();

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
                        if (out->empty() or (lastValue(*out) != sep))
                            out->insert({ distance(in, i), sep });

                        break;
                }
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
        SeparatorSearcher functor(sep, str, format);

        const formats_t n = countAlignments(format);
        const bool left = format & Formats::FillFromLeft;
        const bool center = format & Formats::FillFromCenter;
        const bool right = format & Formats::FillFromRight;

        for (formats_t i = 0; spaces != 0; ++i) {
            Separators::const_iterator it;

            if (left and (  (center and (i % n == n - 2))
                         or (!center and (i % n == n - 1))
                         )
               )
            {
                it = functor(sep->cbegin(), sep->cend());
            } else if (center and (i % n == n - 1)) {
                if ( const auto middle = functor.fraction(1, 2)
                   ; (left and !right) or (   (i % (n + 1) == n)
                                          and (left == right)
                                          )
                   )
                {
                    it = functor( sep->crbegin() + middle
                                , sep->crend()
                                ).base();
                } else {
                    it = functor( sep->cbegin() + middle
                                , sep->cend()
                                );
                }
            } else if (right and (i % n == 0)) {
                it = functor(sep->crbegin(), sep->crend()).base();
            }

            sep->erase(it);

            for (auto m = max; m != 0; --m) {
                str.insert(it->first, 1, str[it->first]);
                --spaces;
            }
        }

        return str;
    } catch (...) { ufold_rethrow; }
}
