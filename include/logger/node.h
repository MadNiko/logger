/** @file node.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2016
 */


#ifndef LOGGER_NODE_H
#define LOGGER_NODE_H


#include <logger/types.h>


namespace logger
{


/** @brief Класс предоставляющий интерфейс записи сообщений в лог с учетом уровней логирования.*/
class LOGGER_EXPORT node
{

public:

    /** @brief Конструктор по умолчанию. */
    node() LOGGER_NOEXCEPT;

    /** @brief Конструктор.
     * @param data - внутренние данные логера.
     */
    explicit node(std::shared_ptr<node_data>&& data) LOGGER_NOEXCEPT;

    /** @brief Конструктор перемещения.
     * @param other - другой объект логера.
     */
    node(node&& other) LOGGER_NOEXCEPT;

    /** @brief Конструктор копирования.
     * @param other - другой объект логера.
     */
    node(const node& other) LOGGER_NOEXCEPT;

    /** @brief Деструктор. */
    ~node();

    /** @brief Оператор перемещения.
     * @param other - другой объект.
     * @return Объект логера.
     */
    node& operator=(node&& other);

    /** @brief Оператор копирования.
     * @param other - другой объект.
     * @return Объект логера.
     */
    node& operator=(const node& other);

    /** @brief Оператор привидения к типу @a bool.
     * @return Если объект логера валиден возвращается @a true, иначе @a false.
     */
    operator bool() const LOGGER_NOEXCEPT;

    /** @brief Проверить является ли объект валидным.
     * @return Если объект логера валиден возвращается @a true, иначе @a false.
     */
    bool is_valid() const LOGGER_NOEXCEPT;

    void swap(node& other) LOGGER_NOEXCEPT;

    /** @brief Получить ключ текущего узла логирования.
     * @return Ключ текущего узла логирования.
     */
    string key() const;

    /** @brief Получить полный ключ текущего узла логирования.
     * @return Полный ключ текущего узла логирования.
     */
    string full_key() const;

    /** @brief Получить узел логирования уровнем выше.
     * @return Узел логирования.
     */
    node upper_node() const LOGGER_NOEXCEPT;

    /** @brief Получить дочерний узел логирования по указанному пути.
     * @details Предпологается что строка имеет только латинские символы.
     * @param full_sub_key - путь к узлу, ключи в строке разделяются символом #key_separator.
     * @return Узел логирования.
     */
    node sub_node(string_list&& full_sub_key) const;
    node sub_node(const string& full_sub_key) const;
    node sub_node(const_chrs full_sub_key) const;

    /** @brief Получить "соседний" узел логирования.
     * @details Предпологается что строка имеет только латинские символы.
     * @param full_sibling_key - путь к узлу первый элемент которогго является соседним данному, ключи в строке разделяются символом #key_separator.
     * @return Узел логирования.
     */
    node sibling_node(string_list&& full_sibling_key) const;
    node sibling_node(const string& full_sibling_key) const;
    node sibling_node(const_chrs full_sibling_key) const;

public:

    /** @brief Записать в лог сообщение уровня Fatal.
     * @param message - сообщение.
     * @return Текущий узел логирования.
     */
    const node& fatal(const_chrs message) const;
    const node& fatal(string&& message) const;

    /** @brief Записать в лог сообщение уровня Critical.
     * @param message - сообщение.
     * @return Текущий узел логирования.
     */
    const node& critical(const_chrs message) const;
    const node& critical(string&& message) const;

    /** @brief Записать в лог сообщение уровня Warning.
     * @param message - сообщение.
     * @return Текущий узел логирования.
     */
    const node& warning(const_chrs message) const;
    const node& warning(string&& message) const;

    /** @brief Записать в лог сообщение уровня Info.
     * @param message - сообщение.
     * @return Текущий узел логирования.
     */
    const node& info(const_chrs message) const;
    const node& info(string&& message) const;

    /** @brief Записать в лог сообщение уровня Debug.
     * @param message - сообщение.
     * @return Текущий узел логирования.
     */
    const node& debug(const_chrs message) const;
    const node& debug(string&& message) const;

