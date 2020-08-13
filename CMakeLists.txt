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


cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0048 NEW)

project(ufold
        VERSION 0.9.0
        DESCRIPTION "The GNU coreutils fold program doped"
        HOMEPAGE_URL "https://github.com/beatussum/ufold/"
        LANGUAGES CXX)

option(WITH_DOC "Build the documentation" OFF)

unset(CMAKE_CXX_FLAGS_RELEASE CACHE)
macro(add_gcc_cxx_flags _flags)
    if(CMAKE_COMPILER_IS_GNUCXX)
         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_flags}")
    endif()
endmacro()

# Use ccache if it is installed
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif()

set(EXPORT_DIR "${CMAKE_BINARY_DIR}/exports" CACHE PATH
    "The path where the export header is generated")

if (WITH_DOC)
    set(DOC_DIR "${CMAKE_BINARY_DIR}/doc" CACHE PATH
        "The path where the documentation is built")

    find_package(Doxygen REQUIRED)

    set(DOXYGEN_OUTPUT_DIRECTORY "${DOC_DIR}")
    set(DOXYGEN_INLINE_INHERITED_MEMB YES)
    set(DOXYGEN_ALIASES "pexample=@par Example")
    set(DOXYGEN_HIDE_UNDOC_CLASSES YES)
    set(DOXYGEN_HIDE_IN_BODY_DOCS YES)
    set(DOXYGEN_WARN_NO_PARAMDOC YES)
    set(DOXYGEN_WARN_LOGFILE "${DOC_DIR}/log")
endif()

macro(add_to_doc _headers)
    if (WITH_DOC)
        doxygen_add_docs(doc
                         "${_headers}"
                         COMMENT "Generating documentation…")
    endif()
endmacro()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

add_gcc_cxx_flags(-fno-gnu-keywords -fno-operator-names)
add_gcc_cxx_flags(-funsigned-char -pipe -fmessage-length=75)
add_gcc_cxx_flags(-Wnoexcept -Wold-style-cast -Woverloaded-virtual)
add_gcc_cxx_flags(-Wall -Wpedantic)
add_gcc_cxx_flags(-Wdouble-promotion -Wimplicit-fallthrough=5 -Wignored-qualifiers)
add_gcc_cxx_flags(-Wmissing-include-dirs -Wuninitialized -Wsuggest-override)
add_gcc_cxx_flags(-Wsuggest-attribute=pure -Wsuggest-attribute=const)
add_gcc_cxx_flags(-Wsuggest-attribute=noreturn -Wsuggest-final-types)
add_gcc_cxx_flags(-Wsuggest-final-types -Wsuggest-final-methods)
add_gcc_cxx_flags(-Wsuggest-override -Wduplicated-branches)
add_gcc_cxx_flags(-Wduplicated-cond -Wno-div-by-zero -Wfloat-equal)
add_gcc_cxx_flags(-Wundef -Wconversion -Wmissing-field-initializers)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_gcc_cxx_flags(-O0)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_gcc_cxx_flags(-O2)
    add_gcc_cxx_flags(-Werror -Wfatal-errors)
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/lib${CMAKE_PROJECT_NAME}")
