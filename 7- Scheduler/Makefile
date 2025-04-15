all: 	main
		./main


main: main.cpp interpreter.o parser.o pcb.o
	g++ -o main main.cpp interpreter.o parser.o pcb.o

interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

pcb.o: pcb.cpp
	g++ -c pcb.cpp

clean:
	rm *.o main