tool: main.cpp display.o
	g++ main.cpp display.o -lcurses -o tool

display.o: display.cpp
	g++ -c display.cpp -lcurses

clean:
	rm -f *.o tool

