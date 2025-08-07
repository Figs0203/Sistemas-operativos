#ifndef PROCESO_H
#define PROCESO_H

#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

// instrucciones va a ser un vector, PC va a ser un puntero a la siguiente instruccion, es el iterador

class Proceso {
    int pid;
    int pc; // Program Counter simulado
    map<string,int> registros;
    int a,b,c;
    int quantum;
    string estado; // "Listo", "Ejecutando", "Terminado"
    vector<string> instrucciones;

public:
    Proceso();
    Proceso(string nombreArchivo);
    bool instruccionesPendientes();
    void guardarContexto();
    void cargarContexto();
    void cargarInformacion(std::string nombreArchivo);
    void cargarInstrucciones();
    int getPID();
    int getQuantum();
    map<string,int>& getElementos();
    string getInstruccion();
    void setEstado(string estado_input);
    string getEstado();
};

#endif
