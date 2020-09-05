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


#ifndef LIBUFOLD_SEPARATOR_FINDER_HPP
#define LIBUFOLD_SEPARATOR_FINDER_HPP

#include "libufold_export.hpp"

#include "ufold/Formats.hpp"
#include "ufold/types.hpp"

#include <map>

namespace ufold
{
    class LIBUFOLD_NO_EXPORT SeparatorFinder final
    {
    public:
        using separator_type_t = int8_t;

        enum class SeparatorType : separator_type_t {
            Capital,
            Punctuation,
            Space
        };

        using Separators = std::map<width_t, SeparatorType>;

        using underlying_type = Separators::const_iterator;
        using string_index_t = Separators::key_type;
    private:
        underlying_type find_closest(const width_t key) const;

        underlying_type fraction( const width_t n
                                , const width_t d
                                ) const;

        underlying_type rfraction( const width_t n
                                 , const width_t d
                                 ) const;

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
        static constexpr bool isSpace(const char_t) noexcept;
        static constexpr bool isSeparator(const char_t) noexcept;
        static constexpr bool isPunctuationMark(const char_t) noexcept;
        static constexpr SeparatorType getSeparatorTypeOf(const char_t) noexcept;
    public:
        SeparatorFinder(const string& str, const Formats format);

        bool isValid() const { return !m_sep_.empty(); }

        string_index_t next();
    private:
        width_t m_size_;
        Formats m_format_;
        formats_t m_i_;
        Separators m_sep_;
    };
}

#include "ufold/SeparatorFinder.ipp"
#endif // LIBUFOLD_SEPARATOR_FINDER_HPP
