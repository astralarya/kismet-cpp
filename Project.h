// Project.h
// Mara Kim
//
// Globals to be included with Options.h


#ifndef PROJECT_H
#define PROJECT_H

#include "Mode.h"

// Typed modes
enum bool_mode{VERBOSE};
template <>
struct Type<bool_mode> {
    typedef bool T;
};

enum int_mode{DEFAULT_DIE};
template <>
struct Type<int_mode> {
    typedef int T;
};

#endif


#ifdef PROJECT_STATICS
/// Static Declarations ///

// Mode Signitures
template <>
typename TypeInfo<bool_mode>::key_type TypeInfo<bool_mode>::keys ({{VERBOSE, "VERBOSE"}});
template <>
typename TypeInfo<bool_mode>::defaults_type TypeInfo<bool_mode>::defaults {};
template <>
typename TypeInfo<bool_mode>::init_type TypeInfo<bool_mode>::init = false;

template <>
typename TypeInfo<int_mode>::key_type TypeInfo<int_mode>::keys ({{DEFAULT_DIE, "DEFAULT_DIE"}});
template <>
typename TypeInfo<int_mode>::defaults_type TypeInfo<int_mode>::defaults {{DEFAULT_DIE,{20}}};
template <>
typename TypeInfo<int_mode>::init_type TypeInfo<int_mode>::init = 0;

#endif
