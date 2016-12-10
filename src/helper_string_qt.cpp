//******************************************************************************************************************************************
//******************************************************************************************************************************************
/** @file helper_string_qt.cpp
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 17.11.2016
 */
//******************************************************************************************************************************************


#include <logger/defines.h>
#if defined(LOGGER_QT_STRING)


#include <limits>

#include <QRegularExpression>

#include <logger/helper.h>

#include "helper_string.h"


namespace logger { namespace helper_string
{


#if defined(LOGGER_CHAR__CHAR)


QString make(const_chrs str)
{
    return QString::fromUtf8(str);
}

QString make(const_chrs str, int length)
{
    return QString::fromUtf8(str, length);
}

QStringList split(const_chrs str, chr separator)
{
    return split(QString::fromUtf8(str), separator);
}

void print(std_ostream& ostream, QString&& text)
{
    ostream << text.toUtf8().data();
}

void append(std_string& std_str, const QString& str)
{
    std_str += str.toUtf8().data();
}


#elif defined(LOGGER_CHAR__WIDE_CHAR)


QString make(const_chrs str)
{
    return QString::fromWCharArray(str);
}

QString make(const_chrs str, int length)
{
    return QString::fromWCharArray(str, length);
}

QStringList split(const_chrs str, chr separator)
{
    return split(QString::fromWCharArray(str), separator);
}

void print(std_ostream& ostream, QString&& text)
{
    ostream << text.toStdWString();
}

void append(std_string& std_str, const QString& str)
{
    std_str += str.toStdWString();
}


#endif


QString&& reserve(QString&& str, std::size_t length)
{
    (void)length;
    return std::move(str);
}

QStringList& add_back(QStringList& list, QString&& str)
{
    list.push_back(str);
    return list;
}

QStringList& add_back(QStringList& list, const QString& str)
{
    list.push_back(str);
    return list;
}

QStringList split(const QString& str, chr separator)
{
    return str.split(QChar::fromLatin1(separator), QString::KeepEmptyParts);
}

QString sub_str(const QString& str, std::size_t off, std::size_t count)
{
    const int position((static_cast<int>(off) >= 0) ? static_cast<int>(off) : str.length());
    const int n((count == static_cast<std::size_t>(-1)) ? -1 : ((static_cast<int>(off) >= 0) ? static_cast<int>(off) : -1));
    return str.mid(position, n);
}

std::size_t length(const QString& str)
{
    return static_cast<std::size_t>(str.length());
}

QString add_tabs_to_begin_lines(QString&& str, std::size_t tab_length)
{
    const QChar SP(QChar::fromLatin1(' '));
    const QChar CR(QChar::fromLatin1('\r'));
    const QChar LF(QChar::fromLatin1('\n'));
    const QChar EN(QChar::fromLatin1('\0'));
    const QString SP_STR(tab_length, SP);

    int pos(0);
    while ((pos = str.indexOf(LF, pos)) != -1)
    {
        pos += 1;
        if (str[pos] == CR) pos += 1;
        if (str[pos] == EN) break;

        str.insert(pos, SP_STR);
        pos += tab_length;
    }

    return std::move(str);
}

std::size_t accumulate_hash(const string& str)
{
    return static_cast<std::size_t>(qHash(str));
}


}} // namespace logger::helper_string


#endif // defined(LOGGER_QT_STRING)
