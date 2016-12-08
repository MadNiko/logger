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

    template<class _Number, class = std::enable_if_t<std::is_integral<_Number>::value>>
    inline static std::string num_to_dec(_Number number, std::size_t min_width)
    {
        if (min_width > 32) min_width = 32;
        char buffer[33] = {'\0'};
        std::sprintf(buffer, "%.*d", min_width, number);
        return std::string(buffer);
    }

    template<class _Number, class = std::enable_if_t<std::is_unsigned<_Number>::value>>
    inline static std::string num_to_hex(_Number number)
    {
        char buffer[2*sizeof(_Number)+1] = {'\0'};
        std::sprintf(buffer, "%.*X", sizeof(buffer)-1, number);
        return std::string(buffer);
    }
};
template<> struct chart<wchar_t>
{
    inline static const wchar_t* find(const wchar_t* str, wchar_t ch) { return std::wcschr(str, ch); }
    inline static std::size_t length_str(const wchar_t* str) { return std::wcslen(str); }

    template<class _Number, class = std::enable_if_t<std::is_integral<_Number>::value>>
    inline static std::wstring num_to_dec(_Number number, std::size_t min_width)
    {
        if (min_width > 32) min_width = 32;
        wchar_t buffer[33] = {L'\0'};
        std::swprintf(buffer, L"%.*d", min_width, number);
        return std::wstring(buffer);
    }

    template<class _Number, class = std::enable_if_t<std::is_unsigned<_Number>::value>>
    inline static std::wstring num_to_hex(_Number number)
    {
        logger::chr buffer[2*sizeof(_Number)+1] = {L'\0'};
        std::swprintf(buffer, sizeof(buffer), L"%.*X", sizeof(buffer)-1, number);
        return std::wstring(buffer);
    }
};


const_chrs level_to_string(logger::level level, std::size_t* length = nullptr);


}} // namespace logger::helper


#endif // LOGGER_HELPER_H
