cmake_minimum_required(VERSION 2.8)

## we have some extra modules here
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

## thats our project
project(pimp)

## we need all that Qt stuff
find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtWebkit REQUIRED)
set(QT_USE_QTSQL TRUE)
set(QT_USE_QTWEBKIT TRUE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(${QT_USE_FILE})
set(LIBS ${LIBS} ${QT_LIBRARIES})

## we need a boost
#find_package( Boost 1.48 COMPONENTS regex REQUIRED )
#include_directories(${Boost_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${Boost_LIBRARIES})

## this will do the imap,pop,smtp stuff
find_package( VMime REQUIRED )
include_directories(${VMime_INCLUDE_DIRS})
set(LIBS ${LIBS} ${VMime_LIBRARIES})

## this will do the rss stuff
find_package( mRss REQUIRED )
include_directories(${mRss_INCLUDE_DIRS})
set(LIBS ${LIBS} ${mRss_LIBRARIES})

## this will do cryptographie (from glibc)
find_package( OpenSSL REQUIRED )
include_directories(${OPENSSL_INCLUDE_DIR})
set(LIBS ${LIBS} ${OPENSSL_LIBRARIES})

## DEBUG
GET_DIRECTORY_PROPERTY(INCLUDES INCLUDE_DIRECTORIES)
MESSAGE( "INCLUDES: ${INCLUDES}" )
MESSAGE( "LIBS: ${LIBS}" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sweet.hpp)

##############################################################################

## our headers
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
	includes/settingsdialog.hpp
	includes/summarymainwidget.hpp
	includes/todomainwidget.hpp
	includes/configmainwidget.hpp
	includes/newmailaccount.hpp
)

## well and the sources
set(pimp_SOURCES 
	src/aes256.cpp
	src/calendarmainwidget.cpp
	src/contactsmainwidget.cpp
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
	src/settingsdialog.cpp
	src/summarymainwidget.cpp
	src/todomainwidget.cpp
	src/configmainwidget.cpp
	src/newmailaccount.cpp
)

## some gui stuff
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
	ui/config.ui
	ui/configmainwidget.ui
	ui/mailaccount.ui
)

## people love pictures
set(pimp_RESOURCES
	resources/icons.qrc
	resources/htmleditor.qrc
)

## we love c++0x and a chatty compiler that comments on our code
set(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb --std=c++0x -std=gnu++0x")

QT4_WRAP_UI(pimp_UIS_H ${pimp_UIS})
QT4_ADD_RESOURCES(pimp_RESOURCES_CPP ${pimp_RESOURCES})

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

target_link_libraries(pimp ${LIBS} crypto)
