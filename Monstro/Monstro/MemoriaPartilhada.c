#include "MemoriaPartilhada.h"

void InicializaMonstro(Monstro *monstro,MemoriaPartilhada *mp){
	int auxX, auxY;

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

	do{
		auxX = rand() % 70;//0 a 69
		auxY = rand() % 70;//0 a 69
	} while (mp[auxX * 70 + auxY].muro == 1 || mp[auxX * 70 + auxY].muro == 2);
	monstro->posx = auxX;
	monstro->posy = auxY;

	WaitForSingleObject(mp[auxX * 70 + auxY].hmutex, INFINITE);
	mp[auxX * 70 + auxY].monstro.clonado = monstro->clonado;
	mp[auxX * 70 + auxY].monstro.lentidao = monstro->lentidao;
	mp[auxX * 70 + auxY].monstro.N = monstro->N;
	mp[auxX * 70 + auxY].monstro.posx = monstro->posx;
	mp[auxX * 70 + auxY].monstro.posy = monstro->posy;
	mp[auxX * 70 + auxY].monstro.sentido = monstro->sentido;
	mp[auxX * 70 + auxY].monstro.tipo = monstro->tipo;
	mp[auxX * 70 + auxY].monstro.vida = monstro->vida;
	ReleaseMutex(mp[auxX * 70 + auxY].hmutex);
}


