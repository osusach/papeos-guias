**Requisitos de la gestión de memoria**

| Requisito           | Definición    |
| :------------------ | :-------------|
| Reubicación         | No es posible conocer de antemano la ubicación en la que un proceso se cargará en la memoria principal.<br><br>Si es que un proceso es llevado al disco durante su ejecución¹, luego al volverse a cargar en la memoria, su ubicación será distinta a la anterior.<br><br>Las referencias a memoria (datos o instrucciones dentro del mismo proceso) deben ser traducidas a direcciones de la memoria física.<br><br>En base a lo anterior, se distinguen 3 tipos de direcciones:<ul><li>**Virtuales o lógicas**: Referencias a memoria</li><li>**Físicas o reales**: Posiciones en la memoria principal</li><li>**Relativas**: Desplazamientos en torno a una posición en específico.</li></ul>Finalmente, la traducción se lleva a cabo con soporte del *hardware*.<br>![soporteHardware.png](sources/Administracion%20de%20memoria/soporteHardware.png) |
| Protección          | Los procesos deben estar protegidos de accesos indebidos a su respectivo espacio de direcciones.<br><br> Para ello, el sistema operativo es quien **verifica** —traduciendo la referencia a memoria en tiempo de ejecución— que la dirección física obtenida no apunte fuera de la imagen del proceso.<br><br>En caso contrario, es el procesador quien **lleva a cabo** las medidas de protección necesarias (por ejemplo, abortar el proceso actual, por medio de un `segmentation fault`)                                                                                                                                                                                                                                                                                                                   |
| Compartición        | Se debe permitir que varios procesos/hebras compartan y accedan a una misma porción de la memoria principal (memoria compartida)²                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| Organización lógica | Un programa está organizado en módulos (código, datos, ...), los cuales:<ul><li>Pueden compilarse independientemente entre sí.</li><li>Pueden contar con distintos grados de protección (solo lectura, <i>execute-only</i>)</li><li>Pueden compartirse entre procesos.</li></ul>Lo anterior está presente en sistemas que particionan la memoria por medio de **segmentación**.                                                                                                                                                                                                                                                                                                                                                                                                                                |
| Organización física | La memoria de un ordenador se divide en dos:<ul><li>Memoria principal (memoria o RAM): Proporciona un rápido acceso a los datos e instrucciones en uso, pero a un alto costo, además de ser volátil; </li><li>Memoria secundaria (disco): Más lenta, pero permite almacenar programas y datos a largo plazo, más barata.</li></ul>El flujo de datos entre ambos es responsabilidad del sistema operativo.                                                                                                                                                                                                                                                                                                                                                                                                      |
[¹]: Recordando el concepto de *swapping*, en el que un proceso que se encuentre cargado en la memoria principal, ya sea *en ejecución*, *listo*, o *bloqueado*, pasa a la memoria secundaria o disco; permitiendo maximizar la utilización del procesador.
[²]: Lo anterior resulta ser más ventajoso en comparación a que todos los procesos/hebras tuviesen una copia en particular de la memoria, al trabajar con un dato de gran tamaño.
## Particionamiento de la memoria

| Técnica               | Descripción                                                               | Ventajas/Desventajas                                                                                                                                                           |
| :-------------------- | ------------------------------------------------------------------------- | :-------------------------------------------------------------- |
| Particionamiento fijo | Se divide la memoria principal en particiones de igual o distinto tamaño. | Si un proceso se carga en una partición de mayor tamaño, la ocupa por completo, malgastando el espacio interno restante (**fragmentación interna**: depende del proceso mismo) |

| Técnica                   | Descripción                                                                                                                       | Ventajas/Desventajas                                                                                                                                                                                                |
| :------------------------ | :-------------------------------------------------------------------------------------------------------------------------------- | :-------------------------------------------------------------- |
| Particionamiento dinámico | Se van creando particiones en la memoria principal a medida que se van cargando procesos en ésta, del tamaño del proceso cargado. | Al terminar su ejecución, las particiones generadas se conservan, lo que puede llevar a la creación de múltiples particiones pequeñas esparcidas por la memoria (**fragmentación externa**: no depende del proceso) |

