#include <iostream>
#include "Proceso.h"
#include "CPU.h"
#include <sstream>
#include <string>
using namespace std;

bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}


vector<string> splitString(string entrada, char separador){
    vector<string> salida;
    stringstream ss(entrada);
    string temporal;
    while(getline(ss,temporal,separador)) salida.push_back(temporal);
    return salida;
}



void CPU::correr(Proceso& proceso){
// cargar las variables que van a ser modificadas dentro de la CPU
    map<string,int>& elementos = proceso.getElementos();
    string instrucciones = proceso.getInstruccion();
    if(instrucciones == "Finished") {   
        cout << "Ejecutando instrucción: " << instrucciones<< " en el Proceso "<< proceso.getPID()<< " Estado: "<<proceso.getEstado() << endl;
        for(pair<string,int> p:elementos)cout<<p.first<<" "<<p.second<<" ";
        cout<<endl;cout<<endl;
        return;
    }
    proceso.setEstado("Running");



// mostrar resultados iniciales
    cout << "Ejecutando instrucción: " << instrucciones<< " en el Proceso "<< proceso.getPID()<< " Estado: "<<proceso.getEstado() << endl;
    for(pair<string,int> p:elementos)cout<<p.first<<" "<<p.second<<" ";
    cout<<endl;

    stringstream ss(instrucciones);
    string instruccion;
    ss>> instruccion;
    
    string temp;
    getline(ss, temp);
    vector<string> variables = splitString(temp, ',');
   
      // quitar espacios
    for (string& s : variables) {
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }

    // ADD
    if (instruccion == "ADD") {
        int& valor1 = elementos[variables[0]];
        string valor2 = variables[1];
        if(isNumber(valor2)) valor1 += stoi(valor2);
        else valor1 += elementos[valor2];
    } 

    // SUB
    else if (instruccion == "SUB") {
        int& valor1 = elementos[variables[0]];
        string valor2 = variables[1];
        if(isNumber(valor2)) valor1 -= stoi(valor2);
        else valor1 -= elementos[valor2];
    }

    // INC
    else if (instruccion == "INC") {
        int& valor = elementos[variables[0]];
        valor++;
    }

    // MUL
    else if (instruccion == "MUL") {
        int& valor1 = elementos[variables[0]];
        string valor2 = variables[1];
        if(isNumber(valor2)) valor1 *= stoi(valor2);
        else valor1 *= elementos[valor2];
    }

    // JM (simulado)
    else if (instruccion == "JMP") {
        int& destino = proceso.getPC();
        destino = stoi(variables[0]);
    }

    // Mostrar resultado actualizado
    for(pair<string,int> p:elementos) cout << p.first << " " << p.second << " ";
    cout << endl;
        
    
}

