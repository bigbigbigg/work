SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=process_pool_server
BINS:=$(SRCS:%.c=%)
CC:=gcc
CFLAGS:=-g -Wall
$(ELF):$(OBJS)
	$(CC)  -o $@ $^ -lpthread 
.PHONY:clean
clean:
	rm $(OBJS) $(ELF)
