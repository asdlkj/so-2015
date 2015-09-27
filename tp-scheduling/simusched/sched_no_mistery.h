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



class SchedNoMistery : public SchedBase {
	public:
		SchedNoMistery(std::vector<int> argn);
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
		
	private:
		struct tarea
		{
			int pid;
			int nivel;
		};
		bool estaBloqueado(int pid);
		tarea Actual;
		int quantumRestante;
		vector<queue<tarea>> tareas;
		vector<int> quantums;
		vector<tarea> bloqueados;


};

#endif
