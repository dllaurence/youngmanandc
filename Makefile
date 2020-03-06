CC = gcc
CFLAGS = -O2 -Wall -Werror

ALL = test_logger

.phony: all
all: $(ALL)

test_logger: test_logger.o logger.o

logger.o: logger.h

clean:
	rm -rf $(ALL)
	rm -rf *.o
