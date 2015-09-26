#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <list>

using namespace std;

typedef std::tuple<int, int>  tarea;	//pid, tiempo que lleva corriendo
typedef pair<int, int> _pid;	//pid = pair<pid, lista en la q esta (y si la tarea esta blokeada es la lista a la que ira)>

#define BUSY 0
#define FREE 1
#define _PID get<0>
#define _tiempoCorriendo get<1>


SchedNoMistery::SchedNoMistery(vector<int> argn) {
	cerr << "Inicio" << endl;
	tiempos.push_back(1);
	for (unsigned int i = 0; i < argn.size(); i++)
	{
		cerr << "argn[" << (i) << "] = " << argn[i] << endl;
		tiempos.push_back((int)argn[i]);	//en tiempos guardo los distintos quantum
	}
	cerr << "argn[" << (argn.size()-1) << "] = " << argn[argn.size()-1] << endl;
	cerr << "antes de task.size" << endl;
	tasks.resize((int)argn.size());	//modifico el tama;o de tasks ahora que se exactamente cuantas listas de prioridad tengo
	cerr << "dsp de task.size" << endl;
	listaMenor = 0;
}

void SchedNoMistery::load(int pid) {
<<<<<<< HEAD
	//cargo las tareas con su pid
	tarea tareaAux = make_tuple (pid, 0);
	tasks[0].push_back(tareaAux);
	dicTareas.push_back(make_pair(pid, 0));
=======
	//cargo las tareas con su pid + FREE (xq no comienzan blokeadas) y hago it.begin() con el primer load
	tarea tareaAux = make_tuple (pid, FREE, 0, 1);

	tasks.push_back(tareaAux);
	it = tasks.begin();
	primero = false;

>>>>>>> 36093d8228ad17201e5b92f79f2232e163588a31
}

void SchedNoMistery::unblock(int pid) {
	//cuando una tarea se desblokea busco a que lista agregarla
	for (list<_pid>::iterator it2 = dicTareas.begin(); it2 != dicTareas.end(); ++it2)
	{
		if (pid == it2->first)
		{
			tarea tareaAux = make_tuple(pid, 0);
			tasks[it2->second].push_back(tareaAux);	//no recuero cuanto llevaba corriendo, siempre hace borron y cuenta nueva
			
			if (it2->second < listaMenor)
				{listaMenor = it2->second;}
		}
	}	
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
			cerr << "incha huevo: " << (int)tasks.size() << " =? "  << tasks.size() << endl;
	int pid = current_pid(cpu);
	if (pid != IDLE_TASK)
	{
		for (it = tasks[listaMenor].begin() ; it != tasks[listaMenor].end() ; ++it)
		{
			if (_PID(*it) == pid) //siempre deberia ser la primer tarea de la primer lista utilizada
				{break;}
		}
	}
	 
	if (m == BLOCK)	//no puede (pid == IDLE_TASK)
	{
		//tengo guardado la lista de menor nivel, de dnd se ejecuto la tarea ahora bloqueada
				
				
		//cuando se bloquea pasa a la lista de tareas anterior
		for (list<_pid>::iterator it2 = dicTareas.begin(); it2 != dicTareas.end(); ++it2)
		{
			if (pid == it2->first)
				{it2->second = max(listaMenor - 1, 0);}
		}

		it = tasks[listaMenor].erase(it);	//incluye ++it
		
		if (it == tasks[listaMenor].end())
			tasks[listaMenor].begin();
			

		
		int menorAux = listaMenor;
		
		while((listaMenor + 1) < (int)tasks.size() && tasks[listaMenor].empty())	{listaMenor++;}
		
		//si sale de este while sin la lista correta es porque todas las tareas estan bloqueadas => idle
		if(tasks[listaMenor].empty())
			{return IDLE_TASK;}
		else
		{
			if (menorAux != listaMenor)
				it = tasks[listaMenor].begin();
			
			return _PID(*it);
		}
	}
	else
	{
		if (m == EXIT)	//no puede (pid == IDLE_TASK)
		{
			//tengo guardado la lista de menor nivel, de dnd se ejecuto la tarea ahora bloqueada
			it = tasks[listaMenor].erase(it);	//incluye ++it
			
			if (it == tasks[listaMenor].end())
				tasks[listaMenor].begin();
			
			//diferencia con bloquear: saco la tarea de list<_pid> dicTareas
			for (list<_pid>::iterator it2 = dicTareas.begin() ; it2 != dicTareas.end() ; ++it2)
			{
<<<<<<< HEAD
				if (pid == it2->first)
=======
				cont--;
				if (get<2>(*itMin) < _min && get<1>(*itMin) == FREE)
>>>>>>> 36093d8228ad17201e5b92f79f2232e163588a31
				{
					it2 = dicTareas.erase(it2);	//incluye ++it2
					break;
				}
			}				
			
			int menorAux = listaMenor;
			
			while((listaMenor + 1) < (int)(tasks.size()) && tasks[listaMenor].empty())	{listaMenor++;}
			
			//si sale de este while sin la lista correta es porque todas las tareas estan bloqueadas => idle
			if(tasks[listaMenor].empty())
				{return IDLE_TASK;}
			else
			{
				if (menorAux != listaMenor)
					it = tasks[listaMenor].begin();
				
				return _PID(*it);
			}
		}
		else
		{
			// m == TICK
			if (pid != IDLE_TASK)
			{
				//veo si cambio de tarea
				_tiempoCorriendo(*it)++; //el tick del reloj que acaba de ocurrir
				if (_tiempoCorriendo(*it) >= tiempos[listaMenor])
				{
					//si se le acaba el tiempo paso la tarea a la siguiente lista
					_tiempoCorriendo(*it) = 0;
					tasks[min(listaMenor+1, (int)tasks.size())].push_back(*it);	
					tasks[listaMenor].erase(it);
					
					//ahora veo a q tarea le toca seguir
					
					int menorAux = listaMenor;
					while((listaMenor + 1) < (int)(tasks.size()) && tasks[listaMenor].empty())	{listaMenor++;}
					//si listaMenor al final del while es distinto a menorAux o a menorAux+1 => error
					if(tasks[listaMenor].empty() || (listaMenor != menorAux && listaMenor != menorAux +1))
					{
						cerr << "Error al mover una tarea a la cola siguiente" << endl;
					}
					else
					{
						if (menorAux != listaMenor)
							it = tasks[listaMenor].begin();
						
						return _PID(*it);
					}
				}
				// sino, no pasa nada y sigue corriendo el mismo programa
				return pid;
			}
			else
			{
				//estaba en IDLE. O sea que se desbloqueo una tarea
				it = tasks[listaMenor].begin();
				return _PID(*it);
			}
		}
	}
}
