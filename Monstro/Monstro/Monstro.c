#include "Jogo.h"

void InicializaMonstro(Monstro *monstro){
	if (monstro->tipo == 0){//distraido
		monstro->lentidao = LentidaoMonstroDistraido;
		monstro->vida = VidaMonstroDistraido;
		monstro->sentido = 0;
	}
	else{
		monstro->lentidao = LentidaoMonstroBully;
		monstro->vida = VidaMonstroBully;
		monstro->sentido = 0;
	}

	Nmonstro = monstro->N;
}

//funcoes mexe monstro
void mexeDistraido(Monstro *monstro, Jogo *j){
	if (Nmonstro == 1){
		if (monstro->sentido == 0){//validacao para cima

		}
		if (monstro->sentido == 1){//validacao para baixo

		}
		if (monstro->sentido == 2){//validacao para esquerda

		}
		if (monstro->sentido == 3){//validacao para direita

		}
		//fazer aqui mudanca de sentido

		Nmonstro = monstro->N;
	}
	else{
		if (monstro->sentido == 0){//validacao para cima

		}
		if (monstro->sentido == 1){//validacao para baixo

		}
		if (monstro->sentido == 2){//validacao para esquerda

		}
		if (monstro->sentido == 3){//validacao para direita

		}
		Nmonstro = Nmonstro - 1;
	}
}
void mexeBully(Monstro *monstro, Jogo *j){
	//validacao do campo de visao=7, se tiver algum jogador vai atras dele
	//ver se consigo partilhar a memoria do array de jogadores, seria muito mais facil
}

//funcoes ataca monstro
//tira um ponto de saude para si ate aos 16
void atacaMonstro(Monstro *monstro, Jogo *j){

}
