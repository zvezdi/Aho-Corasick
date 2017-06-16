TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c11

SOURCES += main.c \
    state.c \
    dfsm.c \
    trie.c \
    queue.c

DISTFILES +=

HEADERS += \
    state.h \
    dfsm.h \
    trie.h \
    queue.h
