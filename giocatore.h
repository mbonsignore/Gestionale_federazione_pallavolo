#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo_giocatore{
	int cartellino;
	int cod_squadra;
	char nome[30];
	char cognome[30];
	int stato;
	int cod_squadra_prestante;
	struct nodo_giocatore* next;
};

struct giocatore{
	struct nodo_giocatore* giocatori_head;
	struct nodo_giocatore* giocatori_tail;
};

typedef struct giocatore* giocatore;

giocatore crea_lista_giocatori();
//Alloca dinamicamente due puntatori di tipo struct nodo_giocatore a NULL

void modifica_nome_giocatore(struct nodo_giocatore* mio_giocatore, char nome[], char cognome[]);
//Modifica nome e cognome del giocatore cercato


#endif
