CC = gcc
CFLAGS = -Wall -g -pthread

all: helgrind

raceCondition: raceCondition.c
	$(CC) $(CFLAGS) $< -o $@

helgrind: raceCondition
	valgrind --tool=helgrind --log-file=helgrindReport.txt ./raceCondition

clean:
	rm -rf raceCondition helgrindReport.txt