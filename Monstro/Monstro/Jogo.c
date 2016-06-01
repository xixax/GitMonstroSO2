#include "Jogo.h"


//criar variavel global que endique quando e que pode andar, esta vai ser mudada numa thread atenta a isso

void JogaMonstro(int argc, LPTSTR argv[]){

	Jogo jogo;

	Monstro monstro;//
	monstro.tipo = argv[0];//isto nao deve estar correto
	monstro.posx = argv[1];
	monstro.posy = argv[2];//ver se ele ja me manda uma posicao sem parede, ou se vejo aqui
	monstro.N = argv[3];
	InicializaMonstro(&monstro);

	//criar thread que indica se pode andar ou nao

	//aqui já temos de ter o jogo partilhado
	while (jogo.jogocomecou == 1){
		//if poder se mexer
		if (monstro.tipo == 0){
			//funcao mexedistraido
			mexeDistraido(&monstro, &jogo);
		}
		else{
			mexeBully(&monstro, &jogo);
		}
		atacaMonstro(&monstro, &jogo);
	}

}