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


#ifndef UFOLD_SEPARATOR_SEARCHER_IPP
#define UFOLD_SEPARATOR_SEARCHER_IPP

namespace ufold
{
    template<class _InputIt>
    _InputIt SeparatorSearcher::find_mapped_type<_InputIt>::operator()(const SeparatorType type) const
    {
        return std::find_if(std::execution::par_unseq, m_first_, m_last_,
            [=] (const Separators::value_type& val) {
                return val.second == type;
            }
        );
    }

    template<class _InputIt>
    _InputIt SeparatorSearcher::operator()(const _InputIt first, _InputIt last)
    {
        switch (countAlignments(m_format_)) {
            case 2:
                if (m_format_ & Formats::FillFromCenter) {
                    last = first + fraction(1, 4);
                } else {
                    last = first + fraction(1, 2);
                }

                break;

            case 3:
                last = first + fraction(1, 4);
                break;
        }

        find_mapped_type<_InputIt> functor(first, last);
        _InputIt out = last;

        if (m_format_ & Formats::PreferPunctuation)
            out = functor(SeparatorType::Punctuation);

        if ((out == last) and (m_format_ & Formats::PreferCapital))
            out = functor(SeparatorType::Capital);

        if (out == last)
            out = functor(SeparatorType::Space);

        return out;
    }
}

#endif // UFOLD_SEPARATOR_SEARCHER_IPP
