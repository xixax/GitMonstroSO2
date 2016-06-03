#include "MemoriaPartilhada.h"

//criar variavel global que endique quando e que pode andar, esta vai ser mudada numa thread atenta a isso

void JogaMonstro(int argc, LPTSTR argv[]){
	HANDLE hMapFile;
	MemoriaPartilhada *mp;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
	_setmode(_fileno(stderr), _O_TEXT);
#endif

	_tprintf(TEXT("Argumentos : %d %d %d %d %d"), atoi(argv[0]), atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));


	//teste memoria partilhada
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "TrabalhoSO");
	//nome do mapfile qualquer
	
	if (hMapFile == NULL){
		_tprintf(TEXT("ERRO %d"),GetLastError());
		while (1){
		}
		exit(-1);
	}
	
	mp = (MemoriaPartilhada*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MemoriaPartilhada));
	
	if (mp == NULL){
		_tprintf(TEXT("ERRO 2"));
		while (1){
		}
		exit(-1);
	}
	
	_tprintf(TEXT("Memoria partilhada jogador 0 vida:%d"), mp->jogador.vida);
	while (1){
	}

	/*
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
	}*/

}














/*
	Movimentaçoes do monstro
*/




//funcoes mexe monstro
void mexeDistraido(Monstro *monstro, Mapa *m){
	if (Nmonstro == 1){
		srand(time(NULL));
		if (monstro->sentido == 0){//validacao para cima
			if (m[(monstro->posx - 1) * 70 + monstro->posy].muro == 0){//x-1 cima
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx - 1) * 70 + monstro->posy].monstro = monstro;
				monstro->posx = monstro->posx - 1;
			}
		}
		if (monstro->sentido == 1){//validacao para baixo
			if (m[(monstro->posx + 1) * 70 + monstro->posy].muro == 0){//x+1 baixo
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx + 1) * 70 + monstro->posy].monstro = monstro;
				monstro->posx = monstro->posx + 1;
			}
		}
		if (monstro->sentido == 2){//validacao para esquerda
			if (m[(monstro->posx) * 70 + monstro->posy - 1].muro == 0){//y-1 é para a esquerda
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx) * 70 + monstro->posy - 1].monstro = monstro;
				monstro->posy = monstro->posy - 1;
			}
		}
		if (monstro->sentido == 3){//validacao para direita
			if (m[(monstro->posx) * 70 + monstro->posy + 1].muro == 0){//y+1 é para a direita
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx) * 70 + monstro->posy + 1].monstro = monstro;
				monstro->posy = monstro->posy + 1;
			}
		}
		//fazer aqui mudanca de sentido
		monstro->sentido = rand() % 4;//vai de 0 a 3
		Nmonstro = monstro->N;
	}
	else{
		if (monstro->sentido == 0){//validacao para cima
			if (m[(monstro->posx - 1) * 70 + monstro->posy].muro == 0){//x-1 cima
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx - 1) * 70 + monstro->posy].monstro = monstro;
				monstro->posx = monstro->posx - 1;
			}
		}
		if (monstro->sentido == 1){//validacao para baixo
			if (m[(monstro->posx + 1) * 70 + monstro->posy].muro == 0){//x+1 baixo
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx + 1) * 70 + monstro->posy].monstro = monstro;
				monstro->posx = monstro->posx + 1;
			}
		}
		if (monstro->sentido == 2){//validacao para esquerda
			if (m[(monstro->posx) * 70 + monstro->posy - 1].muro == 0){//y-1 é para a esquerda
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx) * 70 + monstro->posy - 1].monstro = monstro;
				monstro->posy = monstro->posy - 1;
			}
		}
		if (monstro->sentido == 3){//validacao para direita
			if (m[(monstro->posx) * 70 + monstro->posy + 1].muro == 0){//y+1 é para a direita
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx) * 70 + monstro->posy + 1].monstro = monstro;
				monstro->posy = monstro->posy + 1;
			}
		}
		Nmonstro = Nmonstro - 1;
	}
}
void mexeBully(Monstro *monstro, Mapa *m){
	//validacao do campo de visao=7, se tiver algum jogador vai atras dele
	//ver se consigo partilhar a memoria do array de jogadores, seria muito mais facil
	int i, diftotal, diftotalmin = 14, pos = -1;
	for (i = 0; i < 10; i++){//pesquisa dos jogadores mais perto
		if (jogadores[i] != NULL){
			diftotal = 100;
			int auxX = jogadores[i]->posx - monstro->posx;
			if (auxX < 0){
				auxX = auxX*-1;
			}
			int auxY = jogadores[i]->posy - monstro->posy;
			if (auxY < 0){
				auxY = auxY*-1;
			}
			diftotal = auxX + auxY;
			if (diftotal < diftotalmin){
				diftotalmin = diftotal;
				pos = i;
			}
		}
	}

	if (pos >= 0){
		if ((monstro->posx - jogadores[i]->posx) < 0 && m[(monstro->posx - 1) * 70 + monstro->posy].muro == 0){//x-1 cima
			m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
			m[(monstro->posx - 1) * 70 + monstro->posy].monstro = monstro;
			monstro->posx = monstro->posx - 1;
		}
		else{
			if ((monstro->posx - jogadores[i]->posx) > 0 && m[(monstro->posx + 1) * 70 + monstro->posy].muro == 0){//x+1 baixo
				m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
				m[(monstro->posx + 1) * 70 + monstro->posy].monstro = monstro;
				monstro->posx = monstro->posx + 1;
			}
			else{
				if ((monstro->posy - jogadores[i]->posy) < 0 && m[(monstro->posx) * 70 + monstro->posy - 1].muro == 0){//y-1 é para a esquerda
					m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
					m[(monstro->posx) * 70 + monstro->posy - 1].monstro = monstro;
					monstro->posy = monstro->posy - 1;
				}
				else{
					if ((monstro->posy - jogadores[i]->posy) > 0 && m[(monstro->posx) * 70 + monstro->posy + 1].muro == 0){//y+1 é para a direita
						m[(monstro->posx) * 70 + monstro->posy].monstro = NULL;
						m[(monstro->posx) * 70 + monstro->posy + 1].monstro = monstro;
						monstro->posy = monstro->posy + 1;
					}
				}
			}
		}

	}
}

//funcoes ataca monstro
//tira um ponto de saude para si ate aos 16
void atacaMonstro(Monstro *monstro, Mapa *m){
	if (m[(monstro->posx) * 70 + monstro->posy].jogador != NULL){
		m[(monstro->posx) * 70 + monstro->posy].jogador->vida = m[(monstro->posx) * 70 + monstro->posy].jogador->vida - 1;
		monstro->vida = monstro->vida + 1;

		//fazer aqui a condição, se for 16 a vida, começa um novo processo mosntro
		if (monstro->vida == 16){
			//cria novo monstro com 8 de vida
			monstro->vida = 8;
		}
	}
}