#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Solicitar al usuario la altura de la pirámide
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 10); // Verificar que la altura esté entre 1 y 10

    // Imprimir la pirámide alineada a la izquierda
    for (int i = 1; i <= height; i++)
    {
        // Imprimir espacios en blanco para alinear a la izquierda
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // Imprimir los #
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        // Nueva línea al final de cada fila
        printf("\n");
    }

    return 0;
}
