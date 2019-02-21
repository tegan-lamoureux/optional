optional: main.cpp oauth.o account.o display.o
	g++ main.cpp oauth.o account.o display.o -o optional -lcurses

oauth.o: oauth.cpp
	g++ -c oauth.cpp -lboost

account.o: account.cpp
	g++ -c account.cpp -lboost

display.o: display.cpp
	g++ -c display.cpp -lcurses

clean:
	rm -f *.o optional

