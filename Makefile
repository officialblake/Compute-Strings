GMP_INC = /opt/homebrew/include    # Adjust this path to where GMP is installed
GMP_LIB = /opt/homebrew/lib        # Adjust this path to the GMP library location

strings.x: main.o dfa.o
	g++ -std=c++17 -g main.o dfa.o -lgmp -lgmpxx -L$(GMP_LIB) -o strings.x

main.o: main.cpp dfa.h
	g++ -std=c++17 -g -I$(GMP_INC) main.cpp -o main.o -c

dfa.o: dfa.cpp dfa.h
	g++ -std=c++17 -g -I$(GMP_INC) dfa.cpp -o dfa.o -c

clean:
	rm -f strings.x *.o