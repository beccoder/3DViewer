CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
SOURCES=file_loader.c
OBJECTS=$(SOURCES:.c=.o)
OS = $(shell uname)
TEST_FILE_NAME = test.c

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

build: OpenGLApp uninstall
	mkdir 3DViewer
	cd 3DViewer; cmake ../OpenGLApp

uninstall:
	rm -f 3D
	rm -rf 3DViewer

dvi:
	cp pics/instructions.pdf .

dist: build
	tar --totals -cvf 3DViewer.tar 3DViewer

install: build
	cd 3DViewer; cmake --build ./ --target all
	cp 3DViewer/OpenGLApp.app/Contents/MacOS/OpenGLApp ./3D

all: gcov_report

file_loader.a: clean $(OBJECTS)
	ar -rcs file_loader.a $(OBJECTS)
	rm -f *.o

tests: $(TEST_FILE_NAME) file_loader.a
	$(CC) $(CFLAGS) $(TEST_FILE_NAME) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

gcov_report: tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean: uninstall
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt test.info test.dSYM a

check: tests
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm -rf .clang-format
ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
