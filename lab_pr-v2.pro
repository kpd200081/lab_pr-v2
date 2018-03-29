TEMPLATE = app
CONFIG += console c++11 #-fno-stack-protector
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    rwworker.cpp \
    comclass.cpp \
    sha1.cpp \
    mbworker.cpp \
    train.cpp \
    com2class.cpp \
    car.cpp \
    passenger.cpp

HEADERS += \
    rwworker.h \
    comclass.h \
    sha1.h \
    mbworker.h \
    train.h \
    com2class.h \
    car.h \
    passenger.h