> [!observacion] Algoritmos de ubicación
> Una forma de evitar que se produzca fragmentación externa sería ir decidiendo en qué bloques se deben ir cargando los procesos en base a un determinado criterio, para lo cual existen los siguientes algoritmos:
> * *First-fit*: Se escoge la primera partición de arriba a abajo (↓)
> * *Best-fit*: Se escoge la partición que deje el menor espacio libre
> * *Next-fit*: Lo mismo que *first-fit*, pero invertido (↑)
> 
> También existe el *worst-fit*, que se escoge la partición de mayor tamaño, pero como su nombre alude, viene a ser el peor criterio para escoger particiones.
> 
> $$\text{first-fit} > \text{next-fit} > \text{best-fit} > \text{worst-fit}$$

| Técnica         | Descripción                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| :-------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Sistema *buddy* | Combina tanto los esquemas de particionamiento fijo y dinámico, al considerar a la memoria principal como una partición de tamaño $2^U$, al cargar un proceso de tamaño $s$ en memoria, se debe comprobar que $2^{U-1} < s \leq 2^{U}$, donde:<ul><li>Si se cumple, se asigna dicha partición</li><li>De lo contrario, el bloque principal se divide en dos, y se revisa la misma condición para uno de las dos sub-particiones de tamaño $2^{U-1}$</li></ul>Produce fragmentación interna. |

Un ejemplo del esquema anterior: ![ejemploSistBuddy.png](sources/Administracion%20de%20memoria/ejemploSistBuddy.png)

| Técnica           | Descripción                                                                                                                                                                                                                                                                                                                                                                                                 | Ventajas/Desventajas                                                                                | Direccionamiento                                                                                                                                                                                                                                                                                                                                                             |
| :---------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Paginación simple | Tanto la memoria como los procesos se dividen en bloques idénticos y de igual tamaño¹: **marcos** para la memoria física, y **páginas** para las imágenes de cada proceso.<br><p align="justify">El sistema operativo mantiene un registro de las páginas de cada proceso a través de su respectiva **tabla de página**², donde cada entrada contiene el número del marco en que se encuentra cargada.³</p> | No existe fragmentación externa, pero **podría existir fragmentación interna en la última página**⁴ | Las direcciones físicas y virtuales cuentan con la misma cantidad de bits⁵, determinada por el sistema operativo.<br><br>Ambas cuentan con su número de página/segmento y *offset*.<br><br>Para obtener el número del marco, solo se debe acceder a la entrada de la tabla de página indicada por el número de la dirección virtual.<br><br>![ejDireccPagSimple2.png](sources/Administracion%20de%20memoria/ejDireccPagSimple2.png) |

[¹]: Dicho tamaño generalmente suele ser de 8kB

[²]: Las cuales son cargadas dentro de la memoria física.

[³]: Y a su vez, cada marco contiene información sobre el proceso y la página que alberga. 

[⁴]: Esto es, debido a que como todas las páginas comparten un tamaño fijo entre sí, puede ocurrir que la última página tenga un tamaño mayor al que el proceso realmente utilice, por ende se malgasta.

[⁵]: Salvo que se indique lo contrario.

> Por ejemplo: para un sistema de $16 \ bits$, y de un tamaño de página de $1kB$: ![ejDireccPagSimple.png](sources/Administracion%20de%20memoria/ejDireccPagSimple.png)

