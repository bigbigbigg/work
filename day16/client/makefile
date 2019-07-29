SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=client
BINS:=$(SRCS:%.c=%)
CC:=gcc
CFLAGS:=-g -Wall
$(ELF):$(OBJS)
	$(CC)  -o $@ $^ -lpthread 
.PHONY:clean
clean:
	rm $(OBJS) $(ELF)
