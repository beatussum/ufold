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

project("lib${CMAKE_PROJECT_NAME}"
        VERSION 0.9.0
        LANGUAGES CXX)

set(LIBUFOLD_HPP)
set(LIBUFOLD_CPP)

add_library("${PROJECT_NAME}" SHARED
            "${LIBUFOLD_HPP}" "${LIBUFOLD_CPP}")

include(GenerateExportHeader)
generate_export_header("${PROJECT_NAME}"
                       EXPORT_FILE_NAME "${EXPORT_DIR}/${PROJECT_NAME}.hpp")

target_include_directories("${PROJECT_NAME}"
                           PUBLIC "${EXPORT_DIR}")

doxygen_add_docs(docs
                 ${LIBUFOLD_HPP}
                 COMMENT "Generating documentation…")
