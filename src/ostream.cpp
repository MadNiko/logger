//******************************************************************************************************************************************
//******************************************************************************************************************************************
/** @file stream.cpp
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2014
 */
//******************************************************************************************************************************************


#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <iostream>

#include <logger/helper.h>
#include <logger/def_target/ostream.h>

#include "helper_string.h"


namespace logger { namespace def_target
{


namespace
{


const const_chrs level_system_str(LOGGER_STR("system"));
const std::size_t level_system_str_length(helper::chart<logger::chr>::length_str(level_system_str));
const std::size_t level_str_max_length([]
{
    std::size_t max_length(level_system_str_length);

    for (logger::level level :
    {
         logger::level::off,
         logger::level::fatal,
         logger::level::critical,
         logger::level::warning,
         logger::level::info,
         logger::level::debug,
         logger::level::developer
    })
    {
        std::size_t length(0);
        helper::level_to_string(level, &length);
        if (length > max_length) max_length = length;
    }

    return max_length;
}());


} // namespace anonymous


ostream::ostream(std_ostream& ostream)
    : m_state(state::idle)
    , m_thread_id_str_max_lenght(6)
    , m_ostream(ostream)
{ }

ostream::~ostream()
{
    switch (m_state)
    {
    case state::working:
        this->system(string(
            helper_string::make(LOGGER_STR("Premature removal of the point of logging ")) +
            helper_string::make(this->name()) +
            helper_string::make(LOGGER_STR(", further logging leads to errors."))));
        m_ostream << std::flush;
    break;
    case state::idle:
    case state::stopped:
        // Ok
    break;
    }
}

const_chrs ostream::name() const
{
#if defined(LOGGER_CHAR__CHAR)
    if (&m_ostream == &std::cout)
        return "std::out";
    if (&m_ostream == &std::cerr)
        return "std::err";
    return "std::ostream";
#else // defined(LOGGER_CHAR__WIDE_CHAR)
    if (&m_ostream == &std::wcout)
        return L"std::wout";
    if (&m_ostream == &std::wcerr)
        return L"std::werr";
    return L"std::wostream";
#endif
}

void ostream::start()
{
    const std::lock_guard<std::mutex> lk_ostream(m_ostream_access);

    if (m_state != state::idle)
        return;

    m_state = state::working;
}

void ostream::stop()
{
    const std::lock_guard<std::mutex> lk_ostream(m_ostream_access);

    if (m_state != state::working)
        return;

    m_state = state::stopped;
    m_ostream << std::flush;
}

void ostream::system(string&& message)
{
    std_string header;
    header.reserve(50);

    this->append_head(header);
    this->append_level_system(header);

    const std::size_t header_length(header.length());

    this->print(std::move(header), helper_string::add_tabs_to_begin_lines(std::move(message), header_length));
}

void ostream::message(unsigned char scope_level, logger::level log_level, const string& full_key, string&& message)
{
    const std::size_t visit_str_length(4);
    const std::size_t spaces_length(scope_level * visit_str_length);

    std_string header;
    header.reserve(50 + spaces_length + full_key.length());

    this->append_head(header);
    this->append_level(header, log_level);

    header.append(spaces_length, LOGGER_CHAR(' '));
    header += LOGGER_CHAR('[');
    helper_string::append(header, full_key);
    header += LOGGER_CHAR("] ");

    const std::size_t header_length(header.length());

    this->print(std::move(header), helper_string::add_tabs_to_begin_lines(std::move(message), header_length));
}

void ostream::function(unsigned char scope_level, logger::level log_level, logger::visit visit, const_chrs func_name)
{
    const std::size_t visit_str_length(4);
    const std::size_t spaces_length(scope_level * visit_str_length);

    std_string header;
    header.reserve(50 + spaces_length + helper::chart<logger::chr>::length_str(func_name));

    this->append_head(header);
    this->append_level(header, log_level);

    header.append(spaces_length, LOGGER_CHAR(' '));

    switch (visit)
    {
    case logger::visit::entry:           header += LOGGER_STR("--->"); break;
    case logger::visit::entry_exception: header += LOGGER_STR("exc>"); break;
    case logger::visit::exit:            header += LOGGER_STR("<---"); break;
    case logger::visit::exit_exception:  header += LOGGER_STR("<exc"); break;
    }

    header += func_name;

    this->print(std::move(header), string());
}

void ostream::append_head(std_string& str)
{
    const std::time_t t(std::time(nullptr));
    const std::tm tm(*std::localtime(&t));

    std_string thread_id_str(helper::chart<logger::chr>::number_to_string(std::this_thread::get_id().hash()));
    const std::size_t thread_id_str_length(thread_id_str.length());

    std::size_t tmp_lenght(0);
    do tmp_lenght = m_thread_id_str_max_lenght;
    while (tmp_lenght != m_thread_id_str_max_lenght);

    if (thread_id_str_length <= tmp_lenght)
        tmp_lenght -= thread_id_str_length;
    else
    {
        tmp_lenght = 0;
        m_thread_id_str_max_lenght = thread_id_str_length;
    }

    str += LOGGER_CHAR('[');
    str += helper::chart<logger::chr>::number_to_string(tm.tm_year % 100);
    str += LOGGER_CHAR('.');
    str += helper::chart<logger::chr>::number_to_string(tm.tm_mon + 1);
    str += LOGGER_CHAR('.');
    str += helper::chart<logger::chr>::number_to_string(tm.tm_mday);
    str += LOGGER_STR("] [");
    str += helper::chart<logger::chr>::number_to_string(tm.tm_hour);
    str += LOGGER_CHAR(':');
    str += helper::chart<logger::chr>::number_to_string(tm.tm_min);
    str += LOGGER_CHAR(':');
    str += helper::chart<logger::chr>::number_to_string(tm.tm_sec % 60);
    str += LOGGER_STR("] [");
    if (tmp_lenght > 0) str.append(tmp_lenght, LOGGER_CHAR('0'));
    str += std::move(thread_id_str);
    str += LOGGER_STR("] ");
}

void ostream::append_level(std_string& str, logger::level level) const
{
    std::size_t level_str_length(0);
    const_chrs level_str(helper::level_to_string(level, &level_str_length));

    str += LOGGER_CHAR('[');
    str += level_str;
    if (level_str_length < level_str_max_length)
        str.append((level_str_max_length - level_str_length), LOGGER_CHAR(' '));
    str += LOGGER_STR("] ");
}

void ostream::append_level_system(std_string& str) const
{
    str += LOGGER_CHAR('[');
    str += level_system_str;
    if (level_system_str_length < level_str_max_length)
        str.append((level_str_max_length - level_system_str_length), LOGGER_CHAR(' '));

    str += LOGGER_STR("] ");
}

void ostream::print(std_string&& header, string&& message)
{
    const std::lock_guard<std::mutex> lk_ostream(m_ostream_access);
    if (m_state != state::working)
        return;

    m_ostream << std::move(header);
    helper_string::print(m_ostream, std::move(message));
    m_ostream << std::endl;
}

smart_ostream_on_heap::smart_ostream_on_heap(std_ostream& ostream)
    : ostream(ostream)
{ }

smart_ostream_on_heap::~smart_ostream_on_heap()
{ }

void smart_ostream_on_heap::stop()
{
    ostream::stop();
    delete this;
}


}} // namespace logger::def_target
