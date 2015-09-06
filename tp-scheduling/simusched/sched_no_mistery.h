#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include <iostream>
#include <list>
#include <utility>
#include "basesched.h"

using namespace std;

typedef std::pair<int, bool>  tarea;

class SchedNoMistery : public SchedBase {
	public:
		SchedNoMistery(std::vector<int> argn);
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
		
	private:
		list<tarea> tasks; //tendrá la información de la tarea y si está blokeada o no
		list<tarea>::iterator it;
		bool primero;
};

#endif
