/** @file node.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2016
 */


#include <logger/node.h>
#include <logger/target.h>
#include <logger/constants.h>
#include <logger/function_visiter.h>

#include "node_data.h"
#include "helper_data.h"


namespace logger
{


namespace
{



}


node::node() LOGGER_NOEXCEPT
    : m_data(nullptr)
{ }

node::node(std::shared_ptr<node_data>&& data) LOGGER_NOEXCEPT
    : m_data(std::move(data))
{
    m_data->inc_ref();
}

node::node(node&& other) LOGGER_NOEXCEPT
    : m_data(nullptr)
{
    this->swap(other);
}

node::node(const node& other) LOGGER_NOEXCEPT
    : m_data(other.m_data)
{
    if (m_data)
        m_data->inc_ref();
}

node::~node()
{
    if (m_data && m_data->dec_ref() && m_data->children.empty())
    {
        helper_data::erase_data(m_data.get());
    }
}

node& node::operator=(node&& other)
{
    node(std::move(other)).swap(*this);
    return *this;
}

node& node::operator=(const node& other)
{
    node(other).swap(*this);
    return *this;
}

node::operator bool() const LOGGER_NOEXCEPT
{
    return (m_data != nullptr);
}

bool node::is_valid() const LOGGER_NOEXCEPT
{
    return static_cast<bool>(*this);
}

void node::swap(node& other) LOGGER_NOEXCEPT
{
    std::swap(m_data, other.m_data);
}

string node::key() const
{
    return m_data
        ? helper_data::node_key(m_data.get())
        : string();
}

string node::full_key() const
{
    return m_data
        ? m_data->full_key
        : string();
}

node node::upper_node() const LOGGER_NOEXCEPT
{
    return (m_data && m_data->parent != m_data->root)
        ? node(std::shared_ptr<node_data>(m_data, m_data->parent))
        : node();
}

node node::sub_node(string_list&& full_sub_key) const
{
    return m_data
        ? node(std::shared_ptr<node_data>(m_data, helper_data::sub_data(m_data.get(), std::move(full_sub_key))))
        : node();
}

node node::sub_node(const string& full_sub_key) const
{
    return this->sub_node(helper_string::split(full_sub_key, key_separator));
}

node node::sub_node(const_chrs full_sub_key) const
{
    return this->sub_node(helper_string::split(full_sub_key, key_separator));
}

node node::sibling_node(string_list&& full_sibling_key) const
{
    return m_data
        ? node(std::shared_ptr<node_data>(m_data, helper_data::sub_data(m_data->parent, std::move(full_sibling_key))))
        : node();
}

node node::sibling_node(const string& full_sibling_key) const
{
    return this->sibling_node(helper_string::split(full_sibling_key, key_separator));
}

node node::sibling_node(const_chrs full_sibling_key) const
{
    return this->sibling_node(helper_string::split(full_sibling_key, key_separator));
}

const node& node::fatal(const_chrs message) const
{
    return this->message(level::fatal, message);
}

const node& node::fatal(string&& message) const
{
    return this->message(level::fatal, std::move(message));
}

const node& node::critical(const_chrs message) const
{
    return this->message(level::critical, message);
}

const node& node::critical(string&& message) const
{
    return this->message(level::critical, std::move(message));
}

const node& node::warning(const_chrs message) const
{
    return this->message(level::warning, message);
}

const node& node::warning(string&& message) const
{
    return this->message(level::warning, std::move(message));
}

const node& node::info(const_chrs message) const
{
    return this->message(level::info, message);
}

const node& node::info(string&& message) const
{
    return this->message(level::info, std::move(message));
}

const node& node::debug(const_chrs message) const
{
    return this->message(level::debug, message);
}

const node& node::debug(string&& message) const
{
    return this->message(level::debug, std::move(message));
}

const node& node::message(logger::level level, string&& message) const
{
    if (const node_data* data = this->data_if_log_level(level))
        data->root->target->message(function_visiter::scope_level_this_thread(), level, data->full_key, std::move(message));
    return *this;
}

const node& node::message(logger::level level, const_chrs message) const
{
    if (const node_data* data = this->data_if_log_level(level))
        data->root->target->message(function_visiter::scope_level_this_thread(), level, data->full_key, helper_string::make(message));
    return *this;
}

const node& node::system(const_chrs message) const
{
    if (m_data)
        m_data->root->target->system(helper_string::make(message));
    return *this;
}

const node& node::system(string&& message) const
{
    if (m_data)
        m_data->root->target->system(std::move(message));
    return *this;
}

level_node node::has_fatal() const
{
    return level_node(this->data_if_log_level(level::fatal), level::fatal);
}

level_node node::has_critical() const
{
    return level_node(this->data_if_log_level(level::critical), level::critical);
}

level_node node::has_warning() const
{
    return level_node(this->data_if_log_level(level::warning), level::warning);
}

level_node node::has_info() const
{
    return level_node(this->data_if_log_level(level::info), level::info);
}

level_node node::has_debug() const
{
    return level_node(this->data_if_log_level(level::debug), level::debug);
}

function_visiter node::visiter(const_chrs func_name) const
{
    return function_visiter(m_data.get(), func_name);
}

const node_data* node::data_if_log_level(logger::level level) const
{
    return (m_data && level <= m_data->root->log_level)
        ? m_data.get()
        : nullptr;
}




level_node::level_node()
    : m_level(level::off)
    , m_target(nullptr)
    , m_full_key(nullptr)
{ }

level_node::level_node(const node_data* data, logger::level level)
    : m_level(level)
    , m_target(data->root->target)
    , m_full_key(&data->full_key)
{ }

level_node::level_node(level_node&& other)
    : level_node()
{
    this->swap(other);
}

level_node& level_node::operator=(level_node&& other)
{
    level_node(std::move(other)).swap(*this);
    return *this;
}

level_node::operator bool() const
{
    return (m_target != nullptr);
}

bool level_node::is_valid() const
{
    return static_cast<bool>(*this);
}

void level_node::swap(level_node& other)
{
    std::swap(m_level, other.m_level);
    std::swap(m_target, other.m_target);
    std::swap(m_full_key, other.m_full_key);
}

const level_node& level_node::message(const_chrs message) const
{
    return this->message(helper_string::make(message));
}

const level_node& level_node::message(string&& message) const
{
    m_target->message(function_visiter::scope_level_this_thread(), m_level, *m_full_key, std::move(message));
    return *this;
}


} // namespace logger
