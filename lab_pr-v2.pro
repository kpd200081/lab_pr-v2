TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    rwworker.cpp \
    comclass.cpp \
    sha1.cpp \
    aes.cpp \
    encrypt.cpp

HEADERS += \
    rwworker.h \
    comclass.h \
    sha1.h \
    aes.h \
    encrypt.h
