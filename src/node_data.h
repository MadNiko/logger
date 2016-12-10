/** @file node.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 20.04.2016
 */


#ifndef LOGGER_NODE_DATA_H
#define LOGGER_NODE_DATA_H


#include <memory>
#include <unordered_map>

#include <logger/node.h>
#include <logger/target.h>

#include "helper_string.h"


namespace logger
{


using children_map = std::unordered_map<string, node_data>;

struct node_data;
struct root_node_data;


struct node_data
{
    explicit node_data(node_data* parent) LOGGER_NOEXCEPT;
    node_data(node_data* parent, root_node_data* root) LOGGER_NOEXCEPT;

    string full_key;
    node_data* const parent;
    root_node_data* const root;
    children_map children;

public:

    void inc_ref() LOGGER_NOEXCEPT;
    bool dec_ref() LOGGER_NOEXCEPT;
    bool expired_ref() const LOGGER_NOEXCEPT;

private:

    unsigned int m_ref;
};


struct root_node_data : public node_data
{
    root_node_data(logger::target* target);
    ~root_node_data();

    logger::level log_level;
    logger::level visit_level;

    logger::target* target;
};


inline node_data::node_data(node_data* parent) LOGGER_NOEXCEPT
    : node_data(parent, parent->root)
{}

inline node_data::node_data(node_data* parent, root_node_data* root) LOGGER_NOEXCEPT
    : full_key()
    , parent(parent)
    , root(root)
    , children()
    , m_ref(0)
{}

inline void node_data::inc_ref() LOGGER_NOEXCEPT
{
    m_ref += 1;
}

inline bool node_data::dec_ref() LOGGER_NOEXCEPT
{
    m_ref -= 1;
    return this->expired_ref();
}

inline bool node_data::expired_ref() const LOGGER_NOEXCEPT
{
    return (0 == m_ref);
}




inline root_node_data::root_node_data(logger::target* target)
    : node_data(nullptr, this)
    , log_level(logger::level::warning)
    , visit_level(logger::level::developer)
    , target(target)
{
    this->inc_ref();
    this->target->start();
}

inline root_node_data::~root_node_data()
{
    this->target->stop();
}


} // namespace logger


#endif // LOGGER_NODE_DATA_H
