//Trabajo práctico nº2 - Hernández Clara y Obukhova Daria


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>




// Función que dada una palabra, una lista de palabras y la cantidad de palabras en la lista
//se fija si la palabra ya está en el arreglo.
// esta_palabra: char[], char[][], int -> int
// La palabra es representada por un arreglo de chars, la lista de palabras por un arreglo de arreglos de chars y
//la cantidad de palabras puestas en la lista por un entero.
// Devuelve un entero que representa si está o no la palabra. 0 si está y devuelve
//un número distinto a 0 si no está.

int esta_palabra(char palabra [16], char arreglo_final[][16], int palabras_puestas) {

  int i = 0;
  int contenida=1;

  while (i < palabras_puestas && contenida != 0) {
    contenida = strcmp(arreglo_final[i], palabra);
    i++;
  }

  return contenida;
}


// Función que dada una palabra, una lista de palabras y la cantidad de palabras en la lista
//se fija si está en la lista la palabra invertida.
// no_esta_reversa: char[], char[][], int -> int
// La palabra es representada por un arreglo de chars, la lista de palabras por un arreglo de arreglos de chars y
//la cantidad de palabras puestas en la lista por un entero.

int no_esta_reversa(char palabra[], char arreglo_final[][16], int palabras_puestas) {

  int largo_palabra = strlen(palabra);
  int i, k; //indices de las letras
  char palabra_invertida[largo_palabra];

  for(i = 0, k = largo_palabra-1 ; i<largo_palabra && k >= 0; i++, k--) {
    palabra_invertida[i] = palabra[k];
  }
  palabra_invertida[i] = '\0'; //le agrega el terminador a la palabra.

  return esta_palabra(palabra_invertida, arreglo_final, palabras_puestas);
}



// Función que se fija si la palabra está contenida en alguna otra palabra de la lista.
// no_esta_contenida_en_otraAUX: char[], char[] -> int
// La función toma dos palabras representadas por un arreglo de chars y devuele 1 si la palabra1
//está contenida o es igual en la palabra2. Devuelve 0 en caso contrario.

int no_esta_contenida_en_otraAUX(char palabra1[15], char palabra2[15]) {

	int bandera = 0;
	int largo_palabra1 = strlen(palabra1);

	int m=0;  // índice que representa letras de la palabra1
	int k=0;  // índice que representa letras de la palabra2

	int largo_palabra2 = strlen(palabra2);

	int q = 0; // índice que calcula cantidad de letras iguales en las palabras comparadas

		while (k<largo_palabra2 && bandera == 0) {

			if (palabra2[k]!=palabra1[m]) {
				k++;
				q=0;
				m=0;
			}
			else {
				q++;
				m++;
				k++;
				if (q == largo_palabra1) {
					bandera = 1;
					}
				}
			}


			if (bandera == 1) {
				return 1;
			}
			else {
				return 0;
			}
	}


// Función que compara la palabra con cada palabra de la lista.
// no_esta_contenida_en_otra: char[], char[][], int -> int
// Dado una palabra representada por un arreglo, una lista de palabras representada por un arreglo
//de arreglos de chars y un número representado por un entero, devuelve 1 si no está esta contenida
//en otra palabra y devuelve 0 en caso contrario.

int no_esta_contenida_en_otra(char palabra[], char arreglo_final[][16], int palabras_puestas) {
	int h = 0; // índice que cuenta las palabras chequeadas
	int palabras_iguales = 1;

	while (palabras_iguales == 1 && h < palabras_puestas) {
		if (no_esta_contenida_en_otraAUX(palabra, arreglo_final[h]) || no_esta_contenida_en_otraAUX(arreglo_final[h], palabra)) {
			palabras_iguales = 0;
			 }
		h++;
	 }
return palabras_iguales;
}



// Función que convierte un archivo en un arreglo.
// devuelve_arreglo: char[][] -> int
// Dado un arreglo de arreglos de chars, pasa la información de un archivo a este arreglo.
// Devuelve un un entero que representa la cantidad de palabras que tiene el archivo.

int devuelve_arreglo(char arreglo_base[][16]) {

  FILE*archivo_base = fopen("ejemplo.txt", "r");

  int i=0; //es un índice que cuenta cuantas palabras hay en el archivo.
  while (i < 100 && fgets(arreglo_base[i],17,archivo_base) != NULL) {

    int largo = strlen(arreglo_base[i]);

    arreglo_base[i][largo-1] = '\0'; //largo-1 porque quitamos '\n' y lo reemplazamos por el terminador
    i++;
  }
  fclose(archivo_base);
  return i;
}


