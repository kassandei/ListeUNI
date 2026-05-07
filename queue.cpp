
class Queue {
    public:
        Queue();
        Queue(const Queue& c); // rispondi alla domanda perche devi passare & e const
        // const perche non voglio modificare e & per non copiare poi pensa che se 
        // passi per copia quando fa il delete elimina quello a cui stava puntando quello originale
        ~Queue();
        void enpush(int e);
        void deque();
        int& first() const; // perche const & 
        bool isempty() const;
    private:
        // o usi i vector o head and tail
        // spiega perche uno e meglio dell'altro
        // se usi head&tail aggiungi in coda e rimuovi in testa, perche non il contrario? pensaci
        // se usi una lista semplice aggiungere in coda e rimuovere in testa e la migliore
        // se usi una lista doppiamente fare il contrario non ti da NESSUN VANTAGGIO cioe nessun vantaggio 
        // di complessita asintotica in piu quindi viene considerato errore di programmazione se fa il contrario (aggiungere in testa & eliminare in coda);
        // Inoltre pensaci usare una lista doppiamente concatenata usa 1/3 della memoria in piu dato che contiene 2 puntatori invece di 1 + il dato da salvare
};