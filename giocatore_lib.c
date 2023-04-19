#include "giocatore.h"

giocatore crea_lista_giocatori(){
	//Iniziallizza una variabile di tipo giocatore e alloca la memoria necessaria
	giocatore mio_giocatore = (giocatore)malloc(sizeof(struct giocatore));
	if(mio_giocatore == NULL)
		return NULL;
	//Inizializza i puntatori head e tail a NULL
	mio_giocatore->giocatori_head = NULL;
	mio_giocatore->giocatori_tail = NULL;
	return mio_giocatore;
}

void modifica_nome_giocatore(struct nodo_giocatore* mio_giocatore, char nome[], char cognome[]){
	strcpy((mio_giocatore->nome), nome);
	strcpy((mio_giocatore->cognome), cognome);
}


