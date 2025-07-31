#ifndef PROCESO_H
#define PROCESO_H

#include <string>
#include <queue>
#include <vector>

using namespace std;

// instrucciones va a ser un vector, PC va a ser un puntero a la siguiente instruccion, es el iterador

class Proceso {
    int pid;
    // vector<string>::iterator
    int ax, bx, cx; // Registros simulados
    int quantum;
    string estado; // "Listo", "Ejecutando", "Terminado"
    vector<string> instrucciones;
    vector<string>::iterator pc; // Program Counter simulado

public:
    Proceso();
    Proceso(string nombreArchivo);
    bool instruccionesPendientes();
    void siguienteInstruccion();
    void guardarContexto();
    void cargarContexto();
    void cargarInstrucciones(std::string nombreArchivo);
    int getPID();
    int getQuantum();
};

#endif
