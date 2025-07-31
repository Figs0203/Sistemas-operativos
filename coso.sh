# Compilar los archivos fuente a objetos
g++ -std=c++17 -Wall -c CPU.cpp
g++ -std=c++17 -Wall -c Proceso.cpp
g++ -std=c++17 -Wall -c Sistema.cpp

# Enlazar los objetos en un ejecutable
g++ -std=c++17 -Wall -o programa CPU.o Proceso.o Sistema.o