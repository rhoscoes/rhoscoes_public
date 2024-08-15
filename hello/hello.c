#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string so_and_so = get_string("Soy un codigo escrito en C ¿Cuál es tu nombre?: ");
    printf("¡Hola, %s!\n", so_and_so);
    return 0;
}
