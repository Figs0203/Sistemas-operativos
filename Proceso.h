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
    string estado; 
    vector<string> instrucciones;

public:
    Proceso();
    Proceso(string nombreArchivo);
    bool instruccionesPendientes();
    void cargarInformacion(std::string nombreArchivo);
    void cargarInstrucciones();
    
    map<string,int>& getElementos();
    string getInstruccion();
    int getPID();
    int getQuantum();
    int& getPC();
    void setPC(int n);
    void setEstado(string estado_input);
    string getEstado();
    
    vector<string> splitString(string entrada, char separador);
};

#endif
