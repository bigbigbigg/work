SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)
TARS:=$(SRCS:%.c=%)
CC:=gcc
all:$(TARS)

%:%.c
	$(CC) $< -o $@

clear:
	rm -rf $(TARS) $(OBJS)
	