    const node& message(logger::level level, string&& message) const;
    const node& message(logger::level level, const_chrs message) const;

    /** @brief Записать в лог системное сообщение.
     * @details Данное сообщение будет записано в лог без учета текущего уровня логирования и состояния узла.
     * @param message - сообщение.
     * @return Текущий узел логирования.
     */
    const node& system(const_chrs message) const;
    const node& system(string&& message) const;

    /** @brief Проверить возможно ли выводить сообщения уровля Fatal.
     * @details Объект результата может быть преобразован к типу @a bool,
     *          значение которого будет говорить о возможности вывода сообщений.
     * @return Объект лога способный выводить только сообщения уровня Fatal.
     */
    level_node has_fatal() const;

    /** @brief Проверить возможно ли выводить сообщения уровля Critical.
     * @details Объект результата может быть преобразован к типу @a bool,
     *          значение которого будет говорить о возможности вывода сообщений.
     * @return Объект лога способный выводить только сообщения уровня Critical.
     */
    level_node has_critical() const;

    /** @brief Проверить возможно ли выводить сообщения уровля Warning.
     * @details Объект результата может быть преобразован к типу @a bool,
     *          значение которого будет говорить о возможности вывода сообщений.
     * @return Объект лога способный выводить только сообщения уровня Warning.
     */
    level_node has_warning() const;

    /** @brief Проверить возможно ли выводить сообщения уровля Info.
     * @details Объект результата может быть преобразован к типу @a bool,
     *          значение которого будет говорить о возможности вывода сообщений.
     * @return Объект лога способный выводить только сообщения уровня Info.
     */
    level_node has_info() const;

    /** @brief Проверить возможно ли выводить сообщения уровля Debug.
     * @details Объект результата может быть преобразован к типу @a bool,
     *          значение которого будет говорить о возможности вывода сообщений.
     * @return Объект лога способный выводить только сообщения уровня Debug.
     */
    level_node has_debug() const;

    /** @brief Получить объект записи в лог входа и выхода из функции.
     * @details Вход в функцию логируется при создании объекта, выход из функции будет залогирован при его разрушении.
     * @param funcName - имя функции.
     * @return Объект записи в лог входа и выхода из функции.
     */
    function_visiter visiter(const_chrs func_name) const;

private:

    const node_data* data_if_log_level(logger::level level) const;

protected:

    std::shared_ptr<node_data> m_data;
};


/** @brief Вспомогательный класс лога для оптимизации логирования в случае если формирование строки лога ресурсоемкое. */
class LOGGER_EXPORT LOGGER_ATTR_NODISCARD level_node
{
public:

    /** @brief Конструктор по умолчанию. */
    level_node();

    /** @brief Конструктор.
     * @param data - внутренние данные логера.
     * @param level - уровень логирования.
     */
    level_node(const node_data* data, logger::level level);
    level_node(level_node&& other);
    level_node(const level_node&) = delete;

    /** @brief Деструктор. */
    ~level_node() = default;

    level_node& operator=(level_node&& other);
    level_node& operator=(const level_node&) = delete;

public:

    /** @brief Оператор привидения к типу @a bool.
     * @return Если объект логера валиден возвращается @a true, иначе @a false.
     */
    operator bool() const;

    /** @brief Проверить является ли объект валидным.
     * @return Если объект логера валиден возвращается @a true, иначе @a false.
     */
    bool is_valid() const;

    void swap(level_node& other);

    /** @brief Записать в лог сообщение.
     * @note Метод не проверяет валидность узла логирования, вследствии чего вызов данного
     *      метода для не валидного узла логирования может привести к неопределенному приложения.
     * @param message - сообщение.
     * @return Объект лога.
     */
    const level_node& message(const_chrs message) const;
    const level_node& message(string&& message) const;

private:

    logger::level m_level;
    target* m_target;
    const string* m_full_key;
};


} // namespace logger


#endif // LOGGER_NODE_H
