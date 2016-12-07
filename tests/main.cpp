

#include <iostream>

#include <logger/node.h>
#include <logger/manager.h>
#include <logger/def_target/ostream.h>


int main()
{
    logger::manager logger_manager(new logger::def_target::smart_ostream_on_heap(std::cout));

    logger_manager.running_app();

    logger_manager.system("Hello, world!");

    logger_manager.make_node("main").info("This message not enabled!");

    logger_manager.set_log_level(logger::level::debug);

    logger_manager.make_node("main").info("Work test application...");

    logger_manager.quit_app();

    return 0;
}





