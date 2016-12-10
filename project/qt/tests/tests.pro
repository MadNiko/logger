
include($${PWD}/../library/logger_use.pri)


LOGGER_TESTS_DIR = $${PWD}/../../../tests


TEMPLATE = app

TARGET = $${LOGGER_TARGET_NAME}_tests

DESTDIR = $${LOGGER_BIN_DIR}

INCLUDEPATH += $${LOGGER_TESTS_DIR}

SOURCES += $${LOGGER_TESTS_DIR}/main.cpp
