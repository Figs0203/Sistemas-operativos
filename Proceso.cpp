#include "Proceso.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <cctype>

using namespace std;



Proceso::Proceso() {  
}

Proceso::Proceso(string nombreArchivo) {
    cargarInformacion(nombreArchivo);
    cargarInstrucciones();
    estado = "Ready";
    pc = 0;
}

void Proceso::cargarInstrucciones() {
    // Construir el nombre del archivo segun el PID
    string nombreArchivo = "procesos/" + to_string(pid) + ".txt";
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }
    string linea;
    // Leer cada línea del archivo y agregarla al vector de instrucciones
    while (getline(archivo, linea)) {

        if (linea.empty()) continue; // salta líneas vacías o con espacios

        // Eliminar espacios en blanco al inicio y final de la línea
        linea.erase(0, linea.find_first_not_of(" "));
        linea.erase(linea.find_last_not_of(" ") + 1);
        // Solo agregar líneas que no estén vacías
        if (!linea.empty()) {
            instrucciones.push_back(linea);
        }
    }
    archivo.close();
    cout << "Instrucciones cargadas para Proceso " << pid << " desde " << nombreArchivo << endl;
    cout<<endl;
    // cout<<instrucciones[0].size()<<endl;    
}

void Proceso::cargarInformacion(string linea) {

    // separar la linea por comas
    vector<string> info = splitString(linea,',');

    // conseguir el pid dentro del input
    smatch match;
    regex patron_pid(R"(PID:\s*(\d+))");

    if (regex_search(info[0], match, patron_pid)) pid = stoi(match[1]);
    else cout << "Instrucciones ingresadas erróneamente" << endl;
    
    // conseguir quantum dentro del input
    regex patron_Quantum(R"(Quantum=\s*(\d+))");

    if (regex_search(info[info.size()-1], match, patron_Quantum)) quantum = stoi(match[1]);
    else cout << "Instrucciones ingresadas erróneamente" << endl;

    // registrar registros en el diccionario
    for(int i =1;i<(int)info.size()-1;i++){
        vector<string> registro = splitString(info[i],'=');
        string key = registro[0];
        key.erase(remove(key.begin(), key.end(), ' '), key.end());
        string value = registro[1];
        value.erase(remove(value.begin(), value.end(), ' '), value.end());
        // cout<<key<<" "<<value<<endl;;
        registros[key] = stoi(value); 
    }
    

}


bool Proceso::instruccionesPendientes() {
    return pc < (int) instrucciones.size();
}

vector<string> Proceso::splitString(string entrada, char separador){
    vector<string> salida;
    stringstream ss(entrada);
    string temporal;
    while(getline(ss,temporal,separador)) salida.push_back(temporal);
    return salida;
}

map<string,int>& Proceso::getElementos(){
    return  registros;
}

string Proceso::getInstruccion(){
    if(pc>=(int)instrucciones.size()){
        estado = "Finished";
        return estado;
    }
    string temp = instrucciones[pc];
    pc = pc+1;
    return temp;
}

int Proceso::getPID(){
    return pid;
}

int Proceso::getQuantum(){
    return quantum;
}


int& Proceso::getPC(){
    return pc;
}

void Proceso::setPC(int n){
    pc = n;
}

string Proceso::getEstado(){
    return estado;
}


void Proceso::setEstado(string estado_input){
    estado = estado_input;
}


void Proceso:: writeLog(){

        // guardando datos en .log


        ofstream logFile("output.log", ios::app); // use std::ios::app to append to the file

        if (!logFile) {
            cout << "Failed to open log file!" << endl;
            return;
        }

        // escribir los datos
        logFile<<"PID:"<<pid<<" Quantum: "<<quantum<<" Estado: "<<estado<<endl;

        for(pair<string,int> p: registros)logFile<<p.first<<" "<<p.second<<" ";
        logFile<<endl;


        logFile.close();

        // cout << "Log written successfully.\n";
}





