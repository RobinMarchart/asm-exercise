# Taschenrechner

## Allgemeines

Hier soll ein Taschenrechner implementiert werden.  
Dafür werden Terme in einen Baum an Einzeloperationen ähnlich eines Syntaxbaumes zerlegt, der dann hier evaluiert wird.  
Zuerst werden die einzelnen Operationen implementiert.

## Aufgaben
Jede Operation bekommt über den Stack einen Parameter, der die 32bit Adresse einer Struktur enthält, die die aktuelle Operation beschreibt.
Das Ergebnis wird immer in `eax` zurückgegeben, in `edx` ob die Operation erfolgreich war (0 oder 1).
Außer `ebx` dürfen alle anderen Register nicht verändert werden.
Alle Aufgaben sind in *rechner.asm* zu lösen

### 1.Konstante

diese Struktur beginnt mit 3 `0` bits, gefolgt von einem, 29 bit signed integer.

dieser signed integer soll als 32bit Vorzeichen behaftete Zahl zurückgegeben werden.
`edx` ist immer `0`.

diese Aufgabe soll unter *rechner_const_asm:* gelöst werden.

### 2. Addition

diese Struktur beginnt mit einer 32 bit `1`, gefolgt von zwei 32bit Adressen.
die zwei Adresse zeigen wieder auf eine Operation Struktur, die rekursiv evaluiert werden soll.
Das soll mit einem Aufruf von *rechner_sel_asm* geschehen.
Dieser Unterroutine wird später implementiert und wird sich bezüglich Parameter/Rückgabewerte wie alle anderen Teilaufgaben verhalten.
Die Ergebnisse beider Operationen, soll multipliziert und zurückgegeben werden.
Wenn einer der beiden Operationen `edx` setzt, soll in `edx` `1` zurückgegeben werden, `eax` ist in diesem Fall undefiniert.

diese Aufgabe soll in *rechner_add_asm* gelöst werden.

### 3. Subtraktion

wie Addition, nur wird subtrahiert und nicht addiert.
die Struktur beginnt mit `2`.
Sie soll in *rechner_sub_asm* implementiert werden.

### 4. Multiplikation

Wie Addition, nur beginnt die Struktur mit `3`.
Sie soll in *rechner_mul_asm* implementiert werden.

### 5. Division

Wie Addition, nur beginnt die Struktur mit `4`.
Sie soll in *rechner_div_asm* implementiert werden.

### 6. Select

Diese Unterroutine soll anhand der ersten 3 bits entscheiden, welche Operation gerade bearbeitet wird.
Wenn keine solche Operation gefunden werden konnte, soll in `edx` 1 gesetzt werden, `eax` ist in diesem Fall undefiniert.
Der Aufruf der richtigen Operation soll über jmp erfolgen.
**Achtung: die oben genannten calling conventions müssen immer eingehalten werden**
Diese Funktionalität soll in *rechner_sel_asm* implementiert werden.
