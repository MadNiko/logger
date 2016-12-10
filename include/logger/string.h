/** @file string.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 10.02.2016
 */


#ifndef LOGGER_STRING_H
#define LOGGER_STRING_H


#include <logger/defines.h>

#if defined(LOGGER_QT_STRING)
#   include <QtCore/QString>
#   include <QtCore/QStringList>
#elif defined(LOGGER_STL_STRING)
#   include <list>
#   include <string>
#endif


namespace logger
{


#if defined(LOGGER_CHAR__CHAR)
    using  chr = char;
#elif defined(LOGGER_CHAR__WIDE_CHAR)
    using chr = wchar_t;
#endif

using chrs = chr*;
using const_chrs = const chr*;

#if defined(LOGGER_QT_STRING)
    using string = QString;
    using string_list = QStringList;
    using string_list_iterator = QStringList::iterator;
#elif defined(LOGGER_STL_STRING)
#   if defined(LOGGER_CHAR__CHAR)
        using string = std::string;
#   elif defined(LOGGER_CHAR__WIDE_CHAR)
        using string = std::wstring;
#   endif
    using string_list = std::list<logger::string>;
    using string_list_iterator = std::list<logger::string>::iterator;
#endif


} // namespace logger


#endif // LOGGER_STRING_H
