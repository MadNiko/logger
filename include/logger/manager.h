/** @file manager.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2014
 */


#ifndef LOGGER_MANAGER_H
#define LOGGER_MANAGER_H


#include <logger/types.h>


namespace logger
{


/** @brief Класс управления логированием. */
class LOGGER_EXPORT manager
{
public:

    manager() LOGGER_NOEXCEPT;
    explicit manager(logger::target* target);

    manager(manager&& other) LOGGER_NOEXCEPT;
    ~manager();

    manager& operator=(manager&& other);

    manager(const manager& other) = delete;
    manager& operator=(const manager& other) = delete;

    operator bool() const LOGGER_NOEXCEPT;

    void swap(manager& other) LOGGER_NOEXCEPT;

public:

    void set_log_level(logger::level log_level) LOGGER_NOEXCEPT;
    logger::level log_level() const LOGGER_NOEXCEPT;

    void set_visit_level(logger::level log_level) LOGGER_NOEXCEPT;
    logger::level visit_level() const LOGGER_NOEXCEPT;

public:

    /** @brief Поместить в лог запись о запуске приложения.
     * @param append_message - текст который будет добавлен в конец сообщения.
     */
    void running_app(string&& append_message);
    void running_app(const_chrs append_message = nullptr);

    /** @brief Поместить в лог запись о завершении работы приложения.
     * @param append_message - текст который будет добавлен в конец сообщения.
     */
    void quit_app(string&& append_message);
    void quit_app(const_chrs append_message = nullptr);

    /** @brief Поместить в лог запись о завершении работы приложения.
     * @param error - исключение приведшее к завершению работы приложения.
     * @param append_message - текст который будет добавлен в конец сообщения, но перед описанием исключения.
     */
    //void quit_app_to_exception(const smart_exception& excetion, string&& append_message);
    //void quit_app_to_exception(const smart_exception& excetion, const_chrs append_message = nullptr);

public:

    /** @brief Получить узел логирования по указанному пути.
     * @details Предпологается что строка имеет только латинские символы.
     * @param fullKey - путь к узлу, ключи в строке разделяются символом #KeySeparator.
     * @return Логер.
     */
    node make_node(string_list&& full_key);
    node make_node(const string& full_key);
    node make_node(const_chrs full_key);

    /** @brief Записать в лог системное сообщение.
     * @details Данное сообщение будет записано в лог без учета текущего
     *          уровня логирования и состояния того или иного узла.
     * @param message - сообщение.
     */
    void system(string&& message);
    void system(const_chrs message);

    /** @brief Получить объект записи в лог входа и выхода из функции.
     * @details Вход в функцию логируется при создании объекта, выход из функции будет залогирован при его разрушении.
     * @param funcName - имя функции.
     * @return Объект записи в лог входа и выхода из функции.
     */
    function_visiter visiter(const_chrs func_name);

private:

    std::shared_ptr<root_node_data> m_root_node_data;
};


} // namespace logger


#endif // LOGGER_MANAGER_H
