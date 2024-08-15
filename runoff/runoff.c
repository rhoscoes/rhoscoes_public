#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates

int voter_count; // cantidad total de votantes que participan en la elección

int candidate_count; // cantidad total de candidatos que se postulan en la elección

// Function prototypes

bool vote(int voter, int rank, string name);
/*se encarga de procesar el voto de un votante en una determinada posición de preferencia para un candidato específico*/

void tabulate(void); /*calcula los totales de votos actuales para cada candidato que aún no ha sido eliminado*/

bool print_winner(void); /*imprime el nombre del candidato ganador si ya ha sido determinado*/

int find_min(void); /*determina la menor cantidad de votos que ha recibido cualquier candidato que aún está en la elección*/

bool is_tie(int min); /*verifica si hay un empate entre los candidatos restantes en la elección*/

void eliminate(int min); /*elimina al candidato que ha recibido el número mínimo de votos en la elección*/

int main(int argc, string argv[])

/*int argc: Representa el número de argumentos de la línea de comandos pasados al programa
  argv[]: Es un array de strings que contiene los argumentos de la línea de comandos*/
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n"); // verifica si la cantidad de argumentos pasados al programa es menor que 2

        return 1;
    }

    // Populate array of candidates

    candidate_count = argc - 1; // argc - 1, primer argumento (argv[0]) es el nombre del programa

    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);

        return 2; // verifica si el número de candidatos calculado es mayor que el máximo permitido
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        /*Se asigna el nombre del candidato al campo name del candidato i.
        Se utiliza argv[i + 1] para obtener el nombre del candidato correspondiente al argumento i + 1,
        ya que el primer argumento (argv[1]) contiene el nombre del primer candidato*/

        candidates[i].votes = 0; // el candidato i empieza la eleccion con 0 votos.

        candidates[i].eliminated = false;
        //Se establece que el candidato i no ha sido eliminado aún, asignando false al campo eliminated o eso deberia xd.
    }

    voter_count = get_int("Number of voters: "); //solicitar al usuario que ingrese el número de votantes para la elección

    if (voter_count > MAX_VOTERS) // verifica si el número de votantes ingresado es mayor que el máximo permitido
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) // preferencias de clasificación
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++) // orden de preferencia
        {
            string name = get_string("Rank %i: ", j + 1);
            // solicita al usuario que ingrese el nombre del candidato que desea clasificar en la posición j + 1

            // Record vote, unless it's invalid
            if (!(vote(i, j, name)))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates

        int min = find_min(); // determina cuál es el candidato que tiene el menor número de votos

        bool tie = is_tie(min); // determina si existe un empate entre los candidatos restantes en la elección

        // If tie, everyone wins

        if (tie) // empate
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!(candidates[i].eliminated)) // verifica la falsedad del argumento
                {
                    printf("Empate: %s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)

// voter (índice del votante)
// rank (posición de preferencia del candidato)
// name (nombre del candidato por el que se está votando)

{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        /*devuelve 0 si las cadenas son iguales, lo que significa que se ha
          encontrado un candidatocuyo nombre coincide con el nombre proporcionado*/

        {
            preferences[voter][rank] = i;
            /*se asigna el índice i de ese candidato en el arreglo de candidatos a la
            posición de preferencia rank del votante voter en el arreglo preferences*/

            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int indice_candidatos = preferences[i][j];
            /*accede a la matriz de preferencias preferences
              para obtener el índice del candidato que el votante
              en la posición i ha colocado en la posición de preferencia j*/

            if (!(candidates[indice_candidatos].eliminated)) // verifica la faseldad del argumento
            {
                candidates[indice_candidatos].votes++;
                /*se incrementa el contador de votos (votes) del
                  candidato en candidates[candidate_index].votes
                  y se utiliza break para salir del bucle interno*/

                break;
            }
        }
    }
}

// Print the winner of the election, if there is one

bool print_winner(void)

// verifica si algún candidato ha obtenido más de la mitad de los votos

{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (voter_count / 2))
        // verifica si los votos de candidates[i].votes es mayor a la mitad del numero de votantes

        {
            printf("Ganador: %s\n", candidates[i].name); // imprime al candidato ganador

            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minimo = voter_count;
    /* el primer candidato no eliminado que se encuentre tenga
       al menos tantos votos como el número total de votantes, de modo
       que cualquier otro candidato no eliminado que se encuentre tenga
       menos votos que este valor inicial*/

    for (int i = 0; i < candidate_count; i++)
    {
        if (!(candidates[i].eliminated) && (candidates[i].votes < minimo))
        /*verifica si el candidato no ha sido eliminado y si el número
          de votos del candidato es menor que el valor actual de minimo*/

        {
            minimo = candidates[i].votes;
            // se actualiza el valor de min con el número de votos del candidato (candidates[i].votes),
        }
    }
    return minimo; // actualiza minimo
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int minimo)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!(candidates[i].eliminated) && (candidates[i].votes != minimo))
        /*verifica si el candidato no ha sido eliminado y si el número de votos
          del candidato es diferente del valor mínimo*/

        {
            return false; // no hay empate
        }
    }
    return true; // hay empate
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int minimo)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == minimo) // verifica si el número de votos del candidato i es igual al valor mínimo
        {
            candidates[i].eliminated = true; // elimina al candidato i
        }
    }
}
