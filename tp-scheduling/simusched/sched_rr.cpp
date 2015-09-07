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
	enEspera.push(pid);  	//Lo pongo en la cola
}


void SchedRR::unblock(int pid) {
	int i = 0;
	bool loEncontre = false;
	//Busco entre todos los pid bloqueados la posicion del pid que quiero desbloquear y lo quito.
	while(i < pid_bloqueados.size() && !loEncontre){
		if(pid_bloqueados[i] == pid){
			pid_bloqueados.erase(pid_bloqueados.begin() + i);
			enEspera.push(pid); 			//lo pongo de nuevo en la cola
			loEncontre = true;
		}
		i++;
	}
}

bool SchedRR::estaBloqueado(int pid){ //Devuelve true si el proceso esta bloqueado
	bool loEncontre = false;
	int i = 0;
	while(i < pid_bloqueados.size() && !loEncontre){
		if(pid_bloqueados[i] == pid){
			loEncontre = true;
		}
		i++;
	}
	return loEncontre;
}

void SchedRR::SiEstaBloqueadoQuitar(int pid){ //Busca el pid en el cpu y, si lo encuentra, lo quita
	bool loEncontre = false;
	int i = 0;
	while(i < pid_bloqueados.size() && !loEncontre){
		if(pid_bloqueados[i] == pid){
			loEncontre = true;
			pid_bloqueados.erase(pid_bloqueados.begin() + i);
		}
		i++;
	}
}

int SchedRR::tick(int cpu, const enum Motivo m) {
	if(m == TICK){
		quantum_restantes[cpu]--; 
		if(quantum_restantes[cpu] <= 0){  //Si se termino su tiempo:
			if(pid_cores[cpu] != IDLE_TASK){ //Si no es IDLE entonces lo guardo en la cola.
				enEspera.push(pid_cores[cpu]);
			}
			if(!enEspera.empty()){  //Si hay un proceso en la cola, lo cargo para ejecucion.
				pid_cores[cpu] = enEspera.front();
				enEspera.pop();
				quantum_restantes[cpu] = cpu_quantum;	
			}
			
			
		}
	}
	else if(m == BLOCK){
		if(!estaBloqueado(pid_cores[cpu])){ //Si no esta bloqueada, lo bloqueo
			pid_bloqueados.push_back(pid_cores[cpu]);
			quantum_restantes[cpu] = 0;	
		}
		
		if(!enEspera.empty()){ //Si hay un proceso en la cola, lo cargo para ejecucion.
			pid_cores[cpu] = enEspera.front();
			enEspera.pop();
			quantum_restantes[cpu] = cpu_quantum;
		}
		
	}
	else if(m == EXIT){
		SiEstaBloqueadoQuitar(pid_cores[cpu]);  //Suponiendo que se puede terminar sin desbloquear, entonces lo quito

		
		pid_cores[cpu] = IDLE_TASK; //Cargo la tarea IDLE
		quantum_restantes[cpu] = 0;	 //Dejo el quantum en 0 por si en el proximo tick puedo cambiar a otro proceso.

		if(!enEspera.empty()){ //Si hay un proceso en la cola, lo cargo para ejecucion.
			pid_cores[cpu] = enEspera.front();
			enEspera.pop();
			quantum_restantes[cpu] = cpu_quantum;
		}

	}
	return pid_cores[cpu];
}
