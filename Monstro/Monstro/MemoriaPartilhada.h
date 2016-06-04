#include "Jogo.h"

//lembrar que isto nao passa ponteiros, necessario valores normais
//objetivo, ter um mapa partilhado sem ponteiros, e o servidor actualiza esse mapa quando um jogador joga, e este mapa actualiza o mapa do servidor quando o monstro joga
typedef struct MemoriaPartilhada{
	int visibilidade;//0 invisivel/1 visivel

	int muro;//0 se este bloco não for muro/ 1 se este bloco for muro / 2 se for porta

	Jogador jogador;
	Monstro monstro;

	//objectos
	int pedras;//unico que pode ser mais que 1
	int vitamina;//max 1
	int orangebull;//max 1
	int cafeina;//max 1

	//mutex para nao mexerem todos ao mesmo tempo
	HANDLE hmutex;
}MemoriaPartilhada;


void InicializaMonstro(Monstro *monstro,MemoriaPartilhada *mp);

//memoria a ser partilhada
//falta passar o mutex