TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    oneDimensional.cpp \
    twodimensional.cpp

HEADERS += \
    exprtk.hpp \
    oneDimensional.h \
    twodimensional.h
