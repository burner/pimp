build:
	scons -j3

tags:
	ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q \
	--language-force=C++ -f tags include ui

clean:
	scons --clean

run: build
	./pimp
