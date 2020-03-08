CC = gcc
CFLAGS = -O2 -Wall -Werror

ALL = demo_logger demo_ownership demo_error

.phony: all
all: $(ALL)

demo_logger: demo_logger.o logger.o
demo_ownership: demo_ownership.o logger.o
demo_error: demo_error.o error.o

logger.o: logger.h
error.o: error.h

demo_logger.o : logger.h
demo_ownership.o : logger.h
demo_error.o : error.h

clean:
	rm -rf $(ALL)
	rm -rf *.o
