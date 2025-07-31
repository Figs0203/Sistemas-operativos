#include <iostream>
#include "Proceso.h"
#include "CPU.h"

using namespace std;



void CPU::correr(Proceso& proceso){
    proceso.siguienteInstruccion();
}

