import os
from subprocess import call

CPPFLAGS= "-Wall -ggdb -Iui -I../sweet.hpp --std=c++11"
CPPPATH= ["ui", "include"]
LINKFLAGS = "--std=c++11 -ggdb"


# here comes the magic ui files go here
gladeHeader = Split("""
	ui/g2cpp_mainwindow.glade.hpp
	ui/g2cpp_vimdialog.glade.hpp
""")

gladeFiles = [ "ui/"+i[9:-4] for i in gladeHeader]


# source files go here
srcFiles = Split("""
	src/main.cpp
	src/mainwindow/mainwindow.cpp
	src/vimdialog/vimdialog.cpp
	src/uniquename.cpp
""")

env = Environment()
for i in range(len(gladeFiles)):
	gh = env.Command(gladeHeader[i], gladeFiles[i], "./g2cpp.py $SOURCE $TARGET")

env.Append(CPPFLAGS=CPPFLAGS, LINKFLAGS=LINKFLAGS, CPPPATH=CPPPATH)
env.ParseConfig("pkg-config gtkmm-3.0 vte-2.90 --cflags --libs")
pimp = env.Program('pimp', srcFiles)
Depends(srcFiles, gladeHeader)
