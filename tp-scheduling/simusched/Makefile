export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb -std=c++11
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS) sched_mistery.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

ejercicio1: 
	./simusched Lotes/loteEj1.tsk 1 1 1 SchedFCFS | ./graphsched.py > Lotes/imagenes/Ej1.png 
	./simusched Lotes/loteEj1.tsk 2 1 1 SchedFCFS | ./graphsched.py > Lotes/imagenes/Ej1.png
ejericio2: 
	./simusched Lotes/loteEj2.tsk 1 4 1 SchedFCFS | ./graphsched.py > Lotes/imagenes/Ej3Experimento1.png 
	./simusched Lotes/loteEj2.tsk 2 4 1 SchedFCFS | ./graphsched.py > Lotes/imagenes/Ej3Experimento2.png 
ejercicio3:
	./simusched Lotes/loteEj3.tsk 1 1 1 SchedFCFS | ./graphsched.py > Lotes/imagenes/Ej3Experimento1.png
	./simusched Lotes/loteEj3.tsk 2 1 1 SchedFCFS | ./graphsched.py > Lotes/imagenes/Ej3Experimento1.png 

ejercicio4:
	./simusched Lotes/lote_simple.tsk 1 1 1 SchedRR 10 | ./graphsched.py > Lotes/imagenes/Ej4Experimento1.png 
	./simusched Lotes/lote_simple.tsk 2 1 1 SchedRR 10 10 | ./graphsched.py > Lotes/imagenes/Ej4Experimento2.png
	./simusched Lotes/lote_simple.tsk 2 1 1 SchedRR 10 50 | ./graphsched.py > Lotes/imagenes/Ej4Experimento3.png
	./simusched Lotes/lote_simple2.tsk 1 1 1 SchedRR 10 | ./graphsched.py > Lotes/imagenes/Ej4Experimento4.png 
	./simusched Lotes/lote_simple2.tsk 2 1 1 SchedRR 10 10 | ./graphsched.py > Lotes/imagenes/Ej4Experimento5.png
	./simusched Lotes/lote_simple2.tsk 2 1 1 SchedRR 10 50 | ./graphsched.py > Lotes/imagenes/Ej4Experimento6.png
ejercicio5:
	./simusched Lotes/loteEj5.tsk 1 2 1 SchedRR 2 | ./graphsched.py > Lotes/imagenes/Ej5_q2.png 
	./simusched Lotes/loteEj5.tsk 1 2 1 SchedRR 10 | ./graphsched.py > Lotes/imagenes/Ej5_q10.png 
	./simusched Lotes/loteEj5.tsk 1 2 1 SchedRR 50 | ./graphsched.py > Lotes/imagenes/Ej5_q50.png 
ejercicio6:
	./simusched Lotes/loteEj5.tsk 1 2 1 SchedFCFS | ./graphsched.py > Lotes/imagenes/Ej6.png 
ejercicio7:
	./simusched Lotes/loteEj7.tsk 1 1 1 SchedMistery 2 | ./graphsched.py > Lotes/imagenes/Ej7.png 
	./simusched Lotes/loteEj7.tsk 1 1 1 SchedNoMistery 2 | ./graphsched.py > Lotes/imagenes/Ej7.png 
ejercicio8:
	./simusched Lotes/loteEj8Experimento1.tsk 2 1 1 SchedRR2 5 5| ./graphsched.py > Lotes/imagenes/Ej8Experimento1.png
	./simusched Lotes/loteEj8Experimento2.tsk 2 1 1 SchedRR2 5 5| ./graphsched.py > Lotes/imagenes/Ej8Experimento2.png

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all

