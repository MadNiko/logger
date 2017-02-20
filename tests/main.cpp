

#include <iostream>

#include <logger/node.h>
#include <logger/manager.h>
#include <logger/function_visiter.h>
#include <logger/def_target/ostream.h>


#if defined(LOGGER_CHAR__CHAR)
#	define std_out std::cout
#elif defined(LOGGER_CHAR__WIDE_CHAR)
#	define std_out std::wcout
#endif

#define _STR(text) LOGGER_STR(text)


int main()
{
    logger::node log_main;

    {
		logger::manager logger_manager(new logger::def_target::smart_ostream_on_heap(std_out));

		log_main = logger_manager.make_node(_STR("main"));

        logger_manager.running_app();

		logger_manager.system(_STR("Hello, world!"));

		log_main.info(_STR("This message not enabled!"));

        logger_manager.set_log_level(logger::level::developer);

        {
			const logger::function_visiter visiter(log_main.visiter(_STR(__FUNCTION__)));

			logger_manager.make_node(_STR("main")).info(_STR("Work test application..."));
        }

        logger_manager.quit_app();
    }

	log_main.sub_node(_STR("not_manager")).fatal(_STR("exit to appication"));

    return 0;
}





