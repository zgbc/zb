ZBCLib=../../../../lib/
ZBC=../../../../compile/zbc

all:
	$(ZBC) -lib $(ZBCLib) -o main main.zb
	as main.s -o main.o
	ld main.o -o main

clean:
	rm main main.s
