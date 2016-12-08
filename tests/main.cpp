

#include <iostream>

#include <logger/node.h>
#include <logger/manager.h>
#include <logger/function_visiter.h>
#include <logger/def_target/ostream.h>


int main()
{
    logger::node log_main;

    {
        logger::manager logger_manager(new logger::def_target::smart_ostream_on_heap(std::cout));

        log_main = logger_manager.make_node("main");

        logger_manager.running_app();

        logger_manager.system("Hello, world!");

        log_main.info("This message not enabled!");

        logger_manager.set_log_level(logger::level::developer);

        {
            const logger::function_visiter visiter(log_main.visiter(__FUNCTION__));

            logger_manager.make_node("main").info("Work test application...");
        }

        logger_manager.quit_app();
    }

    log_main.sub_node("not_manager").fatal("exit to appication");

    return 0;
}





