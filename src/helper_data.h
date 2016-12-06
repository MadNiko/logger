/** @file node_manager.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 14.02.2016
 */


#ifndef LOGGER_NODE_MANAGER_H
#define LOGGER_NODE_MANAGER_H


#include <logger/defines.h>

#include "helper_string.h"
#include "node_data.h"


namespace logger { namespace helper_data
{

string node_key(const node_data* data);

node_data* sub_data(node_data* data, string_list&& sub_keys);

void erase_data(node_data* data);


}} // namespace helper_data


#endif // LOGGER_NODE_MANAGER_H
