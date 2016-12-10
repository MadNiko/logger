
LOGGER_INCLUDE_DIR = $${LOGGER_PROJECT_DIR}/include

INCLUDEPATH += $${LOGGER_INCLUDE_DIR}


HEADERS +=  $${LOGGER_INCLUDE_DIR}/*.h \
            \
            $${LOGGER_INCLUDE_DIR}/logger/*.h \
            \
            $${LOGGER_INCLUDE_DIR}/logger/def_target/*.h
