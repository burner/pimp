import os
from subprocess import call

CPPFLAGS= "-Wall -ggdb -Iui --std=c++11"
CPPPATH= ["ui", "include"]
LINKFLAGS = "--std=c++11 -ggdb"


# here comes the magic ui files go here
gladeHeader = Split("""
	ui/g2cpp_mainwindow.glade.hpp
""")

gladeFiles = [ "ui/"+i[9:-4] for i in gladeHeader]

# source files go here
srcFiles = Split("""
	src/main.cpp
	src/mainwindow/mainwindow.cpp
""")

env = Environment()
gh = env.Command(gladeHeader, gladeFiles, "./g2cpp.py $SOURCE")
env.Append(CPPFLAGS=CPPFLAGS, LINKFLAGS=LINKFLAGS, CPPPATH=CPPPATH)
env.ParseConfig("pkg-config gtkmm-3.0 --cflags --libs")
pimp = env.Program('pimp', srcFiles)
Depends(srcFiles, gladeHeader)
