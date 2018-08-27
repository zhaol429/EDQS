src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))

CFLAGS = -Wall -g
LDFLAGS = -Wall -g 
CC = gcc


target = app

#$(target):
all:
	$(CC) *.c -o $(target) $(CFLAGS) 

#%.o : %.c
#	$(CC) $< $(CFLAGS) $@
	

clean:
	rm -rf $(obj) $(target)
distclean: clean
.PHONY: all clean distclean
