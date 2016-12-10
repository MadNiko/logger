
TEMPLATE = subdirs

SUBDIRS += library

!CONFIG(no_tests) {
    SUBDIRS += tests
    tests.depends = library
}


CONFIG -= qt

#DEFINES += LOGGER_CHAR__WIDE_CHAR
