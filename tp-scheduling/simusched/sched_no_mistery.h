#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include <iostream>
#include <list>
#include <utility>      // std::pair, std::make_pair
#include <tuple>        // std::tuple, std::get
#include "basesched.h"



using namespace std;

typedef std::tuple<int, int>  tarea;	//pid, tiempo que lleva corriendo
typedef pair<int, int> _pid;	//pid = pair<pid, lista en la q esta (y si la tarea esta blokeada es la lista a la que ira)>


class SchedNoMistery : public SchedBase {
	public:
		SchedNoMistery(std::vector<int> argn);
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
		
	private:
		list<_pid> dicTareas; 
		list<tarea>::iterator it;
		int listaMenor;
		
		vector<int> tiempos;
		vector<list<tarea> > tasks;
};

#endif
