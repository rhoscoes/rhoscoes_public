#include <cs50.h>
#include <stdio.h>

int main(void) {

    long card_number; // Variable para almacenar el número de tarjeta de crédito

    // Solicitar al usuario ingresar un número de tarjeta de crédito
    do {

        card_number = get_long("Number: ");

    } while (card_number < 0); // Repetir mientras el número ingresado sea menor que 0

    int sum = 0; // Inicializar la variable para almacenar la suma de los dígitos procesados

    int digit_count = 0; // Inicializar contador de dígitos procesados

    long num = card_number; // Crear una copia del número de tarjeta de crédito

    // Procesar cada dígito del número de tarjeta de crédito
    while (num > 0) {

        int digit = num % 10; // Obtener el último dígito del número

        if (digit_count % 2 == 0) { // Verificar si el dígito debe ser multiplicado por 2

            sum += digit; // Sumar el dígito directamente

        } else {

            int doubled_digit = digit * 2; // Multiplicar el dígito por 2

            sum += (doubled_digit % 10) + (doubled_digit / 10); // Sumar los dígitos del resultado de la multiplicación
        }

        num /= 10; // Eliminar el último dígito del número

        digit_count++; // Incrementar el contador de dígitos procesados
    }

    // Verificar el tipo de tarjeta y la validez según el algoritmo de Luhn
    if (sum % 10 == 0)
    {
        if ((card_number >= 340000000000000 && card_number < 350000000000000)
        || (card_number >= 370000000000000 && card_number < 380000000000000))
        {
            printf("AMEX\n"); //El numero es de AMEX
        }
        else if ((card_number >= 5100000000000000 && card_number < 5600000000000000)
        || (card_number >= 2221000000000000 && card_number < 2721000000000000))
        {
            printf("MASTERCARD\n");  //El numero es de MASTERCARD
        }
        else if ((card_number >= 4000000000000 && card_number < 5000000000000)
        || (card_number >= 4000000000000000 && card_number < 5000000000000000))
        {
            printf("VISA\n"); //El numero es de VISA
        }
        else
        {
            printf("INVALID\n"); //El numero es INVALIDO
        }
    }
    else
    {
        printf("INVALID\n"); //El numero es INVALIDO
    }

    return 0;
}