| Técnica             | Descripción                                                                                                                                                                                                                                                                                                                                     | Ventajas/Desventajas                  | Direccionamiento                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| :------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Segmentación simple | Un proceso se divide en múltiples segmentos¹ de largo variable², tal que se van cargando en particiones o bloques libres de la memoria principal.<br><br>El sistema mantiene un registro de ellos por medio de tablas de segmentos por proceso, donde cada entrada contiene la dirección base del segmento en memoria principal, y su longitud. | Puede sufrir de fragmentación externa | Al igual que paginación simple, las direcciones físicas y virtuales son del mismo tamaño³ y dependen del sistema operativo.<br><br>Sin embargo, solamente las virtuales están compuestas de un número de segmento y *offset*; donde éste último se suma a la dirección base indicada por el número del segmento para obtener la dirección real.<br><br>En el caso que la dirección obtenida sea mayor al largo del segmento, se produce un error no recuperable de tipo `segmentation fault`<br>![ejDireccSegSimple.png](sources/Administracion%20de%20memoria/ejDireccSegSimple.png) |

[¹]: Notar que dichos segmentos son visibles para el programador, mientras que las páginas generadas por la técnica de paginación simple no lo son.

[²]: Cada segmento cuenta con un tamaño máximo. 

[³]: Salvo que se indique lo contrario.

> [!definicion]
> El largo, o bien, la cantidad de entradas de una tabla de páginas o segmentos se calcula como "2 elevado al número de $bits$ necesarios para representar el número de página o segmento".
> 
> Por ejemplo, para una dirección virtual de $32 \ bits$, donde $12$ de ellos se utilicen para el número de página o segmento, el total de entradas de su tabla de páginas será de $2^{12}$

> [!observacion] Observación
> En los esquemas de paginación y segmentación simple, a diferencia del particionamiento fijo y dinámico, <u>los bloques (páginas o segmentos) no necesariamente deben estar contiguos en la memoria</u>.

> [!definicion] Carga y enlazamiento de programas
> Para un proceso, todos sus módulos y librerías se unen por medio de un *linker* (compilador), y son cargados a memoria, por medio de un *loader*, proveniente del sistema operativo.
> 
> Existen 3 tipos de carga, las cuales son:
> * **Carga absoluta**: Se traduce en tiempo de ejecución, tal que los procesos pueden suspenderse y volverse a cargar en memoria; método más utilizado en la actualidad.
> * **Carga absoluta**: Se carga a memoria física directamente, utilizando direcciones de ella, por lo que no hay traducción; los procesos no pueden moverse a otras posiciones de la memoria.
> * **Carga reubicable**: Se traduce en tiempo de carga.
### Memoria virtual
Cabe recalcar que hasta este punto, los procesos están alojados dentro del disco, tal que cuando pasan a ejecutarse en el procesador, se cargan completamente, ya sea como un único bloque, o todas sus páginas/segmentos.

Sin embargo, con la introducción del modelo de memoria virtual, éste permite que <u>solamente sea necesario que se carguen algunos de ellos¹, y que se vayan cargando más conforme se necesiten para la ejecución de los procesos</u>.
 
Para ello, utilizando espacio del disco, la memoria virtual genera la "ilusión" de que los procesos están ubicados dentro un gran espacio de direcciones, haciéndoles creer que ya se encuentran cargados dentro de la memoria principal, sirviendo como una expansión de ésta.
 
Lo anterior, junto a la traducción de las direcciones lógicas, por medio del soporte brindado por el *hardware* (procesador), dan origen al concepto de **virtualización**.

En el caso de que se intente referenciar a una página o segmento² que no sea parte del conjunto residente, el procesador genera una interrupción de tipo `page fault`, en la que el sistema operativo interrumpe y bloquea al proceso que provocó el error, y realiza una petición de I/O al disco para obtener la porción referenciada, ejecutando otros procesos en espera de ello.

De esta manera, el modelo de memoria virtual permite tanto que más procesos puedan ejecutarse en la memoria al mismo tiempo³, como la posibilidad de ejecutar un programa cuyo tamaño sea mayor al de la memoria física disponible. 

