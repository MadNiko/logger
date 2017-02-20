//******************************************************************************************************************************************
//******************************************************************************************************************************************
/** @file manager.cpp
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 21.04.2014
 */
//******************************************************************************************************************************************


#include <exception>

#include <logger/manager.h>
#include <logger/constants.h>
#include <logger/function_visiter.h>

#include "helper_string.h"
#include "helper_data.h"
#include "node_data.h"


namespace logger
{


const chr key_separator(LOGGER_CHAR('.'));


manager::manager() LOGGER_NOEXCEPT
    : m_root_node_data()
{}

manager::manager(logger::target* target)
    : m_root_node_data(target ? std::make_shared<root_node_data>(target) : std::shared_ptr<root_node_data>())
{}

manager::manager(manager&& other) LOGGER_NOEXCEPT
    : m_root_node_data(nullptr)
{
    this->swap(other);
}

manager::~manager()
{}

manager& manager::operator=(manager&& other)
{
    manager(std::move(other)).swap(*this);
    return *this;
}

manager::operator bool() const LOGGER_NOEXCEPT
{
    return static_cast<bool>(m_root_node_data);
}

void manager::swap(manager& other) LOGGER_NOEXCEPT
{
    m_root_node_data.swap(other.m_root_node_data);
}

void manager::set_log_level(logger::level level) LOGGER_NOEXCEPT
{
    if (m_root_node_data)
        m_root_node_data->log_level = level;
}

logger::level manager::log_level() const LOGGER_NOEXCEPT
{
    return m_root_node_data
        ? m_root_node_data->log_level
        : logger::level::off;
}

void manager::set_visit_level(logger::level level) LOGGER_NOEXCEPT
{
    if (m_root_node_data)
        m_root_node_data->visit_level = level;
}

logger::level manager::visit_level() const LOGGER_NOEXCEPT
{
    return m_root_node_data
        ? m_root_node_data->visit_level
        : logger::level::off;
}

void manager::running_app(string&& append_message)
{
    if (m_root_node_data)
        m_root_node_data->target->system(string(helper_string::make(LOGGER_STR("Running")) + std::move(append_message)));
}

void manager::running_app(const_chrs append_message)
{
	this->running_app(helper_string::make(append_message ? append_message : LOGGER_STR("")));
}

void manager::quit_app(string&& append_message)
{
    if (m_root_node_data)
        m_root_node_data->target->system(string(helper_string::make(LOGGER_STR("Quit")) + std::move(append_message)));
}

void manager::quit_app(const_chrs append_message)
{
	this->quit_app(helper_string::make(append_message ? append_message : LOGGER_STR("")));
}

//void manager::quit_app_to_exception(const smart_exception& exception, string&& append_message)
//{
//    if (m_root_node_data)
//        m_root_node_data->target->system(helper_string::make(LOGGER_STR("Quit to exception")) + std::move(append_message));
//}
//
//void manager::quit_app_to_exception(const smart_exception& exception, const_chrs append_message)
//{
//    this->quit_app_to_exception(exception, helper_string::make(append_message ? append_message : LOGGER_STR("")));
//}

node manager::make_node(string_list&& full_key)
{
    return m_root_node_data
        ? node(std::shared_ptr<node_data>(m_root_node_data, helper_data::sub_data(m_root_node_data.get(), std::move(full_key))))
        : node();
}

node manager::make_node(const string& full_key)
{
    return m_root_node_data
        ? node(std::shared_ptr<node_data>(m_root_node_data, helper_data::sub_data(m_root_node_data.get(),helper_string::split(full_key, key_separator))))
        : node();
}

node manager::make_node(const_chrs full_key)
{
    return m_root_node_data
        ? node(std::shared_ptr<node_data>(m_root_node_data, helper_data::sub_data(m_root_node_data.get(), helper_string::split(full_key, key_separator))))
        : node();
}

void manager::system(string&& message)
{
    if (m_root_node_data)
        m_root_node_data->target->system(std::move(message));
}

void manager::system(const_chrs message)
{
    if (m_root_node_data)
        m_root_node_data->target->system(helper_string::make(message));
}

function_visiter manager::visiter(const_chrs func_name)
{
    return function_visiter(m_root_node_data.get(), func_name);
}


} // namespace logger

