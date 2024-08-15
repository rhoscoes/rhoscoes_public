#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //itera sobre las filas de la imagen
    {
        for (int j = 0; j < width; j++) //itera sobre las columnas de la imagen
        {

            int promedio = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            /*calcula el promedio de los valores rojo, verde y azul del pixel actual y lo redondea utilizando la funcion `round()`*/

            image[i][j].rgbtRed = promedio; //establece el valor rojo del pixel actual al promedio calculado

            image[i][j].rgbtGreen = promedio; //establece el valor verde del pixel actual al promedio calculado

            image[i][j].rgbtBlue = promedio; //establece el valor azul del pixel actual al promedio calculado
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //itera sobre las filas de la imagen
    {
        for (int j = 0; j < width; j++) //itera sobre las columnas de la imagen
        {

            int R_original = image[i][j].rgbtRed; //almacena el valor rojo original del pixel actual

            int G_original = image[i][j].rgbtGreen; //almacena el valor verde original del pixel actual

            int B_original = image[i][j].rgbtBlue; //almacena el valor azul original del pixel actual


            int R_sepia = round(.393 * R_original + .769 * G_original + .189 * B_original);
            //calcula el valor rojo sepia utilizando los valores RGB originales

            int G_sepia = round(.349 * R_original + .686 * G_original + .168 * B_original);
            //calcula el valor verde sepia utilizando los valores RGB originales

            int B_sepia = round(.272 * R_original + .534 * G_original + .131 * B_original);
            //calcula el valor azul sepia utilizando los valores RGB originales


            image[i][j].rgbtRed = (R_sepia > 255) ? 255 : R_sepia;
            //establece el valor rojo del pixel actual al valor sepia rojo, pero lo limita a 255 si es mayor, por que no funciona ?????

            image[i][j].rgbtGreen = (G_sepia > 255) ? 255 : G_sepia;
            //establece el valor verde del pixel actual al valor sepia verde, pero lo limita a 255 si es mayor

            image[i][j].rgbtBlue = (B_sepia > 255) ? 255 : B_sepia;
            //establece el valor azul del pixel actual al valor sepia azul, pero lo limita a 255 si es mayor
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) //itera sobre las filas de la imagen
    {
        for (int j = 0; j < (width / 2); j++) //itera sobre la mitad de las columnas de la imagen
        {

            RGBTRIPLE temporal = image[i][j]; //almacena temporalmente el pixel actual

            image[i][j] = image[i][width - 1 - j]; //asigna el pixel simetrico al pixel actual

            image[i][width - 1 - j] = temporal; //asigna el pixel actual al pixel simetrico
        }

    }

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporal[height][width]; //declara un arreglo bidimensional `RGBTRIPLE` temporal para almacenar una copia de la imagen

    for (int i = 0; i < height; i++) //itera sobre las filas de la imagen
    {
        for (int j = 0; j < width; j++) //itera sobre las columnas de la imagen
        {
            temporal[i][j] = image[i][j]; //copia el pixel actual de la imagen al arreglo temporal
        }
    }

    // Apply blur filter
    for (int i = 0; i < height; i++) //itera sobre las filas de la imagen
    {
        for (int j = 0; j < width; j++) //itera sobre las columnas de la imagen
        {
            int R = 0; //inicializan las variables para acumular los valores rojo

            int G = 0; // ''' verde

            int B = 0; // ''' azul

            int registro = 0; // se utiliza para contar el numero de pixeles vecinos validos

            // iteracion sobre la cuadricula de 3x3 pixeles
            for (int grid_i = -1; grid_i <= 1; grid_i++)
            {
                for (int grid_j = -1; grid_j <= 1; grid_j++) //itera sobre las columnas de la cuadricula de 3x3 pixeles
                {
                    int final_i = i + grid_i; //calcula la fila del pixel vecino

                    int final_j = j + grid_j; //calcula la columna del pixel vecino

                    // comprobacion si el pixel vecino esta dentro de los limites de la imagen
                    if (final_i >= 0 && final_i < height && final_j >= 0 && final_j < width)
                    {
                        R += temporal[final_i][final_j].rgbtRed; //acumula el valor rojo del pixel vecino

                        G += temporal[final_i][final_j].rgbtGreen; //acumula el valor verde del pixel vecino

                        B += temporal[final_i][final_j].rgbtBlue; //acumula el valor azul del pixel vecino

                        registro++; //incrementa el contador de pixeles vecinos validos
                    }
                }
            }

            //calculo del promedio

            image[i][j].rgbtRed = round((float)R / registro); //calcula el valor rojo promedio del pixel actual y lo asigna a la imagen

            image[i][j].rgbtGreen = round((float)G / registro); //calcula el valor verde promedio del pixel actual y lo asigna a la imagen

            image[i][j].rgbtBlue = round((float)B / registro); //calcula el valor azul promedio del pixel actual y lo asigna a la imagen
        }
    }
}