[¹]: El conjunto de páginas/segmentos cargados en dicho instante en memoria principal recibe el nombre de **conjunto residente**.
[²]: Específicamente, a un dato o instrucción que esté contenido dentro de dicho bloque.
[³]: Asímismo, mejorando la utilización del procesador hasta cierto punto.

Por ejemplo, para un sistema de $32 \ bits$, en el que solo se cuenta con $2 \ GB$ de RAM (memoria principal): ![ejMemVirtual.png](sources/Administracion%20de%20memoria/ejMemVirtual.png) 

| Técnica                              | Descripción                                                                                                                                                                                                                                                                                                                               | Ventajas/Desventajas                                                                                                                                     | Direccionamiento                  |
| :----------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------- |
| Memoria virtual basada en paginación | Similar a la paginación simple, ahora las tablas de página también cuentan con *bits* de control, dentro de los cuales permiten indicar si es que una página está cargada en memoria (**P/V: bit de presencia o validez**), o si una página ha sido modificada desde la última vez que se cargó (**M/S: bit de modificación o suciedad**) | No existe fragmentación externa, mayor grado de multiprogramación, gran espacio de direcciones virtuales; sobrecarga por la compleja gestión de memoria. | Idéntico al de paginación simple. |

> [!ejercicio]
> Si se tiene:
> * Un sistema de $32 \ bits$.
> * Una memoria de $4 \ GB$, donde $1 \ GB$ de ella es utilizada para almacenar tablas de página, donde:
> 	* Cada página tiene un tamaño de $8 \ kB$
> 	* Cada entrada de la tabla está compuesta por $1 \ bit$ de validez, $1 \ bit$ de suciedad, y  $1 \ bit$ de control.
>  * Direcciones físicas de $26 \ bits$ de largo.
> 
> ¿Cuántos procesos se pueden tener en ejecución al mismo tiempo?
> 
> Considerando que —para fines de simplicidad— un proceso estará en ejecución "cuando todas sus páginas estén cargadas en la memoria"; entonces la cantidad de procesos que podrán estar ejecutándose en el sistema se obtiene como "la cantidad de tablas de página que caben dentro de la memoria principal"
> 
> En otras palabras: $$\frac{Tamaño \ de \ la \ memoria \ principal}{Tamaño \ de \ una \ tabla \ de \ página}$$
> 
> Dado que ya se conoce el dato de la memoria principal a utilizar ($1 \ GB$), entonces es necesario calcular el tamaño de una tabla de página, que se obtiene como el producto entre su largo (cantidad de entradas) por su ancho (tamaño o cantidad de bits de una entrada):
> 
> ![ejMemVirtualPag.png](sources/Administracion%20de%20memoria/ejMemVirtualPag.png)  
> 
> Finalmente, haciendo el cálculo, se obtiene que es posible tener hasta $\frac{1 \ GB}{1 \ MB}=\frac{2^{30}}{2^{20}}=2^{10}$ procesos en la memoria al mismo tiempo.

