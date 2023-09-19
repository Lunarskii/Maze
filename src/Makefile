.PHONY: all install uninstall clean dvi dist launch tests style valgrind

CFLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic -g
LDFLAGS = $(shell pkg-config --cflags --libs gtest)
APP_NAME = Maze

OS := $(shell uname -s)
ifeq ($(OS), Linux)
  OPEN = ./build/$(APP_NAME)
endif
ifeq ($(OS), Darwin)
	OPEN = open build/$(APP_NAME).app
endif

all: install launch

install:
	cmake -B build
	make -C build $(APP_NAME)

uninstall:
	$(MAKE) clean
	rm -rf build

clean:
	rm -rf valgrind.txt $(APP_NAME).tar.gz
	rm -rf test

dvi:
	open README.md

dist:
	$(MAKE) install
	tar -czf $(APP_NAME).tar.gz --directory=build/ .

launch:
	$(OPEN)

tests:
	g++ tests/*.cc Model/Cave/*.cc Model/Maze/*.cc $(CFLAGS) $(LDFLAGS) -o test
	./test

style:
	'not defined'