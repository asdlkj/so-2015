#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <list>

using namespace std;

typedef std::tuple<int, bool, int, int>  tarea;	//pid, blokeado, tiempo que corre(total, indice del vector tiempos), tiempo restante del total

#define BUSY 0
#define FREE 1
#define _PID get<0>(*it)
#define _bloqueo get<1>(*it)
#define _indiceTiempos get<2>(*it)
#define _tiempoRestante get<3>(*it)


SchedNoMistery::SchedNoMistery(vector<int> argn) {
	primero = true;
	tiempos.push_back(1);
	for (unsigned int i = 1; i < argn.size(); i++)
	{
		tiempos.push_back(argn[i]);
	}
	
}

void SchedNoMistery::load(int pid) {
	//cargo las tareas con su pid + FREE (xq no comienzan blokeadas) y hago it.begin() con el primer load
	tarea tareaAux = make_tuple (pid, FREE, 0, 1);
	tasks.push_back(tareaAux);
	if (primero)
	{
		it = tasks.begin();
		primero = false;
	}
	
}

void SchedNoMistery::unblock(int pid) {	
	int cont = tasks.size();
	//cerr << "task actual: " << _PID << " | task a desblokear: " << pid;
	while (cont > 0) //recorre todos y vuelve al punto de partida. al final it está en la misma posición de la que salió.
	{
		if (pid == _PID)
			_bloqueo = FREE; 
		
		++it;
		if (it == tasks.end())
			it = tasks.begin();
			
		cont--;
	}	
	//cerr << " | task donde termina: " << _PID << endl;
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
	int pid;
	if (m == BLOCK)
	{
		if (tasks.empty())
			cerr << "m == BLOCK cuando task.empty() == true" << endl;
			
		_bloqueo = BUSY;
		
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
	while (_bloqueo == BUSY && cont > 0)
	{
		++it;
		if (it == tasks.end())
			it = tasks.begin();
			
		cont--;
	}
	if (_bloqueo == BUSY) //recorrió todas las tareas y están todas ocupadas
		pid = IDLE_TASK;
	else
	{
		//si le quedan tics para correr, le resto uno (el que acaba de ocurrir). sino, averiguo cuantos tendrá en la nueva llamada al proceso.
		if (_tiempoRestante > 1)
			_tiempoRestante = _tiempoRestante -1;
		else
		{
			_indiceTiempos = min(_indiceTiempos +1 , (int)tiempos.size()-1);
			_tiempoRestante = tiempos[_indiceTiempos];

			int _min = _indiceTiempos;
			cont = tasks.size();
			while (cont > 0)	//busco la tarea mas "atrasada"
			{
				if (_indiceTiempos < _min)
				{
					_min = _indiceTiempos;
				}
				
				++it;
				if (it == tasks.end())
					it = tasks.begin();	
				cont--;
			}
			cont = tasks.size();
			while (cont > 0)	//me paro sobre la tarea mas atrasada
			{
				++it;
				if (it == tasks.end())
					it = tasks.begin();
				cont--;
				
				if (_indiceTiempos == _min)
				{
					break;
				}
			}
		}
		pid = _PID;
	}
	return pid;
}
