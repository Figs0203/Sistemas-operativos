#include<iostream>
#include <fstream>
#include<vector>
#include<regex>

using namespace std;

// The first thing that the OS must do to run a program is to load its code
// and any static data (e.g., initialized variables) into memory, into the address space of the process.

class Sistema{
      int pid;
    int pc; // Program Counter simulado
    int ax, bx, cx; // Registros simulados
    int quantum;
    string estado; // "Listo", "Ejecutando", "Terminado"
    vector<string> instrucciones;
    vector<string>::iterator it;


public:

    bool instruccionesPendientes(){
        return estado!="Terminado";
    }

    void siguienteInstruccion() {
        // cout<<instrucciones.size()<<endl;
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
                        // std::cout << stoi(match[1]) << std::endl;
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

        // puntero al inicio de las instrucciones, llevará registro de la tarea a ejecutar 
        it = instrucciones.begin();

        // Write to binary file
        ofstream out("data.bin", std::ios::binary);
        if (!out) return;

        // upload the variable values into the RAM/Cache
        // Save fixed-size variables
        out.write(reinterpret_cast<char*>(&ax), sizeof(ax));
        out.write(reinterpret_cast<char*>(&bx), sizeof(bx));
        out.write(reinterpret_cast<char*>(&cx), sizeof(cx));
        out.write(reinterpret_cast<char*>(&pid), sizeof(pid));
        out.write(reinterpret_cast<char*>(&quantum), sizeof(quantum));
        out.write(reinterpret_cast<char*>(&it), sizeof(it));

        // Save vector<string> instrucciones
        size_t size = instrucciones.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size)); // Number of strings

        for (const std::string& str : instrucciones) {
            size_t len = str.size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));        // Write length
            out.write(str.data(), len);                                         // Write characters
        }
        

    }
    


};

int main(){
    Sistema sistema;
    sistema.llenarInstrucciones("procesos/proceso1.txt");
    sistema.siguienteInstruccion();
    // Read from binary file
    int ax,bx,cx,pid,quantum;
    // vector<string>::iterator it;
    std::ifstream in("data.bin", std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open file for reading.\n";
        return 0;
    }
    in.read(reinterpret_cast<char*>(&ax), sizeof(ax));
    cout<<ax<<endl;
    // in.read(reinterpret_cast<char*>(&bx), sizeof(bx));
    // in.read(reinterpret_cast<char*>(&cx), sizeof(cx));
    // in.read(reinterpret_cast<char*>(&pid), sizeof(pid));
    // in.read(reinterpret_cast<char*>(&quantum), sizeof(quantum));
    // in.read(reinterpret_cast<char*>(&it), sizeof(it));

    // std::cout << "Loaded int: " << loadedInt << "\n";
    // std::cout << "Loaded float: " << loadedFloat << "\n";
}


    //     int myInt = 42;
    // float myFloat = 3.14f;

    // // Write to binary file
    // std::ofstream out("data.bin", std::ios::binary);
    // if (!out) return 1;
    // out.write(reinterpret_cast<char*>(&myInt), sizeof(myInt));
    // out.write(reinterpret_cast<char*>(&myFloat), sizeof(myFloat));
    // out.close();

