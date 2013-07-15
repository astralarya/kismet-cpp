// Project.h
// Mara Kim
//
// Globals to be included with Options.h


#ifndef PROJECT_H
#define PROJECT_H

#include "Mode.h"

// Typed modes
enum bool_mode{INTERACTIVE,REACTIVE,PERSONALITY};
template <>
struct Type<bool_mode> {
    typedef bool T;
};

enum int_mode{DEFAULT_DIE};
template <>
struct Type<int_mode> {
    typedef int T;
};

enum string_mode{DEFAULT_LABEL,FULL_REPORT};
template <>
struct Type<string_mode> {
    typedef std::string T;
};

#endif


#ifdef PROJECT_STATICS
/// Static Declarations ///

// Mode Signitures
template <>
typename TypeInfo<bool_mode>::key_type TypeInfo<bool_mode>::keys {{INTERACTIVE, "INTERACTIVE"},{REACTIVE,"REACTIVE"},{PERSONALITY,"PERSONALITY"}};
template <>
typename TypeInfo<bool_mode>::defaults_type TypeInfo<bool_mode>::defaults {{INTERACTIVE,{true}},{REACTIVE,{false}},{PERSONALITY,{true}}};
template <>
typename TypeInfo<bool_mode>::init_type TypeInfo<bool_mode>::init = false;

template <>
typename TypeInfo<int_mode>::key_type TypeInfo<int_mode>::keys {{DEFAULT_DIE, "DEFAULT_DIE"}};
template <>
typename TypeInfo<int_mode>::defaults_type TypeInfo<int_mode>::defaults {{DEFAULT_DIE,{20}}};
template <>
typename TypeInfo<int_mode>::init_type TypeInfo<int_mode>::init = 0;

template <>
typename TypeInfo<string_mode>::key_type TypeInfo<string_mode>::keys {{DEFAULT_LABEL, "DEFAULT_LABEL"}};
template <>
typename TypeInfo<string_mode>::defaults_type TypeInfo<string_mode>::defaults {};
template <>
typename TypeInfo<string_mode>::init_type TypeInfo<string_mode>::init = "";

#endif
