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
		quantum_restantes.push_back(0);
	}

}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
	bool loEncontre = false;
	int i = 0;
	while(i < cant_cores && !loEncontre){
		if(pid_cores[i] == IDLE_TASK){
			loEncontre = true;
			pid_cores[i] = pid;
			quantum_restantes[i] = cpu_quantum;
		}
		i++;
	}
	if(!loEncontre){
		enEspera.push(pid);
	}

}

void SchedRR::unblock(int pid) {
	bool loEncontre = false;
	int i = 0;
	while(!loEncontre && i < pid_bloqueados.size()){
		if(pid_bloqueados[i] == pid){
			bool algunoLibre = false;
			int j = 0;
			while(j < cant_cores && !algunoLibre){
				if(pid_cores[j] == IDLE_TASK && pid_cores[j] == pid){
					algunoLibre = true;
					pid_cores[j] = pid;
				}
				j++;
			}
			if(!algunoLibre){
				enEspera.push(pid);
			}
			pid_bloqueados.erase(pid_bloqueados.begin() + i);
			loEncontre = true;

		}

		i++;
	}
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	if(m == TICK){
		quantum_restantes[cpu]--;
		if(quantum_restantes[cpu] == 0 && !enEspera.empty()){
			enEspera.push(pid_cores[cpu]);
			pid_cores[cpu] = enEspera.front();
			enEspera.pop();
		}
		quantum_restantes[cpu] = cpu_quantum;
		
	}
	else if(m == BLOCK){
		pid_bloqueados.push_back(pid_cores[cpu]);
		//pid_cores[cpu] = IDLE_TASK;
		if(!enEspera.empty()){
			pid_cores[cpu] = enEspera.front();
			enEspera.pop();
			quantum_restantes[cpu] = cpu_quantum;
		}
		
	}
	else if(m == EXIT){
		pid_cores[cpu] = IDLE_TASK;
		if(!enEspera.empty()){
			pid_cores[cpu] = enEspera.front();
			enEspera.pop();
			quantum_restantes[cpu] = cpu_quantum;
		}

	}
	return pid_cores[cpu];
}
