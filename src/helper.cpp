/** @file node_manager.h
 * @brief .
 *
 * @author Ю. Николаев
 *
 * @date 14.02.2016
 */


#include <logger/helper.h>

#include "helper_string.h"


namespace logger { namespace helper
{


const_chrs level_to_string(logger::level level, std::size_t* length)
{
    switch (level)
    {
    case level::off:       if (length) *length = 3; return LOGGER_STR("off");
    case level::fatal:     if (length) *length = 5; return LOGGER_STR("fatal");
    case level::critical:  if (length) *length = 7; return LOGGER_STR("criticl");
    case level::warning:   if (length) *length = 7; return LOGGER_STR("warning");
    case level::info:      if (length) *length = 4; return LOGGER_STR("info");
    case level::debug:     if (length) *length = 5; return LOGGER_STR("debug");
    case level::developer: if (length) *length = 7; return LOGGER_STR("develop");
    default:               if (length) *length = 7; return LOGGER_STR("unknown");
    }
}


/*

    --->
      --->we
          wwer
          --->


[16.12.03] [02:02:15] [000000] [system ] [network.input.request] new [id: 123]
[16.12.03] [02:02:15] [000000] [off    ] [network.input.request.123] wait data...
[16.12.03] [02:02:15] [000000] [fatal  ]
[16.12.03] [02:02:15] [000000] [criticl]
[16.12.03] [02:02:15] [000000] [warning]
[16.12.03] [02:02:15] [000000] [info   ]
[16.12.03] [02:02:15] [000000] [debug  ]
[16.12.03] [02:02:15] [000000] [develop]
[16.12.03] [02:02:15] [000000] [unknown]
[16.12.03] [02:02:15] [] []

 */


}} // namespace logger::helper
