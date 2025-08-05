#include <iostream>
#include "Proceso.h"
#include "CPU.h"
#include <sstream>

using namespace std;

bool isNumber(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}



void CPU::correr(Proceso &proceso){

    vector<int*> elementos = proceso.getElementos();
    string instrucciones = proceso.getInstruccion();
    proceso.setEstado("Running");


    std::cout << "Ejecutando instrucción: " << instrucciones<< " en el Proceso "<< proceso.getPID()<< " Estado: "<<proceso.getEstado() << endl;
    std::cout<<"AX: "<<*elementos[0]<<" Bx: "<<*elementos[1]<<" Cx: "<<*elementos[2]<<endl;

    stringstream ss(instrucciones);
    string instruccion;
    ss>> instruccion;
    string valor1, valor2;
    ss >> valor1;

    if (instruccion == "ADD") {
        ss >> valor2;
        if(isNumber(valor2)){
            int variable1 = valor1[0] - 'A';
            *elementos[variable1] += stoi(valor2);

        }
        else{
            int variable1 = valor1[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            int variable2 = valor2[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            *elementos[variable1] += *elementos[variable2];

        }
        
    } 
    else if (instruccion == "SUB") {    
        ss >> valor2;
        if(isNumber(valor2)){
            int variable1 = valor1[0] - 'A';
            *elementos[variable1] -= stoi(valor2);

        }
        else{
            int variable1 = valor1[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            int variable2 = valor2[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            *elementos[variable1] -= *elementos[variable2];

        }
    }
    else if (instruccion == "INC") {
        int variable1 = valor1[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
        *elementos[variable1] += 1;
    }

    else if (instruccion == "MUL") {
        ss >> valor2;
        if(isNumber(valor2)){
            int variable1 = valor1[0] - 'A';
            *elementos[variable1] *= stoi(valor2);

        }
        else{
            int variable1 = valor1[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            int variable2 = valor2[0] - 'A'; // Convertir 'A', 'B', 'C' a 0, 1, 2
            *elementos[variable1] *= *elementos[variable2];

        }
    }else if (instruccion == "JMP") {
        int salto;
        if(isNumber(valor1)){
        salto = stoi(valor1);
    }
    if (salto >= 0 ) {
        // pc = salto;
    } else {
        // Manejo de error: salto fuera de rango
        std::cout << "Salto fuera de rango: " << salto << std::endl;
    }

    }
    
    if(!proceso.instruccionesPendientes()) proceso.setEstado("Finished");
    else proceso.setEstado("Ready");

    std::cout<<"AX: "<<*elementos[0]<<" Bx: "<<*elementos[1]<<" Cx: "<<*elementos[2]<< " Estado: "<<proceso.getEstado() << endl<<endl;
        
        
    
}

