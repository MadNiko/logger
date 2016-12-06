/** @file node.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2016
 */


#ifndef LOGGER_FUNCTION_VISITER_H
#define LOGGER_FUNCTION_VISITER_H


#include <logger/types.h>


namespace logger
{


class target;
struct node_data;


/** @brief Класс предоставляющий интерфейс записи сообщений в лог с учетом уровней логирования.*/
class LOGGER_EXPORT function_visiter
{

public:

    static unsigned char scope_level_this_thread();

public:

    /** @brief Конструктор.
     * @param data - внутренние данные логера.
     */
    function_visiter(node_data* data, const_chrs func_name);

    /** @brief Конструктор перемещения.
     * @param other - другой объект логера.
     */
    function_visiter(function_visiter&& other) LOGGER_NOEXCEPT;

    function_visiter(const function_visiter& other) = delete;

    /** @brief Деструктор. */
    ~function_visiter();

    function_visiter& operator=(function_visiter&& other) = delete;
    function_visiter& operator=(const function_visiter& other) = delete;

protected:

    const_chrs m_func_name;
    level m_visit_level;
    target* m_target;
    bool m_except;
};


} // namespace logger


#endif // LOGGER_FUNCTION_VISITER_H
