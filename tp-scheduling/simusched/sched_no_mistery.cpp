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
	primero2 = true;
	tiempos.push_back(1);
	for (unsigned int i = 1; i < argn.size(); i++)
	{
		tiempos.push_back(argn[i]);
	}
	
}

void SchedNoMistery::load(int pid) {
	//cargo las tareas con su pid + FREE (xq no comienzan blokeadas) y hago it.begin() con el primer load
	tarea tareaAux = make_tuple (pid, FREE, 0, 1);
	/*
	if (primero)
	{
	*/
		tasks.push_back(tareaAux);
		it = tasks.begin();
		primero = false;
	/*
	}
	else
	{
<<<<<<< HEAD
		++it;
		tasks.insert(it,tareaAux);
		//--it;
		//--it;
=======
		tasks.push_back(tareaAux);
		// ++it;
		// tasks.insert(it,tareaAux);
		// --it;
		// --it;
>>>>>>> feb09d4c9eb04223ef87e0a9b8efeca34c4108b9
	}
	*/
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

	if(primero2)
	{
		cerr << "primero2 = true & " << tasks.size() << endl; 
		for (list<tarea>::iterator it2 = tasks.begin(); it2 != tasks.end(); ++it2)
		{
			cerr <<  "_PID = " << get<0>(*it2) << " &  _bloqueo = " << get<1>(*it2) <<  "_indiceTiempos = " << get<2>(*it2) << " &  _tiempoRestante = " << get<3>(*it2) << endl;
		}
		
		it = tasks.begin();
		primero2 = false;
		cerr << _PID << endl;
		return _PID;
	}

		 
	if (m == BLOCK)
	{
		if (tasks.empty())
			cerr << "m == BLOCK cuando task.empty()" << endl;
			
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
				cerr << "m == EXIT cuando task.empty()" << endl;
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
			
			list<tarea>::iterator itMin = tasks.begin();
			int _min = 999;
			int cont = tasks.size();
			while (cont > 0)	//busco la tarea mas "atrasada"
			{
				cont--;
<<<<<<< HEAD
				if (get<2>(*itMin) < _min && get<1>(*itMin) == FREE)
=======
				if (get<2>(*itMin) < _min && get<1>(*itMin) != BUSY)
>>>>>>> feb09d4c9eb04223ef87e0a9b8efeca34c4108b9
				{
					_min = get<2>(*itMin);
				}
				++itMin;
			}
			if (_min == 999)
			{
				return IDLE_TASK;
				cerr << "idle" << endl;
			}
			//it = tasks.begin();
			cont = tasks.size();
			while (cont > 0)	//me paro sobre la primera tarea mas atrasada
			{
				cont--;
				++it;
				if (it == tasks.end())
					it = tasks.begin();
					
				if (_indiceTiempos == _min && get<1>(*it) == FREE)
					break;
			}			
		}
		pid = _PID;
		if (_bloqueo == BUSY)
		{
			cerr << "fuck" << endl;
		}
		
	}
	return pid;
}
