#ifndef PROCESO_H
#define PROCESO_H

#include <string>
#include <queue>
#include <vector>

using namespace std;

class Proceso {
    int pid;
    int pc; // Program Counter simulado
    int ax, bx, cx; // Registros simulados
    int quantum;
    string estado; // "Listo", "Ejecutando", "Terminado"
    queue<string> instrucciones;

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
