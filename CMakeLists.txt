cmake_minimum_required(VERSION 2.8)

project(pim)

find_package(Qt4 COMPONENTS QtCore QtGui QtWebkit REQUIRED)
SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTWEBKIT TRUE)

include(${QT_USE_FILE})

set(pim_HEADERS 
	includes/main.hpp
	includes/calendarmainwidget.hpp
	includes/instantmainwidget.hpp
	includes/ircmainwidget.hpp
	includes/mailmainwidget.hpp
	includes/mainwindow.hpp
	includes/summarymainwidget.hpp
	includes/todomainwidget.hpp
	includes/loggingmainwidget.hpp
	includes/contactsmainwidget.hpp
	includes/debug.hpp
)

set(pim_SOURCES 
	src/main.cpp
	src/calendarmainwidget.cpp
	src/instantmainwidget.cpp
	src/ircmainwidget.cpp
	src/mailmainwidget.cpp
	src/mainwindow.cpp
	src/summarymainwidget.cpp
	src/todomainwidget.cpp
	src/loggingmainwidget.cpp
	src/contactsmainwidget.cpp
	src/debug.cpp
)

set(pim_MOC_HEADERS 
	includes/calendarmainwidget.hpp
	includes/instantmainwidget.hpp
	includes/ircmainwidget.hpp
	includes/mailmainwidget.hpp
	includes/mainwindow.hpp
	includes/summarymainwidget.hpp
	includes/todomainwidget.hpp
	includes/loggingmainwidget.hpp
	includes/contactsmainwidget.hpp
)

set(pim_UIS 
	ui/calendarmainwidget.ui
	ui/instantmainwidget.ui
	ui/ircmainwidget.ui
	ui/mailmainwidget.ui
	ui/mainwindow.ui
	ui/summarymainwidget.ui
	ui/todomainwidget.ui
	ui/loggingmainwidget.ui
	ui/contactsmainwidget.ui
)

set(pim_RESOURCES
	resources/icons.qrc
)

SET(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb --std=c++0x -std=gnu++0x")

QT4_WRAP_CPP(pim_MOC ${pim_MOC_HEADERS})
QT4_WRAP_UI(pim_UIS_H ${pim_UIS})
QT4_ADD_RESOURCES(pim_RESOURCES_CPP ${pim_RESOURCES})
#QT4_WRAP_CPP(pim_MOC_SOURCES ${pim_MOC_HEADERS})

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_executable(pim
    ${pim_SOURCES}
	${pim_MOC_SOURCES}
	${pim_MOC}
    ${pim_UIS_H}
	${pim_UIS}
	${pim_UIS_H}
	${pim_RESOURCES_CPP}
	${pim_HEADERS}
)

target_link_libraries(pim ${QT_LIBRARIES})
