# HopNet

Repository GitHub: [HopNet - GitHub](https://github.com/CetrioloRiick/hopnet)

Autore: *Diego Quarantani*

Progetto: *Rete neurale di Hopfield*

Data: *2 Giugno 2025*


## Struttura del progetto

Il progetto è stato suddiviso in tre eseguibili distinti:

* **binarize** — generazione dei pattern binari a partire da immagini;
* **train** — fase di apprendimento della rete;
* **recall** — fase di richiamo e correzione di pattern corrotti.

Tutti i programmi condividono parte del codice tramite una struttura a directory comune:

```bash
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

L’input dei programmi viene gestito tramite la libreria [cxxopts](https://github.com/jarro2783/cxxopts), che consente un parsing semplice e robusto degli argomenti da linea di comando.


## Scelte progettuali e implementative

### Binarize — acquisizione dei pattern

Per la binarizzazione delle immagini è stata utilizzata la libreria **OpenCV**.
OpenCV è stata preferita rispetto a SFML in questa fase per la sua maggiore completezza nei metodi di elaborazione delle immagini (conversione in scala di grigi, ridimensionamento con interpolazione bilineare, sogliatura automatica).

Il programma riceve in input una cartella contenente le immagini e restituisce un file `.txt` contenente i pattern binari (valori +1 / -1).
È possibile anche salvare le immagini binarizzate per verifica visiva, attivando l’opzione `-s`.

### Train — fase di apprendimento

La fase di addestramento si basa su due classi principali:

* **Pattern**: incapsula il pattern binario come `std::vector<int>`. Garantisce che tutti i vettori rispettino il formato richiesto (+1 / -1) e abbiano la stessa dimensione, imposta globalmente tramite il metodo statico `setSize(size_t n)`.

* **WeightMatrix**: rappresenta la matrice dei pesi simmetrica della rete di Hopfield. Per ottimizzare lo spazio, vengono memorizzati solo gli elementi della parte superiore della matrice (triangolo superiore), mentre l’accesso agli elementi è gestito via overloading dell’operatore `[]`, tenendo conto della simmetria.

L’algoritmo di apprendimento applica la classica regola di Hebb tramite il metodo `hebbRule(...)`, aggiornando iterativamente la matrice dei pesi a partire dai pattern forniti.

### Recall — fase di richiamo

Anche la fase di richiamo si appoggia parzialmente alla struttura implementata in `train`. In particolare:

* **NeuralNetwork**: gestisce il pattern da richiamare (potenzialmente corrotto) e implementa il metodo `minimizeState(...)`, che cerca uno stato stabile di minima energia aggiornando i neuroni secondo la dinamica di Hopfield fino alla convergenza.

* **WeightMatrix**: viene riutilizzata integralmente anche nella fase di richiamo. Per ottimizzare la compilazione, la classe è suddivisa in più file `.cpp`:

  * `weight_matrix.cpp` (metodi comuni),
  * `weight_matrix-train.cpp` (metodi specifici per l'addestramento),
  * `weight_matrix-recall.cpp` (metodi specifici per il richiamo).

Questa suddivisione consente al CMake di compilare solo le parti effettivamente necessarie in ciascun eseguibile.


## Dipendenze esterne

Per compilare ed eseguire correttamente il progetto sono necessarie le seguenti librerie:

```bash
libcxxopts-dev libopencv-dev libsfml-dev
```

Per installare tutte le dipendenze (compilatore incluso) è sufficiente eseguire:

```bash
sudo apt install g++ cmake ninja-build libcxxopts-dev libopencv-dev libsfml-dev
```


## Istruzioni per l'esecuzione

Tutti i programmi supportano l’opzione `--help` che stampa l’elenco completo degli argomenti disponibili.

### Binarize

Esempio di esecuzione base:

```bash
./binarize.out -i path/to/images/directory
```

dove va indicata la cartella contenente le immagini che si vogliono binarizzare

Opzioni disponibili:

```bash
Convert all images in a folder to binary format (-1, +1)
Usage:
  binarize [OPTION...]

  -i, --input arg      Input folder path (obbligatorio)
  -o, --output arg     Output file path (default: binarized-images.txt)
  -W, --width arg      Width to resize each image (default: 50)
  -H, --height arg     Height to resize each image (default: 50)
  -t, --threshold arg  Threshold for binarization (0-255) (default: 127)
  -s, --show           Save each binarized image during processing
      --help           Print help
```

Se il risultato della binarizzazione non fosse soddisfacente, si consiglia di modificare il parametro `--threshold`.

Per generare un singolo pattern binario, necessario a recall come pattern corrotto da *aggiustare*, eseguire il comando seguente indicando una cartella che contiene solo un'immagine:

```bash
./binarize.out -i path/to/image/directory -o pattern.txt
```

oppure copiare dentro pattern.txt un pattern a qualsiasi tra quelli presenti in binarized-images.txt.

### Train

Esecuzione di default:

```bash
./train.out
```

Opzioni disponibili:

```bash
Train a Hopfield neural network from binary image patterns and save the weight matrix.
Usage:
  train [OPTION...]

  -i, --input arg         Input file path (default: binarized-images.txt)
  -p, --pattern-size arg  Size of the pattern (width * height) (default: 2500)
  -o, --output arg        Output file path for weight matrix (default: hopfield-weights.txt)
  -h, --help              Print help
```

⚠ **Nota importante:** la dimensione del pattern (`-p`) deve essere coerente con la risoluzione scelta nella fase di binarizzazione (`width * height`).

### Recall

Esempio di esecuzione con inserimento di rumore:

```bash
./recall.out -n 0.07
```

Opzioni disponibili:

```bash
Run the recall phase of a Hopfield neural network: load weights, correct a corrupted pattern, and observe convergence.
Usage:
  recall [OPTION...]

  -w, --weights arg            Path to the weight matrix file (default: hopfield-weights.txt)
  -i, --input arg              Corrupted input pattern file (default: pattern.txt)
  -o, --output arg             Output file path (default: corrected-pattern.txt)
  -W, --width arg              Width (pixels) of the input pattern (default: 50)
  -H, --height arg             Height (pixels) of the input pattern (default: 50)
  -m, --monitor-process        Enable monitoring of energy minimization during recall (default: true)
  -n, --noise-probability arg  Probability of introducing noise into the input (0 to 1) (default: 0)
  -h, --help                   Print help
```

L’opzione `-m` consente di monitorare il valore dell’energia a ogni iterazione.
L’opzione `-n` introduce un rumore casuale nel pattern prima di eseguire il recall; può essere disabilitata ponendo `-n 0` se il pattern corrotto è stato generato manualmente.


## Testing

Per la verifica del funzionamento sono stati implementati alcuni test automatici utilizzando il framework **doctest**.
I test sono principalmente di tipo unitario e si concentrano su:

* **Pattern**: verifica della coerenza di dimensione, corretta validazione dei valori ammessi (+1/-1), gestione di errori in caso di dimensioni incompatibili.
* **WeightMatrix**: corretto accesso simmetrico tramite l’overload di `operator[]`, coerenza della regola di Hebb.
* **NeuralNetwork**: verifica della convergenza degli stati, corretto calcolo dell’energia.

Inoltre sono stati eseguiti test funzionali sull’intero flusso binarizzazione → training → recall, utilizzando immagini note e verificando la capacità del sistema di ricostruire pattern correttamente anche in presenza di rumore.


## Interpretazione dei risultati

Il sistema si è dimostrato in grado di apprendere correttamente un numero limitato di pattern, ricostruendoli anche in presenza di rumore moderato.
L’introduzione di un numero eccessivo di pattern o di rumore eccessivo porta, come atteso teoricamente, a fenomeni di instabilità o stati spuri.