> [!observacion] Tablas de página multinivel
> Uno de los defectos de la memoria virtual basada en paginación, es que puede ocurrir que los procesos lleguen a ocupar una cantidad inaceptable de memoria virtual.
> 
> Una posible alternativa consiste en hacer que las tablas de página se carguen en memoria virtual en lugar de la física, tal que estén sujetas a paginación, provocando que una tabla pueda descomponerse en páginas —al igual que los procesos—, lo cual da origen a una estructura jerárquica conocida como un <u>esquema multinivel</u>.
> 
> Por ejemplo, muchos sistemas suelen hacer uso de un esquema de dos niveles, en el que las tablas de primer nivel o **raíz**¹ indican el marco de la memoria física en el que se encuentran cargadas las páginas de la tabla de página, las que se ordenan en tablas **directorio** (segundo nivel), que si apuntan a las páginas del proceso.
> 
> [¹]: Las únicas tablas que se encuentran en memoria física son las **raíz**. 
> 
> > [!ejemplo]
> > Para un sistema de $32 \ bits$, con páginas de $4kB$ de tamaño, y que cuya entrada de tabla de página es de $4 \ bytes$; en el caso de querer trabajar con 2 niveles de tablas de página, ¿cuál sería su respectivo largo?
> > 
> > Para ello, la cantidad de entradas por cada nivel se estaría entendiendo como "la cantidad de páginas que caben dentro de la tabla de página del nivel actual", lo que queda expresado como:$$\frac{\text{Tamaño de la tabla de página del nivel actual}}{\text{Tamaño de una página}}$$
> > 
> > Conociendo el dato del tamaño de las páginas, el tamaño de la tabla del primer nivel (raíz) se calcularía de la siguiente manera:
> > 
> >  ![ejTablasMultiNivel.png](sources/Administracion%20de%20memoria/ejTablasMultiNivel.png) 
> >  
> >  Reemplazando en la formula, el largo de las tablas de página del segundo nivel sería de $\frac{2^{22}}{2^{12}}=2^{10} \ bytes$, de lo cual también se desprende que su número de página usa $10 \ bits$, modificando la estructura de las direcciones virtuales de la siguiente forma:
> >  
> >  ![dirVirtual2doNivel.png](sources/Administracion%20de%20memoria/dirVirtual2doNivel.png)
> >  
> >  ![ejTP2Niveles.png](sources/Administracion%20de%20memoria/ejTP2Niveles.png) 
> >  
> 

> [!observacion] Tabla de página invertida
> Otra posible solución al problema del espacio de la memoria virtual consiste en hacer que, en lugar de que existan tablas de página para cada proceso, <u>solamente exista una, cuyo largo</u> —en lugar de estar dado por la cantidad de páginas de un proceso— <u>esté dado por la cantidad de marcos de la memoria física</u>, tal y como indica la siguiente figura.
> 
> ![tabPagInvertida.png](sources/Administracion%20de%20memoria/tabPagInvertida.png) 
> 
> En ella, una entrada de dicha tabla está compuesta del número de la página que está (o no) cargada en ella¹, junto al PID del proceso al que pertenece, *bits* de control, y un puntero a un índice de la tabla, conocido como cadena.
> 
> En dicho modelo, la traducción de una dirección virtual a una física se lleva a cabo al aplicar una función de *hash* simple sobre el número de página, que entrega como resultado una posición de la tabla invertida, que indica un número de marco de la memoria principal.
> 
> Ahora bien, puede ocurrir que —por la naturaleza de las funciones de *hash*— para dos números de página, se entregue el mismo marco, lo cual recibe el nombre de "colisión", donde se debe recorrer la tabla hasta encontrar otra entrada disponible, registrando su posición en la cadena de la entrada que provocó la colisión. 
> 
> [¹]: Dicho número coincide con el de dirección traducida.
> 
> > [!ejemplo]
> > Para un sistema de $32 \ bits$, con páginas de $8 \ kB$, y de $1 \ GB$ de memoria física; al utilizar una tabla de página invertida, ¿cuántos marcos hay en memoria principal?
> > 
> > Al igual que en el ejemplo de memoria virtual basada en paginación ―y recordando que tanto las páginas de un proceso como los marcos de la memoria comparten la misma cantidad y tamaño― se utiliza la formula del tamaño de la memoria física, entre el tamaño de las páginas: $$\frac{\text{Tamaño memoria física}}{\text{Tamaño página}}$$
> > Dado que ambos datos vienen dados por el enunciado —$1 \ GB = 2^{30} \ bytes$ y $8 \ kB = 2^{3} \cdot 2^{10} = 2^{13} \ bytes$ respectivamente— al reemplazarlos en la ecuación, se obtiene $\frac{2^{30}}{2^{13}}=2^{17} \ marcos$.

