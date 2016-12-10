//******************************************************************************************************************************************
//******************************************************************************************************************************************
/** @file helper_string_stl.cpp
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 17.11.2016
 */
//******************************************************************************************************************************************


#include <logger/defines.h>
#if defined(LOGGER_STL_STRING)


#include <logger/helper.h>

#include "helper_string.h"


namespace logger { namespace helper_string
{


string make(const_chrs str)
{
    return string(str);
}

string make(const_chrs str, std::size_t length)
{
    return string(str, length);
}

string&& reserve(string&& str, std::size_t length)
{
    str.reserve(length);
    return std::move(str);
}

string_list& add_back(string_list& list, string&& str)
{
    list.emplace_back(std::move(str));
    return list;
}

string_list& add_back(string_list& list, const string& str)
{
    list.push_back(str);
    return list;
}

string_list split(const string& str, chr separator)
{
    return split(str.c_str(), separator);
}

string_list split(const_chrs str, chr separator)
{
    string_list result;

    if (str != nullptr && (*str) != LOGGER_CHAR('\0'))
    {
        if (separator == LOGGER_CHAR('\0'))
        {
            result.emplace_back(str);
        }
        else
        {
            const_chrs pos_begin(str);
            const_chrs pos_end(str);

            while ((pos_end = helper::chart<logger::chr>::find(pos_begin, separator)) != nullptr)
            {
                result.emplace_back(pos_begin, (pos_end - pos_begin));

                pos_begin = pos_end + 1;
            }

            result.emplace_back(pos_begin);
        }
    }

    return result;
}

string sub_str(const string& str, std::size_t off, std::size_t count)
{
    return str.substr(off, (count == static_cast<std::size_t>(-1) ? string::npos : count));
}

std::size_t length(const string& str)
{
    return str.length();
}

void print(std_ostream& ostream, string&& text)
{
    ostream << std::move(text);
}

string add_tabs_to_begin_lines(string&& str, std::size_t tab_length)
{
    const char SP(' ');
    const char CR('\r');
    const char LF('\n');
    const char EN('\0');

    string::size_type pos(0);
    while ((pos = str.find(LF, pos)) != string::npos)
    {
        pos += 1;
        if (str[pos] == CR) pos += 1;
        if (str[pos] == EN) break;

        str.insert(pos, tab_length, SP);
        pos += tab_length;
    }

    return std::move(str);
}

void append(std_string& std_str, const std_string& str)
{
    std_str += str;
}

std::size_t accumulate_hash(const string& str)
{
    return std::hash<string>()(str);
}


}} // namespace logger::helper_string


#endif // defined(LOGGER_STL_STRING)
