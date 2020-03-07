a.out:sfunc.o main.o
	gcc -g sfunc.o main.o
sfunc.o:sfunc.c skheader.h
	gcc -g -c sfunc.c
main.o:main.c skheader.h
	gcc -g -c main.c
clear:
	rm *.o a.out
