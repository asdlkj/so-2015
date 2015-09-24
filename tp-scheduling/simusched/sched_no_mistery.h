#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include <iostream>
#include <list>
#include <utility>
#include <tuple>        // std::tuple, std::get
#include "basesched.h"

using namespace std;

typedef std::tuple<int, bool, int, int>  tarea;	//pid, blokeado, tiempo que corre(total, indice del vector tiempos), tiempo restante del total

class SchedNoMistery : public SchedBase {
	public:
		SchedNoMistery(std::vector<int> argn);
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
		
	private:
		list<tarea> tasks; //tendrá la información de la tarea y si está blokeada o no
		list<tarea>::iterator it;
		vector<int> tiempos;
		bool primero;
		bool primero2;
};

#endif
