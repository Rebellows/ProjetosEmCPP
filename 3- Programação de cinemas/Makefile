# Makefile

EXECUTAVEL = app
CFLAGS = -c -std=c++11

all:				${EXECUTAVEL}

${EXECUTAVEL}: 		app3.o Filme.o Endereco.o Cinema.o Programacao.o Aplicacao.o
					@g++ app3.o Filme.o Endereco.o Cinema.o Programacao.o Aplicacao.o -o ${EXECUTAVEL}

app3.o:				app3.cpp Aplicacao.hpp
					@g++ ${CFLAGS} app3.cpp

Aplicacao.o:		Aplicacao.cpp Aplicacao.hpp Cinema.hpp Filme.hpp Programacao.hpp
					@g++ ${CFLAGS} Aplicacao.cpp

Programacao.o:		Programacao.cpp Programacao.hpp Cinema.hpp Filme.hpp
					@g++ ${CFLAGS} Programacao.cpp

Cinema.o:			Cinema.cpp Cinema.hpp Endereco.hpp
					@g++ ${CFLAGS} Cinema.cpp

Endereco.o:			Endereco.cpp Endereco.hpp
					@g++ ${CFLAGS} Endereco.cpp

Filme.o:			Filme.cpp Filme.hpp
					@g++ ${CFLAGS} Filme.cpp


run: 				${EXECUTAVEL}
					@ ./${EXECUTAVEL}

clean :
					@rm -f app3.o Filme.o Endereco.o Cinema.o Programacao.o Aplicacao.o ${EXECUTAVEL}
