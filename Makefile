strings.x: main.o dfa.o
	g++ -std=c++17 -g main.o dfa.o -o strings.x

main.o: main.cpp dfa.h
	g++ -std=c++17 -g main.cpp -o main.o -c

dfa.o: dfa.cpp dfa.h
	g++ -std=c++17 -g dfa.cpp -o dfa.o -c

clean:
	rm -f strings.x *.o