#include "MemoriaPartilhada.h"

#define MAX 256

void JogaMonstro(int argc, LPTSTR argv[]){
	HANDLE hMapFile;
	MemoriaPartilhada *mp;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
	_setmode(_fileno(stderr), _O_TEXT);
#endif

	_tprintf(TEXT("Argumentos : %d %d %d"), atoi(argv[0]), atoi(argv[1]), atoi(argv[2]));

	//teste memoria partilhada
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "TrabalhoSO");
	//nome do mapfile qualquer
	
	if (hMapFile == NULL){
		_tprintf(TEXT("ERRO %d"),GetLastError());
		while (1){
		}
		exit(-1);
	}
	
	mp = (MemoriaPartilhada*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 70*70*sizeof(MemoriaPartilhada));
	
	if (mp == NULL){
		_tprintf(TEXT("ERRO 2"));
		while (1){
		}
		exit(-1);
	}
	
	Monstro monstro;//
	monstro.tipo = atoi(argv[0]);//isto nao deve estar correto
	monstro.N = atoi(argv[1]);
	monstro.clonado = atoi(argv[2]);//se e um clone de outro monstro, ou se e o inicial
	InicializaMonstro(&monstro,mp);
	_tprintf(TEXT("\nMonstro\nPosx:%d\nPosy:%d\n"), monstro.posx, monstro.posy);

	//aqui já temos de ter o jogo partilhado, os array de ponteiros do jogador, e o handle Mutex
	while (mp!=NULL){
		//if poder se mexer
		if (monstro.tipo == 0){
			_tprintf(TEXT("Entrou!\n"));
			mexeDistraido(&monstro, mp);
		}
		else{
			mexeBully(&monstro, mp);
		}
		atacaMonstro(&monstro, mp);
		//fazer aqui um sleep para a lentidao
		Sleep((1000 / monstro.lentidao));
		_tprintf(TEXT("\nMonstro\nPosx:%d\nPosy:%d\nTIPO:%d\n"), monstro.posx, monstro.posy,monstro.tipo);
	}

}














/*
	Movimentaçoes do monstro
*/




