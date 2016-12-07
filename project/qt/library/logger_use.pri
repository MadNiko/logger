

include($${PWD}/logger_config.pri)


CONFIG(logger_lib_static): DEFINES += LOGGER_LIB_STATIC

QMAKE_LIBDIR += $${LOGGER_LIB_DIR}

LIBS += -l$${LOGGER_TARGET_NAME}


include($${PWD}/logger_include.pri)

