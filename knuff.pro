TEMPLATE = app
SOURCES += src/main.cpp \
 src/mainwindow.cpp \
 src/gameview.cpp \
 src/player.cpp \
 src/wall.cpp \
 src/managePlayersDialog.cpp
CONFIG += debug_and_release
FORMS += ui/mainwindow.ui \
 managePlayerDialog.ui
HEADERS += src/mainwindow.h \
 src/gameview.h \
 src/player.h \
 src/itemtypes.h \
 src/wall.h \
 src/managePlayersDialog.h
