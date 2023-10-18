#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// podría mover todas las funciones auxiliares y structs a un archivo .h

// aleatoriamente no funciona puede requerir más de una ejecución
// en LINUX/WSL no funciona (lectura del archivo)

// Lucas Mesias

// structs y funciones auxiliares
typedef struct Laberinto
{
	int n;
	int m;
	char **matriz;
} laberinto;

typedef struct Coordenada
{
	int x;
	int y;
} coord;

typedef struct Camino
{
	int largo;
	coord *lista_coords;
	
} camino;


laberinto crear_lab(int n, int m)
{
	laberinto lab;
	lab.n = n;
	lab.m = m;
	lab.matriz = malloc(sizeof(char *) * n);
	for (int i = 0; i < n; i++)
	{
		lab.matriz[i] = malloc(sizeof(char)*m);
	}
	return lab;
}

laberinto copiar_lab(laberinto copiar)
{
	laberinto lab;
	lab.n = copiar.n;
	lab.m = copiar.m;

	lab.matriz = malloc(sizeof(char *) * lab.n);
	for (int i = 0; i < lab.n; i++)
	{
		lab.matriz[i] = malloc(sizeof(char)*lab.m);
	}

	for (int i = 0; i < lab.n; i++)
	{
		for (int j = 0; j < lab.m; j++)
		{
			lab.matriz[i][j] = copiar.matriz[i][j];
		}
	}
	return lab;
}

void imprimir_laberinto(laberinto lab)
{
	printf("\n");
	for (int i = 0; i < lab.n; i++)
	{
		for (int j = 0; j < lab.m; j++)
		{
			printf("%c",lab.matriz[i][j]);
		}
		printf("\n");
	}
}
camino crear_camino()
{
	camino cam;
	cam.largo = 0;
    return cam;
}

camino camino_append(camino viejo, coord agregar)
{
	camino res;
	res.largo = viejo.largo + 1;

	res.lista_coords = malloc(sizeof(coord) * res.largo);

    for (int i = 0; i < viejo.largo; i++)
    {
        res.lista_coords[i] = viejo.lista_coords[i];
    }
	res.lista_coords[res.largo-1] = agregar;

    free(viejo.lista_coords);

	return res;
}

FILE *abrir_archivo(char *nom)
{
	FILE *fp = fopen(nom, "r");
	if( fp == NULL)
	{
		printf("Problema con el archivo\n");
		return NULL;
	}
	else
	{
		printf("Archivo leido\n");
		return fp;
	}
}

// funciones para el problema
// lectura desde archivo
laberinto leer_laberinto(FILE *fp)
{
	int n, m;
	fscanf(fp, "%d %d\n", &n, &m);
	laberinto lab = crear_lab(n, m);
	printf("n:%d m:%d\n", lab.n, lab.m);

	for (int i=0; i<n; i++)
	{
		fgets(lab.matriz[i],m+1, fp);
		if(strlen(lab.matriz[i]) < m-1)
			i--;
	}
    fclose(fp);
    return lab;
}

// buscar 'e'
coord buscar_e(laberinto lab)
{
	coord res;
	for (int i = 0; i < lab.n; i++)
	{
		for (int j = 0; j < lab.m; j++)
		{
			if(lab.matriz[i][j] == 'e')
			{
				res.x = i;
				res.y = j;
				return res;
			}
		}
	}
}

