#include "Jogo.h"


//criar variavel global que endique quando e que pode andar, esta vai ser mudada numa thread atenta a isso

void JogaMonstro(int argc, LPTSTR argv[]){


#ifdef UNICODE
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
	_setmode(_fileno(stderr), _O_TEXT);
#endif

	_tprintf(TEXT("Argumentos : %d %d %d %d %d"), argv[0], argv[1], argv[2], argv[3], argv[4]);

	Jogo jogo;

	Monstro monstro;//
	monstro.tipo = argv[0];//isto nao deve estar correto
	monstro.posx = argv[1];
	monstro.posy = argv[2];//ver se ele ja me manda uma posicao sem parede, ou se vejo aqui
	monstro.N = argv[3];
	monstro.clonado = argv[4];//se e um clone de outro monstro, ou se e o inicial
	InicializaMonstro(&monstro);

	//criar thread que indica se pode andar ou nao

	//aqui já temos de ter o jogo partilhado, os array de ponteiros do jogador, e o handle Mutex
	while (jogo.jogocomecou == 1){
		//if poder se mexer
		if (monstro.tipo == 0){
			mexeDistraido(&monstro, jogo.mapa);
		}
		else{
			mexeBully(&monstro, jogo.mapa);
		}
		atacaMonstro(&monstro, jogo.mapa);
	}

}