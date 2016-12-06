
include($${PWD}/config_logger.pri)

TEMPLATE = lib

TARGET = $${LOGGER_TARGET_NAME}

CONFIG += dll shared
#CONFIG += staticlib

DEFINES += LOGGER_BUILD
DEFINES += LOGGER_CHAR__WIDE_CHAR
CONFIG(staticlib): DEFINES += LOGGER_LIB_STATIC

CONFIG -= qt

include($${PWD}/include/include.pri)
include($${PWD}/src/src.pri)


OTHER_FILES += use_logger.pri

DLLDESTDIR = $${PWD}/bin
DESTDIR = $${PWD}/lib



