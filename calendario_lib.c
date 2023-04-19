#include "calendario.h"
#include "campionato.h"
#include "giocatore.h"

calendario crea_calendario(){
	//Iniziallizza una variabile di tipo calendario e alloca la memoria necessaria
	calendario mio_calendario = (calendario)malloc(sizeof(struct calendario));
	if (mio_calendario == NULL)
		return NULL;
	//Inizializza i puntatori head e tail a NULL
	mio_calendario->partita_head = NULL;
	mio_calendario->partita_tail = NULL;
	return mio_calendario;
}

int inserimento_partite(calendario mio_calendario, int codice_casa, int codice_trasferta, int giornata){
	//Inizializza un puntatore di tipo struct partita* e alloca la memoria necessaria
	struct partita* nuova_partita;
	nuova_partita = (struct partita*)malloc(sizeof(struct partita));
	if(nuova_partita == NULL) 
        	return 1;
    	//Riempio il nuovo nodo
    	nuova_partita->codice_casa = codice_casa;
    	nuova_partita->codice_trasferta = codice_trasferta;
    	nuova_partita->giornata = giornata;
    	nuova_partita->set_casa = 0;
    	nuova_partita->set_trasferta = 0;
    	nuova_partita->next = NULL;
    	//Caso lista vuota
    	if((mio_calendario->partita_head == NULL) && (mio_calendario->partita_tail == NULL)){
    		mio_calendario->partita_head = nuova_partita;
        	mio_calendario->partita_tail = nuova_partita;
        	return 0;
    	}
    	//Caso generale
    	mio_calendario->partita_tail->next = nuova_partita;
    	mio_calendario->partita_tail = nuova_partita;
    	return 0;
}

int controlla_partita(calendario mio_calendario, int codice_casa, int codice_trasferta){
	//Controlla che esista gia' una partita tra le due squadre
	partita p = mio_calendario->partita_head;
	while((p != NULL) && (((p->codice_casa != codice_casa) || (p->codice_trasferta != codice_trasferta)) && ((p->codice_casa != codice_trasferta) || (p->codice_trasferta != codice_casa)))){
		p = p->next;
	}
	if(p == NULL)
		//partita non trovata
		return 1;	
	//partita trovata
	return 0;		
}

int controlla_giornata(calendario mio_calendario, int casa, int giornata){
	//Controlla se la squadra ha gia' giocato nella giornata selezionata
	partita p = mio_calendario->partita_head;
	//Scorre fino alla giornata selezionata
	while((p != NULL) && (p->giornata != giornata))
		p = p->next;
	//Scorre nelle partite della giornata per cercare la squadra
	while((p != NULL) && ((casa != p->codice_casa) && (casa != p->codice_trasferta)) && (giornata == p->giornata))
		p = p->next;
	if(p == NULL)
		//Squadra non ha giocato
		return 1;
	if(casa == p->codice_casa)
		//Se la squadra gioca in casa
		return 2;
	//Se la squadra gioca fuori casa		
	return 0;			
}

