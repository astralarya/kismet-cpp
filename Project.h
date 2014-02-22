// Project.h
//
// Copyright (C) 2013 Mara Kim
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/.


/** \file Project.h
 *  Globals defining option types
 */

#ifndef PROJECT_H
#define PROJECT_H

#include "Type.h"

/** Project enums */
namespace Project {
    enum bool_mode{INTERACTIVE,REACTIVE,PERSONALITY};
    enum int_mode{DEFAULT_DIE,SHORT_REPORT_CUTOFF};
    enum string_mode{DEFAULT_LABEL,FULL_REPORT};
}

// Typed modes
template <>
struct Type<Project::string_mode> {
    typedef std::string T;
};

template <>
struct Type<Project::int_mode> {
    typedef int T;
};

template <>
struct Type<Project::bool_mode> {
    typedef bool T;
};

template<>
struct Type<char> {
    typedef bool T;
};

// Overrides
template <>
bool TypeInfo<Project::string_mode>::assign(std::string& var, const std::string& str);

#endif


#ifdef PROJECT_STATICS
/// Static Declarations ///

using namespace Project;

// Mode Signitures
template <>
typename TypeInfo<bool_mode>::key_type TypeInfo<bool_mode>::keys {{INTERACTIVE, "INTERACTIVE"},{REACTIVE,"REACTIVE"},{PERSONALITY,"PERSONALITY"}};
template <>
typename TypeInfo<bool_mode>::defaults_type TypeInfo<bool_mode>::defaults {{INTERACTIVE,{true}},{REACTIVE,{false}},{PERSONALITY,{true}}};
template <>
typename TypeInfo<bool_mode>::init_type TypeInfo<bool_mode>::init = false;

template <>
typename TypeInfo<int_mode>::key_type TypeInfo<int_mode>::keys {{DEFAULT_DIE, "DEFAULT_DIE"},{SHORT_REPORT_CUTOFF,"SHORT_REPORT_CUTOFF"}};
template <>
typename TypeInfo<int_mode>::defaults_type TypeInfo<int_mode>::defaults {{DEFAULT_DIE,{20}},{SHORT_REPORT_CUTOFF,{256}}};
template <>
typename TypeInfo<int_mode>::init_type TypeInfo<int_mode>::init = 0;

template <>
typename TypeInfo<string_mode>::key_type TypeInfo<string_mode>::keys {{DEFAULT_LABEL, "DEFAULT_LABEL"}};
template <>
typename TypeInfo<string_mode>::defaults_type TypeInfo<string_mode>::defaults {};
template <>
typename TypeInfo<string_mode>::init_type TypeInfo<string_mode>::init = "";
template <>
bool TypeInfo<string_mode>::assign(std::string& var, const std::string& str) { var = str; return var==str; }

#endif

