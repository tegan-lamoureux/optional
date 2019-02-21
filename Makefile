optional: main.cpp account.o display.o
	g++ main.cpp account.o display.o -o optional -lcurses

account.o: account.cpp
	g++ -c account.cpp -lboost

display.o: display.cpp
	g++ -c display.cpp -lcurses

clean:
	rm -f *.o optional

