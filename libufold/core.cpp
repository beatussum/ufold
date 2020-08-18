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


#include "ufold/core.hpp"

namespace ufold::core
{
    string::difference_type distance(const string_view first, const string_view::const_iterator last)
    {
        using std::distance;

        return distance(first.cbegin(), last);
    }

    string::difference_type distance(const string_view rfirst, const string_view::const_reverse_iterator rlast)
    {
        using std::distance;

        return distance(rfirst.crbegin(), rlast);
    }
}
