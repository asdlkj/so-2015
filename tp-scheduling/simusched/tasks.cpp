#include "tasks.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

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
	srand(time(NULL));
	for(int i = 0; i < params[0]; i++ ){
		int tiempoBloqueado = rand()%(params[2] - params[1] +1) + params[1];
		uso_IO(pid, tiempoBloqueado);
	}	
}

	


bool esta(vector<int> arr, int cant, int valor){
	bool resul = false;
	for(int i = 0; !resul && i < cant; i++){
		resul = (arr[i] == valor);
	}
	return resul;
}


void TaskBatch(int pid, vector<int> params){//params: total_cpu y cant_bloqueos
	srand(time(NULL));
	int total_cpu = params[0];
	int cant_bloqueos = params[1];
	vector<int> momentoABloquear(cant_bloqueos);
	int i = 0; 
	//Me armo un arreglo con los momentos donde se va a bloquear
	while(i < cant_bloqueos){
		int valor = rand()%total_cpu;
		if(!esta(momentoABloquear, i, valor)){
			momentoABloquear[i] = valor;
			i++;
		}	
	}
	//Lo ordeno
	sort(momentoABloquear.begin(), momentoABloquear.end());
	//Realizo el proceso de cpu y bloqueos
	i = 0;
	for(int j = 0; j < total_cpu; j++){
		if(momentoABloquear[i] == j){
			uso_IO(pid, 1);
			i++;
		}
		else{
			uso_CPU(pid, 1);
		}
	}

}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskBatch, 2);
}
