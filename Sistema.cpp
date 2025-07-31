#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Proceso.h"
#include "CPU.h"

using namespace std;



void cargarProcesos(unordered_map<int,Proceso>& procesos, vector<string>& archivosProcesos, queue<int>& roundRobin){
    for(int i =0;i< (int)archivosProcesos.size();i++){
        Proceso p(archivosProcesos[i]);
        roundRobin.push(p.getPID());
        procesos[p.getPID()] = p;
        // cout<<archivosProcesos[i]<<endl;
    }
    cout<<"Procesos cargados en \"RAM\" "<<endl;
}

int main(){

    CPU cpu;
    vector<string> archivosProcesos;
    cout<<"procplanner - Simulación de planificación de procesos."<<endl;
    cout<<"para ejecutar escribe run"<<endl;
    
    // Proceso proceso("/procesos/proceso1.txt");
    string input; 
    do{
        cout<<"escribe el documento que tiene las instrucciones de un proceso"<<endl;
        cin>>input;
        if(input =="run")break;
        input = "procesos/"+input;
        archivosProcesos.push_back(input);
    }while(input!="run");

    for(string s:archivosProcesos) cout<<s<<endl;
    

    queue<int> roundRobin;
    unordered_map<int,Proceso> procesos;
    cargarProcesos(procesos,archivosProcesos,roundRobin);

    while(!roundRobin.empty()){
        Proceso temporal = procesos[roundRobin.front()];
        roundRobin.pop();
        
        int quantum = temporal.getQuantum();
        int ID = temporal.getPID();
        for(int i = 0; i< quantum;i++){
            cpu.correr(procesos[ID]);
        }
        if(temporal.instruccionesPendientes()) roundRobin.push(temporal.getPID());
    }
    
    return 0;

}

