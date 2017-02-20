/** @file helper_string.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 14.02.2016
 */


#ifndef LOGGER_HELPER_STRING_H
#define LOGGER_HELPER_STRING_H


#include <cwchar>
#include <cstring>
#include <exception>
#include <functional>

#include <logger/types.h>
#include <logger/string.h>


namespace logger { namespace helper_string
{


string make(const_chrs str);
string make(const_chrs str, std::size_t length);
string&& reserve(string&& str, std::size_t length);

string_list& add_back(string_list& list, string&& str);
string_list& add_back(string_list& list, const string& str);

string_list split(const string& str, chr separator);
string_list split(const_chrs str, chr separator);

string sub_str(const string& str, std::size_t off = 0, std::size_t count = static_cast<std::size_t>(-1));
std::size_t length(const string& str);

void print(std_ostream& ostream, string&& text);

string add_tabs_to_begin_lines(string&& str, std::size_t tab_length);

void append(std_string& std_str, const string& str);

std::size_t accumulate_hash(const string& str);


}} // namespace logger::helper_string


#if defined(LOGGER_QT_STRING)
namespace std
{

template<>
struct hash<logger::string>
{
    using argument_type = logger::string;
    using result_type = std::size_t;
    inline result_type operator()(argument_type const& str) const
    {
        return logger::helper_string::accumulate_hash(str);
    }
};


} // namespace std
#endif


#endif // LOGGER_HELPER_STRING_H
