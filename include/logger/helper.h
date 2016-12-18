/** @file node_manager.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 14.02.2016
 */


#ifndef LOGGER_HELPER_H
#define LOGGER_HELPER_H


#include <string>
#include <cstdio>
#include <cwchar>
#include <cstring>
#include <cstdarg>
#include <type_traits>

#include <logger/types.h>


namespace logger { namespace helper
{


template<class _Char> struct chart {};
template<> struct chart<char>
{
    inline static const char* find(const char* str, char ch) { return std::strchr(str, ch); }
    inline static std::size_t length_str(const char* str) { return std::strlen(str); }
    inline static char* copy_n(char* dest, const char* src, std::size_t count){ return std::strncpy(dest, src, count); }
};
template<> struct chart<wchar_t>
{
    inline static const wchar_t* find(const wchar_t* str, wchar_t ch) { return std::wcschr(str, ch); }
    inline static std::size_t length_str(const wchar_t* str) { return std::wcslen(str); }
    inline static wchar_t* copy_n(wchar_t* dest, const wchar_t* src, std::size_t count){ return std::wcsncpy(dest, src, count); }
};


const_chrs level_to_string(logger::level level, std::size_t* length = nullptr);


}} // namespace logger::helper


#endif // LOGGER_HELPER_H
