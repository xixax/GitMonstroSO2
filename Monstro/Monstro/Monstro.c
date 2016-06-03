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

	if (monstro->clonado==1){
		monstro->vida = 8;
	}

	Nmonstro = monstro->N;
}


