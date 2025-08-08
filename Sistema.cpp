#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Proceso.h"
#include "CPU.h"

using namespace std;


int main(){

    CPU cpu;
    vector<string> archivosProcesos;
    cout<<"procplanner - Simulación de planificación de procesos."<<endl;
    cout<<endl;


    ifstream file("procesos/procesos.txt");
    if (!file) {
        cout << "Error abriendo archivo!" << endl;
        return 0;
    }
    
    queue<int> roundRobin;
    map<int,Proceso> procesos;
    string line;
// cargar diccionario de procesos y queue de PIDs para ejecutar el algoritmo de roundrobin
    while (getline(file, line)) { 
        cout << line << endl;
        Proceso p(line);
        procesos[p.getPID()] = p;
        roundRobin.push(p.getPID());
    }
    // cpu.correr(procesos[1]);

    file.close();

    while(!roundRobin.empty()){
        int pid = roundRobin.front();
        Proceso& procesoTemp = procesos[pid];
        roundRobin.pop();
        int quantum = procesoTemp.getQuantum();

        // por n quantums correr n veces el proceso
        for(int i = 0; i< quantum;i++){
            if(procesoTemp.getEstado()=="Finished") break;
            cpu.correr(procesoTemp);
        // imprimir en el .log
            for(pair<int,Proceso> pares: procesos) pares.second.writeLog();
            ofstream logFile("output.log", ios::app);
            logFile<<"----------------------"<<endl;
        }


        if(procesoTemp.getEstado()!="Finished") {roundRobin.push(pid);procesoTemp.setEstado("Ready");}

        
    }
    
    return 0;


}

