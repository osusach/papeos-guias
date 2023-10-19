# El lenguaje C

Todo lo mencionado en Algoritmos debieron haberlo visto, o por lo menos haber obtenido una noción de ello con los ramos que ya han tenido, ya sea Fundamentos de Programación o Fundamentos de Computación, sin embargo C debería ser completamente nuevo, a menos que hayan estudiado por su cuenta.

C difiere bastante de lo que es Python en bastantes aspectos. C es un lenguaje que te entrega muchas más libertades y acceso a los recursos de computador, como la memoria del computador, e incluso propiedades del procesador y el sistema operativo. Sin embargo, no se preocupen, en este ramo sólo verán el acceso a la memoria, el lado del procesador y sistema operativo lo verán en SISTOPE (Junten miedo).

Algo muy importante que se debe entender es que saber programar es muy distinto de saber un lenguaje de programación. Si aprendieron bien en FPI, deberían saber programar, y aparte, saber Python, y en este curso no deberían aprender a programar, sino aprender la sintaxis y reglas gramaticales que conforman el lenguaje.

## C

C, a diferencia de Python, es un lenguaje compilado. Esto quiere decir que cada vez que quieran ejecutar el programa que hayan escrito deberán compilarlo, es decir, transformar el archivo .C en un ejecutable. Existen varios compiladores, pero el utilizado en este curso (y en general) es gcc. 

La estructura de un programa en C está conformada en tres partes principales. La primera, consiste en la declaración de bibliotecas, muy parecido a cuando hacían `import` en Python. La segunda, consiste en todas las funciones y variables globales del programa, y la última, y más importante, la función main. La función main es fundamental en cualquier programa en C, pues al correr el programa, el computador busca el main y lo ejecuta. Si no hay una función main, no sucederá nada.

También es muy importante mencionar que C es un lenguaje fuertemente tipado, es decir, que primero, ustedes deben indicar de qué tipo es la variable que quieren asignar, y ese tipado no puede cambiar. Lo bueno es que una vez lo declaran, no es necesario declararlo de nuevo, y el mismo compilador les dirá que está malo, en caso de que quieran asignar tipos que no correspondan.

## Tipado vs No Tipado, diferencias y su efecto en memoria
Que un lenguaje sea tipado, implica que debes indicar qué tipo de dato vas a almacenar en memoria antes de comenzar a trabajar con él.
```c
int x; // alocar memoria para una variable
x = 5; // asignar valor
x = "Hola!"; // error de compilación, "Hola!" no es de tipo entero
```
Por el contrario, en un lenguaje *no tipado* como Python, puedes simplemente tener una variable y sobreescribir el valor como quieras.
```python
x = 5
x = "Hola!"
```
### ¿Porqué en C no se puede y en Python sí?
Python es considerado un lenguaje de alto nivel, está hecho para ser un mediador entre tú y la computadora, siendo lo más amigable posible contigo, Python hace muchas cosas por ti sin que te des cuenta. Por este motivo, Python es uno de los lenguajes más populares entre los programadores novatos.

C es considerado un lenguaje de bajo nivel, está hecho para darte mayor control sobre la computadora, ahora eres responsable de manejar la memoria de tu programa correctamente. *"C hace que el mundo gire"*, con esta herramienta se hizo Windows y Unix (Linux). El intérprete de python está hecho en C.fuertemente

## Ejemplos de tipado en C

### Correcto
Acá se declara una variable number y se le asigna instantáneamente el número 69.
```c
int number = 69; 
```

### Correcto
Aquí se declara una variable number, es decir, ahora el programa sabe que existe una variable de tipo
int llamada number (Ojo, que por ahora no guarda ningún número, ni siquiera es un 0, por lo que si intentan utilizarlo puede tirar errores o entregar números incorrectos)
```c
int number;
```

### Correcto
Aquí se declara una variable number de tipo entero, y luego se le asigna el número 420. Este proceso de
asignar un número a una variable vacía se le dice "inicializar" la variable.

```c
int number;
number = 420;
```

### Incorrecto
Aquí se intenta cambiar el tipo de la variable number de entero a flotante.
```c
int number = 30;
float number;
```

### Incorrecto
Aquí se intenta asignar un flotante a una variable de tipo int
```c
int number = 30;
number = 3.94;
```

Como habrán notado a lo largo de estos ejemplos, también hay un detalle bastante diferente a lo que se acostumbra en Python, y es que todas las líneas de código terminan con un punto y coma `;`. En C, las líneas de código no se separan por un "Enter" (Salto de línea para los más entendidos), sino que se separan por un `;`, lo que permite que sucedan cosas como esta:

```c
int number; number = 10; number = number + 10; int anotherNumber = 20; int result; result = anotherNumber + number;
```

Este código es totalmente válido para el compilador, sin embargo se vuelve muy difícil de leer para nosotros, por lo que lo ideal es que sigan programando con la misma estructura que han visto durante todo Python, dejando una instrucción por línea.

## Operadores

Los operadores más esenciales de la programación se encuentran tanto en Python como en C. El operador de asignación = y operadores de comparación como ==, <=, >=, <, >, != son idénticos entre lenguajes, así que sólo se mencionarán los que impliquen un cambio o novedad en comparación con Python.

### Incrementación y disminución

Este es un poco más personal, pero encuentro muy práticos estos operadores que no se encuentran en Python. Los operadores `++` y `--` se encargan de aumentar y disminuir en `1` un número. Estos pueden ir adelante o detrás de una variable, ¡y su orden sí afecta su funcionamiento!. La mejor manera de explicarlo es con un ejemplo.

```c
int number = 5;
int result = 10 + number++
```
Al final de este ejemplo, el valor de `number` es `6` y el valor de `result` es `15`, pero ¿Qué está sucediendo acá?

