#include "tasks.h"

using namespace std;

void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

void TaskConsola(int pid, vector<int> params){//params: n, bmin y bmax
	for(int i = 0; i < params[0]; i++ ){
		int tiempoBloqueado = (rand()%params[2]) + params[1];
		usa_IO(pid, tiempoBloqueado);
	}	
}

void TaskAlgoritmoComplejo(int pid){
	uso_CPU(pid, 100);
}

void TaskCancionFavorita(int pid){
	for(int i = 0; i < 20; i++){
		usa_IO(pid, 2);
	}
}

void TaskNavegarInternet(int pid){
	for(int i = 0; i < 25; i++){
		usa_IO(pid, 4);
	}
}

void loteRolando(int pidComplejo, int pidCancion, int pidNavegar,  vector<int> params){//
	TaskAlgoritmoComplejo(pidComplejo);
	TaskCancionFavorita(pidCancion);
	TaskNavegarInternet(pidNavegar);
}	

void TaskBatch(int pid, vector<int> params){//params: total_cpu y cant_bloqueos

}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
}
