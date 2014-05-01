
all: BSPExplode BSPDiff
BSPExplode: bspexplode.o gamelump.o overlaylump.o mapflagslump.o
	gcc -o BSPExplode bspexplode.o gamelump.o overlaylump.o mapflagslump.o
BSPDiff: bspdiff.o gamelump.o overlaylump.o mapflagslump.o
	gcc -o BSPDiff bspdiff.o gamelump.o overlaylump.o mapflagslump.o
bspexplode.o: bspexplode.c
	gcc -c bspexplode.c
bspdiff.o: bspdiff.c
	gcc -c bspdiff.c
gamelump.o: lumps/gamelump.c lumps/gamelump.h
	gcc -c lumps/gamelump.c
overlaylump.o: lumps/overlaylump.c lumps/overlaylump.h
	gcc -c lumps/overlaylump.c
mapflagslump.o: lumps/mapflagslump.c lumps/mapflagslump.h
	gcc -c lumps/mapflagslump.c
clean:
	rm *.o *.exe