Sucede que cuando el operador `++` es utilizado, este suma `1`, y cuando va después de la variable, lo hace después de ser "evaluado". Es decir, que primero que hace el cálculo de la suma entre `10` y `number`, y después se aumenta el valor en uno a `number`.

En el caso contrario, cuando el operador ++ va antes de la variable, primero se aumenta el valor en uno a `number`, y después se hace el cálculo de la suma entre `10` y `number`.

```
int number = 5;
int result = 10 + ++number
```

Al final de este ejemplo el valor de `number` es `6`, y el valor de `result` es `16`.


### Operadores Lógicos

Los operadores lógicos también cambian entre Python y C. En Python se utilizan las palabras `and`, `or` y `not`, lo que vuelve mucho más natural su uso, sin embargo, en C se ocupa una sintaxis distinta.

#### And

En C, la operación `and` se realiza con el operador `&&`, por ejemplo.

```c
int a = 1;
int b = 0;
int resultado = a && b; // Resultado es False o 0
```

#### Or

En C, la operación `or` se realiza con el operador `||`, por ejemplo.

```c
int a = 1;
int b = 0;
int resultado = a || b; // Resultado es True o 1;
```

#### Not
En C, la operación `not`, o el negado de un booleano, se realiza con el operador `!`, por ejemplo

```c
int a = 1;
int resultado = !a; // Resultado es False o 0.
```

### Operador condicional

En Python veíamos cómo el operador `if` se hacía de la manera
```python
numero = 10
condicion = True
if condicion:
    numero = numero + 5
print(numero)
```

Aquí todo lo que determinaba si las instrucciones iban dentro del `if` era que estuvieran después del `:`y que estuvieran identados dentro (o hacia adelante).
En C esto cambia un poco. Primero, la condición tiene que estar sí o sí dentro de un paréntesis, de lo contrario el compilador no lo entenderá. Por otro lado, todas las instrucciones que sean parte del `if` deben ir dentro de llaves, por lo que no importa si están identados o no (Aunque por orden del código, nuevamente, es ideal mantener la estructura que se aprendió en Python), por ejemplo

```c
int numero = 10;
int condicion = 1;
if (condicion) {
  numero = numero + 5;
}
// Print(numero)
```

La parte del print la dejaremos para más tarde.

### Operadores cíclicos

Hay dos cambios principales en los ciclos, uno ya visto anteriormente y otro más distinto.
#### While
El ciclo while sufre básicamente el mismo cambio que el operador `if`, las condiciones ahora van dentro de un paréntesis, y lo que ocurre dentro del while va en llaves. Por ejemplo

```c
int i = 0;
int resultado = 0;
while (i < 10) {
  resultado = resultado + 1;
  i++; // Lo mismo que hacer i += 1
}
```

#### For

Este ya cambia bastante más en relación a su versión de Python. Mientras en Python existe la palabra clave `in` para trabajar con los ciclos for, acá sólo existen tres declaraciones.

La estructura es

```c
for (Declaración 1; Declaración 2; Declaración 3) {
  // cuerpo del ciclo
}
```

Donde la primera declaración es la instrucción que se realiza al inicio del `for`.
La segunda declaración determina el límite de iteración, o cuando detener la repetición del ciclo `for`.
La tercera declaración determina qué instrucción se realiza al final de cada iteración. Por ejemplo

```c
int resultado = 0;
int i;
for (i = 0; i < 15; i++) {
  resultado += 2;
}
```

El código realiza el cálculo de 2 * 15, sin utilizar el operador de multiplicación.

En este ciclo `for`, lo primero que se hace es declarar que `i = 0`, luego se declara que el ciclo `for` continuará mientras `i < 15` y finalmente se declara que al final de cada ciclo se aumenta en uno el valor de `i`.

## Funciones

Las funciones en C se comportan exactamente de la misma manera en que se comportan en Python e incluso la matemática, la única diferencia es que debemos respetar las nuevas reglas de tipado estático que se mencionaron anteriormente.

Todas las funciones deben incluir el tipo de dato que retorna, y el tipo de dato que poseen sus argumentos, de la manera.

```c
tipoRetorno nombreFuncion(tipoArg arg1, tipoArg arg2...) {
    // Cuerpo de la función
    // ...
    return valorDeRetorno;
}
```
De la misma manera que ya no se utilizan los dos puntos `:` y las identaciones para determinar jerarquía de instrucciones, ahora todas las instrucciones de la función van dentro de las llaves.

Es muy importante que la función posea siempre un valor de retorno, y que el tipo del dato que se retorne coincida con el tipo de la función. Lo bueno es que si se equivocan (O intentan cambiarlo deliberadamente) el mismo compilador no les dejará correr el programa :-).

Un ejemplo real del uso de una función es

```c
int multiplicarSinSuma(int multiplicando, int multiplicador) {
    int resultado = 0;
    for (int i = 0; i < multiplicador; i++) {
      resultado = resultado + multiplicando;
    }
    return resultado;
}
```

Se puede observar correctamente cómo el tipo del retorno de la función y el tipo de la variable que se retorna son iguales, y aparte se asegura de que los dos números que recibe sí sean operables con la suma.

### Void

Existe un tipo de dato especial para las funciones que no tienen ningún valor de retorno, este tipo de dato es el `void`. Es raro tener funciones con este comportamiento con la información que tenemos hasta ahora, sin embargo serán más útiles con lo que se verá más adelante en el curso. Un ejemplo es

```c
int number = 0; // Variable global

void sumarANumber(int n) {
    number += n;
    return;
}
```

Esta función modifica una variable global declarada en el código, y no tiene por qué retornar el número modificado, pues es accesible desde todo el código.



