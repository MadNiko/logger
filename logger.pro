
include($${PWD}/config_logger.pri)

TEMPLATE = lib

TARGET = $${LOGGER_TARGET_NAME}

#CONFIG += dll shared

DEFINES += LOGGER_BUILD

QT -= gui


include($${PWD}/include/include.pri)
include($${PWD}/src/src.pri)


OTHER_FILES += use_logger.pri


