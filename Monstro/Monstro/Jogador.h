#include "Main.h"

typedef struct Jogador{
	int vida; 
	int lentidao;
	int pedras;//unico objecto que pode acumular at� 15 pedras
	//variavel a indicar se ataca com pedra ou mao

	//posicao
	int posx;
	int posy;
}Jogador;

//fun�oes de constru�ao do jogador e comandos do jogador