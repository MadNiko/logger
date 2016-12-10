
LOGGER_SRC_DIR = $${LOGGER_PROJECT_DIR}/src

INCLUDEPATH += $${LOGGER_SRC_DIR}


HEADERS +=  \
            $${LOGGER_SRC_DIR}/helper_string.h \
            $${LOGGER_SRC_DIR}/helper_data.h \
            \
            $${LOGGER_SRC_DIR}/node_data.h \


SOURCES +=  \
            $${LOGGER_SRC_DIR}/helper_string_qt.cpp \
            $${LOGGER_SRC_DIR}/helper_string_stl.cpp \
            $${LOGGER_SRC_DIR}/helper_data.cpp \
            \
            $${LOGGER_SRC_DIR}/node.cpp \
            $${LOGGER_SRC_DIR}/manager.cpp \
            $${LOGGER_SRC_DIR}/function_visiter.cpp \
            \
            $${LOGGER_SRC_DIR}/helper.cpp \
            $${LOGGER_SRC_DIR}/ostream.cpp \
