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


#ifndef UFOLD_SEPARATORS_IPP
#define UFOLD_SEPARATORS_IPP

#include <cwctype>

namespace ufold
{
    using namespace core;

    constexpr bool isSpace(const char_t c) noexcept
    {
        switch (c) {
            case L' ':      // SPACE
            case L'\u2000': // EN QUAD
            case L'\u2001': // EM QUAD
            case L'\u2002': // EN SPACE
            case L'\u2003': // EM SPACE
            case L'\u2004': // THREE-PER-EM-SPACE
            case L'\u2005': // FOUR-PER-EM-SPACE
            case L'\u2006': // SIX-PER-EM-SPACE
            case L'\u2007': // FIGURE SPACE
            case L'\u2008': // PUNCTUATION SPACE
            case L'\u2009': // THIN SPACE
            case L'\u200A': // HAIR SPACE
            case L'\u202F': // NARROW NO-BREAK SPACE
            case L'\u205F': // MEDIUM MATHEMATICAL SPACE
            case L'\u3000': // IDEOGRAPHIC SPACE
                return true;
            default:
                return false;
        }
    }

    constexpr bool isSeparator(const char_t c) noexcept
    {
        switch (c) {
            case L'-':      // HYPHEN-MINUS
            case L'\u00AD': // SOFT HYPHEN
            case L'\u2010': // HYPHEN
            case L'\u2E3A': // TWO-EM DASH
            case L'\u2E3B': // THREE-EM DASH
                return true;
            default:
                return isSpace(c);
        }
    }

    constexpr bool isPunctuationMark(const char_t c) noexcept
    {
        switch (c) {
            case L',':
            case L';':
            case L':':
            case L'?':
            case L'!':
            case L'\u203D': // INTERROBANG
            case L'(':
            case L')':
            case L'"':
            case L'\'':
            case L'`':
            case L'\u2018': // LEFT SINGLE QUOTATION MARK
            case L'\u2019': // RIGHT SINGLE QUOTATION MARK
            case L'\u201A': // SINGLE LOW-9 QUOTATION MARK
            case L'\u201B': // SINGLE HIGH-REVERSED-9 QUOTATION MARK
            case L'\u201C': // LEFT SINGLE QUOTATION MARK
            case L'\u201D': // RIGHT SINGLE QUOTATION MARK
            case L'\u201E': // DOUBLE LOW-9 QUOTATION MARK
            case L'\u201F': // DOUBLE HIGH-REVERSED-9 QUOTATION MARK
            case L'\u2039': // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
            case L'\u203A': // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
            case L'\u00AB': // DOUBLE LEFT-POINTING ANGLE QUOTATION MARK
            case L'\u00BB': // DOUBLE RIGHT-POINTING ANGLE QUOTATION MARK
                return true;
            default:
                return false;
        }
    }

    constexpr SeparatorType getSeparatorTypeOf(const char_t c) noexcept
    {
        if (std::iswupper(c)) {
            return SeparatorType::Capital;
        } else if (isPunctuationMark(c)) {
            return SeparatorType::Punctuation;
        } else if (isSpace(c)) {
            return SeparatorType::Space;
        } else {
            return bad_enum<SeparatorType>();
        }
    }
}

#endif // UFOLD_SEPARATORS_IPP