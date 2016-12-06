/** @file node.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2016
 */


#include <logger/target.h>
#include <logger/function_visiter.h>

#include "node_data.h"


#if defined(LOGGER_CC_MSVC) && LOGGER_CC_MSVC < 1900
#   define LOGGER_THREAD_LOCAL __declspec(thread)
#else
#   define LOGGER_THREAD_LOCAL thread_local
#endif


namespace logger
{


LOGGER_THREAD_LOCAL unsigned char th_loc_scope_level(0);


unsigned char function_visiter::scope_level_this_thread()
{
    return th_loc_scope_level;
}


function_visiter::function_visiter(node_data* data, const_chrs func_name)
    : m_func_name(func_name)
    , m_visit_level(data ? data->root->visit_level : level::off)
    , m_target((data && m_visit_level <= data->root->log_level) ? data->root->target : nullptr)
    , m_except(m_target ? std::uncaught_exception() : false)
{
    if (m_target)
        m_target->function(th_loc_scope_level++, m_visit_level, (m_except ? visit::entry_exception : visit::entry), m_func_name);
}

function_visiter::function_visiter(function_visiter&& other) LOGGER_NOEXCEPT
    : m_func_name(nullptr)
    , m_visit_level(level::off)
    , m_target(nullptr)
    , m_except(false)
{
    std::swap(m_func_name, other.m_func_name);
    std::swap(m_visit_level, other.m_visit_level);
    std::swap(m_target, other.m_target);
    std::swap(m_except, other.m_except);
}

function_visiter::~function_visiter()
{
    if (m_target)
        m_target->function(--th_loc_scope_level, m_visit_level, (m_except ? visit::exit_exception : visit::exit), m_func_name);
}


} // namespace logger