> [!definicion] TLB (*translation buffer cache*)
> Todo acceso a la memoria virtual implica al menos <u>dos accesos a la memoria física</u>, siendo estos el acceso a una página en específico, y a un dato dentro de dicha página respectivamente.
> 
> Sin embargo, la cantidad de accesos ―y por consiguiente, el tiempo invertido en ellos― pueden aumentar de manera considerable de acuerdo al tipo de gestión de memoria utilizado.
> 
> Por ejemplo, para un sistema de paginación multinivel, pueden existir tantos accesos a memorias como niveles hayan; mientras que una tabla de página invertida, existirán tantos accesos como colisiones ocurran.
> 
> Es por ello que la mayoría de esquemas de memoria virtual utilizan un tipo de caché especial de alta velocidad denominado *buffer de traducción anticipada* o TLB, que contiene las entradas de tabla de página utilizadas recientemente¹.
> 
> Al traducir una referencia a memoria, el procesador sigue una serie de pasos para buscar aquella página que contenga el dato o instrucción solicitado, comenzando con:
> 
> * Revisar si es que está cargada dentro de la TLB, tal que de ser así (*hit TLB*), se genera la dirección física utilizando el número de marco ubicado en la misma entrada de la TLB²; de lo contrario (*TLB miss*), se realiza el siguiente paso.
>   ⠀
> * Revisar si ya se encuentra cargada en memoria, comprobando el valor del *bit* de presencia de su entrada en la tabla de página; en dicho caso (*TP hit*), se actualiza la TLB con la página en cuestión, y se genera la dirección física utilizando el marco de su entrada.
>   ⠀
> * Si ninguno de los dos casos se cumple (*TP miss*), se produce un error de tipo `page fault`, en el que el sistema operativo le solicita al procesador una lectura al disco, en la que se cargue la página en cuestión de la memoria secundaria a la principal³ por medio de una operación de I/O, actualizando la tabla de páginas del proceso.
>   
>   Finalmente, se vuelve a buscar la instrucción dentro de la tabla de página, donde ahora si se encontrará, y será llevada a la TLB. 
> 
>  [¹]: Basándose en el principio de localidad temporal.
>
> [²]: A diferencia de la entrada de una tabla de página común, que está compuesta por su número de marco y otros datos, una entrada de la TLB está compuesta tanto por un número de página, como por un número de marco.
>
> [³]: Si llegase a ocurrir que la memoria principal está llena, se debe hacer el reemplazo de alguna de las páginas presentes, lo cual puede estar sujeto a alguna prioridad o algoritmo, como se verá más adelante.
>   
> > [!definicion] Tiempo promedio de generación de una dirección física
> > Cada una de dichas búsquedas cuenta con su propio tiempo de acceso y tasa de ocurrencia de *hit*, las que permiten estimar el tiempo promedio que toma generar una dirección física, la que se desglosa a continuación:
> > 
> > ![tiempoGeneracionDirFisica.png](sources/Administracion%20de%20memoria/tiempoGeneracionDirFisica.png)
> 
> > [!ojo]
> > Si bien es posible definir la TLB en función de la memoria caché como "un tipo de caché especial", <u><b>no son lo mismo</b></u>, dado que mientras una se encarga de almacenar datos e instrucciones, la otra solo almacena porciones de la tabla de página.
> 
> > [!observacion]
> > Dado que la TLB va agregando páginas según se vayan necesitando para la ejecución de un proceso, sin que necesariamente estén ordenadas entre sí por su número de página, puede provocar que —al momento de buscar si se encuentra una página en específico por su respectivo número— pueda llegar a ser costoso en términos de tiempo.
> >
> > Es por ello que, en lugar de que se vayan revisando todas las entradas de la TLB uno por uno, se revisan en simultáneo, con soporte del *hardware*, lo que recibe el nombre de "traducción asociativa" o *associative mapping*, mientras que el sistema utilizado por las tablas de página corresponde a traducción directa o indexación.

