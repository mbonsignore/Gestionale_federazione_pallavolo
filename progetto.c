#include <stdio.h>
#include <stdlib.h>
#include "giocatore.h"
#include "campionato.h"
#include "calendario.h"

int main(){
	int a, controllo = 0, codice_squadra, inizializzazione = 0;
	campionato mio_campionato;
	int errore;
	char nome_squadra[30];
	char palestra_casa[30];
	squadra squadra_cercata;
	char squadra_c[30];
	struct nodo_giocatore* giocatore_cercato;
	char nome_c[30], cognome_c[30];
	char nome_giocatore[30];
	char cognome_giocatore[30];
	char nome_g_modifica[30];
	char cognome_g_modifica[30];
	int stato_modifica;
	char nome_modifica[30];
	char palestra_modifica[30];
	int cartellino, cartellino_cercato, cod_prestante;
	char nome_scambio_uno[30], nome_scambio_due[30];
	char cognome_scambio_uno[30], cognome_scambio_due[30];
	struct nodo_giocatore* scambio_uno;
	struct nodo_giocatore* scambio_due;
	squadra squadra_scambio_uno, squadra_scambio_due;
	char nome_prestito[30];
	char cognome_prestito[30];
	struct nodo_giocatore* giocatore_prestito;
	squadra squadra_prestante;
	char squadra_ricevente_nome[30];
	squadra squadra_ricevente;
	struct nodo_giocatore* g;
	char nome_vendita[30];
	char cognome_vendita[30];
	struct nodo_giocatore* giocatore_vendita;
	squadra squadra_venditrice;
	squadra squadra_acquirente;
	calendario mio_calendario;
	squadra p;
	int controllo_calendario, controllo_simula_partite;
	//Il menu e' composto da cicli infiniti che terminano solo con apposito comando
	printf("\nPROGRAMMA GESTIONALE FEDERAZIONE DI PALLAVOLO\n");
	for(;;){
		printf("\nMENU PRINCIPALE");
		printf("\n\n(1) Carica dati da file \n(2) Crea campionato \n(3) Crea nuova squadra \n(4) Stampa lista squadre \n(5) Cerca \n(6) Mercato \n(7) Campionato \n(8) Salva e termina\n");
		printf("Inserisci comando: ");
		scanf("%d", &a);
		switch(a){
			case 1:
			if(inizializzazione == 1){
				printf("\nCampionato gia' creato");
				break;
			}
			mio_campionato = crea_campionato();
			if (mio_campionato == NULL)
				printf("C'e' stato un errore nell'allocazione della memoria");
			mio_campionato = carica_dati(mio_campionato);
			inizializzazione = 1;
			break;
			case 2:
			//Inizializzazione e' una variabile che mi permette di vedere se il campionato e' gia' stato inizializzato
			if(inizializzazione == 1){
				printf("\nCampionato gia' creato");
				break;
			}
			mio_campionato = crea_campionato();
			inizializzazione = 1;
			if (mio_campionato == NULL)
				printf("C'e' stato un errore nell'allocazione della memoria");
			break;
			case 3:
			//Controllo se il campionato e' stato inizializzato
			if(inizializzazione != 1){
				printf("\nPrima devi creare il campionato");
				break;
			}
			//Chiedo in input all'utente i dati della squadra e controllo che non esista gia' una squadra con lo stesso nome o codice squadra
			printf("\nInserisci il nome della squadra: ");
			scanf("%s", nome_squadra);
			squadra check = cerca_squadra_nome(mio_campionato, nome_squadra);
			if(check != NULL){
				printf("\nNome squadra gia' esistente");
				break;
			}
			printf("\nInserisci il nome della palestra di casa: ");
			scanf("%s", palestra_casa);
			printf("\nInserisci il codice della squadra, compreso tra 1 e 50: ");
			scanf("%d", &codice_squadra);
			check = cerca_squadra_codice(mio_campionato, codice_squadra);
			if(check != NULL){
				printf("\nCodice squadra gia' in uso");
				break;
			}
			errore = inserisci_squadra_ordinato(mio_campionato, codice_squadra, nome_squadra, palestra_casa);
			if(errore == 1)
				printf("C'e' stato un errore nell'allocazione della memoria");
			break;
			case 4:
			//Stampo la lista delle squadre
			if(inizializzazione != 1){
				printf("\nPrima devi creare il campionato");
				break;
			}
			stampa_lista_squadre(mio_campionato);
			break;
			case 5:
			//Apre il menu di ricerca
			if(inizializzazione != 1){
				printf("\nPrima devi creare il campionato");
				break;
			}
			for(;;){
				if(controllo == 1){
					controllo = 0;
					break;
				}
				printf("\n\nMENU DI RICERCA");
				printf("\n\n(1) Cerca squadra per nome\n(2) Cerca squadra per codice\n(3) Cerca giocatore per nome e cognome\n(4) Cerca giocatore per cartellino\n(5) Trona indietro\n");
				printf("Inserisci il comando: ");
				scanf("%d", &a);
				switch(a){
					case 1:
					//Chiede in input il nome della squadra da cercare e se esiste ne apre il menu squadra
					printf("\nInserisci il nome della squadra che vuoi cercare: ");
					scanf("%s", squadra_c);
					squadra_cercata = cerca_squadra_nome(mio_campionato, squadra_c);
					if(squadra_cercata == NULL){
						printf("\nRicerca non andata a buon fine");
						break;
					}
					for(;;){
						if(controllo == 1){
							controllo = 0;
							break;
						}
						printf("\n\nMENU SQUADRA");
						printf("\n\n(1) Stampa info squadra\n(2) Stampa lista giocatori\n(3) Inserisci nuovo giocatore\n(4) Modifica nome squadra\n(5) Modifica palestra di casa\n(6) Ritira squadra dalla federazione\n(7) Torna indietro\n");
						printf("Inserisci il comando: ");
						scanf("%d", &a);
						switch(a){
							case 1:
							//Stampa le informazioni della squadra
							stampa_info_squadra(squadra_cercata);
							break;
							case 2:
							//Stampa la lista dei giocatori
							stampa_lista_giocatori(squadra_cercata, mio_campionato);
							break;
							case 3:
							//Chiede in input i dati del nuovo giocatore e se non sono gia' stati utilizzati aggiunge il giocatore alla lista dei giocatori della squadra
							printf("\nInserisci il nome del giocatore: ");
							scanf("%s", nome_giocatore);
							printf("\nInserisci il cognome del giocatore: ");
							scanf("%s", cognome_giocatore);
							struct nodo_giocatore* check = cerca_giocatore_nome_cognome(mio_campionato, nome_giocatore, cognome_giocatore);
							if(check != NULL){
								printf("\nNome e cognome già presenti nel database");
								break;
							}
							printf("\nInserisci il numero del cartellino: ");
							scanf("%d", &cartellino);
							check = cerca_giocatore_cartellino(mio_campionato, cartellino);
							if(check != NULL){
								printf("\nCartellino gia' in uso");
								break;
							}
							errore = inserisci_giocatore_ordinato(squadra_cercata, cartellino, nome_giocatore, cognome_giocatore);
							if(errore == 1)
								printf("C'e' stato un errore nell'allocazione di memoria");
							break;
							case 4:
							//chiede in input il nuovo nome da mettere alla squadra e se non e' gia stato utilizzato lo modifica
							printf("\nInserisci il nuovo nome per la squadra: ");
							scanf("%s", nome_modifica);
							squadra check_1 = cerca_squadra_nome(mio_campionato, nome_modifica);
							if(check_1 != NULL){
								printf("\nNome squadra gia' esistente");
								break;
							}
							modifica_nome_squadra(squadra_cercata, nome_modifica);
							break;
							case 5:
							//Chiede in input il nuovo nome da mettere alla palestra e lo modifica
							printf("\nInserisci il nuovo nome per la palestra: ");
							scanf("%s", palestra_modifica);
							modifica_palestra(squadra_cercata, palestra_modifica);
							break;
							case 6:
							//Elimina la squadra
							elimina_squadra(mio_campionato, squadra_cercata);
							controllo = 1;
							break;
							case 7:
							controllo = 1;
							break;
							default:
							break;
						}
					}
					break;
					case 2:
					//Chiede in input il codice della squadra da cercare e se esiste ne apre il menu squadra
					printf("\nInserisci il codice della squadra che vuoi cercare: ");
					scanf("%d", &codice_squadra);
					squadra_cercata = cerca_squadra_codice(mio_campionato, codice_squadra);
					if(squadra_cercata == NULL){
						printf("\nRicerca non andata a buon fine");
						break;
					}
					for(;;){
						if(controllo == 1){
							controllo = 0;
							break;
						}
						printf("\n\nMENU SQUADRA");
						printf("\n\n(1) Stampa info squadra\n(2) Stampa lista giocatori\n(3) Inserisci nuovo giocatore\n(4) Modifica nome squadra\n(5) Modifica palestra di casa\n(6) Ritira squadra dalla federazione\n(7) Torna indietro\n");
						printf("Inserisci il comando: ");
						scanf("%d", &a);
						switch(a){
							case 1:
							//Stampa le informazioni della squadra
							stampa_info_squadra(squadra_cercata);
							break;
							case 2:
							//Stampa la lista dei giocatori
							stampa_lista_giocatori(squadra_cercata, mio_campionato);
							break;
							case 3:
							//Chiede in input i dati del nuovo giocatore e se non sono gia' stati utilizzati aggiunge il giocatore alla lista dei giocatori della squadra
							printf("\nInserisci il nome del giocatore: ");
							scanf("%s", nome_giocatore);
							printf("\nInserisci il cognome del giocatore: ");
							scanf("%s", cognome_giocatore);
							struct nodo_giocatore* check = cerca_giocatore_nome_cognome(mio_campionato, nome_giocatore, cognome_giocatore);
							if(check != NULL){
								printf("\nNome e cognome già presenti nel database");
								break;
							}
							printf("\nInserisci il numero del cartellino: ");
							scanf("%d", &cartellino);
							check = cerca_giocatore_cartellino(mio_campionato, cartellino);
							if(check != NULL){
								printf("\nCartellino gia' in uso");
								break;
							}
							errore = inserisci_giocatore_ordinato(squadra_cercata, cartellino, nome_giocatore, cognome_giocatore);
							if(errore == 1)
								printf("C'e' stato un errore nell'allocazione di memoria");
							break;
							case 4:
							//chiede in input il nuovo nome da mettere alla squadra e se non e' gia stato utilizzato lo modifica
							printf("\nInserisci il nuovo nome per la squadra: ");
							scanf("%s", nome_modifica);
							squadra check_1 = cerca_squadra_nome(mio_campionato, nome_modifica);
							if(check_1 != NULL){
								printf("\nNome squadra gia' esistente");
								break;
							}
							modifica_nome_squadra(squadra_cercata, nome_modifica);
							break;
							case 5:
							//Chiede in input il nuovo nome da mettere alla palestra e lo modifica
							printf("\nInserisci il nuovo nome per la palestra: ");
							scanf("%s", palestra_modifica);
							modifica_palestra(squadra_cercata, palestra_modifica);
							break;
							case 6:
							//Elimina la squadra
							elimina_squadra(mio_campionato, squadra_cercata);
							controllo = 1;
							break;
							case 7:
							controllo = 1;
							break;
							default:
							break;
						}
					}
					break;
					case 3:
					//Chiede in input il nome del giocatore da cercare e se esiste ne apre il menu giocatore
					printf("\nInserisci il nome del giocatore che vuoi cercare: ");
					scanf("%s", nome_c);
					printf("\nInserisci il cognome del giocatore che vuoi cercare: ");
					scanf("%s", cognome_c);
					giocatore_cercato = cerca_giocatore_nome_cognome(mio_campionato, nome_c, cognome_c);
					if(giocatore_cercato == NULL){
						printf("\nRicerca non andata a buon fine");
						break;
					}
					for(;;){
						if(controllo == 1){
							controllo = 0;
							break;
						}
						printf("\n\nMENU GIOCATORE");
						printf("\n\n(1) Stampa info giocatore\n(2) Modifica nome e cognome\n(3) Modifica contratto\n(4) Elimina giocatore\n(5) Torna indietro\n");
						printf("Inserisci il comando: ");
						scanf("%d", &a);
						switch(a){
							case 1:
							//Stampa le informazioni del giocatore
							stampa_info_giocatore(mio_campionato, giocatore_cercato);
							break;
							case 2:
							//Chiede in input il nuovo nome e cognome del giocatore e se non sono gia' stati utilizzati li modifica
							printf("\nInserisci il nuovo nome per il giocatore: ");
							scanf("%s", nome_g_modifica);
							printf("\nInserisci il nuovo cognome per il giocatore: ");
							scanf("%s", cognome_g_modifica);
							struct nodo_giocatore* check = cerca_giocatore_nome_cognome(mio_campionato, nome_g_modifica, cognome_g_modifica);
							if(check != NULL){
								printf("\nNome e cognome già presenti nel database");
								break;
							}
							modifica_nome_giocatore(giocatore_cercato, nome_g_modifica, cognome_g_modifica);
							break;
							case 3:
							//Chiede in input che tipo di modifica al contratto del giocatore si vuole effettuare
							printf("\n(1) Di proprietà\n(2) In prestito");
							printf("\nInserisci il codice del nuovo tipo di contratto: ");
							scanf("%d", &stato_modifica);
							if(stato_modifica == 1)
								modifica_contratto(mio_campionato, giocatore_cercato, stato_modifica, cod_prestante);
							else if(stato_modifica == 2){
								printf("\nInserisci il codice della squadra prestante: ");
								scanf("%d", &cod_prestante);
								squadra check = cerca_squadra_codice(mio_campionato, cod_prestante);
								if(check == NULL){
									printf("\nSquadra inesistente");
									break;
								}
								modifica_contratto(mio_campionato, giocatore_cercato, stato_modifica, cod_prestante);
							}
							else
								printf("\nCodice non valido");
							break;
							case 4:
							//Elimina il giocatore
							squadra_cercata = cerca_squadra_codice(mio_campionato, (giocatore_cercato->cod_squadra));
							elimina_giocatore(squadra_cercata, giocatore_cercato);
							controllo = 1;
							break;
							case 5:
							controllo = 1;
							break;
							default:
							break;
						}
					}
					break;
					case 4:
					//Chiede in input il numero del cartellino del giocatore da cercare e se esiste ne apre il menu giocatore
					printf("\nInserisci il numero del cartellino del giocatore che vuoi cercare: ");
					scanf("%d", &cartellino_cercato);
					giocatore_cercato = cerca_giocatore_cartellino(mio_campionato, cartellino_cercato);
					if(giocatore_cercato == NULL){
						printf("\nRicerca non andata a buon fine");
						break;
					}
					for(;;){
						if(controllo == 1){
							controllo = 0;
							break;
						}
						printf("\n\nMENU GIOCATORE");
						printf("\n\n(1) Stampa info giocatore\n(2) Modifica nome e cognome\n(3) Modifica contratto\n(4) Elimina giocatore\n(5) Torna indietro\n");
						printf("Inserisci il comando: ");
						scanf("%d", &a);
						switch(a){
							case 1:
							//Stampa le informazioni del giocatore
							stampa_info_giocatore(mio_campionato, giocatore_cercato);
							break;
							case 2:
							//Chiede in input il nuovo nome e cognome del giocatore e se non sono gia' stati utilizzati li modifica
							printf("\nInserisci il nuovo nome per il giocatore: ");
							scanf("%s", nome_g_modifica);
							printf("\nInserisci il nuovo cognome per il giocatore: ");
							scanf("%s", cognome_g_modifica);
							struct nodo_giocatore* check = cerca_giocatore_nome_cognome(mio_campionato, nome_g_modifica, cognome_g_modifica);
							if(check != NULL){
								printf("\nNome e cognome già presenti nel database");
								break;
							}
							modifica_nome_giocatore(giocatore_cercato, nome_g_modifica, cognome_g_modifica);
							break;
							case 3:
							//Chiede in input che tipo di modifica al contratto del giocatore si vuole effettuare
							printf("\n(1) Di proprietà\n(2) In prestito");
							printf("\nInserisci il codice del nuovo tipo di contratto: ");
							scanf("%d", &stato_modifica);
							if(stato_modifica == 1)
								modifica_contratto(mio_campionato, giocatore_cercato, stato_modifica, cod_prestante);
							else if(stato_modifica == 2){
								printf("\nInserisci il codice della squadra prestante: ");
								scanf("%d", &cod_prestante);
								squadra check = cerca_squadra_codice(mio_campionato, cod_prestante);
								if(check == NULL){
									printf("\nSquadra inesistente");
									break;
								}
								modifica_contratto(mio_campionato, giocatore_cercato, stato_modifica, cod_prestante);
							}
							else
								printf("\nCodice non valido");
							break;
							case 4:
							//Elimina il giocatore
							squadra_cercata = cerca_squadra_codice(mio_campionato, (giocatore_cercato->cod_squadra));
							elimina_giocatore(squadra_cercata, giocatore_cercato);
							controllo = 1;
							break;
							case 5:
							controllo = 1;
							break;
							default:
							break;
						}
					}
					break;
					case 5:
					controllo = 1;
					break;
					default:
					break;	
				}
			}
			break;
			case 6:
			//Apre il menu di mercato
			if(inizializzazione != 1){
				printf("\nPrima devi creare il campionato");
				break;
			}
			for(;;){
				if(controllo == 1){
					controllo = 0;
					break;
					}
				printf("\n\nMENU DI MERCATO");
				printf("\n\n(1) Effettua scambio\n(2) Effettua prestito\n(3) Effettua vendita\n(4) Torna indietro\n");
				printf("Inserisci il comando: ");
				scanf("%d", &a);
				switch(a){
					case 1:
					//Chiede i dati del primo giocatore e controlla se esiste
					printf("\nInserisci il nome del primo giocatore: ");
					scanf("%s", nome_scambio_uno);
					printf("\nInserisci il cognome del primo giocatore: ");
					scanf("%s", cognome_scambio_uno);
					scambio_uno = cerca_giocatore_nome_cognome(mio_campionato, nome_scambio_uno, cognome_scambio_uno);
					if(scambio_uno == NULL){
						printf("\nGiocatore inesistente");
						break;
					}
					//Chiede i dati del secondo giocatore e controlla se esiste
					printf("\nInserisci il nome del secondo giocatore: ");
					scanf("%s", nome_scambio_due);
					printf("\nInserisci il cognome del primo giocatore: ");
					scanf("%s", cognome_scambio_due);

					scambio_due = cerca_giocatore_nome_cognome(mio_campionato, nome_scambio_due, cognome_scambio_due);
					if(scambio_due == NULL){
						printf("\nGiocatore inesistente");
						break;
					}
					//Effettua lo scambio
					squadra_scambio_uno = cerca_squadra_codice(mio_campionato, scambio_uno->cod_squadra);
					squadra_scambio_due = cerca_squadra_codice(mio_campionato, scambio_due->cod_squadra);
					scambia(squadra_scambio_uno, squadra_scambio_due, scambio_uno, scambio_due);
					break;
					case 2:
					//Chiede i dati del giocatore da cedere in prestito e controlla se esiste
					printf("\nInserisci il nome del giocatore da cedere in prestito: ");
					scanf("%s", nome_prestito);
					printf("\nInserisci il cognome del giocatore da cedere in prestito: ");
					scanf("%s", cognome_prestito);
					giocatore_prestito = cerca_giocatore_nome_cognome(mio_campionato, nome_prestito, cognome_prestito);
					if(giocatore_prestito == NULL){
						printf("\nGiocatore inesistente");
						break;
					}
					squadra_prestante = cerca_squadra_codice(mio_campionato, giocatore_prestito->cod_squadra);
					//Chiede il nome della squadra che ricevera' il giocatore e controlla se esiste
					printf("\nInserisci il nome della squadra che prendera' in prestito il giocatore: ");
					scanf("%s", squadra_ricevente_nome);
					squadra_ricevente = cerca_squadra_nome(mio_campionato, squadra_ricevente_nome);
					if(squadra_ricevente == NULL){
						printf("\nSquadra inesistente");
						break;
					} else if(squadra_ricevente == squadra_prestante){
						printf("\nComando non valido");
						break;
					}
					vendita(squadra_prestante, squadra_ricevente, giocatore_prestito);
					g = cerca_giocatore_nome_cognome(mio_campionato, nome_prestito, cognome_prestito);
					modifica_contratto(mio_campionato, g, 2, squadra_prestante->codice);
					break;
					case 3:
					//Chiede i dati del giocatore da vendere e controlla se esiste
					printf("\nInserisci il nome del giocatore da cedere: ");
					scanf("%s", nome_vendita);
					printf("\nInserisci il cognome del giocatore da cedere: ");
					scanf("%s", cognome_vendita);
					giocatore_vendita = cerca_giocatore_nome_cognome(mio_campionato, nome_vendita, cognome_vendita);
					if(giocatore_vendita == NULL){
						printf("\nGiocatore inesistente");
						break;
					}
					squadra_venditrice = cerca_squadra_codice(mio_campionato, giocatore_vendita->cod_squadra);
					//Chiede il nome della squadra che ricevera' il giocatore e controlla se esiste
					printf("\nInserisci il nome della squadra che acquistera' il giocatore: ");
					scanf("%s", squadra_ricevente_nome);
					squadra_acquirente = cerca_squadra_nome(mio_campionato, squadra_ricevente_nome);
					if(squadra_acquirente == NULL){
						printf("\nSquadra inesistente");
						break;
					}
					vendita(squadra_venditrice, squadra_acquirente, giocatore_vendita);
					break;
					case 4:
					controllo = 1;
					break;
					default:
					break;
				}
			}
			break; 
			case 7:
			//Apre il menu di campionato
			if(inizializzazione != 1){
				printf("\nPrima devi creare il campionato");
				break;
			}
			for(;;){
				if(controllo == 1){
					controllo = 0;
					break;
					}
				printf("\n\nMENU DI CAMPIONATO");
				printf("\n\n(1) Genera calendario\n(2) Simula partite\n(3) Visualizza classifica finale\n(4) Torna indietro\n");
				printf("Inserisci il comando: ");
				scanf("%d", &a);
				switch(a){
					case 1:
					//Conta il numero di squadre per vedere se coincide con il numero di squadre necessario per la funzione
					p = mio_campionato->squadre_head;
					int counter = 0;
					while(p != NULL){
						counter++;
						p = p->next;
					}
					if(((counter % 4) != 0) && (counter != 2)){
						printf("\nPer generare il calendario c'e' bisogno di un numero di squadre pari a 2 o multipli di 4");
						break;
					}
					//Inizializza il calendario e lo riempie
					mio_calendario = crea_calendario();
					genera_calendario(mio_calendario, mio_campionato);
					controllo_calendario = 1;
					break;
					case 2:
					//Controlla che sia stato inizializzato il calendario e simula le partite
					if(controllo_calendario != 1){
						printf("\nDevi prima generare il calendario");
						break;
					}
					simula_partite(mio_campionato, mio_calendario);
					controllo_simula_partite = 1;
					break;
					case 3:
					//Controlla che sia stato inizializzato il calendario e siano state simulate le partite e genera la classifica
					if(controllo_calendario != 1){
						printf("\nDevi prima generare il calendario");
						break;
					}
					if(controllo_simula_partite != 1){
						printf("\nDevi prima simulare le partite");
						break;
					}
					classifica_finale(mio_campionato, mio_calendario);
					break;
					case 4:
					controllo = 1;
					break;
					default:
					break;
				}
			}
			break;
			case 8:
			salva_dati(mio_campionato);
			exit(0);
			break;
			default:
			break;
		}
	}
}


