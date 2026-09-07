.PHONY: clean

scheduler: main.c job.c executor.c parser.c common.h job.h executor.h parser.h
	gcc -Wall -Wextra main.c job.c executor.c parser.c -o scheduler

clean:
	rm -f scheduler
