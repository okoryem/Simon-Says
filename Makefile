INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm

all: simon
simon: main.o input.o output.o
	cc -o simon main.o input.o output.o $(LDFLAGS)

clean:
	rm -f *.o simon
main.o: main.c project.h
	cc -c main.c -I ~/include
input.o: input.c project.h
	cc -c input.c -I ~/include
output.o: output.c project.h
	cc -c output.c -I ~/include

run: simon
	./simon.sh | ./simon
