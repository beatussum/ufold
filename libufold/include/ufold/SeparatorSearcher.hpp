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


#ifndef UFOLD_SEPARATOR_SEARCHER_HPP
#define UFOLD_SEPARATOR_SEARCHER_HPP

#include "ufold/Formats.hpp"
#include "ufold/Separators.hpp"

namespace ufold
{
    class LIBUFOLD_NO_EXPORT SeparatorSearcher final
    {
    public:
        enum FirstIterator : uint8_t { L, LC, RC, R };
    private:
        using size_t = string::size_type;
    private:
        Separators::const_iterator find_closest(const width_t key) const;

        template<class _InputIt>
        class find_mapped_type final
        {
        public:
            constexpr find_mapped_type( const _InputIt first
                                      , const _InputIt last
                                      ) noexcept
                : m_first_(first)
                , m_last_(last)
            {}

            _InputIt operator()(const SeparatorType type) const;
        private:
            const _InputIt m_first_;
            const _InputIt m_last_;
        };

        template<class _InputIt>
        _InputIt find_separator( const _InputIt first
                               , const _InputIt last
                               ) const;
    public:
        SeparatorSearcher( Separators&& sep
                         , const string& str
                         , const Formats format
                         )
            : m_sep_(std::move(sep))
            , m_size_(str.size())
            , m_format_(format)
        {}

        width_t operator()(const FirstIterator first);
    private:
        const Separators m_sep_;
        const size_t m_size_;
        const Formats m_format_;
    };
}

#include "ufold/SeparatorSearcher.ipp"
#endif // UFOLD_SEPARATOR_SEARCHER_HPP
