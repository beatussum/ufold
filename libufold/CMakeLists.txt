# Copyright (C) 2020 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
#
# This program is free software:  you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published  by
# the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
#
# This program is distributed in the hope that it will be  useful,
# but WITHOUT ANY WARRANTY;   without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program. If not, see <https://www.gnu.org/licenses/>.

set(LIBUFOLD_HPP)
set(LIBUFOLD_CPP)

if(WITH_DOCS)
    set(DOCS_DIR "${CMAKE_BINARY_DIR}/docs" CACHE PATH
        "The path where the documention is built")

    find_package(Doxygen REQUIRED)

    set(DOXYGEN_OUTPUT_DIRECTORY ${DOCS_DIR})
    set(DOXYGEN_INLINE_INHERITED_MEMB YES)
    set(DOXYGEN_HIDE_UNDOC_CLASSES YES)
    set(DOXYGEN_HIDE_IN_BODY_DOCS YES)
    set(DOXYGEN_WARN_NO_PARAMDOC YES)
    set(DOXYGEN_WARN_LOGFILE "${DOCS_DIR}/log")

    doxygen_add_docs(docs
                     ${LIBUFOLD_HPP}
                     ALL
                     COMMENT "Generating documentation…")
endif()
