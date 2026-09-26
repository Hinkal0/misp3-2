.PHONY: run clean all

all: main

main: main.o TimeMeter_win.o TimeMeter_lin.o
	g++ $^ -o main

%.o: %.cpp
	g++ -c $< -o $@

run: all
	./main

clean:
	rm -rf *.o main
