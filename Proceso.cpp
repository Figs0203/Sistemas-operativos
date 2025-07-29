#include <iostream>
#include <vector>
#include <fstream>
#include <regex>


using namespace std;

class Proceso {
    int pid;
    int pc; // Program Counter simulado
    int ax, bx, cx; // Registros simulados
    int quantum;
    string estado; // "Listo", "Ejecutando", "Terminado"
    vector<string> instrucciones;
    vector<string>::iterator it;


public:
    Proceso(string nombreArchivo) {
        llenarInstrucciones(nombreArchivo);
        it = instrucciones.begin();
    }

    bool instruccionesPendientes(){
        return estado!="Terminado";
    }

    void siguienteInstruccion() {
        cout<<instrucciones.size()<<endl;
        while (it != instrucciones.end()) {
            cout << "Ejecutando instrucción: " << *it << endl;
            ++it;
        }
        if(it == instrucciones.end()) estado = "Terminado";
    }


    void llenarInstrucciones(string nombreArchivo){
        string linea;
        ifstream MyReadFile(nombreArchivo);
        bool primeraLinea = true;
        int* elementos[5] = {&pid,&ax, &bx, &cx, &quantum};

        while (getline (MyReadFile, linea)) {
            if(primeraLinea){

                smatch match;
                string patrones[5] = {R"(PID:\s*(\d+))",R"(AX=\s*(\d+))",R"(BX=\s*(\d+))",R"(CX=\s*(\d+))",R"(Quantum=\s*(\d+))"};

                for(int i = 0; i<5;i++){
                    regex patron(patrones[i]);
                    if (std::regex_search(linea,match, patron)) {
                        *elementos[i] = stoi(match[1]);
                        std::cout << stoi(match[1]) << std::endl;
                    } else {
                        std::cout << "Instrucciones ingresadas erroneamente" << std::endl;
                        break;
                    }
                }
                primeraLinea = false;
                continue;
            }
            instrucciones.push_back(linea);
            // cout << linea <<endl;
        }   
        MyReadFile.close();

    }
};

int main() {
    Proceso p("proceso1.txt");
    p.siguienteInstruccion();
    return 0;
}