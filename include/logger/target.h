//******************************************************************************************************************************************
//******************************************************************************************************************************************
/** @file target.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2014
 */
//******************************************************************************************************************************************


#ifndef LOGGER_TARGET_H
#define LOGGER_TARGET_H


#include <logger/types.h>


namespace logger
{


/** @brief Базовый класс для точек приема логируемой информации. */
class LOGGER_EXPORT target
{
public:

    target(target&& other) = delete;
    target(const target& other) = delete;
    target&operator=(target&& other) = delete;
    target&operator=(const target& other) = delete;

public:

    /** @brief Получение имени узла логирования.
     * @details Используется в рамках системных сообщений при запуске/остановке точек логирования.
     * @return Имя узла логирования.
     */
    virtual const_chrs name() const = 0;

    /** @brief Запуск работы данного объекта по приему логируемой информации.
     * @details После отработки метода данный объект начнет получать сообщения.
     */
    virtual void start() = 0;

    /** @brief Остановка работы данного объекта по приему логируемой информации.
     * @details После отработки метода данный объект уже не будет получать сообщения.
     */
    virtual void stop() = 0;

    /** @brief Записать в лог системное сообщение.
     * @param message - сообщение.
     */
    virtual void system(string&& message) = 0;

    /** @brief
     * @param tab
     * @param full_key
     * @param level
     * @param message
     */
    virtual void message(unsigned char scope_level, logger::level log_level, const string& full_key, string&& message) = 0;

    /** @brief
     * @param tab
     * @param visit
     * @param funcName
     */
    virtual void function(unsigned char scope_level, logger::level log_level, logger::visit visit, const_chrs func_name) = 0;

protected:

    target() = default;
    virtual ~target() = default;
};


} // namespace Logger


#endif // LOGGER_TARGET_H
