#ifndef CAMPIONATO_H
#define CAMPIONATO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "giocatore.h"

struct squadra{
	int codice;
	char nome_squadra[30];
	char palestra[30];
	giocatore giocatori;
	struct squadra* next;
};

typedef struct squadra* squadra;

struct campionato{
	squadra squadre_head;
	squadra squadre_tail;
};

typedef struct campionato* campionato;

campionato crea_campionato();
//Alloca dinamicamente due puntatori di tipo struct squadra a NULL

int inserisci_squadra_ordinato(campionato mio_campionato, int codice, char nome[], char palestra[]);
//Alloca dinamicamente un nodo di tipo squadra e lo inserisce ordinatamente rispetto al codice squadra nella lista,
//passando tutti i dati da inserire al suo interno, crea anche una lista giocatori con la funzione crea_lista_giocatori

squadra cerca_squadra_codice(campionato mio_campionato, int codice);
//Cerca una squadra in base al suo codice, restituise un puntatore a struct squadra che vale NULL se la
//squadra non è stata trovata

squadra cerca_squadra_nome(campionato mio_campionato, char nome[]);
//Cerca una squadra in base al suo nome, restituisce un puntatore a struct squadra che vale NULL se la
//squadra non è stata trovata

struct nodo_giocatore* cerca_giocatore_cartellino(campionato mio_campionato, int cartellino);
//Cerca un giocatore in base al suo cartellino, restituisce un puntatore a struct giocatore che vale NULL
//se il giocatore non è stato trovato

struct nodo_giocatore* cerca_giocatore_nome_cognome(campionato mio_campionato, char nome[], char cognome[]);
//Cerca un giocatore in base al suo nome e cognome, restituisce un puntatore a struct giocatore che vale NULL
//se il giocatore non è stato trovato

void stampa_lista_squadre(campionato mio_campionato);
//Stampa la lista di tutte le squadre iscritte al campionato con nome e codice squadra

void stampa_info_squadra(squadra mia_squadra);
//Stampa le informazioni di una squadra ricevendo in ingresso un puntatore a struct squadra

void stampa_info_giocatore(campionato mio_campionato, struct nodo_giocatore* mio_giocatore);
//Stampa le informazioni relative ad un giocatore ricevendo in input un puntatore a struct giocatore

void stampa_lista_giocatori(squadra mia_squadra, campionato mio_campionato);
//Stampa la lista dei giocatori di una squadra ricevendo in ingresso un puntatore a struct squadra

int inserisci_giocatore_ordinato(squadra mia_squadra, int cartellino, char nome[], char cognome[]);
//Alloca dinamicamente un nodo di tipo struct giocatore e lo inserisce ordinatamente rispetto al cartellino, passando tutti i dati
//da inserire al suo interno

void modifica_nome_squadra(squadra mia_squadra, char nome[]);
//Modifica il nome della squadra

void modifica_palestra(squadra mia_squadra, char palestra[]);
//modifica il nome della palestra

void elimina_squadra(campionato mio_campionato, squadra mia_squadra);
//Cancella una squadra dalla lista, restituendo un intero che indica il codice di eventuali errori. Riceve in input il puntatore
//alla squadra da cancellare e il puntatore alla lista.

void elimina_giocatore(squadra mia_squadra, struct nodo_giocatore* mio_giocatore);
//Elimina un giocatore dalla lista della squadra

void modifica_contratto(campionato mio_campionato, struct nodo_giocatore* mio_giocatore, int stato, int cod_prestante);
//Permette di modificare lo stato di un giocatore, da "in prestito" a "di proprietà" e viceversa

void scambia(squadra squadra_uno, squadra squadra_due, struct nodo_giocatore* giocatore_uno, struct nodo_giocatore* giocatore_due);
//Scambia due giocatori tra due squadre

void vendita(squadra squadra_venditrice, squadra squadra_acquirente, struct nodo_giocatore* mio_giocatore);
//Passa un giocatore da una squadra all'altra modificando lo stato in "di proprietà"

void salva_dati(campionato mio_campionato);
//Carica i dati relativi alle sauadre in un file e i dati relativi ai giocatori in un altro file

campionato carica_dati(campionato mio_campionato);
//Carica i dati relativi a squadre e giocatori dai file sul programma
#endif
