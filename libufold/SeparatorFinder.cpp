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


#include "ufold/SeparatorFinder.hpp"

namespace ufold
{
    using namespace core;

    SeparatorFinder::underlying_type SeparatorFinder::find_closest(const width_t key) const
    {
        const auto a = m_sep_.upper_bound(key);
        const auto b = m_sep_.lower_bound(key);

        return (key - a->first) < (b->first - key) ? a : b;
    }

    SeparatorFinder::underlying_type SeparatorFinder::fraction(const width_t n, const width_t d) const
    {
        return find_closest(m_size_ * n / d);
    }

    SeparatorFinder::underlying_type SeparatorFinder::rfraction(const width_t n, const width_t d) const
    {
        return find_closest(m_size_ - std::max(m_size_ * n / d, 1uL));
    }

    SeparatorFinder::SeparatorFinder(const string& str, const Formats format)
        : m_size_(str.size())
        , m_format_(format)
        , m_i_()
    {
        for (auto i = str.cbegin(); i != str.cend(); ++i) {
            switch (const auto sep = getSeparatorTypeOf(*i); sep) {
                case SeparatorType::Capital:
                    if (m_format_ & Formats::PreferCapital)
                        goto insert;

                    break;

                case SeparatorType::Punctuation:
                    if (m_format_ & Formats::PreferPunctuation)
                        goto insert;

                    break;

                case SeparatorType::Space:
                insert:
                    if (!isValid() or (lastValue(m_sep_) != sep))
                        m_sep_.insert({ distance(str, i), sep });

                    break;
            }
        }
    }

    SeparatorFinder::string_index_t SeparatorFinder::next()
    {
        string_index_t out;

        ++m_i_;

        const formats_t n = countAlignments(m_format_);
        const bool left   = m_format_ & Formats::FillFromLeft;
        const bool center = m_format_ & Formats::FillFromCenter;
        const bool right  = m_format_ & Formats::FillFromRight;

        if (left and (  (center and (m_i_ % n == n - 2))
                     or (!center and (m_i_ % n == n - 1))
                     )
           )
        {
            SeparatorFinder::underlying_type last;
            if (center) {
                last = fraction(1, 4);
            } else if (right) {
                last = fraction(1, 2);
            } else {
                last = m_sep_.cend();
            }

            out = find_separator(m_sep_.cbegin(), last)->first;
        } else if (center and (m_i_ % n == n - 1)) {
            if ((left and !right) or (   (m_i_ % (n + 1) == n)
                                     and (left == right)
                                     )
               )
            {
                out =
                    find_separator(
                        std::make_reverse_iterator(fraction(1, 2)),
                        m_sep_.crend()
                    ).base()->first;
            } else {
                out =
                    find_separator(
                        rfraction(1, 2),
                        m_sep_.cend()
                    )->first;
            }
        } else if (right and (m_i_ % n == 0)) {
            SeparatorFinder::underlying_type last;
            if (center) {
                last = rfraction(1, 4);
            } else if (left) {
                last = rfraction(1, 2);
            } else {
                last = m_sep_.cend();
            }

            out =
                find_separator(
                    m_sep_.crbegin(),
                    std::make_reverse_iterator(last)
                ).base()->first;
        }

        return out;
    }
}
