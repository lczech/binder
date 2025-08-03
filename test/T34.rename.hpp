// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// Copyright (c) 2025 Lucas Czech <luc.czech@gmail.com>
//
// All rights reserved. Use of this source code is governed by a
// MIT license that can be found in the LICENSE file.

#pragma once

#include <cstdint>
#include <string>

// The main purpose of the renaming config tokens is to clean up cases
// where the automatic name mangling does not result in intuitituve names.
// However, for testing purposes, we here use this functionality also
// for other renamings, to see if it generally works as intended.

// -------------------------------------------------------------------------------------------------
//   Basics
// -------------------------------------------------------------------------------------------------

// Simple base cases for testing the renaming, for testing.
// Not really recommended for real applications,
// as it will confuse users more than helping them.

// Case where we want to rename all overloads.
void my_weird_cpp_func( int ) {};
void my_weird_cpp_func( std::string ) {};

// Case where we only want to rename one overload
void my_other_cpp_func( int ) {};
void my_other_cpp_func( std::string ) {};

// Rename a class.
struct MyCppStruct
{
    void some_func() const
    {}
};

// Rename a function member.
struct MySecondStruct
{
    void my_cpp_func() const
    {}
};

// Rename a class and functions within it.
struct MyOtherCppStruct
{
    // Case where we want to rename all overloads.
    void some_weird_cpp_func( int ) {};
    void some_weird_cpp_func( std::string ) {};

    // Case where we only want to rename one overload
    void some_other_cpp_func( int ) {};
    void some_other_cpp_func( std::string ) {};
};

// -------------------------------------------------------------------------------------------------
//   Template Selection
// -------------------------------------------------------------------------------------------------

// Instantiations of function templates by default are working fine,
// as they just end up as overloads of the function name.
// However, there is an interesting edge case where the template types
// are not part of the parameters. In that case, the overloads are
// indistinguishable from each other in Python, as they all have the
// same name. Calling the function will just result in the first overlad (?)
// being called. Hence, allowing to rename them enables to bind them all
// in a distinguishable way in Python.

template<typename T>
T tagged_function()
{
    return T{};
}

template int         tagged_function<int>();
template std::string tagged_function<std::string>();

// For completeness, test the case where we just rename both as well.

template<typename T>
T tagged_cpp_function()
{
    return T{};
}

template int         tagged_cpp_function<int>();
template std::string tagged_cpp_function<std::string>();

// -------------------------------------------------------------------------------------------------
//   Template Parameters
// -------------------------------------------------------------------------------------------------

// LLVM resolves types to some "default" type which is not always wanted,
// and can lead to name discrepancies between C++ and Python.

template<typename I>
class NumericalClass
{};

// These instances are using clear aliases in C++, but get renamed
// to unclear names in Python that do not correspond to their original.
// uint8_t  --> unsigned char  --> NumericalClass_unsigned_char_t
// uint16_t --> unsigned short --> NumericalClass_unsigned_short_t
// uint32_t --> unsigned int   --> NumericalClass_unsigned_int_t
// uint64_t --> unsigned long  --> NumericalClass_unsigned_long_t
// Let's rename them so that the names are the same again.
template class NumericalClass<uint8_t>;
template class NumericalClass<uint16_t>;
template class NumericalClass<uint32_t>;
template class NumericalClass<uint64_t>;

// Furthermore, in previous versions of Binder, template argument lists
// in class names were resolved with no space after the comma, which made
// their usage in config directives inconsistent with other lists.
// Here, we hence test how this behaves now with respect to the config.
template<typename A, typename B, typename C>
class ComplicatedClass
{};

template class ComplicatedClass<int, int, int>;

// Same with functions.

template<typename A, typename B, typename C>
void complicated_func(A, B, C)
{}

template void complicated_func<int, int, int>(int, int, int);

// -------------------------------------------------------------------------------------------------
//   Namespace Resolution
// -------------------------------------------------------------------------------------------------

// This is where the renaming for classes might be most relevant,
// as LLVM seems to resolve template arguments fully including their namespace,
// which leads to naming discrepancies between C++ and Python.

namespace foo {
namespace bar {

struct Tag
{};

template<typename T>
class TaggedClass
{
    T tag;

public:

    T get_tag() const
    {
        return tag;
    }

    // Also test renaming within class templates
    void another_cpp_func() const
    {}
};

// Instantiate the class for Tag.
// This yields a cumbersome name without renaming: `TaggedClass_foo_bar_Tag_t`,
// where the namespace of the template argument gets mangled into the name.
template class TaggedClass<Tag>;

}
}