void genera_calendario(calendario mio_calendario, campionato mio_campionato){
	//Conta il numero di squadre presenti nella lista
	int num_squadre = 0;
	squadra q = mio_campionato->squadre_head;
	while(q != NULL){
		num_squadre++;
		q = q->next;
	}
	//Calcola il numero di giornate che ci dovranno essere nel girone di andata
	int num_giornate = num_squadre - 1;
	//Calcola il numero di partite per ogni giornata
	int num_partite_giornata = num_squadre / 2;
	int giornata = 1;
	squadra casa = mio_campionato->squadre_head;
	squadra trasferta = mio_campionato->squadre_head;
	int check;
	int counter_c = 0, counter_t = 0, counter_t_2 = 0;
	//Questo ciclo controlla il numero di giornate, il <= e' dovuto a giornata che e' inizializzata a 1
	while(giornata <= num_giornate){				
		int contatore_partite = 0;
		casa = mio_campionato->squadre_head;
		//Questo ciclo controlla il numero di partite per ogni giornata
		while(contatore_partite < num_partite_giornata){
			//Questo ciclo controlla che scorrendo le squadre di casa non si sfori dalla lista
			for(int i = 0; i < num_squadre; i++){
				counter_c = 0;
				//Controllo se la squadra di casa ha gia' giocato nella giornata selezionata
				int a = controlla_giornata(mio_calendario, casa->codice, giornata);		
				//Se ha gia' giocato scorre finche' non trova una squadra che non ha ancora giocato
				while((a != 1) && (counter_c < num_squadre)){
					casa = casa->next;
					a = controlla_giornata(mio_calendario, casa->codice, giornata);
					//Counter_c mi permette di non uscire dalla lista scorrendo
					counter_c++;
				}										
				trasferta = mio_campionato->squadre_head;
				//Questo ciclo controlla che scorrendo le squadre di trasferta non si sfori dalla lista						
				for(int j = 0; j < (num_squadre - 1); j++){
					counter_t = 0;
					counter_t_2 = 0;
					//Controllo se la squadra di trasferta ha gia' giocato nella giornata selezionata
					int b = controlla_giornata(mio_calendario, trasferta->codice, giornata);	
					//Se ha gia' giocato scorre finche' non trova una squadra che non ha ancora giocato	
					while((b != 1) && (counter_t < (num_squadre - 1))){
						trasferta = trasferta->next;
						b = controlla_giornata(mio_calendario, trasferta->codice, giornata);
						counter_t++;
					}	
					//Se squadra di casa e trasferta coincidono trasferta scorre alla squadra successiva
					if(casa == trasferta)
						trasferta = trasferta->next;	
					//Effettua nuovamente il controllo sulle squadre in trasferta
					int c = controlla_giornata(mio_calendario, trasferta->codice, giornata);		
					while((c != 1) && (counter_t_2 < (num_squadre - 1 - counter_t))){
						trasferta = trasferta->next;
						c = controlla_giornata(mio_calendario, trasferta->codice, giornata);
						counter_t_2++;
					}
					//Controlla che la partita tra le squadre selezionate non esista gia'
					check = 0;
					check = controlla_partita(mio_calendario, casa->codice, trasferta->codice);
					//Se la partita non esiste esce dai cicli e stampa la partita
					if(check == 1)
						break;
					//Se la partita esiste la squadra in trasferta scorre e ricomincia il for
					trasferta = trasferta->next;
				}
				if(check == 1)
					break;
				casa = casa->next;
			}
			//Inserisce la partita nella lista
			int errore = inserimento_partite(mio_calendario, casa->codice, trasferta->codice, giornata);
			if(errore == 1)
				printf("\nErrore");
			//Dopo aver inserito la partita aumenta il contatore partite
			contatore_partite++;
		}
		//Dopo aver finito le partite di una giornata aumenta il contatore delle giornate
		giornata++;
		
	}
	//Genera_ritorno aggiunge alla lista il girone di ritorno, prendendo il girone di andata e scambiando le squadre in casa con quelle in trasferta 
	genera_ritorno(mio_calendario, giornata, num_partite_giornata);
	//Stampa il calendario appena generato
	stampa_calendario(mio_campionato, mio_calendario);
}

void stampa_calendario(campionato mio_campionato, calendario mio_calendario){
	partita p = mio_calendario->partita_head;
	printf("\nCALENDARIO\n");
	//Scorre la lista fino alla fine e stampa tutte le partite con le relative informazioni
	while(p != NULL){
		squadra casa = cerca_squadra_codice(mio_campionato, p->codice_casa);
		squadra trasferta = cerca_squadra_codice(mio_campionato, p->codice_trasferta);
		printf("\n%s vs %s -Palestra: %s -Giornata: %d", casa->nome_squadra, trasferta->nome_squadra, casa->palestra, p->giornata);
		p = p->next;
	}
}

void genera_ritorno(calendario mio_calendario, int giornate, int num_partite_giornata){
	int counter = 1;
	int counter_partite = 0;
	int giornate_ritorno = giornate;
	partita p = mio_calendario->partita_head;
	//Questo ciclo controlla il numero di giornate
	while(counter < giornate){
		counter_partite = 0;
		//Questo ciclo controlla il numero di partite per ogni giornata
		while(counter_partite < num_partite_giornata){
			//Vengono inserite le partite scambiando casa e trasferta rispetto al girone di andata
			int errore = inserimento_partite(mio_calendario, p->codice_trasferta, p->codice_casa, giornate_ritorno);
			p = p->next;
			counter_partite++;
		}	
		giornate_ritorno++;
		counter++;
	}
} 

void simula_partite(campionato mio_campionato, calendario mio_calendario){
	srand(time(NULL));
	partita p = mio_calendario->partita_head;
	//Scorre fino alla fine delle partite
	while(p != NULL){
		//Sceglie casualmente tra 0 e 1
		int scelta = rand() % 2;
		//Se esce 1 la squadra in casa vince e alla squadra in trasferta vengono assegnati casualmente da 0 a 2 set 
		if(scelta == 1){
			p->set_casa = 3;
			p->set_trasferta = rand() % 3;
		}
		//Se esce 0 la squadra in trasferta vince e alla squadra in casa vengono assegnati casualmente da 0 a 2 set 
		else{
			p->set_trasferta = 3;
			p->set_casa = rand() % 3;
		}
		p = p->next;
	}
	p = mio_calendario->partita_head;
	//Stampa tutte le partite con i risultati appena generati
	while(p != NULL){
		squadra casa = cerca_squadra_codice(mio_campionato, p->codice_casa);
		squadra trasferta = cerca_squadra_codice(mio_campionato, p->codice_trasferta);
		printf("\n%s vs %s -Risultato: %d-%d -Giornata: %d", casa->nome_squadra, trasferta->nome_squadra, p->set_casa,p->set_trasferta, p->giornata);
		p = p->next;
	}
	//system("PAUSE");
}

