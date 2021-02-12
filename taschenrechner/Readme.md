# Taschenrechner

## Allgemeines

Hier soll ein Taschenrechner implementiert werden.  
Dafür wurden Terme in einen Baum an Einzeloperationen ähnlich eines Syntaxbaumes zerlegt, der dann hier evaluiert wird.  
Um das Ergebnis einer solchen Operation zu berechnen, soll die Adresse zur Root Node des Baums an *rechner_sel_asm* übergeben werden.  

## Aufgaben

Jede Operations Node Struktur ist mindestens 32 bit lang.
Die ersten 2 bit enthalten die Art der Operation als vorzeichnlose Zahl.

| Operation | Zahl |
| const     | 0    |
| add       | 1    |
| sub       | 2    |
| mul       | 3    |

### Selector

Die Aufgabe dieser Unterroutine ist, anhand der ersten 2 bit, in die richtige subroutine zu springen.  
Davor soll `ebp` entsprechend gesetzt werden.
Das Zurücksetzen von `ebp` soll in den jeweiligen Subroutinen geschehen.

### 1.Konstante

diese Struktur beginnt mit 2 `0` bits, gefolgt von einem, 30 bit signed integer.

dieser signed integer soll als 32bit Vorzeichen behaftete Zahl zurückgegeben werden.
`edx` ist immer `0`.

diese Aufgabe soll unter *rechner_const_asm:* gelöst werden.

### 2. Addition, Subtraktion, Multiplikation

diese Strukturen beginnen mit dem 32 bit  gefolgt von zwei 32bit Adressen.
die zwei Adresse zeigen wieder auf eine Operation Struktur, die rekursiv evaluiert werden soll.
Das soll mit einem Aufruf von *rechner_sel_asm* geschehen.
Die Ergebnisse beider Operationen, soll entsprechend kombiniert in `eax` zurückgegeben werden.
Wenn dabei ein overflow entsteht, soll `edx` auf `1` gesetzt werden, sonst soll nach dem return `0` enthalten
Wenn einer der beiden Operationen `edx` setzt, soll in `edx` `1` zurückgegeben werden.
Wenn `edx` gesetzt ist, ist `eax` undefiniert.

Diese Aufgabe soll in *rechner_add_asm*, *rechner_sub_asm* und *rechner_mul_asm* gelöst werden.

