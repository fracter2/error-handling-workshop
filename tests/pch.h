#pragma once
#include <codeanalysis\warnings.h> //ALL_CODE_ANALYSIS_WARNINGS

//Kill the static analyzer for the Google Test include.
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include <gtest/gtest.h>
#pragma warning(pop)

/*
 * The macros below are intended solely for silencing warnings triggered by the
 * Google Test framework itself, not your own test code.
 *
 * Your test code should adhere to best practices and maintain clean, warning-free
 * code wherever possible. By keeping warnings enabled, you can ensure better code
 * hygiene and avoid suppressing meaningful feedback from the compiler or static analyzer.
 *
 * Tips for addressing common warnings:
 *
 *   - "Prefer to use at() instead of unchecked subscript":
 *     Instead of adding bounds-checking branches (e.g., if index < size()), refactor to
 *     use range-based for-loops or algorithms. This makes your code safe by construction
 *     and eliminates unnecessary branches.
 *
 *   - "Avoid pointer arithmetic; use span instead":
 *     While std::span is a great choice in some cases, often what you really want are
 *     utilities like std::next or std::prev. For example, replace expressions like
 *     "begin() + count" with "std::next(begin(), count)" for better clarity and safety.
 */

//Wrap your test code in these macros, as needed
#define DISABLE_WARNINGS_FROM_GTEST \
    __pragma(warning(push)) \
    /* C26446: Prefer to use gsl::at() instead of unchecked subscript operator (bounds.4). */ \
    __pragma(warning(disable : 26446)) \
    /* C26455: Default constructor is not declared as noexcept */ \
    __pragma(warning(disable : 26455)) \
    /* C26426: Global initializer calls a non-constexpr function */ \
    __pragma(warning(disable : 26426)) \
    /* C26409: Avoid calling new and delete explicitly, use smart pointers */ \
    __pragma(warning(disable : 26409)) \
    /* C26477: Use 'override' instead of base class member name */ \
    __pragma(warning(disable : 26477)) \
    /* C26433: Function can be marked as noexcept */ \
    __pragma(warning(disable : 26433)) \
    /* C26818: Prefer std::vector over C array */ \
    __pragma(warning(disable : 26818)) \
    /* C26440: Function can be declared 'const' */ \
    __pragma(warning(disable : 26440))

#define RESTORE_WARNINGS __pragma(warning(pop))