void classifica_finale(campionato mio_campionato, calendario mio_calendario){
	//Inizializza la classifica
	classifica mia_classifica = crea_classifica();
	partita p = mio_calendario->partita_head;
	squadra s = mio_campionato->squadre_head;
	int punti;
	//Scorre le squadre dalla prima all'ultima
	while(s != NULL){
		punti = 0;
		int codice_squadra = s->codice;
		p = mio_calendario->partita_head;
		//Scorre ogni partita
		while(p != NULL){
			//Se la squadra selezionata e' la squadra di casa controlla quanti set ha vinto e quanti ne ha vinti l'avversario per aumentare il suo punteggio in classifica
			if(codice_squadra == p->codice_casa){
				if((p->set_casa == 3) && (p->set_trasferta == 2))
					punti = punti + 2;
				if((p->set_casa == 3) && (p->set_trasferta < 2))
					punti = punti + 3;
				if((p->set_casa == 2) && (p->set_trasferta == 3))
					punti = punti + 1;
			//Se la squadra selezionata e' la squadra in trasferta controlla quanti set ha vinto e quanti ne ha vinti l'avversario per aumentare il suo punteggio in classifica
			}else if(codice_squadra == p->codice_trasferta){
				if((p->set_trasferta == 3) && (p->set_casa == 2))
					punti = punti + 2;
				if((p->set_trasferta == 3) && (p->set_casa < 2))
					punti = punti + 3;
				if((p->set_trasferta == 2) && (p->set_casa == 3))
					punti = punti + 1;
			}
			p = p->next;
		}
		//Inserisce la squadra in classifica in ordine di punti
		int errore = inserisci_posizione_ordinato(mia_classifica, punti, s->codice);
		if(errore == 1)
			printf("\nErrore nell'allocazione di memoria");
		s = s->next;
	}
	//Stampa la classifica finita 
	stampa_classifica(mia_classifica, mio_campionato);
	//Elimina la classifica dopo averla stampata per non avere memory leak
	elimina_classifica(mia_classifica);
}

classifica crea_classifica(){
	//Iniziallizza una variabile di tipo classifica e alloca la memoria necessaria
	classifica mia_classifica = (classifica)malloc(sizeof(struct classifica));
	if (mia_classifica == NULL)
		return NULL;
	//Inizializza i puntatori head e tail a NULL
	mia_classifica->posizione_head = NULL;
	mia_classifica->posizione_tail = NULL;
	return mia_classifica;
}


int inserisci_posizione_ordinato(classifica mia_classifica, int punteggio, int codice_squadra){
    	posizione r = mia_classifica->posizione_head;
    	posizione q = mia_classifica->posizione_head;
    	posizione p;
    	//Inizializza una variabile di tipo posizione e alloca la memoria necessaria
    	p = (posizione)malloc(sizeof(struct posizione));
    	if(p == NULL) 
        	return 1;
    	p->punteggio = punteggio;
    	p->codice_squadra = codice_squadra;
    	//Caso lista vuota
    	if((mia_classifica->posizione_head == NULL) && (mia_classifica->posizione_tail == NULL)){
        	p->next = NULL;
        	mia_classifica->posizione_head = p;
        	mia_classifica->posizione_tail = p;
        	return 0;
   	 }
   	 //Scorro per trovare posizione corretta
    	while ((q != NULL) && (q->punteggio > p->punteggio)){
       		r = q;
        	q = q->next;
    	}
    	//Caso inserimento in testa
    	if(q == mia_classifica->posizione_head){
        	p->next = mia_classifica->posizione_head;
        	mia_classifica->posizione_head = p;
        	return 0;
    	}
    	//Caso inserimento in coda
    	if(q == mia_classifica->posizione_tail){
        	p->next = NULL;
        	q->next = p;
        	mia_classifica->posizione_tail = p;
        	return 0;
    	}
    	//Caso generale
    	r->next = p;
    	p->next = q;
    	return 0;
}

void stampa_classifica(classifica mia_classifica, campionato mio_campionato){
	posizione p = mia_classifica->posizione_head;
	printf("\nCLASSIFICA FINALE\n");
	int posizione = 1;
	//Scorre la classifica e man mano la stampa
	while(p != NULL){
		squadra casa = cerca_squadra_codice(mio_campionato, p->codice_squadra);
		printf("\n%d) %s %d pt.", posizione, casa->nome_squadra, p->punteggio);
		posizione++;
		p = p->next;
	}
}

void elimina_classifica(classifica mia_classifica){
	classifica t = mia_classifica;
	posizione p = mia_classifica->posizione_head;
	posizione q = mia_classifica->posizione_head;
	//scorre la classifica dal primo elemento e man mano la elimina
	while(q != NULL){
		q = p->next;
		free(p);
		p = q;
		//Quando tutte le posizioni sono state eliminate elimina anche i puntatori head e tail
		if(q == NULL){
			free(t);
		}
	}
}







