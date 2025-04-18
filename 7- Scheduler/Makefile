all: 	main
		./main


main: main.cpp interpreter.o parser.o pcb.o scheduler.o
	g++ -o main main.cpp interpreter.o parser.o pcb.o scheduler.o -Wall

interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

pcb.o: pcb.cpp
	g++ -c pcb.cpp

scheduler.o: scheduler.cpp
	g++ -c scheduler.cpp

clean:
	rm *.o main