#include "Mapa.h"
int total;
int totalnojogo;
int Nmonstro;
Jogador *jogadores[10];//todos os jogadores - mais facil para modificar os parametros depois

typedef struct Jogos{
	Mapa *mapa;
	Jogador jogador;//utilizado para enviar o jogador do cliente

	// _TCHARbuf[256];
	int jogocomecou;//0 nao e 1 sim
}Jogo;


void JogaMonstro(int argc,LPTSTR argv[]);
void mexeDistraido(Monstro *monstro, Mapa *m);
void mexeBully(Monstro *monstro, Mapa *m);
void atacaMonstro(Monstro *monstro, Mapa *m);
