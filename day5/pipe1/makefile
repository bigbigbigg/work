SRCS:=$(wildcard *.c)
OBJECTS:=$(SRCS:%.c=%.o)
BINS:=$(SRCS:%.c=%)
CC:=gcc
all:$(BINS)

%:%.c
	$(CC) $< -o $@
.PHONY:clean
clean:
	rm $(BINS) $(OBJECTS)
