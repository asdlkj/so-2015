#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include "basesched.h"

using namespace std;

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		struct core
		{
			int pidActual;
			int quantum_restante_actual; 
			queue<int> enEspera;
			bool bloqueado;
		};

		vector<core> nucleos;
		int cant_cores;
		int cpu_quantum;
};

#endif
