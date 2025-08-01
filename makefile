
CXX = g++
CXXFLAGS = -Wall

SRC = main.cpp Proceso.cpp CPU.cpp
OBJS = main.o Proceso.o CPU.o
EXEC = programa

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

main.o: main.cpp Proceso.h CPU.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Proceso.o: Proceso.cpp Proceso.h
	$(CXX) $(CXXFLAGS) -c Proceso.cpp

CPU.o:
	$(CXX) $(CXXFLAGS) -c CPU.cpp

clean:
	$(RM) *.o $(EXEC)

.PHONY: clean