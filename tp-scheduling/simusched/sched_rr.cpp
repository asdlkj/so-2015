#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	cant_cores = argn[0];
	cpu_quantum = argn[1];
	for(int i = 0; i < cant_cores; i++){
		pid_cores.push_back(IDLE_TASK);  		//Los cores que no tengan un proceso ejecutando le ponemos la tarea idle
		cores_bloqueados.push_back(false);
		quantum_restantes.push_back(0);

	}

}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	bool encontreUno = false;
	int i = 0;
	while(!encontreUno && i < cant_cores){
		if(pid_cores[i] == IDLE_TASK){
			pid_cores[i] = pid;
			encontreUno = true;
			quantum_restantes[i] = cpu_quantum;
		}
		else{
			i++;
		}
		
	}
	if(i == cant_cores){
		enEspera.push(pid);
	}

}

void SchedRR::unblock(int pid) {
	bool laEncontre = false;
	int i = 0;
	while(i < cant_cores && !laEncontre){   //Busco el core donde se esta ejecutando y lo marco como no bloqueado
		if(pid_cores[i] == pid){
			laEncontre = true;
			cores_bloqueados[i] = false;
		}
		i++;
	}
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	if(m == TICK){
		if(!cores_bloqueados[cpu]){   //Si el core esta ejecutando un proceso bloqueado, entonces no se hace nada.
			quantum_restantes[cpu]--;
			if(quantum_restantes[cpu] == 0){ //Si se me acabo el tiempo, entonces lo guardo en la cola global y pongo el siguiente a ejecutar en ese core
				enEspera.push(pid_cores[cpu]);
				pid_cores[cpu] = enEspera.front();
				enEspera.pop();
				cores_bloqueados[cpu] = false;
				quantum_restantes[cpu] = cpu_quantum;
			}
		}
	}
	else if(m == BLOCK){
		quantum_restantes[cpu]--;
		cores_bloqueados[cpu] = true;   //Lo marco como bloqueado
	}
	else if(m == EXIT){
		pid_cores[cpu] = IDLE_TASK;
		if(cores_bloqueados[cpu] = false){
			cores_bloqueados[cpu] = false;
		}
		if(!enEspera.empty()){
			pid_cores[cpu] = enEspera.front();
			enEspera.pop();
			quantum_restantes[cpu] = cpu_quantum;
		}

	}
	return pid_cores[cpu];
}
