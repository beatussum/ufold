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
        const auto a = m_sep_->upper_bound(key);
        const auto b = m_sep_->lower_bound(key);

        return (key - a->first) < (b->first - key) ? a : b;
    }

    Separators::difference_type SeparatorSearcher::fraction(const size_t n, const size_t d) const
    {
        return distance( *m_sep_
                       , find_closest(m_size_ * n / d)
                       );
    }
}
