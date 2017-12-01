
TEMPLATE = app
TARGET = create_table
INCLUDEPATH += .
QT += sql
CONFIG += console debug
CONFIG -= moc
CONFIG += c++11
# QMAKE_CXXFLAGS += -std=c++11

# Input
SOURCES += create_table.cpp