//funcoes mexe monstro
void mexeDistraido(Monstro *monstro, MemoriaPartilhada *mp){
	if (Nmonstro == 1){
		srand(time(NULL));
		if (monstro->sentido == 0){//validacao para cima
			if (mp[(monstro->posx - 1) * 70 + monstro->posy].muro == 0){//x-1 cima
				WaitForSingleObject(mp[(monstro->posx - 1) * 70 + monstro->posy].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx - 1) * 70 + monstro->posy].monstro, *monstro);
				monstro->posx = monstro->posx - 1;
				ReleaseMutex(mp[(monstro->posx - 1) * 70 + monstro->posy].hmutex);
			}
		}
		if (monstro->sentido == 1){//validacao para baixo
			if (mp[(monstro->posx + 1) * 70 + monstro->posy].muro == 0){//x+1 baixo
				WaitForSingleObject(mp[(monstro->posx + 1) * 70 + monstro->posy].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx + 1) * 70 + monstro->posy].monstro, *monstro);
				monstro->posx = monstro->posx + 1;
				ReleaseMutex(mp[(monstro->posx + 1) * 70 + monstro->posy].hmutex);
			}
		}
		if (monstro->sentido == 2){//validacao para esquerda
			if (mp[(monstro->posx) * 70 + monstro->posy - 1].muro == 0){//y-1 é para a esquerda
				WaitForSingleObject(mp[(monstro->posx) * 70 + monstro->posy - 1].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx) * 70 + monstro->posy - 1].monstro,*monstro);
				monstro->posy = monstro->posy - 1;
				ReleaseMutex(mp[(monstro->posx) * 70 + monstro->posy - 1].hmutex);
			}
		}
		if (monstro->sentido == 3){//validacao para direita
			if (mp[(monstro->posx) * 70 + monstro->posy + 1].muro == 0){//y+1 é para a direita
				WaitForSingleObject(mp[(monstro->posx) * 70 + monstro->posy + 1].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx) * 70 + monstro->posy + 1].monstro, *monstro);
				monstro->posy = monstro->posy + 1;
				ReleaseMutex(mp[(monstro->posx) * 70 + monstro->posy + 1].hmutex);
			}
		}
		//fazer aqui mudanca de sentido
		monstro->sentido = rand() % 4;//vai de 0 a 3
		Nmonstro = monstro->N;
	}
	else{
		if (monstro->sentido == 0){//validacao para cima
			if (mp[(monstro->posx - 1) * 70 + monstro->posy].muro == 0){//x-1 cima
				WaitForSingleObject(mp[(monstro->posx - 1) * 70 + monstro->posy].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx - 1) * 70 + monstro->posy].monstro, *monstro);
				monstro->posx = monstro->posx - 1;
				ReleaseMutex(mp[(monstro->posx - 1) * 70 + monstro->posy].hmutex);
			}
		}
		if (monstro->sentido == 1){//validacao para baixo
			if (mp[(monstro->posx + 1) * 70 + monstro->posy].muro == 0){//x+1 baixo
				WaitForSingleObject(mp[(monstro->posx + 1) * 70 + monstro->posy].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx + 1) * 70 + monstro->posy].monstro, *monstro);
				monstro->posx = monstro->posx + 1;
				ReleaseMutex(mp[(monstro->posx + 1) * 70 + monstro->posy].hmutex);
			}
		}
		if (monstro->sentido == 2){//validacao para esquerda
			if (mp[(monstro->posx) * 70 + monstro->posy - 1].muro == 0){//y-1 é para a esquerda
				WaitForSingleObject(mp[(monstro->posx) * 70 + monstro->posy - 1].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx) * 70 + monstro->posy - 1].monstro, *monstro);
				monstro->posy = monstro->posy - 1;
				ReleaseMutex(mp[(monstro->posx) * 70 + monstro->posy - 1].hmutex);
			}
		}
		if (monstro->sentido == 3){//validacao para direita
			if (mp[(monstro->posx) * 70 + monstro->posy + 1].muro == 0){//y+1 é para a direita
				WaitForSingleObject(mp[(monstro->posx) * 70 + monstro->posy + 1].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx) * 70 + monstro->posy + 1].monstro, *monstro);
				monstro->posy = monstro->posy + 1;
				ReleaseMutex(mp[(monstro->posx) * 70 + monstro->posy + 1].hmutex);
			}
		}
		Nmonstro = Nmonstro - 1;
	}
}
void mexeBully(Monstro *monstro, MemoriaPartilhada *mp){
	//validacao do campo de visao=7, se tiver algum jogador vai atras dele
	//ver se consigo partilhar a memoria do array de jogadores, seria muito mais facil
	int x,y, diftotalX=0,diftotalY=0, diftotalmin = 14,auxdiftotalX,auxdiftotalY;
	//ver o jogador mais perto e ter com ele
	for (x = -3; x < 3; x++){
		for (y = -3; y < 13; y++){
			auxdiftotalX = 0;
			auxdiftotalY = 0;
			if (mp[(monstro->posx+x) * 70 + monstro->posy+y].jogador.vida>-1){
				auxdiftotalX = mp[((monstro->posx + x)) * 70 + monstro->posy + y].jogador.posx - monstro->posx;
				auxdiftotalY = mp[((monstro->posx + x)) * 70 + monstro->posy + y].jogador.posy - monstro->posy;
				if (auxdiftotalX < 0 && auxdiftotalY < 0){
					if ((auxdiftotalX + auxdiftotalY)*(-1) < diftotalmin){
						diftotalmin = (auxdiftotalX + auxdiftotalY)*(-1);
						diftotalX = auxdiftotalX;
						diftotalY = auxdiftotalY;
					}
				}
				else{
					if (auxdiftotalX < 0){
						if ((auxdiftotalX*(-1) + auxdiftotalY) < diftotalmin){
							diftotalmin = (auxdiftotalX*(-1) + auxdiftotalY);
							diftotalX = auxdiftotalX;
							diftotalY = auxdiftotalY;
						}
					}
					else{
						if (auxdiftotalY < 0){
							if ((auxdiftotalX + auxdiftotalY*(-1)) < diftotalmin){
								diftotalmin = (auxdiftotalX + auxdiftotalY*(-1));
								diftotalX = auxdiftotalX;
								diftotalY = auxdiftotalY;
							}
						}
					}
				}
			}
		}
	}

	
	if (diftotalX != 0 || diftotalY!=0){
		if (mp[(monstro->posx - 1) * 70 + monstro->posy].muro == 0 && diftotalX<0){//x-1 cima
			WaitForSingleObject(mp[(monstro->posx - 1) * 70 + monstro->posy].hmutex, INFINITE);
			inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
			copiaMonstro(&mp[(monstro->posx - 1) * 70 + monstro->posy].monstro, *monstro);
			monstro->posx = monstro->posx - 1;
			ReleaseMutex(mp[(monstro->posx - 1) * 70 + monstro->posy].hmutex);
			_tprintf(TEXT("ENCONTROUUUUUUU!!!!!!!"));
		}
		else{
			if (mp[(monstro->posx + 1) * 70 + monstro->posy].muro == 0 && diftotalX>0){//x+1 baixo
				WaitForSingleObject(mp[(monstro->posx + 1) * 70 + monstro->posy].hmutex, INFINITE);
				inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
				copiaMonstro(&mp[(monstro->posx + 1) * 70 + monstro->posy].monstro, *monstro);
				monstro->posx = monstro->posx + 1;
				ReleaseMutex(mp[(monstro->posx + 1) * 70 + monstro->posy].hmutex);
				_tprintf(TEXT("ENCONTROUUUUUUU!!!!!!!"));
			}
			else{
				if (mp[(monstro->posx) * 70 + monstro->posy - 1].muro == 0 && diftotalY<0){//y-1 é para a esquerda
					WaitForSingleObject(mp[(monstro->posx) * 70 + monstro->posy - 1].hmutex, INFINITE);
					inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
					copiaMonstro(&mp[(monstro->posx) * 70 + monstro->posy - 1].monstro, *monstro);
					monstro->posy = monstro->posy - 1;
					ReleaseMutex(mp[(monstro->posx) * 70 + monstro->posy - 1].hmutex);
					_tprintf(TEXT("ENCONTROUUUUUUU!!!!!!!"));
				}
				else{
					if (mp[(monstro->posx) * 70 + monstro->posy + 1].muro == 0 && diftotalY>0){//y+1 é para a direita
						WaitForSingleObject(mp[(monstro->posx) * 70 + monstro->posy + 1].hmutex, INFINITE);
						inicializaMonstroNull(&mp[(monstro->posx) * 70 + monstro->posy].monstro);
						copiaMonstro(&mp[(monstro->posx) * 70 + monstro->posy + 1].monstro, *monstro);
						monstro->posy = monstro->posy + 1;
						ReleaseMutex(mp[(monstro->posx) * 70 + monstro->posy + 1].hmutex);
						_tprintf(TEXT("ENCONTROUUUUUUU!!!!!!!"));
					}
				}
			}
		}
	}
}

