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

/**
 * @file ufold/Formats.hpp
 * @author Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 * @date 2020-08-13
 * @copyright GPL-3+
 */


#ifndef LIBUFOLD_FORMAT_HPP
#define LIBUFOLD_FORMAT_HPP

#include "ufold/core.hpp"

/// Namespace of libufold
namespace ufold
{
    /// Underlying type of #Formats
    using formats_t = int8_t;

    /// An `enum` type representing how spaces are added
    enum class Formats : formats_t {
        /**
         * Prefer to add spaces where the next character is an
         * uppercase letter
         *
         * @pexample
         *
         * ```plain
         * Hello, I am Bob. I see my friend Bub    |
         * Hello,  I am  Bob. I see my  friend  Bub| (a)
         * Hello,  I  am Bob. I see my  friend  Bub| (b)
         * ```
         *
         * @note (a) Formats::PreferCapital, Formats::FillFromLeft
         *           and Formats::FillFromRight are set.
         * @note (b) Same thing except that Formats::PreferCapital
         *           is unset.
         */
        PreferCapital = 0x1,
        /**
         * Prefer to add spaces where the previous character is a
         * punctuation mark
         *
         * @pexample
         *
         * ```plain
         * Hello, I am Bob. I see an example sentence   |
         * Hello,  I am Bob.  I see an example  sentence| (a)
         * Hello,  I  am Bob. I see an example  sentence| (b)
         * ```
         *
         * @note (a) Formats::PreferPunctuation, Formats::FillFromLeft
         *           and Formats::FillFromRight are set.
         * @note (b) Same thing except that Formats::PreferPunctuation
         *           is unset.
         */
        PreferPunctuation = 0x2,
        /// Mask for Formats::PreferPunctuation and Formats::PreferCapital
        mask_Separator = 0x3,
        /**
         * If Formats::FillFromCenter is unset, only add spaces from
         * the left.
         *
         * @pexample
         *
         * ```plain
         * I am Bob and I see an example sentence   |
         * I  am  Bob  and I see an example sentence|
         * ```
         *
         * @see Formats::FillFromCenter
         */
        FillFromLeft = 0x4,
        /**
         * 1. If Formats::FillFromLeft or Formats::FillFromRight is set,
         *    add spaces from the center and then from the corresponding
         *    side.
         * 2. Otherwise, add spaces from the corresponding side and then
         *    from the center.
         *
         * @pexample
         *
         * ```plain
         * I am Bob and I see an example sentence   |
         * I  am Bob and  I see an example  sentence| (a)
         * I  am Bob and  I  see an example sentence| (b)
         * I  am Bob  and  I see an example sentence| (c)
         * I am Bob and I  see  an example  sentence| (d)
         * I am Bob  and  I  see an example sentence| (e)
         * ```
         *
         * @note (a) Formats::FillFromLeft, Formats::FillFromRight
         *           and Formats::FillFromCenter are set.
         * @note (b) Same thing except that Formats::FillFromCenter
         *           is unset.
         * @note (c) Only Formats::FillFromLeft and Formats::FillFromCenter
         *           are set.
         * @note (d) Only Formats::FillFromRight and Formats::FillFromCenter
         *           are set.
         * @note (e) Only Formats::FillFromCenter is set.
         */
        FillFromCenter = 0x8,
        /**
         * If Formats::FillFromCenter is unset, only add spaces from
         * the right.
         *
         * @pexample
         *
         * ```plain
         * I am Bob and I see an example sentence   |
         * I am Bob and I see  an  example  sentence|
         * ```
         *
         * @see Formats::FillFromCenter
         */
        FillFromRight = 0x10,
        /**
         * Mask for Formats::FillFromLeft, Formats::FillFromCenter,
         * and Formats::FillFromRight
         */
        mask_Alignment = 0x1C
    };
    LIBUFOLD_ADD_FLAGS_OP(Formats)

    /// Default value used for #Formats flag
    constexpr Formats defaultFormat = Formats::PreferPunctuation
                                    | Formats::FillFromLeft
                                    | Formats::FillFromCenter
                                    | Formats::FillFromRight;

    [[gnu::const]]
    constexpr formats_t countAlignments(const Formats format) noexcept;
}

#include "ufold/Formats.ipp"
#endif // LIBUFOLD_FORMAT_HPP
