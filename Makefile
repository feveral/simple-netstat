CFLAGS = -O2 -g -Wall -I include

OBJS = \
	src/main.o \
	src/connection.o \
	src/list.o \
	src/utility.o \
	src/process.o

EXEC = simple-netstat

src/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

all: $(EXEC)
run: $(EXEC) 
	sudo ./$(EXEC)
clean:
	rm $(OBJS) $(EXEC)
