#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <list>

using namespace std;

#define BUSY 1
#define FREE 0

SchedNoMistery::SchedNoMistery(vector<int> argn) {
	primero = true;
}

void SchedNoMistery::load(int pid) {
	//cargo las tareas con su pid + FREE (xq no comienzan blokeadas) y hago it.begin() con el primer load
	pair<int,bool> tareaAux = make_pair(pid, FREE);
	tasks.push_back(tareaAux);
	if (primero)
	{
		it = tasks.begin();
		primero = false;
	}
	
}

void SchedNoMistery::unblock(int pid) {
	pair<int,bool> tareaAux = make_pair(pid, FREE);
	
	int cont = tasks.size();
	while (cont >= 0) //recorre todos y vuelve al punto de partida. al final it está en la misma posición de la que salió.
	{
		if (pid == it->first)
		{
			it = tasks.erase(it);
			tasks.insert(it, tareaAux);
		}
		
		++it;
		cont--;
	}
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	int pid;
	if (m == BLOCK)
	{
		it->second = BUSY;
		++it;
	}
	else
	{
		if (m == EXIT)
		{
			if (tasks.empty())
				cerr << "m == EXIT cuando task.empty() == true" << endl;
			else
			{
			it = tasks.erase(it);	//incluye ++it
			if (tasks.size() == 0)
				return IDLE_TASK;
			}
		}
	}
	
	//vale para los 3 estados
	int cont = tasks.size();
	while (it->second == BUSY && cont > 0)
	{
		++it;
		cont--;
	}
	if (it->second == BUSY) //recorrio todas las tareas y están todas ocupadas
	{
		pid = IDLE_TASK;
	}
	else
	{
		pid = it->first;
	}
	
	return pid;
}
