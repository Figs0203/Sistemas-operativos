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
    pc = 0;
}


bool Proceso::instruccionesPendientes() {
    return pc != (int) instrucciones.size();
}


vector<string> splitString(string entrada, char separador){
    vector<string> salida;
    stringstream ss(entrada);
    string temporal;
    while(getline(ss,temporal,separador)) salida.push_back(temporal);
    return salida;
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

    if (regex_search(info[info.size()-1], match, patron_Quantum)) pid = stoi(match[1]);
    else cout << "Instrucciones ingresadas erróneamente" << endl;

    // registrar registros en el diccionario
    for(int i =1;i<(int)info.size()-1;i++){
        vector<string> registro = splitString(info[i],'=');
        string key =registro[0];
        key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
        string value =registro[1];
        value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
        // cout<<key<<" "<<value<<endl;;
        registros[key] = stoi(value); 
    }

}


int Proceso::getPID(){
    return pid;
}

int Proceso::getQuantum(){
    return quantum;
}

map<string,int>& Proceso::getElementos(){
    return  registros;
}

string Proceso::getInstruccion(){
    string temp = instrucciones[pc];
    pc = pc+1;
    return temp;
}

void Proceso::setEstado(string estado_input){
    estado = estado_input;
}

string Proceso::getEstado(){
    return estado;
}


//Guardar en binario
void Proceso::guardarContexto() {
    // string ramAddress = "data"+to_string(pid)+".bin";
    // ofstream archivo(ramAddress, ios::binary);
    // if (!archivo) {
    //     cerr << "No se pudo abrir el archivo." << endl;
    //     return;
    // }

    // archivo.write(reinterpret_cast<char*>(&pid), sizeof(pid));
    // archivo.write(reinterpret_cast<char*>(&pc), sizeof(pc));
    // archivo.write(reinterpret_cast<char*>(&ax), sizeof(ax));
    // archivo.write(reinterpret_cast<char*>(&bx), sizeof(bx));
    // archivo.write(reinterpret_cast<char*>(&cx), sizeof(cx));
    // archivo.write(reinterpret_cast<char*>(&quantum), sizeof(quantum));

    // size_t lenEstado = estado.size();
    // archivo.write(reinterpret_cast<char*>(&lenEstado), sizeof(lenEstado));
    // archivo.write(estado.c_str(), lenEstado);

    // size_t numInstrucciones = instrucciones.size();
    // archivo.write(reinterpret_cast<char*>(&numInstrucciones), sizeof(numInstrucciones));
    
    // int iterador = 0; //Mirar opción de usar un for each
    // while (iterador < instrucciones.size()) {
    //     string instr = instrucciones[iterador];
        
    //     size_t lenInstr = instr.size();
    //     archivo.write(reinterpret_cast<char*>(&lenInstr), sizeof(lenInstr));
    //     archivo.write(instr.c_str(), lenInstr);
    //     iterador++;
    // }

    // archivo.close();
    // cout<<"contexto guardado"<<endl;
}

//Cargar binario
void Proceso::cargarContexto() {
    // ifstream archivo("data.bin", ios::binary);
    // if (!archivo) {
    //     cerr << "No se pudo abrir el archivo para lectura." << endl;
    //     return;
    // }

    // archivo.read(reinterpret_cast<char*>(&pid), sizeof(pid));
    // archivo.read(reinterpret_cast<char*>(&pc), sizeof(pc));
    // archivo.read(reinterpret_cast<char*>(&ax), sizeof(ax));
    // archivo.read(reinterpret_cast<char*>(&bx), sizeof(bx));
    // archivo.read(reinterpret_cast<char*>(&cx), sizeof(cx));
    // archivo.read(reinterpret_cast<char*>(&quantum), sizeof(quantum));

    // size_t lenEstado;
    // archivo.read(reinterpret_cast<char*>(&lenEstado), sizeof(lenEstado));
    // estado.resize(lenEstado);
    // archivo.read(&estado[0], lenEstado);
    
    // instrucciones.clear();

    // size_t numInstrucciones;
    // archivo.read(reinterpret_cast<char*>(&numInstrucciones), sizeof(numInstrucciones));

    // for (size_t i = 0; i < numInstrucciones; i++) {
    //     size_t lenInstr;
    //     archivo.read(reinterpret_cast<char*>(&lenInstr), sizeof(lenInstr));
    //     string instr(lenInstr, '\0');
    //     archivo.read(&instr[0], lenInstr);
    //     instrucciones.push_back(instr);
    // }

    // archivo.close();
    // cout<<"contexto cargado"<<endl;
}
