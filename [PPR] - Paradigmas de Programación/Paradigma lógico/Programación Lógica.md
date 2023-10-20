## Autor:
-  <img width="16" src="https://avatars.githubusercontent.com/u/96759895?v=4"></img> [Jorge Jimenez](https://github.com/shinkest)
  
## Descripción general
A partir de una base de conocimientos, conformada por una serie de <u>hechos</u> y <u>reglas</u>, se realizan una serie de consultas sobre elementos de la misma.

### Hecho
Predicado que describe la relación entre un objeto y sus atributos o propiedades.
Dichos atributos también reciben el nombre de "*átomos*".

Un ejemplo: Si se quiere crear una estructura que almacene el nombre de un estudiante, y sus notas, se crea la relación `estudiante`, que cuenta con dichos campos.

```prolog
estudiante(jorge, 7, 4).
estudiante(juan, 5, 3).
estudiante(benja, 3.8, 3.9).
```

Asimismo, al querer consultar sobre algún dato en particular de la base de conocimientos, se realiza de la siguiente forma:

```prolog
estudiante(jorge, 7, 4).
estudiante(juan, 5, 3).
estudiante(benja, 4, 3.9).
%====================================================================================
% query
%Consultas sobre nombres de los estudiantes
estudiante(X, _, _).
```

Observación: Todo hecho descrito en una base de conocimientos, es considerado como un axioma; es decir, para el sistema, la información descrita por una relación corresponde a una verdad absoluta e irrefutable.

### Regla
Sentencia que se cumple bajo el cumplimiento de uno o más hechos, a partir de una serie de condiciones lógicas.

Tomando el ejemplo anterior, se define la regla `aprobado`, que se cumple cuando el promedio de las notas del estudiante es mayor o igual a 3.95.

```prolog
estudiante(jorge, 7, 4).
estudiante(juan, 5, 3).
estudiante(benja, 3.9, 3.9).

aprobado(NombreEstudiante):-
	estudiante(NombreEstudiante, Nota1, Nota2),
	((Nota1 + Nota2)/2) >= 3.95.

%====================================================================================
% query
aprobado(jorge).
```

Observación: Es posible generalizar a todas aquellas entidades que cumplan con una serie de condiciones dentro de una misma clase o categoría, mediante una regla en particular.

En el caso anterior, puesto que los estudiantes (entidades) `jorge` y `juan` entregan `true` para la regla `aprobado`, entonces ambos entran a la categoría de aprobados.

## Buscando elementos en la base de conocimientos
Si bien, al declarar una relación con una serie de parámetros cuyos caracteres comienzan en minúsculas, se está enseñando dicha información a la base de conocimientos, es posible buscar información en particular de una entidad de la siguiente forma:

Para buscar información sobre uno o varios datos de una entidad que cuenta con <u>información en específico</u>, se declara dicha relación, ingresando dicha información en minúsculas, y dejando los campos de la información a buscar con identificadores en Mayúsculas.

```prolog
estudiante(jorge, 7, 4).
estudiante(juan, 5, 3).
estudiante(benja, 3.8, 3.9).

% query
% Se quiere buscar los nombres de los estudiantes cuya primera nota sea mayor a 4.
estudiante(Nombre, Nota1, _), Nota1 > 4.
```

---
## Manejo de listas
Para ello, se hace uso de dos conceptos fundamentales dentro del paradigma: 

| **Nombre**  | **Funcionamiento**  |
| ----------- | ------------------- |
| Unificación | (Atributos → Lista) |
| Inferencia  | (Lista → Atributos) |

### Crear una lista
Se declara como una relación, con un identificador y una serie de atributos, tal que dichos atributos constituyan los elementos de la lista a crear (**unificación**).

```prolog
estudiante(Nombre, Nota1, Nota2, [Nombre, Nota1, Nota2]).
% query
estudiante(jorge, 7, 4, Estudiante1).
```

  Otra forma de crear una lista es asignando manualmente una lista de elementos a un identificador que empiece con un carácter en Mayúsculas:

```prolog
% query
Estudiante = [jorge, 7, 4].
```

### Obtener un elemento de una lista
* Consultando directamente sobre uno o más datos de una lista conocida (**inferencia**):

```prolog
estudiante(Nombre, Nota1, Nota2, [Nombre, Nota1, Nota2]).
% query
Estudiante = [jorge, 7, 4],
estudiante(NombreBuscado, Nota1Buscada, Nota2Buscada, Estudiante).
```

* Definiendo una regla, que recibe la Lista a buscar, y que entrega el Elemento que se desea obtener (**inferencia**):

```prolog
estudiante(Nombre, Nota1, Nota2, [Nombre, Nota1, Nota2]).
buscarNombreEstudiante(Estudiante, NombreBuscado):-
	estudiante(NombreBuscado, _, _, Estudiante).
%query
Estudiante = [jorge, 7, 4],
buscarNombreEstudiante(Estudiante, X).
```

### Modificar un elemento de una lista
Puesto que en el paradigma actual <u>no existen las variables mutables</u>, <u>se debe crear una nueva lista que contenga al parámetro actualizado</u>.

Para ello, se define una regla que reciba la Lista sobre la que se va a trabajar, y el Nuevo valor del elemento, y que retorne la Nueva lista actualizada.

En ésta, primero se busca la entidad con los atributos descritos por la Lista (salvo por el parámetro a modificar) (**inferencia**), y se guardan dichos datos en identificadores temporales.

Luego, utilizando dichos identificadores, se crea la nueva lista (**unificación**) tal que, en el campo correspondiente al del parámetro a actualizar, se coloca el Nuevo valor del elemento.

```prolog
estudiante(Nombre, Nota1, Nota2, [Nombre, Nota1, Nota2]).
modificarNota1(Estudiante, NuevaNota1, NuevoEstudiante):-
	estudiante(Nombre, _, Nota2, Estudiante),
	estudiante(Nombre, NuevaNota1, Nota2, NuevoEstudiante).
% query
Estudiante = [jorge, 7, 4],
modificarNota1(Estudiante, 5, Estudiante1).
```

## Manipulación directa de los elementos de una lista
Una lista, independiente de su largo o contenido, está conformada de dos componentes: una **cabeza** (el primer elemento de una lista) y una **cola** (el resto de la lista).

Es posible segmentar ambas componentes mediante el uso del operador `|`
Un ejemplo, si se tiene la lista [1, 2, 3, 4], ésta se puede descomponer en sus elementos de la siguiente manera:

```prolog
Lista = [1, 2, 3, 4]
      = [1 | [2, 3, 4]]
      = [1 | [2 | [3, 4]]]
      = [1 | [2 | [3 | [4]]]]
```

```prolog
%query
[1, 2, 3, 4]=[1| [2 | [3 | [4]]]].
```

---
## Recursividad
Al igual que en el paradigma funcional, si se desea ejecutar una operación que vaya revisando todos los elementos de una estructura, se debe hacer uso de la **recursión**, que consiste en llamadas de una función a sí misma, en las que se va revisando el cumplimiento de una condición o caso base.

En Prolog, puesto que no existe el concepto de "función", y dada su naturaleza lógica, la implementación de un procedimiento lógico se realiza de forma distinta:

Para los casos base, éstos (según se requiera) se declaran como relaciones o reglas en las que se pregunta respecto del cumplimiento de una determinada clausula; mientras que para las llamadas recursivas, se declara una regla que se "cumple" cuando al evaluar nuevamente (por ejemplo, avanzar al siguiente elemento de una lista) en los casos base, alguno de ellos retorna `true`, terminando el funcionamiento del programa.

En el caso de que se hayan revisado todos los elementos de una estructura, y no se satisfaga ninguna de las condiciones planteadas, el programa retorna `false`. 

Por ejemplo, determinar si alguno de los elementos de una lista cualquiera es par o no.

```prolog
%Se define la regla es_par/1, que es la que se encarga de realizar la comparación matemática de si un valor cualquiera es par o no.
es_par(Valor):-
	(Valor mod 2) =:= 0.
%Luego, se define el caso base, que revisa si el primer elemento de la lista actual es par o no.
% De serlo, se revisa el siguiente elemento de la lista.
% De lo contrario, retorna false, terminando la ejecución del programa.
es_lista_par([Cabeza | _]):-
	\+(es_par(Cabeza)).      % \+ (not) permite cambiar el valor de true → false para
	                         % evitar que se deje de ejecutar la función.
%Por último, se define la regla que realiza la llamada recursiva para seguir revisando los elementos de la lista.
es_lista_par([_ | Cola]):-
	\+(es_lista_par(Cola)).  % \+ permite indicar cuando deja de ejecutarse la función,
	                         % al encontrarse un elemento impar.
% query
es_lista_par([2, 4, 6, 8, 10]).
```


Cabe aclarar que es posible crear reglas con el mismo nombre y número de parámetros, como lo es el caso de `es_lista_par/1` 

Observación: Para la implementación de una función recursiva que haga uso de la recursión de cola, se declara una regla que recibe los parámetros de entrada y salida, que permite relacionar los parámetros entregados con un "*acumulador*" que almacena todas las soluciones parciales.