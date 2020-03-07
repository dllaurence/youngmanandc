CC = gcc
CFLAGS = -O2 -Wall -Werror

ALL = demo_logger

.phony: all
all: $(ALL)

demo_logger: demo_logger.o logger.o

logger.o: logger.h

clean:
	rm -rf $(ALL)
	rm -rf *.o