// Función que convierte un arreglo en un archivo.
// devuelve_archivo: char[][], int -> None
// Dada una lista de palabras representada por un arreglo de arreglos de chars, y un entero que
//representa la cantidad de palabras en la lista, crea un archivo con las palabras de la lista. Si
//ya existe un archivo con ese nombre, lo pisa con la nueva versión.

void devuelve_archivo(char arreglo_final[][16], int palabras_puestas){
	FILE* archivo_final = fopen("listado.txt", "w"); // w:write

	int i;

	for (i = 0; i < palabras_puestas; i++)
		fprintf (archivo_final, "%s\n", arreglo_final[i]);

	fclose(archivo_final);
}



// Función que pasa a minusculas las palabras del arreglo.
// minuscula: char[][], int -> None
// Dada una lista de palabras representada por un arreglo de arreglos de chars, y un entero
//que representa la cantidad de palabras en la lista, pisa al archivo con las mismas
//palabras pero en letras minúsculas.

void minuscula(char arreglo_base[][16], int cantidad_palabras) {
  int i, j;
  for(i = 0; i< cantidad_palabras ; i++) {
    for (j = 0; arreglo_base[i][j] != '\0' ; j++){
      arreglo_base[i][j] = tolower(arreglo_base[i][j]);
    }
  }
}



// Función que crea la lista de los indices para las palabras posibles.
// f_lista_indices: int[], int -> None
// Dada una lista de números representadas por un arreglo de enteros y un entero que
//representa la cantidad de palabras en la lista de palabras, crea una lista de números
//que representa los índices que tiene la lista de palabras.

void f_lista_indices(int lista_indices[100], int cantidad_palabras) {
  int i;
  for(i=0; i<cantidad_palabras ; i++) {
    lista_indices[i] = i;
  }
}


// Función main.
// Dado un archivo de texto con una lista de palabras, si se puede, devuelve un archivo de texto
//con una lista de palabras elegidas aleatoriamente.
// Va a poder crear el archivo de texto, siempre y cuando, la cantidad de palabras que se eligieron aleatoriamente
//para poner sea igual a la cantidad de palabras que se pueden poner.

int main() {

  srand(time(NULL));

  char arreglo_final[100][16]; //16 letras ya que se icluye el '\0'
  char arreglo_base[100][16];
  int cantidad_palabras = devuelve_arreglo(arreglo_base);  //Se define la cantidad de palabras que tiene el archivo base y se le asigna las palabras a arreglo_base.
  int posiciones_validas[cantidad_palabras]; //dependiendo de la cantidad de palabras se le asigna las posiciones válidas.
  int palabras_posibles = cantidad_palabras; //se inicia las posiciones posibles igual a la cantidad de palabras.
  int palabras_puestas = 0;

  f_lista_indices(posiciones_validas, cantidad_palabras); //se crea la lista de índices.

  minuscula(arreglo_base, cantidad_palabras); //Se pasa todas las palabras a minúsculas.

  if (cantidad_palabras == 0) {
    printf("No hay palabras en la lista.\n");
  }

  else {

    int palabras_por_poner = random()%cantidad_palabras+1; //Según la cantidad de palabras posibles elige aleatoriamente cuantas palabras se van a poner.

    while(palabras_puestas != palabras_por_poner && palabras_posibles >= palabras_por_poner - palabras_puestas) {

      int i = random()%palabras_posibles; //índice de la palabra a evaluar según las posibilidades.
      int posPalabra = posiciones_validas[i]; //toma la posición de la palabra.

      if   ((strlen(arreglo_base[posPalabra]) > 3) &&
            (no_esta_contenida_en_otra(arreglo_base[posPalabra], arreglo_final, palabras_puestas)) &&
            (no_esta_reversa(arreglo_base[posPalabra], arreglo_final, palabras_puestas))) {
              strcpy(arreglo_final[palabras_puestas], arreglo_base[posPalabra]);
              palabras_puestas++;
            }
      palabras_posibles--;
      posiciones_validas[i] = posiciones_validas[palabras_posibles]; //sea o no válida la palabra, elimina la opción para no volverla a elegir.
    }

    printf("La cantidad de palabras por poner fue %d.\n", palabras_por_poner);


    if (palabras_puestas == palabras_por_poner) {
      devuelve_archivo(arreglo_final, palabras_puestas);
      printf("El archivo se creó exitosamente.\n");
      }

      else {
        printf("Pero la cantidad de palabras posibles fueron %d. No se pudo crear el archivo.\n",palabras_puestas);
      }
    }
  return 0;
}
