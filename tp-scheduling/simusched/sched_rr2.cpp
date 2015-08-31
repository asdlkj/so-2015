#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	cant_cores = argn[0];
	cpu_quantum = argn[1];
	nucleos.resize(cant_cores);
	for(int i = 0; i < cant_cores; i++){
		nucleos[i].bloqueado = false;
		nucleos[i].pidActual = IDLE_TASK;
		nucleos[i].quantum_restante_actual = 0;
	}
}

SchedRR2::~SchedRR2() {

}

void SchedRR2::load(int pid) {
	//Busco el nucleo que tenga menos procesos.
	int indice_resultado = 0;
	for(int i = 1; i < cant_cores; i++){
		if(nucleos[i].enEspera.size() < nucleos[indice_resultado].enEspera.size()){
			indice_resultado = i;
		}
	}


	if(nucleos[indice_resultado].pidActual == IDLE_TASK){
		nucleos[indice_resultado].pidActual = pid;
		nucleos[indice_resultado].quantum_restante_actual = cpu_quantum;
	}
	else{
		nucleos[indice_resultado].enEspera.push(pid);
	}
	
}

void SchedRR2::unblock(int pid) {
	bool laEncontre = false;
	int i = 0;
	while(i < cant_cores && !laEncontre){   //Busco el core donde se esta ejecutando y lo marco como no bloqueado
		if(nucleos[i].pidActual == pid){
			laEncontre = true;
			nucleos[i].bloqueado = false;
		}
		i++;
	}
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	if(m == TICK){
		if(!nucleos[cpu].bloqueado){   //Si el core esta ejecutando un proceso bloqueado, entonces no se hace nada.
			nucleos[cpu].quantum_restante_actual--;
			if(nucleos[cpu].quantum_restante_actual == 0){ //Si se me acabo el tiempo, entonces lo guardo en la cola global y pongo el siguiente a ejecutar en ese core
				nucleos[cpu].enEspera.push(nucleos[cpu].pidActual);
				nucleos[cpu].pidActual = nucleos[cpu].enEspera.front();
				nucleos[cpu].enEspera.pop();
				nucleos[cpu].quantum_restante_actual = cpu_quantum;
			}
		}
	}
	else if(m == BLOCK){
		nucleos[cpu].quantum_restante_actual--;
		nucleos[cpu].bloqueado = true;   //Lo marco como bloqueado
	}
	else if(m == EXIT){
		nucleos[cpu].pidActual = IDLE_TASK;
		if(!nucleos[cpu].enEspera.empty()){
			nucleos[cpu].pidActual = nucleos[cpu].enEspera.front();
			nucleos[cpu].enEspera.pop();
			nucleos[cpu].quantum_restante_actual = cpu_quantum;
		}

	}
	return nucleos[cpu].pidActual;
}
