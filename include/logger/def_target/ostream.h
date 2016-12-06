//******************************************************************************************************************************************
//******************************************************************************************************************************************
/** @file stream.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2014
 */
//******************************************************************************************************************************************


#ifndef LOGGER_DEF_TARGET_STREAM_H
#define LOGGER_DEF_TARGET_STREAM_H


#include <mutex>
#include <vector>
#include <ostream>

#include <logger/helper.h>
#include <logger/target.h>


namespace logger { namespace def_target
{


class LOGGER_EXPORT std::mutex;


/** @brief Базовый класс для точек приема логируемой информации. */
class LOGGER_EXPORT ostream : public logger::target
{
private:

    enum class state
    {
        idle = 0,
        working,
        stopped,
    };

public:

    ostream(std_ostream& ostream);
    virtual ~ostream();

public:

    /** @brief Получение имени узла логирования.
     * @details Используется в рамках системных сообщений при запуске/остановке точек логирования.
     * @return Имя узла логирования.
     */
    virtual const_chrs name() const override;

    /** @brief Запуск работы данного объекта по приему логируемой информации.
     * @details После отработки метода данный объект начнет получать сообщения.
     */
    virtual void start() override;

    /** @brief Остановка работы данного объекта по приему логируемой информации.
     * @details После отработки метода данный объект уже не будет получать сообщения.
     */
    virtual void stop() override;

    /** @brief Записать в лог системное сообщение.
     * @param message - сообщение.
     */
    virtual void system(string&& message) override;

    /** @brief
     * @param tab
     * @param full_key
     * @param level
     * @param message
     */
    virtual void message(unsigned char scope_level, logger::level log_level, const string& full_key, string&& message) override;

    /** @brief
     * @param tab
     * @param visit
     * @param funcName
     */
    virtual void function(unsigned char scope_level, logger::level log_level, logger::visit visit, const_chrs func_name) override;

protected:

    void append_head(std_string& str);

    void append_level(std_string& str, logger::level level) const;
    void append_level_system(std_string& str) const;

private:

    void print(std_string&& header, string&& message);

private:

    state m_state;
    std::size_t m_thread_id_str_max_lenght;
    std_ostream& m_ostream;
    std::mutex m_ostream_access;
};


class LOGGER_EXPORT smart_ostream_on_heap : public ostream
{
public:

    smart_ostream_on_heap(std_ostream& ostream);

    virtual void stop() override;

private:

    virtual ~smart_ostream_on_heap();
};


}} // namespace logger::def_target


#endif // LOGGER_DEF_TARGET_STREAM_H
