TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += debug

# Input
HEADERS += board.h \
           checker.h \
           clickablelabel.h \
           dice.h \
           diceanimation.h \
           doubledice.h \
           mainwindow.h \
           point.h \
           spot.h \
           lineedit.h
SOURCES += board.cpp \
           checker.cpp \
           clickablelabel.cpp \
           dice.cpp \
           diceanimation.cpp \
           doubledice.cpp \
           main.cpp \
           mainwindow.cpp \
           point.cpp \
           spot.cpp \
           lineedit.cpp
RESOURCES += images.qrc
