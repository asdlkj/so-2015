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
		//nucleos[i].bloqueado = false;
		nucleos[i].pidActual = IDLE_TASK;
		nucleos[i].quantum_restantes = 0;
	}
}

SchedRR2::~SchedRR2() {

}

void SchedRR2::load(int pid) {
	//Busco el nucleo que tenga menos procesos.
	int indice_resultado = 0;
	for(int i = 1; i < cant_cores; i++){
		int tamanoIndice = nucleos[indice_resultado].enEspera.size() + nucleos[indice_resultado].pid_bloqueados.size();
		int tamanoi = nucleos[i].enEspera.size() + nucleos[i].pid_bloqueados.size();

		if(nucleos[i].pidActual != IDLE_TASK){
			tamanoi++;
		}
		if(nucleos[indice_resultado].pidActual != IDLE_TASK){
			tamanoIndice++;
		}

		if( tamanoi <  tamanoIndice){
			indice_resultado = i;
		}
	}


	if(!estaBloqueado(nucleos[indice_resultado].pidActual, indice_resultado)){
		nucleos[indice_resultado].enEspera.push(pid);
	}
	else{
		nucleos[indice_resultado].quantum_restantes = cpu_quantum;	
		nucleos[indice_resultado].pidActual = pid;
	}
	
	
	
}

void SchedRR2::unblock(int pid) {
	int i = 0;
	int cpu = dondeSeEncuentraBloqueado(pid);
	bool loEncontre = false;
	while(i < nucleos[cpu].pid_bloqueados.size() && !loEncontre){
		if(nucleos[cpu].pid_bloqueados[i] == pid){
			nucleos[cpu].pid_bloqueados.erase(nucleos[cpu].pid_bloqueados.begin() + i);
			nucleos[cpu].enEspera.push(pid);
			loEncontre = true;
		}
		i++;
	}
}

int SchedRR2::dondeSeEncuentraBloqueado(int pid){
	int cpu;
	bool loEncontre = false;
	for(int i = 0; (i < nucleos.size() && !loEncontre); i++){
		for(int j = 0; (j < nucleos[i].pid_bloqueados.size() && !loEncontre); j++){
			if(nucleos[i].pid_bloqueados[j] == pid){
				loEncontre = true;
				cpu = i;
			}
		}
	}

	return cpu;
}

bool SchedRR2::estaBloqueado(int pid, int cpu){
	bool loEncontre = false;
	int i = 0;
	while(i < nucleos[cpu].pid_bloqueados.size() && !loEncontre){
		if(nucleos[cpu].pid_bloqueados[i] == pid){
			loEncontre = true;
		}
		i++;
	}
	return loEncontre;
}

void SchedRR2::SiEstaBloqueadoQuitar(int pid, int cpu){
	bool loEncontre = false;
	int i = 0;
	while(i < nucleos[cpu].pid_bloqueados.size() && !loEncontre){
		if(nucleos[cpu].pid_bloqueados[i] == pid){
			loEncontre = true;
			nucleos[cpu].pid_bloqueados.erase(nucleos[cpu].pid_bloqueados.begin() + i);
		}
		i++;
	}
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
	if(m == TICK){
		nucleos[cpu].quantum_restantes--;
		if(nucleos[cpu].quantum_restantes <= 0){
			if(nucleos[cpu].pidActual != IDLE_TASK){
				nucleos[cpu].enEspera.push(nucleos[cpu].pidActual);
			}
			if(!nucleos[cpu].enEspera.empty()){
				nucleos[cpu].pidActual = nucleos[cpu].enEspera.front();
				nucleos[cpu].enEspera.pop();
				nucleos[cpu].quantum_restantes = cpu_quantum;	
			}
			
			
		}
	}
	else if(m == BLOCK){
		if(!estaBloqueado(nucleos[cpu].pidActual, cpu)){ //Si no esta bloqueada lo bloqueo
			nucleos[cpu].pid_bloqueados.push_back(nucleos[cpu].pidActual);
			nucleos[cpu].quantum_restantes = 0;	
		}
		
		if(!nucleos[cpu].enEspera.empty()){
			nucleos[cpu].pidActual = nucleos[cpu].enEspera.front();
			nucleos[cpu].enEspera.pop();
			nucleos[cpu].quantum_restantes = cpu_quantum;
		}
		
	}
	else if(m == EXIT){
		SiEstaBloqueadoQuitar(nucleos[cpu].pidActual, cpu);

		
		nucleos[cpu].pidActual = IDLE_TASK;
		nucleos[cpu].quantum_restantes = 0;	

		if(!nucleos[cpu].enEspera.empty()){
			nucleos[cpu].pidActual = nucleos[cpu].enEspera.front();
			nucleos[cpu].enEspera.pop();
			nucleos[cpu].quantum_restantes = cpu_quantum;
		}

	}
	return nucleos[cpu].pidActual;
}
