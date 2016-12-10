/** @file defines.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2014
 */


#ifndef LOGGER_DEFINES_H
#define LOGGER_DEFINES_H


// Платформа сборки
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#   define LOGGER_OS_WIN
#elif defined(__linux) || defined(__linux__)
#   define LOGGER_OS_LINUX
#else
#   error("Undefined OS for using logger module")
#endif


// Компилятор сборки
#if defined(_MSC_VER)
#   define LOGGER_CC_MSVC _MSC_VER
#elif defined(__MINGW32__)
#   define LOGGER_CC_MINGW __MINGW32__
#elif defined(__GNUC__)
#   define LOGGER_CC_GNU
#elif defined(__clang__)
#   define LOGGER_CC_CLANG __clang__
#else
#   error("Undefined Compiller for using logger module")
#endif


#define LOGGER_DEBUG


// With C++17: [[nodiscard]]
#ifndef LOGGER_NODISCARD
#   ifdef LOGGER_CC_GNU
#       define LOGGER_ATTR_NODISCARD __attribute__ ((__warn_unused_result__))
#   else
#       define LOGGER_ATTR_NODISCARD
#   endif
#endif


// Определяем способ сборки/использования библиотеки
#ifndef LOGGER_EXPORT
#   ifdef LOGGER_OS_WIN
#       ifndef LOGGER_LIB_STATIC
#           ifdef LOGGER_BUILD
#               define LOGGER_EXPORT __declspec(dllexport)
#           else
#               define LOGGER_EXPORT __declspec(dllimport)
#           endif
#       else
#           define LOGGER_EXPORT
#       endif
#   else
#       define LOGGER_EXPORT
#   endif
#endif

//#pragma warning(disable:4005)

#if defined(LOGGER_CC_MSVC) && LOGGER_CC_MSVC < 1900
#   define LOGGER_NOEXCEPT
#else
#   define LOGGER_NOEXCEPT noexcept
#endif // defined(LOGGER_CC_MSVC) && LOGGER_CC_MSVC < 1900


// Определяем для внешнего интерфейса тип строки: QT или STL
#if !defined(LOGGER_QT_STRING) && !defined(LOGGER_STL_STRING)
#   ifdef QT_CORE_LIB
#       define LOGGER_QT_STRING
#   else
#       define LOGGER_STL_STRING
#   endif
#elif defined(LOGGER_QT_STRING) && defined(LOGGER_STL_STRING)
#   error("The conflict in the definition library for strings. Set one the define: LOGGER_QT_STRING, LOGGER_STL_STRING")
#endif // !defined(LOGGER_QT_STRING) && !defined(LOGGER_STL_STRING)


//
#if !defined(LOGGER_CHAR__WIDE_CHAR) && !defined(LOGGER_CHAR__CHAR)
#   define LOGGER_CHAR__CHAR
#elif defined(LOGGER_CHAR__WIDE_CHAR) && defined(LOGGER_CHAR__CHAR)
#   error("The conflict in the definition library for strings. Set one the define: LOGGER_CHAR__WIDE_CHAR, LOGGER_CHAR__CHAR")
#endif // !defined(LOGGER_QT_STRING) && !defined(LOGGER_STL_STRING)


//
#if defined(LOGGER_CHAR__CHAR)
#   define LOGGER_STR(text) (text)
#   define LOGGER_CHAR(ch)  (ch)
#else // defined(LOGGER_CHAR__WIDE_CHAR)
#   define LOGGER_STR(text) (L##text)
#   define LOGGER_CHAR(ch)  (L##ch)
#endif



#endif // LOGGER_DEFINES_H
