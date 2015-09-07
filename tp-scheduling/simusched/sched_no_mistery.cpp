#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <list>

using namespace std;

typedef std::pair<int, pair<bool, int> >  tarea;	//pid, blokeado/tiempo de ejecucion restante (índice en el vector entrada)

#define BUSY 0
#define FREE 1

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	tiempo = 0;
	primero = true;
	tiempos.push_back(1);
	for (unsigned int i = 0; i < argn.size(); i++)
	{
		tiempos[i+1] = argn[i];
	}
	
}

void SchedNoMistery::load(int pid) {
	//cargo las tareas con su pid + FREE (xq no comienzan blokeadas) y hago it.begin() con el primer load
	tarea tareaAux = make_pair(pid, make_pair(FREE,0));
	tasks.push_back(tareaAux);
	if (primero)
	{
		it = tasks.begin();
		primero = false;
	}
	
}

void SchedNoMistery::unblock(int pid) {	
	int cont = tasks.size();
	while (cont >= 0) //recorre todos y vuelve al punto de partida. al final it está en la misma posición de la que salió.
	{
		if (pid == it->first)
		{
			(it->second).first = FREE;
			//it = tasks.erase(it);
			//tasks.insert(it, tareaAux);
		}
		
		++it;
		if (it == tasks.end())
			it = tasks.begin();
			
		cont--;
	}
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	
	(it->second).second = max((int)tiempos.size()-1, (it->second).second +1);
	
	int pid;
	if (m == BLOCK)
	{
		if (tasks.empty())
			cerr << "m == BLOCK cuando task.empty() == true" << endl;
			
		(it->second).first = BUSY;
		
		++it;
		if (it == tasks.end())
			it = tasks.begin();
	}
	else
	{
		if (m == EXIT)
		{
			if (tasks.empty())
				cerr << "m == EXIT cuando task.empty() == true" << endl;
			else
				it = tasks.erase(it);	//incluye ++it
		}
	}
	//vale para los 3 estados
	if (tasks.empty())
		return IDLE_TASK;

	int cont = tasks.size();
	while ((it->second).first == BUSY && cont > 0)
	{
		++it;
		if (it == tasks.end())
			it = tasks.begin();
			
		cont--;
	}
	if ((it->second).first == BUSY) //recorrio todas las tareas y están todas ocupadas
		pid = IDLE_TASK;
	else
		pid = it->first;
	
	return pid;
}
