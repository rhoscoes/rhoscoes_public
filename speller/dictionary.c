#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];

    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 5381; //N de potencias de 2

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lowercase_word[LENGTH + 1]; // Arreglo para almacenar la palabra en minusculas

    for (int i = 0; word[i]; i++) // Recorre cada caracter de la palabra
    {
        lowercase_word[i] = tolower(word[i]); // Convierte el caracter a minuscula
    }
    lowercase_word[strlen(word)] = '\0'; // Agrega el caracter nulo al final de la cadena

    unsigned int index = hash(lowercase_word); // Calcula el índice de la palabra en la tabla hash

    node *cursor = table[index]; // Puntero al nodo en la posicion index de la tabla

    while (cursor != NULL) // Recorre la lista enlazada en esa posicion de la tabla
    {
        if (strcmp(cursor->word, lowercase_word) == 0) // Compara la palabra con la palabra en el nodo actual
        {
            return true; // Devuelve verdadero si la palabra esta en el diccionario
        }
        cursor = cursor->next; // Avanza al siguiente nodo
    }
    return false; // Devuelve falso si la palabra no esta en el diccionario
}

// Funcion para calcular el hash de una palabra
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0; // Inicializa el valor de hash en 0

    for (int i = 0; word[i] != '\0'; i++) // Recorre cada caracter de la palabra
    {
        hash_value = (hash_value * 31) + word[i]; // Calcula el nuevo valor de hash
    }

    return hash_value % N; // Reduce el valor de hash al tamaño de la tabla
}

//Fuente: version adaptada del algoritmo de DJB2.

// Carga el diccionario en memoria, devuelve verdadero si tiene éxito, de lo contrario falso
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r"); // Abre el archivo en modo lectura

    if (file == NULL) // Verifica si se pudo abrir el archivo
    {
        return false; // Devuelve falso si no se pudo abrir el archivo
    }

    char word[LENGTH + 1]; // Arreglo para almacenar una palabra del diccionario

    while (fscanf(file, "%s", word) != EOF) // Lee palabras del archivo hasta el final
    {
        node *new_node = malloc(sizeof(node)); // Asigna memoria para un nuevo nodo

        if (new_node == NULL) // Verifica si se pudo asignar memoria
        {
            fclose(file); // Cierra el archivo

            return false; // Devuelve falso si no se pudo asignar memoria
        }
        strcpy(new_node->word, word); // Copia la palabra al nodo

        unsigned int index = hash(word); // Calcula el índice de la palabra en la tabla hash

        new_node->next = table[index]; // Establece el siguiente del nuevo nodo al nodo actual en esa posicion

        table[index] = new_node; // Actualiza la tabla con el nuevo nodo
    }

    fclose(file); // Cierra el archivo

    return true; // Devuelve verdadero si se cargo el diccionario correctamente
}

// Devuelve el numero de palabras en el diccionario si esta cargado, de lo contrario 0
unsigned int size(void)
{
    unsigned int count = 0; // Inicializa el contador de palabras en 0

    for (int i = 0; i < N; i++) // Recorre la tabla hash
    {
        node *cursor = table[i]; // Puntero al nodo en la posicion i

        while (cursor != NULL) // Recorre la lista enlazada en esa posicion
        {
            count++; // Incrementa el contador de palabras

            cursor = cursor->next; // Avanza al siguiente nodo
        }
    }
    return count; // Devuelve el total de palabras en el diccionario
}

// Libera el diccionario de la memoria, devuelve verdadero si tiene éxito, de lo contrario falso
bool unload(void)
{
    for (int i = 0; i < N; i++) // Recorre la tabla hash
    {
        node *cursor = table[i]; // Puntero al nodo en la posicion i

        while (cursor != NULL) // Recorre la lista enlazada en esa posicion
        {
            node *temp = cursor; // Guarda el nodo actual en una variable temporal

            cursor = cursor->next; // Avanza al siguiente nodo

            free(temp); // Libera la memoria del nodo guardado
        }
        table[i] = NULL; // Establece el puntero en esa posicion a NULL
    }
    return true; // Devuelve verdadero si se libero la memoria correctamente
}
