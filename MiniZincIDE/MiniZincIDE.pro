#-------------------------------------------------
#
# Project created by QtCreator 2013-12-12T09:32:30
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): {
  greaterThan(QT_MINOR_VERSION, 5): {
    QT += webenginewidgets
    DEFINES += MINIZINC_IDE_HAVE_WEBENGINE
  }
  !greaterThan(QT_MINOR_VERSION, 5): {
    QT += webkitwidgets
  }
}

TARGET = MiniZincIDE
TEMPLATE = app

VERSION = 2.2.3
DEFINES += MINIZINC_IDE_VERSION=\\\"$$VERSION\\\"

bundled {
    DEFINES += MINIZINC_IDE_BUNDLED
}

CONFIG += c++11

macx {
    ICON = mznide.icns
    OBJECTIVE_SOURCES += macos_extras.mm
    QT += macextras
    LIBS += -framework Cocoa
    macx-xcode {
      QMAKE_INFO_PLIST = mznide-xcode.plist
    } else {
      QMAKE_INFO_PLIST = mznide-makefile.plist
    }
}

RC_ICONS = mznide.ico

CONFIG += embed_manifest_exe

#LIBS += -L/Users/tack/Programming/MiniZinc/libmzn/build_xcode/Debug -lminizinc_compiler -lminizinc_fzn -lminizinc_cplex -lminizinc_nl -lminizinc_gurobi -lminizinc_osicbc
#INCLUDEPATH += /Users/tack/Programming/MiniZinc/libmzn/include /Users/tack/Programming/MiniZinc/libmzn/build_xcode/include
#DEFINES += MINIZINC_IDE_HAVE_LIBMINIZINC

SOURCES += main.cpp\
    mainwindow.cpp \
    codeeditor.cpp \
    highlighter.cpp \
    fzndoc.cpp \
    solverdialog.cpp \
    gotolinedialog.cpp \
    finddialog.cpp \
    paramdialog.cpp \
    outputdockwidget.cpp \
    checkupdatedialog.cpp \
    project.cpp \
    htmlwindow.cpp \
    htmlpage.cpp \
    moocsubmission.cpp \
    solverconfiguration.cpp \
    esclineedit.cpp

HEADERS  += mainwindow.h \
    codeeditor.h \
    highlighter.h \
    fzndoc.h \
    macos_extras.h \
    solverdialog.h \
    gotolinedialog.h \
    finddialog.h \
    paramdialog.h \
    outputdockwidget.h \
    checkupdatedialog.h \
    project.h \
    htmlwindow.h \
    htmlpage.h \
    moocsubmission.h \
    solverconfiguration.h \
    esclineedit.h

FORMS    += \
    mainwindow.ui \
    solverdialog.ui \
    gotolinedialog.ui \
    finddialog.ui \
    paramdialog.ui \
    checkupdatedialog.ui \
    htmlwindow.ui \
    moocsubmission.ui

RESOURCES += \
    minizincide.qrc

target.path = $$PREFIX/bin
INSTALLS += target
