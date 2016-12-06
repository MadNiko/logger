/** @file types.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2014
 */


#ifndef LOGGER_TYPES_H
#define LOGGER_TYPES_H


#include <memory>

#include <logger/defines.h>
#include <logger/string.h>


namespace logger
{


/** @brief Уровень логирования узла. */
enum class level : unsigned int
{
    off       = static_cast<unsigned int>(-1),  //!< Логирование отключено.
    fatal     = 0,                              //!< Дальнейшая работа приложения не возможна.
    critical  = level::fatal + 1,               //!< Дальнейшее выполнение текущей задачи в рамках приложения не возможно, но при этом работа приложения всё ещё может продолжаться (в зависимости от задачи).
    warning   = level::critical + 1,            //!< Не стандартная "ветка" выполнения приложения (отсутствие данных, не корректные данные, ошибка в работе с данными и т.п.).
    info      = level::warning + 1,             //!< Общая информация о ходе работы приложения.
    debug     = level::info + 1,                //!< Отладочная информация (возможны какие либо служебные данные).
    developer = level::debug + 1                //!< Отладочная информация с дополнительной информацией (логирование посещения функций, логирование "координат" места записи в лог).
};


enum class visit : unsigned int
{
    entry,
    entry_exception,
    exit,
    exit_exception
};


class node;
class target;
class level_node;
class smart_exception;
class function_visiter;

struct node_data;
struct root_node_data;


using std_string = std::basic_string<logger::chr>;
using std_ostream = std::basic_ostream<logger::chr, std::char_traits<logger::chr>>;
using std_ostringstream = std::basic_ostringstream<logger::chr, std::char_traits<logger::chr>, std::allocator<logger::chr>>;


template<class _Ty>
class LOGGER_EXPORT std::shared_ptr;


} // namespace logger


#endif // LOGGER_TYPES_H
