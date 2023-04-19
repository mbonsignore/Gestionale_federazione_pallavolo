#include "giocatore.h"
#include "campionato.h"

campionato crea_campionato(){
	//Iniziallizza una variabile di tipo campionato e alloca la memoria necessaria
	campionato mio_campionato = (campionato)malloc(sizeof(struct campionato));
	if (mio_campionato == NULL)
		return NULL;
	//Inizializza i puntatori head e tail a NULL
	mio_campionato->squadre_head = NULL;
	mio_campionato->squadre_tail = NULL;
	return mio_campionato;
}

int inserisci_squadra_ordinato(campionato mio_campionato, int codice, char nome[], char palestra[]){
	//Inizializzo due puntatori che mi serviranno a scorrere la lista per trovare la posizione corretta per l'inserimento
	squadra r = mio_campionato->squadre_head;
	squadra q = mio_campionato->squadre_head;
	//Inizializza un puntatore di tipo squadra e alloca la memoria necessaria
	squadra p;
	p = (squadra)malloc(sizeof(struct squadra));
	if(p == NULL)
		return 1;
	//Riempio il nodo
	p->codice = codice;
	strcpy((p->nome_squadra), nome);
	strcpy((p->palestra), palestra);
	giocatore miei_giocatori = crea_lista_giocatori();
	p->giocatori = miei_giocatori;
	//Caso lista vuota
	if((mio_campionato->squadre_head == NULL) && (mio_campionato->squadre_tail == NULL)){
		p->next = NULL;
		mio_campionato->squadre_head = p;
		mio_campionato->squadre_tail = p;
		return 0;
	}
	//Scorro per trovare posizione corretta
    	while ((q != NULL) && (q->codice < p->codice)){
        	r = q;
        	q = q->next;
    	}
    	//Caso inserimento in testa
   	if(q == mio_campionato->squadre_head){
        	p->next = mio_campionato->squadre_head;
        	mio_campionato->squadre_head = p;
        	return 0;
    	}
    	//Caso inserimento in coda
    	if(q == mio_campionato->squadre_tail){
        	p->next = NULL;
        	q->next = p;
        	mio_campionato->squadre_tail = p;
        	return 0;
    	}
    	//Caso generale
    	r->next = p;
    	p->next = q;
    	return 0;
}

squadra cerca_squadra_nome(campionato mio_campionato, char nome[]){
	squadra p = mio_campionato->squadre_head;
	int x;
	//Scorre la lista finche' non trova la squadra con lo stesso nome
	while((p != NULL) && (x = strcmp((p->nome_squadra), nome) != 0))
		p = p->next;
	if(p == NULL)
		//Squadra non trovata
		return NULL;
	//Squadra trovata, ne restituisce il puntatore
	return p;
}

squadra cerca_squadra_codice(campionato mio_campionato, int codice){
	squadra p = mio_campionato->squadre_head;
	//Scorre la lista finche' non trova la squadra con lo stesso codice
	while((p != NULL) && ((p->codice) != codice))
		p = p->next;
	if(p == NULL)
		//Squadra non trovata
		return NULL;
	//Squadra trovata, ne restituisce il puntatore
	return p;
}

struct nodo_giocatore* cerca_giocatore_cartellino(campionato mio_campionato, int cartellino){
	squadra q = mio_campionato->squadre_head;
	//Scorre la lista giocatori finche' non trova il giocatore con lo stesso cartellino
	while(q != NULL){
			struct nodo_giocatore* p = q->giocatori->giocatori_head;
		while ((p != NULL) && ((p->cartellino) != cartellino)){
			p = p->next;
		}
		if(p != NULL)
			//Giocatore trovato, ne restituisce il puntatore
			return p;
		//Scorre alla squadra successiva
		q = q->next;
	}
	//Giocatore non trovato
	return NULL;
}