> [!definicion] Tiempo de recuperación del dato o instrucción
> De la misma manera en que la TLB permite reducir la cantidad de accesos a memoria física para obtener el número de marco de —contenido dentro de una entrada de tabla de página— durante la traducción de una dirección lógica, al ir cargando directamente las páginas dentro de dicho *buffer*; la memoria caché permite reducir la cantidad de accesos a memoria física <u>al momento de recuperar un dato o instrucción</u> en concreto.
> 
> Para ello, la memoria caché se divide en 2 (o a veces 3) niveles: $L0$ y $L1$, los que cuentan con sus respectivas tasas de éxito (*hit*) y tiempo de acceso asociado.
> 
> ![tiempoRecuperacionDatoInstrucc.png](sources/Administracion%20de%20memoria/tiempoRecuperacionDatoInstrucc.png)
> 
> Finalmente, el **tiempo total de acceso a memoria** queda descrito por la siguiente relación: $$\bar{T}_{\text{acceso memoria}}=\bar{T}_{\text{generación dirección física}} + \bar{T}_{\text{recuperación dato/instrucción}}$$ 

> [!observacion] Consideraciones sobre el tamaño de página
> Idealmente, se prefiere trabajar con páginas de pequeño tamaño, de alrededor de $8 \ KB$, dado que para páginas...
> 
> |...más pequeñas|...más grandes|
> |:----------------|:--------------|
> |<ul><li>Tablas de página de mayor tamaño, por lo que deben situarse en memoria virtual en lugar de la física.</li><li>Un proceso requiere de más páginas para ejecutarse, lo que implica que el procesador constantemente haga <i>swapping</i> de páginas, en lugar de avanzar con la ejecución de éstos (<i><b>trashing</i></b>)</li></ul><center><b>Se pierde localidad</b></center>|<ul><li>Tablas de página de menor tamaño.</li><li>Fragmentación interna.</li><li>Al haber más direcciones por página, se vuelve más difícil encontrar una dirección en concreto,</li><li>Se reduce el tamaño del conjunto residente.</li></ul><center><b>Se pierde localidad </b></center>|
> 
> ![tamañoPaginaVSTasaPageFault.png](sources/Administracion%20de%20memoria/tamañoPaginaVSTasaPageFault.png) 
> 

| Técnica                                                         | Descripción                                                                                                                                                                 | Ventajas/Desventajas                         | Direccionamiento                                                                                                                                                                                                                                                                                                                                                        |
| :-------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Memoria virtual basada en paginación y segmentación combinadas¹ | La memoria virtual se divide en segmentos, los que a su vez también se dividen en páginas.<br><br>En lugar de existir tablas de páginas por proceso, hay por cada segmento. | No hay ni fragmentación externa, ni interna. | Una dirección virtual está compuesta por su *offset*, el número de página del segmento, y el número del segmento en sí.<br><br>Para obtener el número de marco, se debe acceder primero a la tabla de segmentos, de la cual —por medio del número de segmento— se obtiene la dirección en memoria física en la que reside la tabla de página, que contiene dicho marco. |
> [!ejercicio]
> Para un sistema de $64kB$ de memoria física, que están divididos en marcos de $4kB$, y si se tiene un proceso que está dividido en 3 segmentos:
> * $S_{0}$, de $32.768 \ bytes$ 
> * $S_{1}$, de $16.386 \ bytes$
> * $S_{2}$, de $15.870 \ bytes$
>   
> a) ¿Se podrá cargar dicho proceso completamente en memoria?
> b) ¿En cuántas páginas ocurrirá fragmentación interna?
> 
> a) Que un proceso quepa por completo dentro de la memoria en el esquema de memoria virtual basada en segmentación y paginación combinadas implica que <u>todos sus segmentos caben dentro de los marcos (disponibles) de la memoria</u>.
> 
> Para ello, se obtiene la cantidad de marcos como: $\frac{\text{Tamaño disponible memoria}}{\text{Tamaño marco}}=\frac{64 \ [kB]}{4 \ [kB]}=\text{16 marcos}$
> 
> Luego, se revisa cuantos marcos ocupa cada segmento:
> * $S_{0}: \frac{32768 \ bytes}{4 \ kB}=\frac{32768}{4 \cdot 2^{10}}=\text{8 marcos}$
> * $S_{1}: \frac{16386 \ bytes}{4 \ kB}=\frac{16386}{4096}=4,\textcolor{red}{0004 \ldots} \text{ marcos}$
> * $S_{2}: \frac{15870 \ bytes}{4 \ kB}=\frac{15870}{4096}=3,\textcolor{red}{87 \ldots} \text{ marcos}$
> 
> En el caso de $S_{1}$ y $S_{2}$, debido a que <font color="#ff0000"><u>los segmentos no caben exactamente en los marcos</u></font>, se debe usar un marco adicional que cubra lo que falta.
> 
> Por ende, para cargar el proceso entero, se necesitarían $8+4+\textcolor{red}{1}+3+\textcolor{red}{1}=17 \text{ marcos}$, que es mayor a los $16$ marcos de la memoria física, por ende **el proceso no cabe completamente**.
> 
> b) Entendiendo que un segmento se divide en múltiples páginas, donde comparten el mismo tamaño que los marcos, los segmentos $S_{1}$ y $S_{2}$, al no caber exactamente en un marco/página, deben usar uno adicional, provocando fragmentación interna -> <font color="#ff0000">2 páginas</font>.

