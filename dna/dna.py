import csv
import sys

def main():

    # Verifica el uso de la línea de comandos
    if len(sys.argv) != 3:

        print("Uso correcto: python dna.py archivo_base_de_datos.csv archivo_secuencia_adn.txt")

        sys.exit(1)

    # Lee el archivo de la base de datos
    base_de_datos = sys.argv[1]

    try:

        with open(base_de_datos, 'r') as d_b:

            perfiles = list(csv.reader(d_b))

    except FileNotFoundError:

        print(f"El archivo {base_de_datos} no existe.")

        sys.exit(1)

    # Lee el archivo de la secuencia de ADN
    secuencia_ADN_Archivo = sys.argv[2]

    try:

        with open(secuencia_ADN_Archivo, 'r') as ADN:

            secuencia_ADN = ADN.read().strip()

    except FileNotFoundError:

        print(f"El archivo {secuencia_ADN_Archivo} no existe.")

        sys.exit(1)

    # Encuentra la longitud de la ejecución más larga de cada STR en la secuencia de ADN

    identificador_str = perfiles[0][1:]  # Obtén los nombres de los marcadores STR desde la primera fila de la base de datos

    # Accede a los elementos desde el segundo hasta el último

    secuencia_larga = []

    for marcador in identificador_str:

        secuencia_larga.append(longest_match(secuencia_ADN, marcador))

        #Para cada marcador en identificador_str, se llama a una función llamada
        #longest_match pasando dos argumentos: secuencia_ADN y marcador

    # Compara las coincidencias encontradas con los perfiles en la base de datos
    for perfiles in perfiles[1:]:

        #---

        nombre, *valores_perfil = perfiles

        #Se desempaqueta la fila actual de la base de datos.

        #El primer elemento se asigna a nombre, y los demás elementos se agrupan
        #en la lista valores_perfil

        #---

        if all(int(valor_perfil) == run for valor_perfil, run in zip(valores_perfil, secuencia_larga)):


            #Se verifica si todos los valores en valores_perfil coinciden con los valores en secuencia_larga.

            #La función zip combina los elementos de ambas listas en pares, y luego se compara cada par.

            #Si todas las comparaciones son verdaderas, se ejecuta el siguiente bloque de código, print(f"{nombre}").

         #---

            print(f"{nombre}")

            return

    print("No match")

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0

    subsequence_length = len(subsequence)

    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length

            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:

                count += 1

            # If there is no match in the substring
            else:

                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run

main()
