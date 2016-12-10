/** @file node_manager.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 14.02.2016
 */


#include <cassert>

#include <logger/constants.h>

#include "node_data.h"
#include "helper_data.h"
#include "helper_string.h"


namespace logger { namespace helper_data
{


namespace
{


void verify_keys(const string_list& sub_keys)
{
    for (const string& key : sub_keys)
    {
        (void)key; // TODO
    }
}

node_data* sub_data(node_data* parent_data, string_list_iterator& it_key, const string_list_iterator& it_key_end)
{
    const std::pair<children_map::iterator, bool> pair(
        parent_data->children.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(std::move(*it_key)),
            std::forward_as_tuple(parent_data)));

    node_data* const child_data(&pair.first->second);

    if (pair.second)
    {
        const string& key_ref(pair.first->first);
        if (child_data->parent == child_data->root)
            child_data->full_key = key_ref;
        else
            child_data->full_key = (child_data->parent->full_key + key_separator + key_ref);
    }

    std::advance(it_key, +1);
    return (it_key == it_key_end) ? child_data : sub_data(child_data, it_key, it_key_end);
}


} // namespace anonymous


string node_key(const node_data* data)
{
    return (data->parent == data->root)
        ? data->full_key
        : helper_string::sub_str(data->full_key, helper_string::length(data->parent->full_key) + 1);
}

node_data* sub_data(node_data* data, string_list&& sub_keys)
{
#if defined(LOGGER_DEBUG)
    verify_keys(sub_keys);
#endif // defined(LOGGER_DEBUG)

    return sub_data(data, std::begin(sub_keys), std::end(sub_keys));
}

void erase_data(node_data* data)
{
    assert(data);
    assert(data->parent);
    assert(data->expired_ref());
    assert(data->children.empty());

    do
    {
        const string key(node_key(data));

        node_data* const parent_data(data->parent);

        assert(&parent_data->children.at(key) == data);

        parent_data->children.erase(key);

        data = parent_data;
    }
    while (data->expired_ref() && data->children.empty());
}


}} // namespace logger::helper_data

