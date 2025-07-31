
CXX = g++
CXXFLAGS = -Wall


OBJS = main.o Proceso.o

programa: $(OBJS)
	$(CXX) $(OBJS) -o programa

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp

Proceso.o: Proceso.cpp 
	$(CXX) $(CXXFLAGS) -c Proceso.cpp

clean:
	rm -f *.o programa
