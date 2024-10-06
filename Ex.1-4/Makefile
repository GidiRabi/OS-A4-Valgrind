#!make -f

CXX = g++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion -fprofile-arcs -ftest-coverage -g -pg
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean reports cps

all: main

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o main

%.o: %.cpp graph.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

reports: main
	./main -a 2> /dev/null 2>&1 || true
	./main -e 10a -v 5 -s 10 > /dev/null 2>&1 || true
	./main -e 10 -v 5a -s 10 > /dev/null 2>&1 || true
	./main -e 10 -v 5 -s 10a > /dev/null 2>&1 || true
	./main -e 0 -v 5 -s 10 > /dev/null 2>&1 || true
	./main -e 100 -v 5 -s 10 > /dev/null 2>&1 || true
	./main -e 1 -v 5 -s 10 > /dev/null 2>&1 || true
	./main -e 10 -v 5 -s 10 > /dev/null 2>&1 || true
	./main -e 4950 -v 100 -s 10 > /dev/null 2>&1 || true
	@mkdir coverageReport profilingReport valgrindReport
	gcov main.cpp
	gprof main gmon.out > profilingReport/profilingReport.txt
	valgrind $(VALGRIND_FLAGS) ./main -e 45 -v 10 -s 10 > valgrindReport/valgrindReport.txt 2>&1 || true
	valgrind --tool=callgrind ./main -e 45 -v 10 -s 10 > valgrindReport/callgrind.txt 2>&1 || true
	callgrind_annotate callgrind.out.* > valgrindReport/callgrindReport.txt
	@mv *.gcda *.gcno *.gcov coverageReport/
	@mv gmon.out profilingReport/
	@mv callgrind.out.* valgrindReport/
	kcachegrind valgrindReport/callgrind.out.*

html-report: reports
	lcov --directory . --capture --output-file coverageReport/coverage.info
	genhtml coverageReport/coverage.info --output-directory coverageReport/html

clean:
	rm -f -r *.o main coverageReport profilingReport valgrindReport *.gcda *.gcno *.gcov callgrind.out.* *.out
