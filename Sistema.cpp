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


    ifstream file("procesos/procesos.txt");
    if (!file) {
        cout << "Error abriendo archivo!" << endl;
        return 0;
    }
    
    queue<int> roundRobin;
    unordered_map<int,Proceso> procesos;
    string line;

    while (getline(file, line)) { 
        cout << line << endl;
        Proceso p(line);
        procesos[p.getPID()] = p;
        roundRobin.push(p.getPID());
    }

    file.close();

    return 0;

    while(!roundRobin.empty()){
        Proceso &procesoTemp = procesos[roundRobin.front()];
        roundRobin.pop();

        int quantum = procesoTemp.getQuantum();
        
        for(int i = 0; i< quantum;i++){
            if(procesoTemp.getEstado()=="Finished") break;
            cpu.correr(procesoTemp);
        }
        if(procesoTemp.getEstado()!="Finished") roundRobin.push(procesoTemp.getPID());
    }
    
    return 0;


}

