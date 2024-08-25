**Definición**
* Abstracción o unidad de ejecución más pequeña que un proceso.
* Poseen su propio identificador (TID: *thread ID*)
* En un sistema operativo basado en hebras, los procesos pueden ser ejecutados por:
	* Una sola hebra (proceso monohebreado)[¹]
	* Varias hebras (proceso multihebreado):
		* Que se ejecutan en forma concurrente o intercalada, para un sistema monoprocesador.
		* Que se ejecutan en forma paralela o simultánea, para un sistema multiprocesador.
* Cada hebra contiene su propio *stack* de usuario (que contiene su PC, PSW, *stack pointer*), y *stack* de *kernel*; mientras que el resto de elementos de la imagen del proceso son compartidos entre ellas.[²]

[¹]: Hasta este punto, la forma en que se ejecutaban los procesos era similar a la de un proceso monohebreado.
[²]: Esto hace que las hebras sean más ligeras en tamaño, en comparación a los procesos creados por medio de `fork`, quienes al momento de trabajar con un procesos pesados, crean otro de igual tamaño, copiando el código, datos globales, y *heap* de éstos; asimismo, los cambios de contexto entre hebras serán más rápidos, al no requerir de la intervención directa del *kernel*.

> [!observacion] Algunas observaciones
> * En lugar de que un proceso pase de un estado de ejecución a otro (listo, corriendo, bloqueado), moviendo su PCB, ahora lo hará una de sus hebras, con su respectivo TCB (*thread control block*).
> * De la misma manera, ahora se planificarán hebras en lugar de procesos completos.
> * De acuerdo al diseño del sistema operativo, un proceso se dejará de ejecutar cuando sus hebras también dejen de hacerlo.
> * Al crear una hebra, esta utilizará parte del espacio disponible de la imagen de un proceso.
> * Al hacer `fork` de un proceso con hebras, se creará otro proceso con otras hebras.

**Hebras a nivel de usuario y a nivel de *kernel***

|                                           | Usuario                                                                       | *Kernel*                                              |     |
| :---------------------------------------- | :---------------------------------------------------------------------------- | :---------------------------------------------------- | --- |
| **Creación y manejo**                     | Por parte del proceso mismo, a partir de una librería o biblioteca de hebras. | Por parte del *kernel*, usando la API&nbsp;`pthreads` |     |
| **Visibilidad de hebras por el *kernel*** | Invisibles                                                                    | Visibles                                              |     |
| **Tipo de planificación de las hebras**   | Puede estar determinada por el proceso mismo.                                 | Determinada por el sistema operativo.                 |     |
| **Cambios de contexto**                   | No involucra al *kernel*, por lo que no hay cambio de modo.                   | Involucra al *kernel*, cambio de modo y contexto.     |     |
| **¿Paralelismo?**                         | No                                                                            | Solo en sistemas multiprocesador.                     |     |
| **Ante un *syscall*/IO...**               | ...se bloquea el proceso completo[¹]                                          | ...se puede planificar otra hebra del mismo proceso.  |     |
[¹]: Aún así, dado que las hebras se "simulan", el estado de la hebra indica que se sigue ejecutando, cuando en realidad no está haciendo ninguna labor.

<div style="page-break-after: always;"></div>

> [!definicion] Arquitecturas de procesadores paralelos de tipo MIMD, que utilizan memoria compartida
> 
> Tal y como su nombre indica, corresponden a un conjunto de procesadores que operan paralelamente, trabajando sobre una serie de datos e instrucciones contenidas dentro de una memoria compartida, por la cual también se comunican entre sí.
> 
> De acuerdo a la forma en que asignan procesos a los procesadores, existen de dos tipos:
> 
> **<u>Maestro/esclavo</u>**
> El *kernel* solo puede ejecutarse en uno de los procesadores, al cual se le llamará **maestro**, mientras que el resto de procesadores, los **esclavos**, solamente pueden ejecutar procesos en modo usuario. De ésta forma, si se hace un *syscall* en uno de los esclavos, se debe esperar a que el maestro esté libre para hacer el cambio de modo.
> 
> Adicionalmente, solo el maestro puede planificar procesos.
> 
>  **<u>Multiprocesamiento simétrico (SMP)</u>**
>  Al contrario que el anterior, el *kernel* se puede ejecutar en cualquier procesador, y cualquiera de estos puede planificar procesos/hebras.

**API `pthreads`** (**POSIX** *threads*)
* API: *Application Program Interface*, no es una librería.
* Se utiliza por medio de `#include <pthread.h>`

**Creación de una hebra**
* `*thread`: Identificador de la hebra
* `pthread_attr_t`: Parámetros de entrada
* `start_routine`: Función de tipo `void*` que la hebra ejecuta apenas se crea.
	* `(void*)`: Indica que la función recibe un parámetro
	* `*arg`: Argumento para `start_routine()

```c
#include <pthread.h>

int phtread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
```

* En caso de éxito, retorna 0; de lo contrario retorna otro valor.

**Destrucción de una hebra**
* Para destruir la hebra actual:
	* `*status`: Valor de retorno a la hebra padre

```c
#include <pthread.h>

void pthread_exit(void *status);
```

* Para destruir una hebra en específico desde afuera:
	* `thread`: El identificador de la hebra a destruir

```c
#include <pthread.h>

void pthread_cancel(pthread_t thread);
```

<div style="page-break-after: always;"></div>

***Attaching* (*joining*), o acoplar una hebra hija con otra padre**
* Por defecto, al crear una hebra, ésta estará acoplada o `attached` a la hebra padre que ejecutó la instrucción `create`
	* También se dice que la hebra hija creada es `joinable` (`detachstate = PTHREAD_CREATE_JOINABLE`)
* Es posible hacer que la hebra padre espere por un valor retornado por la ejecución de la hebra hija, por medio de `pthread_join()`
* `thread`: Identificador de la hebra hija a unir.
* `value_ptr`: Valor a retornar por la hija.
	* Si no se quiere retornar ningún valor, se inicializa con `NULL`

```c
#include <pthread.h>

int pthread_join(pthread_t thread, void **value_ptr);
```

***Detaching*, o desacoplar una hebra con otra padre**
* Esto quiere decir que la hebra padre no espera por la ejecución de la hebra hija.
* La hebra hija es `no joinable` (`detachstate = PTHREAD_CREATE_DETACHED`)
* Para desacoplarla antes de su creación:

```c
pthread_t t_id;
pthread_attr_t attr;

pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
pthread_create();
```

* Para desacoplarla una vez creada:

```c
pthread_detach(pthread_t thread);
```

**Sincronización entre hebras**
Para asegurarse de que la ejecución de las hebras no genere soluciones erróneas, o que el dato compartido no se corrompa, la API `pthreads` provee dos mecanismos:
* Semáforos *mutex*.
* Variables de condición.