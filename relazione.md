# HopNet

*di Diego Quarantani ([Github](github.com/CetrioloRiick)), in data 2 Giugno 2025*


## Scelte progettuali e implementative

Come suggerito ho diviso il progetto in tre programmi separati che vengono compilati dallo stesso cmake, ho scelto questa struttura delle directory che mi permette di avere codice comune tra i programmi:

```shell
.
|-- include
|   |-- binarize
|   |-- common
|   |-- recall
|   `-- train
|-- src
|   |-- binarize
|   |-- common
|   |-- recall
|   `-- train
`-- tests
```

per l'input di tutti i programmi ho utilizzato la libreria [cxxopts](https://github.com/jarro2783/cxxopts)
### Binarize - Aquisizione dei pattern

Ho utilizzato la libreria OpenCV per riscalare le immagini (con interpolazione bilineare) e per la costruzione del pattern binario, l'ho preferita rispetto a sfml per questa prima parte del progetto perchè offriva dei metodi più specifici e diretti per la conversione in bianco e nero rispetto a sfml. Nel concreto il programma converte tutte le immagini in una cartella indicata dall'utente nei pattern binari (+1 e -1) e salva questi ultimi in un file .txt, se l'utente abilita la visualizzazione dei pattern le immagini convertite vengono salvare nella working direcotory

### Train - Fase di apprendimento

Per la fase di apprendimento sono state definite due classi, Pattern e WeighMatrix:

* Pattern, dal nome autoesplicativo, gestisce il pattern attraverso un std::vector<int> privato. Nel programma questa classe ha l'unico scopo di assicurarsi che tutti i pattern (in ultima analisi vettori di int) contengano solo +1 e -1 e siano della stessa lunghezza. Fa in modo che ogni sua istanza abbia la stessa dimensione grazie al metodo statico setSize(size_t n) che deve essere chiamato solo una volta nel programma prima dell'utilizzo della classe.  

* WeighMatrix (poi riutilizzata anche in Recall) è la matrice dei pesi W, essendo simmetrica e con diagonale nulla memorizza solo la metà superiore e poi l'operatore [] gestisce i vari casi (invertendo per esempio gli indici quando il primo è maggiore del secondo). Il metodo principale usato nel programma poi è hebbRule(...) che dato un Pattern aggiorna la matrice con la regola di Hebb.

### Recall - Fase di richiamo
