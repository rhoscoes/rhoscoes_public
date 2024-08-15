#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int n_argumentos, string arreglo_argumentos[])
{
    if (n_argumentos != 2) // Verifica que se haya proporcionado un único argumento como clave de sustitucion
    {

        printf("Uso: ./substitution 'clave invalida'. Proporcione un solo argumento en la clave de sustitucion.\n"); // Imprime un mensaje de error, deberia xd
        return 1; // Retorna 1 para indicar un error
    }

    string clave = arreglo_argumentos[1]; // Obtiene la clave de sustitución del argumento de línea de comandos, es un string

    int longitud_clave = strlen(clave); // Obtiene la longitud de la clave

    if (longitud_clave != 26) // Verifica que la clave tenga 26 caracteres
    {
        printf("La clave debe contener 26 caracteres. Su clave tiene %d caracteres\n", longitud_clave); // Imprime un mensaje de error
        return 1; // Retorna 1 para indicar un error
    }

    for (int i = 0; i < longitud_clave; i++) // Bucle para verificar la validez de la clave
    {
        if (!(isalpha(clave[i]))) // Verifica que la clave contenga solo caracteres alfabéticos
        {
            printf("La clave debe contener solo caracteres alfabéticos. %c no es un caracter alfabetico.\n", clave[i]); // Imprime un mensaje de error
            return 1; // Retorna 1 para indicar un error, toy cansado jefe
        }

        for (int j = i + 1; j < longitud_clave; j++) // Bucle para verificar caracteres repetidos en la clave
        {
            if (clave[i] == clave[j]) // Compara caracteres para detectar repeticiones
            {
                printf("La clave no debe contener caracteres repetidos. El caracter %c se repite 2 veces o mas.\n", clave[i]); // Imprime un mensaje de error
                return 1; // Retorna 1 para indicar un error
            }
        }
    }

    string texto_sin_formato = get_string("Introducza el texto sin formato: "); // Obtiene el texto sin formato del usuario

    printf("texto encriptado: "); // Imprime un mensaje antes de mostrar el texto encriptado

    for (int i = 0, n = strlen(texto_sin_formato); i < n; i++) // Bucle para encriptar el texto
    {
        if (isalpha(texto_sin_formato[i])) // Verifica si el carácter es alfabético
        {

            //Declaracion ternaria 'char':

            char letra = isupper(texto_sin_formato[i]) ? 'A' : 'a'; // Determina si el carácter es mayúscula o minúscula

            // Calcula el índice de la letra en la clave de sustitucion:

            //ASCII(A) = 2

            int indice = texto_sin_formato[i] - letra; // ASCII(texto_sin_formato[i]) - ASCII(A) = posicion de i en la clave

            //Operador ternario:

                //if isupper(texto_sin_formato[i]: Si la letra en texto sin formato es mayuscula --

                    //toupper(clave[indice]) =  convierte la letra correspondiente en la --clave-- a mayúscula

                //else: si es minuscula

                    //tolower(clave[indice]) = convierte la letra correspondiente en la --clave-- a minúscula

            printf("%c", isupper(texto_sin_formato[i]) ? toupper(clave[indice]) : tolower(clave[indice])); // Encripta y muestra el carácter encriptado
        }

        else
        {
            printf("%c", texto_sin_formato[i]); // Muestra el carácter sin encriptar si no es alfabético
        }
    }

    printf("\n"); // Imprime un salto de línea al final del texto encriptado

    return 0; // Retorna 0 para indicar que el programa se ejecutó correctamente
}
