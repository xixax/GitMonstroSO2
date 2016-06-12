#include "Monstro.h"


void inicializaMonstroNull(Monstro *m){
	m->clonado = -1;
	m->lentidao = -1;
	m->N = -1;
	m->posx = -1;
	m->posy = -1;
	m->sentido = -1;
	m->tipo = -1;
	m->vida = -1;
}

void copiaMonstro(Monstro *m1, Monstro m2){
	m1->clonado = m2.clonado;
	m1->lentidao = m2.clonado;
	m1->N = m2.N;
	m1->posx = m2.posx;
	m1->posy = m2.posy;
	m1->sentido = m2.sentido;
	m1->tipo = m2.tipo;
	m1->vida = m2.vida;
}