| Políticas | Descripción                                                                                     | Tipos                                                                                                                                                                                                                                                                |     |
| :-------- | :---------------------------------------------------------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --- |
| *fetch*   | Determina cuando una página es cargada en memoria principal                                     | **Paginación**: Se trae <b><u>una</u></b> página cuando se necesite.<br><br>**Pre-paginación**: Todas las que se necesiten, y las contiguas a estas (principio de localidad)                                                                                         |     |
| Ubicación | Determina donde ubicar una página en memoria principal.<br><br>Importante en segmentación       |                                                                                                                                                                                                                                                                      |     |
| Reemplazo | Determina que página reemplazar cuando no hay marcos disponibles                                | **Cerrado de marcos**: Se "cierra" un marco por medio de un *bit* de cerradura, evitando ser reemplazada.                                                                                                                                                            |     |
| Limpieza  | Determina que página se debe "limpiar" (escribir a memoria secundaria) luego de ser modificada. | **Limpieza por demanda**: Cuando ha sido seleccionada para reemplazo; ello implica dos transferencias a memoria secundaria por&nbsp;`page-fault`<br><br>**Pre-limpieza**: Se escribe antes de ser seleccionada a reemplazo, escribiéndose varias palabras por lotes. |     |

| Algoritmos de reemplazo       | Descripción                                                                                                                                                                                                                                                                                       |     |
| :---------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | --- |
| Algoritmo óptimo              | Se selecciona la página cuyo tiempo hasta la próxima referencia es el más largo.<br><br>Sin embargo, resulta imposible predecir cuando se referenciará.                                                                                                                                           |     |
| *Least Recently Used* (LRU)   | Se reemplaza la página que no se ha referenciado durante más tiempo.                                                                                                                                                                                                                              |     |
| *Least Frecuently User* (LFU) | Se reemplaza la página que ha sido referenciada menos veces.                                                                                                                                                                                                                                      |     |
| FIFO                          | Se reemplaza la página que lleva más tiempo en memoria.                                                                                                                                                                                                                                           |     |
| Política del reloj            | Se reemplaza la página que no está siendo usada, siendo esto indicado por un *bit* de uso.<ul><li>Si el <i>bit</i> está en 1 → 0</li><li>Si el <i>bit</i> está en 0 → 1, y se reemplaza</li></ul> |     |
