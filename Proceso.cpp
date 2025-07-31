#include "Proceso.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

Proceso::Proceso() {
   
}

Proceso::Proceso(string nombreArchivo) {
    cargarInstrucciones(nombreArchivo);
    pc = instrucciones.begin();
}


bool Proceso::instruccionesPendientes() {
    return !instrucciones.empty();
}

void Proceso::siguienteInstruccion() {
    // cout << instrucciones.size() << endl;
    std::cout<<"AX: "<<ax<<" Bx: "<<bx<<" Cx: "<<cx<<endl;

    if (pc!=instrucciones.end()) {
        string cabeza = *pc;
        std::cout << "Ejecutando instrucción: " << cabeza << endl;
        
        stringstream ss(cabeza);
        string instruccion;

        ss>> instruccion;

        string valor1, valor2;
        int* elementos[3] = {&ax, &bx, &cx};
        if (instruccion == "ADD") {
            ss >> valor1;
            ss >> valor2;
            int variable1 = valor1[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            int variable2 = valor2[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            *elementos[variable1] += *elementos[variable2];
            
        } 
        else if (instruccion == "SUB") {
            ss >> valor1;
            ss >> valor2;
            int variable1 = valor1[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            int variable2 = valor2[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            *elementos[variable1] -= *elementos[variable2];
        }
        else if (instruccion == "INC") {
            ss >> valor1;
            int variable1 = valor1[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            *elementos[variable1] += 1;
        }
        else if (instruccion == "MUL") {
            ss >> valor1;
            ss >> valor2;
            int variable1 = valor1[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            int variable2 = valor2[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            *elementos[variable1] -= *elementos[variable2];
        }
        
        
        pc+=1;

    }
}


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
    // while (!instrucciones.empty()) {
    //     string instr = instrucciones.front();
    //     instrucciones.pop();

    //     size_t lenInstr = instr.size();
    //     archivo.write(reinterpret_cast<char*>(&lenInstr), sizeof(lenInstr));
    //     archivo.write(instr.c_str(), lenInstr);
    // }

    // archivo.close();
    // cout<<"contexto guardado"<<endl;
}

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

    // while(!instrucciones.empty()) instrucciones.pop();

    // size_t numInstrucciones;
    // archivo.read(reinterpret_cast<char*>(&numInstrucciones), sizeof(numInstrucciones));

    // for (size_t i = 0; i < numInstrucciones; i++) {
    //     size_t lenInstr;
    //     archivo.read(reinterpret_cast<char*>(&lenInstr), sizeof(lenInstr));
    //     string instr(lenInstr, '\0');
    //     archivo.read(&instr[0], lenInstr);
    //     instrucciones.push(instr);
    // }

    // archivo.close();
    // cout<<"contexto cargado"<<endl;
}

void Proceso::cargarInstrucciones(string nombreArchivo) {
    string linea;
    ifstream MyReadFile(nombreArchivo);
    bool primeraLinea = true;
    int* elementos[5] = {&pid, &ax, &bx, &cx, &quantum};

    while (getline(MyReadFile, linea)) {
        if (primeraLinea) {
            smatch match;
            string patrones[5] = {R"(PID:\s*(\d+))",R"(AX=\s*(\d+))",R"(BX=\s*(\d+))",R"(CX=\s*(\d+))",R"(Quantum=\s*(\d+))"};

            for (int i = 0; i < 5; i++) {
                regex patron(patrones[i]);
                if (regex_search(linea, match, patron)) {
                    *elementos[i] = stoi(match[1]);
                    // cout << match[1] << endl;
                } else {
                    cout << "Instrucciones ingresadas erróneamente" << endl;
                    break;
                }
            }
            estado = "Listo";
            primeraLinea = false;
            continue;
        }
        // cout<<pid<<endl;
        instrucciones.push_back(linea);
    }

    MyReadFile.close();
}

int Proceso::getPID(){
    return pid;
}

int Proceso::getQuantum(){
    return quantum;
}
