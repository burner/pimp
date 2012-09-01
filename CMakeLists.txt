cmake_minimum_required(VERSION 2.8)

project(pimp)

find_package(Qt4 COMPONENTS QtCore QtGui QtWebkit REQUIRED)
SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTWEBKIT TRUE)

include(${QT_USE_FILE})

set(pimp_HEADERS 
	includes/main.hpp
	includes/calendarmainwidget.hpp
	includes/instantmainwidget.hpp
	includes/rssmainwidget.hpp
	includes/ircmainwidget.hpp
	includes/mailmainwidget.hpp
	includes/mainwindow.hpp
	includes/summarymainwidget.hpp
	includes/todomainwidget.hpp
	includes/loggingmainwidget.hpp
	includes/contactsmainwidget.hpp
	includes/debug.hpp
	includes/newfeeddialog.hpp
)

set(pimp_SOURCES 
	src/main.cpp
	src/calendarmainwidget.cpp
	src/instantmainwidget.cpp
	src/rssmainwidget.cpp
	src/ircmainwidget.cpp
	src/mailmainwidget.cpp
	src/mainwindow.cpp
	src/summarymainwidget.cpp
	src/todomainwidget.cpp
	src/loggingmainwidget.cpp
	src/contactsmainwidget.cpp
	src/debug.cpp
	src/newfeeddialog.cpp
)

set(pimp_MOC_HEADERS 
	includes/calendarmainwidget.hpp
	includes/instantmainwidget.hpp
	includes/ircmainwidget.hpp
	includes/mailmainwidget.hpp
	includes/mainwindow.hpp
	includes/summarymainwidget.hpp
	includes/todomainwidget.hpp
	includes/loggingmainwidget.hpp
	includes/contactsmainwidget.hpp
	includes/rssmainwidget.hpp
	includes/newfeeddialog.hpp
)

set(pimp_UIS 
	ui/calendarmainwidget.ui
	ui/instantmainwidget.ui
	ui/ircmainwidget.ui
	ui/mailmainwidget.ui
	ui/mainwindow.ui
	ui/summarymainwidget.ui
	ui/todomainwidget.ui
	ui/loggingmainwidget.ui
	ui/contactsmainwidget.ui
	ui/rssmainwidget.ui
	ui/newfeeddialog.ui
)

set(pimp_RESOURCES
	resources/icons.qrc
)

set(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb --std=c++0x -std=gnu++0x")

QT4_WRAP_CPP(pimp_MOC ${pimp_MOC_HEADERS})
QT4_WRAP_UI(pimp_UIS_H ${pimp_UIS})
QT4_ADD_RESOURCES(pimp_RESOURCES_CPP ${pimp_RESOURCES})
#QT4_WRAP_CPP(pimp_MOC_SOURCES ${pimp_MOC_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_executable(pimp
    ${pimp_SOURCES}
	${pimp_MOC_SOURCES}
	${pimp_MOC}
    ${pimp_UIS_H}
	${pimp_UIS}
	${pimp_UIS_H}
	${pimp_RESOURCES_CPP}
	${pimp_HEADERS}
)

target_link_libraries(pimp ${QT_LIBRARIES} mrss)
