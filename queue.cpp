// rifare usando il pimpl, fare due implementazioni con liste e vector
#include <iostream>
#include <vector>
#include <assert.h>
class Queue {
    public:
        Queue();
        Queue(const Queue& c); // rispondi alla domanda perche devi passare & e const
        // const perche non voglio modificare e & per non copiare poi pensa che se 
        // passi per copia quando fa il delete elimina quello a cui stava puntando quello originale
        ~Queue();
        void enqueue(int e);
        void dequeue();
        int& first() const; // perche const & 
        bool isempty() const;
        int head() const;

    private:
        // o usi i vector o head and tail
        // spiega perche uno e meglio dell'altro
        // se usi head&tail aggiungi in coda e rimuovi in testa, perche non il contrario? pensaci
        // se usi una lista semplice aggiungere in coda e rimuovere in testa e la migliore
        // se usi una lista doppiamente fare il contrario non ti da NESSUN VANTAGGIO cioe nessun vantaggio 
        // di complessita asintotica in piu quindi viene considerato errore di programmazione se fa il contrario (aggiungere in testa & eliminare in coda);
        // Inoltre pensaci usare una lista doppiamente concatenata usa 1/3 della memoria in piu dato che contiene 2 puntatori invece di 1 + il dato da salvare

        // 12/05 Queue con i vector
        std::vector<int> v(100);
        int last; // indice dell'elemento piu vecchio nel vettore 
        int next; // indice della prossima posizione libera del vettore
        int elem;
        // last > next possibile dato che utilizziamo l'aritmetica modulare
        // last == next rappresenta coda vuota
        // quando last == next significa anche coda piena es. 4 elementi
        // usiamo elem ~ mi ricordo lascio uno spazio vuoto o uso un contatore elem
};

Queue::Queue() {
    next = 0;
    last = 0;
    elem = 0;
}

Queue::~Queue() {

}

void Queue::enqueue(int x) {
    if(elem < 100) {
        v.at(next) = x;
        next = (next+1) % 100;
        elem++;
    }
    else {
        // allunga vettore
    }
}

void Queue::dequeue() {
    if(elem > 0) {
        last = (last+1) % 100;
        elem--;
    }
}

int Queue::head() const {
    assert(elem > 0);
    return v.at(last);
}

bool Queue::isempty() const {
    return (elem == 0);
}