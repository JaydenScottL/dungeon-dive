dungeondive: main.c roomManip.c stringManip.c
	gcc main.c roomManip.c stringManip.c -o dungeondive.o -lm

clean:
	rm *.o