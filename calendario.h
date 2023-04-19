#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "campionato.h"
#include "giocatore.h"

struct partita{
	int codice_casa;
	int codice_trasferta;
	int set_casa;
	int set_trasferta;
	int giornata;
	struct partita* next;
};

typedef struct partita* partita;

struct calendario{
	partita partita_head;
	partita partita_tail;
};

typedef struct calendario* calendario;

struct posizione{
	int punteggio;
	int codice_squadra;
	struct posizione* next;
};

typedef struct posizione* posizione;

struct classifica{
	posizione posizione_head;
	posizione posizione_tail;
};

typedef struct classifica* classifica;

calendario crea_calendario();
//Alloca dinamicamente due puntatori di tipo struct partita a NULL

int inserimento_partite(calendario mio_calendario, int codice_casa, int codice_trasferta, int giornata);
//Effettua un inserimento in coda nella lista delle partite

int controlla_partita(calendario mio_calendario, int codice_casa, int codice_trasferta);
//Controlla se esistono gia' partite tra due squadre

int controlla_giornata(calendario mio_calendario, int casa, int giornata);
//Controlla se la squadra in questione ha gia' giocato nell'attuale giornata

void genera_calendario(calendario mio_calendario, campionato mio_campionato);
//Genera il calendario degli scontri prendendo in input la lista con le squadre e il numero di giornate e poi lo stampa

void stampa_calendario(campionato mio_campionato, calendario mio_calendario);
//Stampa la lista delle partite

void genera_ritorno(calendario mio_calendario, int giornate, int num_partite_giornata);
//Genera il girone di ritorno del calendario e lo stampa

void simula_partite(campionato mio_campionato, calendario mio_calendario);
//Inserisce casualmente un punteggio ai set di ogni squadra per simulare le partite

void classifica_finale(campionato mio_campionato, calendario mio_calendario);
//Stipula la calssifica finale controllando partita per partita i punti di ogni squadra

classifica crea_classifica();
//Alloca dinamicamente due puntatori di tipo struct posizione a NULL

int inserisci_posizione_ordinato(classifica mia_classifica, int punteggio, int codice_squadra);
//Inserisce nella struttura dati classifica in maniera ordinata le posizioni

void stampa_classifica(classifica mia_classifica, campionato mio_campionato);
//Stampa la classifica finale

void elimina_classifica(classifica mia_classifica);
//Dealloca tutto lo spazio occupato dalla lista classifica in memoria
#endif
