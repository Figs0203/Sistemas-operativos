CXX = g++
CXXFLAGS = -Wall

SRC = Sistema.cpp Proceso.cpp CPU.cpp
OBJS = Sistema.o Proceso.o CPU.o
EXEC = simulador

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

Sistema.o: Sistema.cpp Proceso.h CPU.h
	$(CXX) $(CXXFLAGS) -c Sistema.cpp

Proceso.o: Proceso.cpp Proceso.h
	$(CXX) $(CXXFLAGS) -c Proceso.cpp

CPU.o: CPU.cpp CPU.h
	$(CXX) $(CXXFLAGS) -c CPU.cpp

clean:
	del *.o $(EXEC)

.PHONY: clean
