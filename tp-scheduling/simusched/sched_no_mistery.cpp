#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <list>

using namespace std;


SchedNoMistery::SchedNoMistery(vector<int> argn) {
	tarea id;
	id.pid = IDLE_TASK;
	id.nivel = 0;

	Actual = id;
	quantumRestante = 0;
	//quantums.push_back(1);
	//queue<tarea> q;
	//tareas.push_back(q);
	for(unsigned int i=0; i<argn.size() ;i++){
		queue<tarea> r;
		tareas.push_back(r);
		quantums.push_back(argn[i]);
	}
	
}

void SchedNoMistery::load(int pid) {
	tarea nueva;
	nueva.pid = pid;
	nueva.nivel = 0;
	tareas[0].push(nueva);
}

void SchedNoMistery::unblock(int pid) {
	for(int i = 0; i<bloqueados.size() ;i++){
		if(bloqueados[i].pid == pid){

			tarea desbloqueada = bloqueados[i];
			bloqueados.erase(bloqueados.begin() + i);

			if(desbloqueada.nivel != 0){
				desbloqueada.nivel -= 1; 
				tareas[desbloqueada.nivel].push(desbloqueada);
			}
			else{
				tareas[desbloqueada.nivel].push(desbloqueada);
			}
			break;
		}
	}

}

bool SchedNoMistery::estaBloqueado(int pid){
	for(int i = 0; i<bloqueados.size() ;i++){
		if(bloqueados[i].pid == pid){

			return true;
		}
	}
	return false;
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	if(m == TICK){
		if(quantumRestante > 1){
			quantumRestante--;
			return Actual.pid;
		}
		if(Actual.pid != IDLE_TASK){
			if(Actual.nivel + 1 == tareas.size()){ //Si ya estoy en el ultimo
				tareas[Actual.nivel].push(Actual);
			}
			else{
				Actual.nivel++;
				tareas[Actual.nivel].push(Actual);
			}
				
		}

	}
	else if(m == BLOCK){
		if((!estaBloqueado(Actual.pid))){
			bloqueados.push_back(Actual);
			Actual.pid = IDLE_TASK;
			Actual.nivel = 0;
			quantumRestante = 0;
		}
		//return IDLE_TASK;
	}
	else if(m == EXIT){

	}

	Actual.pid = IDLE_TASK;
	Actual.nivel = 0;

	for(unsigned int i = 0; i<tareas.size() ;i++){  //Busco en las colas la primera que no este vacia.
		if(!tareas[i].empty()){
			Actual = tareas[i].front();
			quantumRestante = quantums[Actual.nivel];
			tareas[i].pop();
			break;
		}
	}

	return Actual.pid;
}
