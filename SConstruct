import os
from subprocess import call

CPPFLAGS= ' `pkg-config gtkmm-3.0 --cflags` ' + "-Wall -ggdb -Iui --std=c++11"
CPPPATH= ["ui", "include"]
LINKFLAGS = ' `pkg-config gtkmm-3.0 --libs` ' + "--std=c++11 -ggdb"

# here comes the magic
gladeHeader = Split("""
	ui/g2cpp_mainwindow.glade.hpp
""")

gladeFiles = [ "ui/"+i[9:-4] for i in gladeHeader]

srcFiles = Split("""
	src/main.cpp
""")

env = Environment()
gh = env.Command(gladeHeader, gladeFiles, "./g2cpp.py $SOURCE")
env.Append(CPPFLAGS=CPPFLAGS, LINKFLAGS=LINKFLAGS, CPPPATH=CPPPATH)
pimp = env.Program('pimp', srcFiles)
Depends(srcFiles, gladeHeader)
