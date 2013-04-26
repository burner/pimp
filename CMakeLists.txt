cmake_minimum_required(VERSION 2.8.10)

## we have some extra modules here
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

## thats our project
project(pimp)

## we need all that Qt stuff
#find_package(Qt COMPONENTS QtCore QtGui QtXml QtWebkit REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)

#set(QT_USE_QTSQL TRUE)
#set(QT_USE_QTWEBKIT TRUE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#include(${QT_USE_FILE})
#set(LIBS ${LIBS} ${QT_LIBRARIES})

## this will do the imap,pop,smtp stuff

## DEBUG
GET_DIRECTORY_PROPERTY(INCLUDES INCLUDE_DIRECTORIES)
#MESSAGE( "INCLUDES: ${INCLUDES}" )
#MESSAGE( "LIBS: ${LIBS}" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sweet.hpp)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

##############################################################################

## our headers
set(pimp_HEADERS 
	includes/mainwindow/mainwindow.hpp	

	includes/mailwidget/mailmainwidget.hpp

	includes/vimdialog/vimdialog.hpp
	includes/vimdialog/uniquename.hpp

	includes/main.hpp
)

## well and the sources
set(pimp_SOURCES 
	src/mainwindow/mainwindow.cpp	

	src/mailwidget/mailmainwidget.cpp

	src/vimdialog/vimdialog.cpp
	src/vimdialog/uniquename.cpp

	src/main.cpp
)

## some gui stuff
set(pimp_UIS 
	ui/mainwindow/mainwindow.ui

	ui/mailwidget/mailmainwidget.ui

#ui/vimdialog/vimdialog.ui
)

## people love pictures
set(pimp_RESOURCES
	resources/icons.qrc
	resources/htmleditor.qrc
)

## we love c++0x and a chatty compiler that comments on our code
set(CMAKE_CXX_FLAGS "-Wall -ggdb --std=c++0x -std=gnu++0x")

qt5_wrap_ui(pimp_UIS_H ${pimp_UIS})

include_directories(
	${CMAKE_CURRENT_BINARY_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR}/includes
)

add_executable(pimp
    ${pimp_SOURCES}
    ${pimp_UIS_H}
	${pimp_RESOURCES_CPP}
	${pimp_HEADERS}
)

qt5_use_modules(pimp Widgets)
target_link_libraries(pimp Qt5::Core)