struct nodo_giocatore* cerca_giocatore_nome_cognome(campionato mio_campionato, char nome[], char cognome[]){
	squadra q = mio_campionato->squadre_head;
	//Scorre la lista giocatori finche' non trova il giocatore con lo stesso nome e cognome
	while(q != NULL){
		int x, y;
		struct nodo_giocatore* p = q->giocatori->giocatori_head;
		while ((p != NULL) && ((x = strcmp((p->nome), nome) != 0) || (y = strcmp((p->cognome), cognome) != 0))){
			p = p->next;
		}
		if(p != NULL)
			//Giocatore trovato, ne restituisce il puntatore
			return p;
		//Scorre alla squadra successiva
		q = q->next;
	}
	//Giocatore non trovato
	return NULL;
}

void stampa_lista_squadre(campionato mio_campionato){
	squadra p = mio_campionato->squadre_head;
	//i e' un contatore che rappresenta il numero di squadre 
	int i = 1;
	printf("\nLISTA SQUADRE");
	//Scorre la lista squadre e stampa le informazioni relative ad ogni squadra
	while(p != NULL){
		printf("\n%d)Nome: %s", i, p->nome_squadra);
		printf("\n  Codice: %d", p->codice);
		printf("\n  Palestra di casa: %s\n", p->palestra);
		p = p->next;
		i++;
	}
}

void stampa_info_squadra(squadra mia_squadra){
	printf("\nINFO SQUADRA");
	printf("\n\nNome squadra: %s", (mia_squadra->nome_squadra));
	printf("\nPalestra di casa: %s", (mia_squadra->palestra));
	printf("\nCodice squadra: %d", (mia_squadra->codice));
}

void stampa_info_giocatore(campionato mio_campionato, struct nodo_giocatore* mio_giocatore){
	//Stampa le info del giocatore
	printf("\nINFO GIOCATORE");
	printf("\nNome: %s", (mio_giocatore->nome));
	printf("\nCognome: %s", (mio_giocatore->cognome));
	printf("\nCartellino: %d", (mio_giocatore->cartellino));
	squadra a = cerca_squadra_codice(mio_campionato, mio_giocatore->cod_squadra);
	printf("\nSquadra: %s", a->nome_squadra);
	if(mio_giocatore->stato == 1)
		printf("\nStato: di proprieta'");
	else{
		squadra s = cerca_squadra_codice(mio_campionato, mio_giocatore->cod_squadra_prestante);
		if(s == NULL)
			printf("\nStato: di proprieta'");
		else
			printf("\nStato: in prestito da %s", s->nome_squadra);
	}
}

void stampa_lista_giocatori(squadra mia_squadra, campionato mio_campionato){
	//Stampa la lista dei giocatori di una squadra con relative info
	struct nodo_giocatore* p = mia_squadra->giocatori->giocatori_head;
	int i = 1;
	printf("\nLISTA GIOCATORI");
	while(p != NULL){
		printf("\n%d)Nome: %s", i, p->nome);
		printf("\n  Cognome: %s", p->cognome);
		if((p->stato) == 1)
			printf("\n  Stato: di proprieta'\n");
		else{
			squadra s = cerca_squadra_codice(mio_campionato, p->cod_squadra_prestante);
			if(s == NULL)
				printf("\n  Stato: di proprieta'");
			else
				printf("\n  Stato: in prestito da %s", s->nome_squadra);
		}
		p = p->next;
		i++;
	}
}

