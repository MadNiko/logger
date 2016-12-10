
include($${PWD}/logger_config.pri)

TEMPLATE = lib

TARGET = $${LOGGER_TARGET_NAME}

CONFIG += dll shared

DEFINES += LOGGER_BUILD
CONFIG(logger_lib_static) CONFIG += staticlib
CONFIG(staticlib): DEFINES += LOGGER_LIB_STATIC


include($${PWD}/logger_include.pri)
include($${PWD}/logger_src.pri)


DLLDESTDIR = $${LOGGER_BIN_DIR}
DESTDIR = $${LOGGER_LIB_DIR}


OTHER_FILES += $${PWD}/logger_use.pri
