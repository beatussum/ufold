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


#include "ufold/SeparatorSearcher.hpp"

namespace ufold
{
    using namespace core;

    Separators::const_iterator SeparatorSearcher::find_closest(const width_t key) const
    {
        const auto a = m_sep_.upper_bound(key);
        const auto b = m_sep_.lower_bound(key);

        return (key - a->first) < (b->first - key) ? a : b;
    }

    width_t SeparatorSearcher::operator()(const FirstIterator first)
    {
        switch (first) {
            case L:
            {
                Separators::const_iterator last;
                if (m_format_ & Formats::FillFromCenter) {
                    last = find_closest(m_size_ / 4);
                } else if (m_format_ & Formats::FillFromRight) {
                    last = find_closest(m_size_ / 2);
                } else {
                    last = m_sep_.cend();
                }

                return find_separator(m_sep_.cbegin(), last)->first;
            }
            case LC:
            {
                return find_separator(
                    std::make_reverse_iterator(find_closest(m_size_ / 2)),
                    m_sep_.crend()
                )->first;
            }
            case RC:
            {
                return find_separator(
                    find_closest(m_size_ / 2),
                    m_sep_.cend()
                )->first;
            }
            case R:
            {
                Separators::const_iterator last;
                if (m_format_ & Formats::FillFromCenter) {
                    last = find_closest(m_size_ * 3 / 4);
                } else if (m_format_ & Formats::FillFromLeft) {
                    last = find_closest(m_size_ / 2);
                } else {
                    last = m_sep_.cend();
                }

                return find_separator(
                    m_sep_.crbegin(),
                    std::make_reverse_iterator(last)
                )->first;
            }
        }
    }
}
