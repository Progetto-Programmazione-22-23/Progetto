# Progetto

## Requisiti minimi e obbligatori
- La mappa deve avere una grafica ASCII
- Lo schema del livello è **scelto in modo random da un insieme di livelli pre-definiti (o generati random)**
    Quindi **non si parte mai dallo stesso schema**.
- Man mano che si procede la difficoltà aumenta (più nemici, meno potenziamenti)
- Non esistono traguardi
- Durante la partita, il protagonista può tornare indietro di schema e trovare esattamente tutto come lo ha lasciato
- Devono essere presenti **diversi tipi di nemici e una valuta**
- **La valuta** può essere utilizzata per acquistare potenziamenti (vita, poteri, armi)
- Il gioco deve quindi prevedere un **livello market** (e.g., a inizio partita) in cui acquisire vita aggiuntiva, poteri e/o armi.
- Se il protagonista muore, mantiene i bonus, poteri e/o armi che ha acquistato e
alla prossima partita partirà da uno schema random (vedi punto 2) e una difficoltà
proporzionata ai potenziamenti che ha acquisito
- Il giocatore umano controlla il protagonista
- Nel percorso il protagonista incontra nemici i quali possono **togliere** vita
colpendo o entrando a contatto con il protagonista
- I nemici sono controllati dal computer: si possono muovere e sparare, possono
venire uccisi dal protagonista (es. sparando)
- Game over quando la vita scende a 0

## ESEMPIO DIVISIONE DEL LAVORO ALL’INTERNO DI UN GRUPPO
▸ Componente #1: si occupa delle mappe
▸ Componente #2: implementa personaggi e nemici
▸ Componente #3: si occupa della interazione con la libreria
grafica
▸ Componente #4: si fa carico dei potenziamenti, del
mercato e del salvataggio di stato

## Impostazione del progetto
- Il progetto deve essere realizzato usando le classi
- Le stanze e gli elementi in una stanza devono essere gestiti tramite strutture dati dinamiche (prevedendo, quindi, inserimento e rimozione)
- Il progetto è organizzato in più file
- Ad ogni classe corrispondono due file: `NomeClasse.cpp` e `NomeClasse.hpp`

## How to run
- Linux
1. Installa la libreria `ncurses` con la seguente linea di codice:
    `$ sudo apt-get install libncurses5-dev libncursesw5-dev`
2. Vai nella directory
    `cd ../`
3. Compilazione
    `g++ HelloWorld.cpp -lncurses -o HelloWorld`
4. Esecuzione
    `./HelloWorld`


## Valutazione
- Il progetto è parte integrante dell’esame ed è **obbligatorio**
- Ha un voto massimo di 8 punti che si sommano al voto dello scritto (max 24)
- Il lavoro viene svolto in gruppi, ma la valutazione del progetto è **individuale**
- Studenti dello stesso gruppo possono prendere voti diversi!

## Tempistiche
- Da consegnare entro il **28/02/2024**
- un appello di discussione per ogni appello scritto

## Consegna
- Da consegnare
    - Codice (sorgente e binari)
    - File README
    - screen recording (video) con l'esecuzione del gioco
    - breve relazione 3/4 pagine