int inserisci_giocatore_ordinato(squadra mia_squadra, int cartellino, char nome[], char cognome[]){
	//Inizializzo due puntatori che mi serviranno a scorrere la lista per trovare la posizione corretta per l'inserimento
	struct nodo_giocatore* r = mia_squadra->giocatori->giocatori_head;
	struct nodo_giocatore* q = mia_squadra->giocatori->giocatori_head;
	//Inizializza un puntatore di tipo struct nodo_giocatore e alloca la memoria necessaria
	struct nodo_giocatore* p;
	p = (struct nodo_giocatore*)malloc(sizeof(struct nodo_giocatore));
	if(p == NULL) 
        	return 1;
        //Riempio il nodo
        p->cartellino = cartellino;
        p->cod_squadra = mia_squadra->codice;
        strcpy((p->nome), nome);
        strcpy((p->cognome), cognome);
        p->stato = 1;
        p->cod_squadra_prestante = 0;
        //Caso lista vuota
	if((mia_squadra->giocatori->giocatori_head == NULL) && (mia_squadra->giocatori->giocatori_tail == NULL)){
		p->next = NULL;
		mia_squadra->giocatori->giocatori_head = p;
		mia_squadra->giocatori->giocatori_tail = p;
		return 0;
	}
	//Scorro per trovare posizione corretta
    	while ((q != NULL) && (q->cartellino < p->cartellino)){
        	r = q;
        	q = q->next;
    	}
    	//Caso inserimento in testa
   	if(q == mia_squadra->giocatori->giocatori_head){
        	p->next = mia_squadra->giocatori->giocatori_head;
        	mia_squadra->giocatori->giocatori_head = p;
        	return 0;
    	}
    	//Caso inserimento in coda
    	if(q == mia_squadra->giocatori->giocatori_tail){
        	p->next = NULL;
        	q->next = p;
        	mia_squadra->giocatori->giocatori_tail = p;
        	return 0;
    	}
    	//Caso generale
    	r->next = p;
    	p->next = q;
    	return 0;
}

void modifica_nome_squadra(squadra mia_squadra, char nome[]){
	strcpy((mia_squadra->nome_squadra), nome);
}

void modifica_palestra(squadra mia_squadra, char palestra[]){
	strcpy((mia_squadra->palestra), palestra);
}

void elimina_squadra(campionato mio_campionato, squadra mia_squadra){
	//Inizializzo due puntatori che mi servono a scorrere la lista per trovare la squadra da eliminare
	squadra r = mio_campionato->squadre_head;
	squadra q = mio_campionato->squadre_head;
	while(q != mia_squadra){
		r = q;
		q = q->next;
	}
	//Caso elemento in testa
	if(q == mio_campionato->squadre_head)
		mio_campionato->squadre_head = mio_campionato->squadre_head->next;
	//Caso elemento in coda
	if(q == mio_campionato->squadre_tail)
		mio_campionato->squadre_tail = r;
	//Caso generale
	else
		r->next = q->next;
	//Inizializzo due puntatori che mi servono per scorrere la lista giocatori 
	struct nodo_giocatore* t = q->giocatori->giocatori_head;
	struct nodo_giocatore* v = q->giocatori->giocatori_head;
	while(v != NULL){
		v = t->next;
		elimina_giocatore(mia_squadra, t);
		t = v;
	}
	//Quando tutta la lista e' vuota dealloco anche i puntatori head e tail
	giocatore a = q->giocatori;
	free(a);
	free(q);
}

void elimina_giocatore(squadra mia_squadra, struct nodo_giocatore* mio_giocatore){
	//Inizializzo due puntatori che mi servono per scorrere la lista giocatori
	struct nodo_giocatore* r = mia_squadra->giocatori->giocatori_head;
	struct nodo_giocatore* q = mia_squadra->giocatori->giocatori_head;
	while(q != mio_giocatore){
		r = q;
		q = q->next;
	}
	//Caso elemento in testa
	if(q == mia_squadra->giocatori->giocatori_head)
		mia_squadra->giocatori->giocatori_head = mia_squadra->giocatori->giocatori_head->next;
	//Caso elemento in coda
	if(q == mia_squadra->giocatori->giocatori_tail)
		mia_squadra->giocatori->giocatori_tail = r;
	//Caso generale
	else
		r->next = q->next;
	free(q);
}

void modifica_contratto(campionato mio_campionato, struct nodo_giocatore* mio_giocatore, int stato, int cod_prestante){
	//Caso giocatore di proprieta'
	if(stato == 1)
		mio_giocatore->stato = stato;
	//Caso giocatore in prestito
	else{
		squadra s = cerca_squadra_codice(mio_campionato, cod_prestante);
		//Se la squadra prestante e' gia' la squadra del giocatore o non esiste da errore
		if((mio_giocatore->cod_squadra == cod_prestante) || (s == NULL)){
			printf("\nCodice non valido");
			return;	
		}
		mio_giocatore->stato = stato;
		mio_giocatore->cod_squadra_prestante = cod_prestante;
	}
}

