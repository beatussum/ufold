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


#include "libufold_export.hpp"

#include <cstdint>

namespace ufold
{
    class LIBUFOLD_EXPORT Format final
    {
    public:
        using flags_t = uint8_t;

        enum Formats : flags_t {
            prioritizePunctuation = 0x1
        };
    private:
        constexpr Format(const flags_t f) noexcept
            : m_flags_(f)
        {}
    public:
        constexpr Format() noexcept
            : m_flags_(0)
        {}

        Format(const Format& f) noexcept { *this = f; }
        Format(const Formats f) noexcept { *this = f; }

        Format operator=(const Format) noexcept;
        Format operator=(const Formats) noexcept;

        constexpr Format operator|(const Format) noexcept;
        Format operator|=(const Format) noexcept;
        friend constexpr bool operator&(const Format, const Formats) noexcept;
    private:
        flags_t m_flags_;
    };
}