//funcoes ataca monstro
//tira um ponto de saude para si ate aos 16
void atacaMonstro(Monstro *monstro, MemoriaPartilhada *mp){
	TCHAR buf[TAM], executavel[MAX] = TEXT("C:\\Users\\ASUS\\Documents\\Ambiente de Trabalho\\Joao\\universidade3ano\\2semestre\\SO2\\Trabalho Prático\\Monstro\\Monstro\\Debug\\Monstro.exe");
	TCHAR argumentos[MAX];
	if (monstro->tipo == 0){
		_tcscpy(argumentos, TEXT("0 3 1"));
	}
	else{
		_tcscpy(argumentos, TEXT("1 3 1"));
	}
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	if (mp[(monstro->posx) * 70 + monstro->posy].jogador.vida>-1){
		mp[(monstro->posx) * 70 + monstro->posy].jogador.vida = mp[(monstro->posx) * 70 + monstro->posy].jogador.vida - 1;
		monstro->vida = monstro->vida + 1;

		//fazer aqui a condição, se for 16 a vida, começa um novo processo mosntro
		if (monstro->vida == 16){
			//cria novo monstro com 8 de vida
			ZeroMemory(&si, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);
			if (CreateProcess(executavel, argumentos, NULL, NULL, 0, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi) == 0){
				_tprintf(TEXT("\nOcorreu um erro ao iniciar o Monstro!!!!\n\n"));
			}
			monstro->vida = 8;
		}
	}
}