void scambia(squadra squadra_uno, squadra squadra_due, struct nodo_giocatore* giocatore_uno, struct nodo_giocatore* giocatore_due){
	inserisci_giocatore_ordinato(squadra_due, giocatore_uno->cartellino, giocatore_uno->nome, giocatore_uno->cognome);
	elimina_giocatore(squadra_uno, giocatore_uno);
	inserisci_giocatore_ordinato(squadra_uno, giocatore_due->cartellino, giocatore_due->nome, giocatore_due->cognome);
	elimina_giocatore(squadra_due, giocatore_due);
}

void vendita(squadra squadra_venditrice, squadra squadra_acquirente, struct nodo_giocatore* mio_giocatore){
	inserisci_giocatore_ordinato(squadra_acquirente, mio_giocatore->cartellino, mio_giocatore->nome, mio_giocatore->cognome);
	elimina_giocatore(squadra_venditrice, mio_giocatore);
}

void salva_dati(campionato mio_campionato){
	//Apro i file in lettura
	FILE* fs = fopen("squadre.txt", "w");
	FILE* fg = fopen("giocatori.txt", "w");
	//Controllo che i file siano stati aperti correttamente
	if((fs == NULL) || (fg == NULL)){
		printf("\nErrore nell'apertura file");
		return;
	}
	squadra s = mio_campionato->squadre_head;
	//Il ciclo scorre le squadre e ogni volta salva su file le informazioni
	while(s != NULL){
		struct nodo_giocatore* g = s->giocatori->giocatori_head;
		fprintf(fs, "%s ", s->nome_squadra);
		fprintf(fs, "%s ", s->palestra);
		fprintf(fs, "%d ", s->codice);
		fprintf(fs, "\n");
		//Il ciclo scorre la lista giocatori della squadra e salva ogni volta i dati di ogni giocatore
		while(g != NULL){
			fprintf(fg, "%s ", g->nome);
			fprintf(fg, "%s ", g->cognome);
			fprintf(fg, "%d ", g->cartellino);
			fprintf(fg, "%d ", g->cod_squadra);
			fprintf(fg, "%d ", g->stato);
			fprintf(fg, "%d ", g->cod_squadra_prestante);
			fprintf(fg, "\n");
			g = g->next;
		}
		s = s->next;
	}
	//Chiudo i file
	fclose(fs);
	fclose(fg);
}

campionato carica_dati(campionato mio_campionato){
	FILE* fs = fopen("squadre.txt", "r");
	FILE* fg = fopen("giocatori.txt", "r");
	if((fs == NULL) || (fg == NULL)){
		printf("\nErrore nell'apertura file");
		return NULL;
	}
	char nome_squadra[30];
	char palestra[30];
	int codice;
	while(fscanf(fs, "%s%s%d\n", nome_squadra, palestra, &codice) != EOF){
		int errore = inserisci_squadra_ordinato(mio_campionato, codice, nome_squadra, palestra);
		if(errore == 1){
			printf("\nC'e' stato un errore nell'allocazione di memoria");
			return NULL;
		}
	}
	char nome[30];
	char cognome[30];
	int cartellino;
	int cod_squadra;
	int stato;
	int cod_squadra_prestante;
	while(fscanf(fg, "%s%s%d%d%d%d\n", nome, cognome, &cartellino, &cod_squadra, &stato, &cod_squadra_prestante) != EOF){
		squadra mia_squadra = cerca_squadra_codice(mio_campionato, cod_squadra);
		int error = inserisci_giocatore_ordinato(mia_squadra, cartellino, nome, cognome);
		if(error == 1){
			printf("\nC'e' stato un errore nell'allocazione di memoria");
			return NULL;
		}
		if(stato != 1){
			struct nodo_giocatore* mio_giocatore = cerca_giocatore_cartellino(mio_campionato, cartellino);
			modifica_contratto(mio_campionato, mio_giocatore, stato, cod_squadra_prestante);
		}	
	}
	fclose(fs);
	fclose(fg);
	return mio_campionato; 
}










