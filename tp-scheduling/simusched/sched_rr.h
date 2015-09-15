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
		bool estaBloqueado(int pid);
		void SiEstaBloqueadoQuitar(int pid);
		
		vector<int> pid_cores;
		vector<int> pid_bloqueados;  //Los procesos que estan bloqueados.
		vector<int> cpu_quantum;
		vector<int> quantum_restantes;
		int cant_cores;
		queue<int> enEspera;  //Cola global donde estan los que estan en ready
};

#endif
