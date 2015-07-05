#-------------------------------------------------
#
# Project created by QtCreator 2015-04-13T18:44:49
#
#-------------------------------------------------

QT                  += core

QT                  -= gui

TARGET              = SECD
CONFIG              += console
CONFIG              -= app_bundle
QMAKE_CXXFLAGS      += -std=c++11
#QMAKE_LFLAGS    += -static


TEMPLATE            = app


SOURCES             += main.cpp \
                    parser.cpp \
                    machine.cpp \
                    integer.cpp \
                    bool.cpp \
                    list.cpp \
                    instruction.cpp \
                    nil.cpp \
                    elem.cpp \
                    closure.cpp \
                    stack_t.cpp

HEADERS             += \
                    parser.h \
                    machine.h \
                    elem.h \
                    exception.h \
                    integer.h \
                    bool.h \
                    nil.h \
                    list.h \
                    instruction.h \
                    closure.h \
    stack_t.h

DISTFILES += \
    Source/log.sced \
    Source/fib.sced \
    Source/factor.sced \
    Source/log.sced \
    Source/template_recurtion.secd \
    Source/test.secd
