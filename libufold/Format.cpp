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


#include "ufold/Format.hpp"

namespace ufold
{
    constexpr bool operator&(const Format a, const Format::Formats b) noexcept
    {
        return a.m_flags_ & static_cast<Format::flags_t>(b);
    }

    Format Format::operator=(const Format a) noexcept
    {
        m_flags_ = a.m_flags_;

        return *this;
    }

    Format Format::operator=(const Formats a) noexcept
    {
        m_flags_ = static_cast<flags_t>(a);

        return *this;
    }

    constexpr Format Format::operator|(const Format a) noexcept
    {
        return m_flags_ | a.m_flags_;
    }

    Format Format::operator|=(const Format a) noexcept
    {
        *this = *this | a.m_flags_;

        return *this;
    }
}
