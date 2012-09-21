cmake_minimum_required(VERSION 2.8)

project(pimp)

find_package(Qt4 COMPONENTS QtCore QtGui QtWebkit REQUIRED)
SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTWEBKIT TRUE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(${QT_USE_FILE})

set(pimp_HEADERS 
	includes/aes256.hpp
	includes/calendarmainwidget.hpp
	includes/contactsmainwidget.hpp
	includes/debug.hpp
	includes/exception.hpp
	includes/highlighter.hpp
	includes/instantmainwidget.hpp
	includes/ircmainwidget.hpp
	includes/loggingmainwidget.hpp
	includes/mailmainwidget.hpp
	includes/main.hpp
	includes/mainwindow.hpp
	includes/newfeeddialog.hpp
	includes/newmailwindow.hpp
	includes/rssmainwidget.hpp
	includes/settings.hpp
	includes/summarymainwidget.hpp
	includes/todomainwidget.hpp
)

set(pimp_SOURCES 
	src/aes256.cpp
	src/calendarmainwidget.cpp
	src/contactsmainwidget.cpp
	src/debug.cpp
	src/exception.cpp
	src/highlighter.cpp
	src/instantmainwidget.cpp
	src/ircmainwidget.cpp
	src/loggingmainwidget.cpp
	src/mailmainwidget.cpp
	src/main.cpp
	src/mainwindow.cpp
	src/newfeeddialog.cpp
	src/newmailwindow.cpp
	src/rssmainwidget.cpp
	src/settings.cpp
	src/summarymainwidget.cpp
	src/todomainwidget.cpp
)

set(pimp_UIS 
	ui/calendarmainwidget.ui
	ui/instantmainwidget.ui
	ui/inserthtmldialog.ui
	ui/ircmainwidget.ui
	ui/mailmainwidget.ui
	ui/mainwindow.ui
	ui/summarymainwidget.ui
	ui/todomainwidget.ui
	ui/loggingmainwidget.ui
	ui/contactsmainwidget.ui
	ui/rssmainwidget.ui
	ui/newfeeddialog.ui
	ui/newmailwindow.ui
)

set(pimp_RESOURCES
	resources/icons.qrc
	resources/htmleditor.qrc
)

set(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb --std=c++0x -std=gnu++0x")

QT4_WRAP_UI(pimp_UIS_H ${pimp_UIS})
QT4_ADD_RESOURCES(pimp_RESOURCES_CPP ${pimp_RESOURCES})

include_directories(
	${CMAKE_CURRENT_BINARY_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_executable(pimp
    ${pimp_SOURCES}
    ${pimp_UIS_H}
	${pimp_RESOURCES_CPP}
	${pimp_HEADERS}
)

target_link_libraries(pimp ${QT_LIBRARIES} mrss vmime boost_regex crypto)
