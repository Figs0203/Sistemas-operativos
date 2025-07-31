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
    }
    cout<<"Procesos cargados en \"RAM\" "<<endl;
}

int main(){

    // CPU cpu;
    // vector<string> archivosProcesos;
    // cout<<"procplanner - Simulación de planificación de procesos."<<endl;
    // cout<<"para ejecutar escribe run"<<endl;
    
    
    // string input; 
    // do{
    //     cout<<"escribe el documento que tiene las instrucciones de un proceso"<<endl;
    //     cin>>input;
    //     if(input =="run")break;
    //     input = "procesos/"+input;
    //     archivosProcesos.push_back(input);
    // }while(input!="run");

    // for(string s:archivosProcesos) cout<<s<<endl;
    

    // queue<int> roundRobin;
    // unordered_map<int,Proceso> procesos;
    // cargarProcesos(procesos,archivosProcesos,roundRobin);

    // while(!roundRobin.empty()){
    //     Proceso procesoTemp = procesos[roundRobin.front()];
    //     roundRobin.pop();
        
    //     int quantum = procesoTemp.getQuantum();
    //     int ID = procesoTemp.getPID();
    //     for(int i = 0; i< quantum;i++){
    //         if(!procesoTemp.instruccionesPendientes()) break;
    //         cpu.correr(procesos[ID]);
    //     }
    //     if(procesoTemp.instruccionesPendientes()) roundRobin.push(procesoTemp.getPID());
    // }
    
    // return 0;

    Proceso p("procesos/proceso1.txt");
    p.siguienteInstruccion();
    p.siguienteInstruccion();
    p.siguienteInstruccion();
    p.siguienteInstruccion();
    p.siguienteInstruccion();


}

