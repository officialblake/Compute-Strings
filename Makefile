GMP_INC = /opt/homebrew/include    
GMP_LIB = /opt/homebrew/lib       

CXXFLAGS = -std=c++17 -g 

strings.x: main.o dfa.o
	g++ $(CXXFLAGS) main.o dfa.o -L$(GMP_LIB) -lgmp -lgmpxx -o strings.x

main.o: main.cpp dfa.h
	g++ $(CXXFLAGS) -I$(GMP_INC) -c main.cpp -o main.o

dfa.o: dfa.cpp dfa.h
	g++ $(CXXFLAGS) -I$(GMP_INC) -c dfa.cpp -o dfa.o

clean:
	@rm -f strings.x *.o