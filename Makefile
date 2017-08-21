#Compiler
CC=gcc

#Output File Name
OUTPUT = out

#sources files
SRC  = main.c
SRC += rpi.c

#Include directories
INCDIR =

#Optimization options
OPT = -O0

#Cflags
CPFLAGS = $(OPT)

#Linker Flags
LDFLAGS =

OBJS  = $(SRC:.c=.o)

all: $(OBJS) $(OUTPUT).bin

$(OBJS): %.o: %.c
	$(CC) -c $(CPFLAGS) -I. $(INCDIR) $< -o $@

%bin: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -rf *.o
	rm -f $(OUTPUT).bin
