#ifndef __SCHED_RR__
#define __SCHED_RR__

#include <vector>
#include <queue>
#include "basesched.h"

using namespace std;

class SchedRR : public SchedBase {
	public:
		SchedRR(std::vector<int> argn);
        ~SchedRR();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);
	private:
		vector<int> pid_cores;
		vector<bool> cores_bloqueados;
		vector<int> quantum_restantes;
		int cant_cores;
		int cpu_quantum;
		queue<int> enEspera;
};

#endif
