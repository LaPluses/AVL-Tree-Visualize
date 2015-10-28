#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T19:50:17
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AVL_Tree_Visualize
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    treenode.cpp \
    treeedge.cpp \
    treeview.cpp \
    avltree.cpp \
    treepath.cpp \
    speedcontroller.cpp

HEADERS  += widget.h \
    treenode.h \
    treeedge.h \
    treeview.h \
    avltree.h \
    treepath.h \
    speedcontroller.h