// funcion que realiza la busqueda
camino buscar(laberinto lab_original)
{
    int acum = 0;

	coord comienzo = buscar_e(lab_original); // la ubicación de la 'e'
    coord coord_actual; // se genera aquí para no crear variables redundantes, es necesario solo una de estas

    // laberinto temporal para no buscar en espacios donde ya buscamos
	laberinto lab_recorrido;

    // para tapar las bifurcaciones
    camino ultima_bifurcacion;
    // para guardar el camino a la salida
    camino camino_salida;

	bool camino_encontrado = false, comprobando_camino = true, camino_viable = true, bifurcacion = false;
	bool dir[4];

	int x,y;
    
    // redundante, ya que se sale de la función con un retorno, pero es necesario un loop "infinito"
	while (!camino_encontrado) 
	{
        x = comienzo.x; // comienza desde 'e' cada vez que termine con una bifurcacion
        y = comienzo.y;
        lab_recorrido = copiar_lab(lab_original); // se crea la copia temporal para evitar caminos redundantes
        free(camino_salida.lista_coords); // se limpia la lista
        camino_salida = crear_camino();
        comprobando_camino = true;

		while (comprobando_camino)
		{
            // para usar las funciones de caminos
            coord_actual.x = x;
            coord_actual.y = y;

            camino_salida = camino_append(camino_salida, coord_actual);

            if (lab_original.matriz[x][y] == 's') // retornar la salida
            {
                return camino_salida;
            }

            if (bifurcacion)
            {
                // guardar la bifurcación para luego taparla
                ultima_bifurcacion = camino_append(ultima_bifurcacion, coord_actual);
            }
            // se tapa con 'x' el camino recorrido en el laberinto temporal
            lab_recorrido.matriz[x][y] = 'x';
            
            // reiniciar los booleanos
            for (int i = 0; i < 4; i++)
            {
                dir[i] = false;
            }

            // revisar las direcciones de busqueda
			// izq
			if (y != 0)
				if (lab_recorrido.matriz[x][y-1] != 'x')
					dir[0] = true;
			// arriba
			if (x != 0) 
				if (lab_recorrido.matriz[x-1][y] != 'x')
					dir[1] = true;
			// der
			if (y != (lab_original.m - 1))
				if (lab_recorrido.matriz[x][y+1] != 'x')
					dir[2] = true;
			// abajo
			if (x != (lab_original.n - 1))
				if (lab_recorrido.matriz[x+1][y] != 'x')
					dir[3] = true;

            acum = 0;
            for (int i = 0; i < 4; i++)
            {
                if (dir[i])
                    acum++; // acum = cant de direcciones a las que se puede mover
            }

            if (acum == 0) // sin salida
            {
                if (bifurcacion) // sin salida + estando en bifurcación
                {
                    // se tapa con 'x' todo el recorrido de la bifurcación
                    for (int i = 0; i < ultima_bifurcacion.largo; i++)
                    {
                        lab_original.matriz[ultima_bifurcacion.lista_coords[i].x][ultima_bifurcacion.lista_coords[i].y] = 'x';
                    }
                    bifurcacion = false;
                    comprobando_camino = false; // re-empezamos desde 'e'
                }
                else
                    return crear_camino(); // camino de largo 0 = no hay camino a la salida
            }

            if (acum > 1) // si hay más de 1 direccion disponible -> bifurcación encontrada
            {
                free(ultima_bifurcacion.lista_coords); // liberar la memoria usada por el camino que se va a borrar
                ultima_bifurcacion = crear_camino(); // reiniciar el camino a uno vacio

                // ultima_bifurcacion = camino_append(ultima_bifurcacion, coord_actual);
                // no se guarda la casilla donde ocurre la bifurcación porque se tapa la misma
                bifurcacion = true;
            }

            // probar con las direcciones disponibles en orden, una a una
            if (dir[0]) // izq
                y--;
            else if (dir[1]) // arriba
                x--;
            else if (dir[2]) // der
                y++;
            else if (dir[3]) // abajo
                x++;
		}
	}
}

// presentación del resultado y otras preparaciones
void buscar_lab(char nom_archivo[30])
{
    FILE *fp = abrir_archivo(nom_archivo);
	laberinto lab = leer_laberinto(fp);

    imprimir_laberinto(lab);
    camino cam = buscar(lab);

    if (cam.largo == 0)
    {
        printf("Camino no encontrado :(\n");
		return;
    }

    int x,y;
    printf("Camino hacia la salida: \n(");
    for (int i = 0; i < cam.largo-1; i++)
    {
        // la resta de los vectores siempre dará (0,-1), (-1,0), (0,1) o (1,0)
        x = cam.lista_coords[i+1].x - cam.lista_coords[i].x; 
        y = cam.lista_coords[i+1].y - cam.lista_coords[i].y;
        if (x == 0 && y == -1)
            printf("L"); // left izq
        if (x == -1 && y == 0)
            printf("U"); // up arriba
        if (x == 0 && y == 1)
            printf("R"); // right der
        if (x == 1 && y == 0)
            printf("D"); // down abajo
    }
    printf(")\n");
	
	char vis;
	printf("Visualizar?: (y/n)\n");
	vis = getc(stdin);
    getc(stdin);
	if(vis == 'y' || vis == 'Y')
	{
        printf("Presione [enter] para ver cada paso\n");
		for (int e=0; e < cam.largo; e++)
		{
			for (int i=0; i<lab.n; i++)
			{
				for (int j=0; j<lab.m; j++)
				{
					if (i == cam.lista_coords[e].x && j == cam.lista_coords[e].y)
						printf(" ");
					else
						printf("%c", lab.matriz[i][j]);
				}
				printf("\n");
			}
            getc(stdin);
		}
	}

}

int main(int argc, char *argv[])
{
    buscar_lab(argv[1]);
}