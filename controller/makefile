OBJS	= main.o
SOURCE	= main.cpp
HEADER	= 
OUT	= controller
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lncurses -ltinfo 


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

run: all
	./controller
	
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 


clean:
	rm -f $(OBJS) $(OUT)
