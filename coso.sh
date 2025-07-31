g++ -c Sistema.cpp -o sistema.o
g++ -c Proceso.cpp -o proceso.o
g++ -c CPU.cpp -o cpu.o
g++ -c cpu.o proceso.o sistema.o -o programa