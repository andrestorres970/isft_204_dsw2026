#include <stdio.h>
#include <string.h> // Quitar el '\n' del final de fgets(): nombre[strcspn(nombre, "\n")] = '\0';
// #include <math.h>
#include <ctype.h>

// 29/09/26
// Ej. 2: Atletas.
// Se lee:
// -Nombre de 15 atletas.
// -Tiempo en 3 carreras (s) de 100mts.
// Se devuelve:
//               a. El nombre del atleta que obtuvo el mejor tiempo promedio.
//               b. Dado el nombre de un atleta, informe su mejor tiempo y en qué carrera lo obtuvo.
//               c. Dado un número de carrera obtener el nombre y el tiempo del atleta vencedor.

#define NUMATL 2
#define CHARMAX 101
#define LAPS 3

void charge(char names[][CHARMAX], int times[][LAPS]);
void best_time_overall(char names[][CHARMAX], int times[][LAPS]);

void name_search(char names[][CHARMAX], int times[][LAPS]);
void race_search(char names[][CHARMAX], int times[][LAPS]);
void search_loop(char names[][CHARMAX], int times[][LAPS], void (*name_search)(char names[][CHARMAX], int times[][LAPS]), void (*race_search)(char names[][CHARMAX], int times[][LAPS]));

int main(void)
{
    char names[NUMATL][CHARMAX];
    int times[NUMATL][LAPS];

    char bestTimeAthlete[CHARMAX];

    printf("///////////////////////////////\nWelcome to the athlete analisis app!\n---\n");
    charge(names, times);
    best_time_overall(names, times);
    search_loop(names, times, &name_search, &race_search);

    printf("///////////////////////////////\n");

    return 0;
};

void charge(char names[][CHARMAX], int times[][LAPS])
{

    for (int i = 0; i < NUMATL; i++)
    {
        printf("Insert the name of the n%d athlete: ", i + 1);
        fgets(names[i], CHARMAX, stdin);
        names[i][strcspn(names[i], "\n")] = '\0';

        for (int j = 0; j < LAPS; j++)
        {
            printf("-- Insert the time of lap #%d: ", j + 1);
            scanf("%d", &times[i][j]);
            // printf("\nLap Input -> %d", times[i][j]);
        }
        getchar();
    };
};

void best_time_overall(char names[][CHARMAX], int times[][LAPS])
{
    char bestTimeAthlete[CHARMAX];
    int bestTimeOverall;

    for (int i = 0; i < NUMATL; i++)
    {
        if (i == 0)
        {
            bestTimeOverall = times[i][0];
            strcpy(bestTimeAthlete, names[i]);
        };
        for (int j = 0; j < LAPS; j++)
        {
            if (times[i][j] < bestTimeOverall)
            {
                bestTimeOverall = times[i][j];
                strcpy(bestTimeAthlete, names[i]);
            }
        }
    }

    printf("---\nThe athlete with best overall time is %s (%ds).\n", bestTimeAthlete, bestTimeOverall);
};

void search_loop(char names[][CHARMAX], int times[][LAPS], void (*name_search)(char names[][CHARMAX], int times[][LAPS]), void (*race_search)(char names[][CHARMAX], int times[][LAPS]))
{
    int input;

    do
    {
        printf("*********************************\nChoose the type of search:\n(1) Best time and race by name.\n(2) Winner by race number.\n(0) Exit app.\n*********************************\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            name_search(names, times);
            break;
        case 2:
            race_search(names, times);
            break;
        case 0:
            printf("The app will close.\n");
            break;
        default:
            printf("Input one of the specified values.");
            getchar();
            break;
        }
    } while (input);
};

void name_search(char names[][CHARMAX], int times[][LAPS])
{
    char nameInput[CHARMAX];

    int bestTime, bestRace;

    int wrongInput = 0;
    int match = 0;
    int loop = 1;

    do
    {
        printf("--------------\nBest time and race by name.\nInput the athlete's name: ");
        fgets(nameInput, CHARMAX, stdin);

        // Condicional que controla overflow por superar CHARMAX, y, en caso 0, limpia el '\n' del string.
        if (strchr(nameInput, '\n') == NULL)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            };
        }
        else
        {
            nameInput[strcspn(nameInput, "\n")] = '\0';
        }

        for (int i = 0; nameInput[i] != '\0'; i++)
        {
            if (isdigit(nameInput[i]))
            {
                wrongInput = 1;
                break;
            }
        }

        if (wrongInput)
        {
            printf("\nThe input must only contain letters. Try again.\n");
        }
        else
        {
            for (int i = 0; i < NUMATL; i++)
            {
                if (!strcmp(nameInput, names[i]))
                {
                    match = 1;
                    for (int j = 0; j < LAPS; j++)
                    {
                        if (j == 0)
                        {
                            bestTime = times[i][j];
                            bestRace = j + 1;
                        }
                        else if (times[i][j] < bestTime)
                        {
                            bestTime = times[i][j];
                            bestRace = j + 1;
                        }
                    };

                    printf("\n%s's best time was %ds on race number %d.\n", names[i], bestTime, bestRace);
                    loop = 0;
                    break;
                }
            };
            if (!match)
            {
                printf("\nSpecified name wasn't found. Try again.\n");
            }
        }
    } while (loop);
};

void race_search(char names[][CHARMAX], int times[][LAPS])
{
    getchar();
    int raceInput, match, bestTime;
    char winner[CHARMAX];

    int wrongInput = 0;
    int loop = 1;

    do
    {
        printf("--------------\nWinner by race number.\nInput the number of the race: ");
        scanf("%d", &raceInput);

        if (!isdigit(raceInput))
        {
            printf("\nThe input must be a number. Try again\n");
        }
        else if (raceInput > 3 || raceInput < 1)
        {
            printf("\nValue must be between 1 and 3. Try again\n");
        }
        else
        {
            for (int i = 0; i < NUMATL; i++)
            {
                if (i == 0)
                {
                    bestTime = times[i][raceInput];
                    strcpy(names[i], winner);
                    continue;
                }
                else
                {
                    if (times[i][raceInput] < bestTime)
                    {
                        bestTime = times[i][raceInput];
                        strcpy(names[i], winner);
                    }
                }
            };
            printf("\nThe winner of the race number %d is the athlete %s with a time of %ds.\n", raceInput, winner, bestTime);
        }
    } while (loop);
};
/*
// 29/09/26
// Ej. 1: Competencia de ciclismo.
//  Los participantes hacen dos pruebas. La primera registra tiempo, la segunda numero de vueltas.
//  Se almacenan en arreglos los nombres, tiempo (pp), y vueltas (sp).
//  Se debe calcular:
//                   - Nombre del menor tiempo de la prueba.
//                   - Nombre y tiempo del ciclista con mayor numero de vueltas.

#define FYC 100

int carga(char nombres[][FYC], int tiempoPruebaUno[], int vueltasPruebaDos[], int maxCiclistas);
void calculo_menor_tiempo(char nombres[][FYC], int tiempoPruebaUno[], int maxCiclistas);
void calculo_mayor_vuelta(char nombres[][FYC], int tiempoPruebaUno[], int vueltasPruebaDos[], int maxCiclistas);

int main(void)
{
    int maxCiclistas = 100;
    int ciclistas;

    char nombres[FYC][FYC];
    int tiempoPrubeaUno[FYC];
    int vueltasPruebaDos[FYC];

    printf("///////////////////////////////////\nBienvenido al programa de evaluacion de ciclistas!\nIngrese un numero dentro del input de nombre si desea finalizar la aplicacion (max. 100 ciclistas).\n");

    ciclistas = carga(nombres, tiempoPrubeaUno, vueltasPruebaDos, maxCiclistas);
    printf("Los ciclistas ingresados fueron %d.\n", ciclistas);
    if (ciclistas > 0)
    {
        calculo_menor_tiempo(nombres, tiempoPrubeaUno, ciclistas);
        calculo_mayor_vuelta(nombres, tiempoPrubeaUno, vueltasPruebaDos, ciclistas);
    }

    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");

    return 0;
};

int carga(char nombres[][FYC], int tiempoPruebaUno[], int vueltasPruebaDos[], int maxCiclistas)
{

    int mainLoop = 1;
    int ingresoPruebaUno = 1;
    int ingresoPruebaDos = 1;
    int ciclistas = 0;

    do
    {
        ingresoPruebaUno = 1;
        ingresoPruebaDos = 1;

        printf("---\nIngrese el nombre del ciclista n%d: ", ciclistas + 1);
        fgets(nombres[ciclistas], FYC, stdin);
        nombres[ciclistas][strcspn(nombres[ciclistas], "\n")] = '\0';

        if (isdigit(nombres[ciclistas][0]))
        {
            printf("\nHa ingresado un numero dentro del input de nombre, se finalizara la aplicacion.\n////////////////////////////////////////////////////////////////////////////////////////////////\n");
            mainLoop = 0;
        }
        else
        {
            do
            {
                printf("- Ingrese el tiempo de la primera prueba en segundos enteros: ");
                scanf("%d", &tiempoPruebaUno[ciclistas]);
                if (tiempoPruebaUno[ciclistas] > 0)
                {
                    ingresoPruebaUno = 0;
                }
                else
                {
                    printf("Ingrese un valor mayor a cero.");
                }
            } while (ingresoPruebaUno);
            do
            {
                printf("- Ingrese las vueltas de la segunda prueba: ");
                scanf("%d", &vueltasPruebaDos[ciclistas]);
                if (vueltasPruebaDos[ciclistas] > 0)
                {
                    ciclistas++;
                    ingresoPruebaDos = 0;
                    getchar();
                }
                else
                {
                    printf("Ingrese un valor mayor a cero.");
                }
            } while (ingresoPruebaDos);
        }
    } while (mainLoop);

    return ciclistas;
};

void calculo_menor_tiempo(char nombres[][FYC], int tiempoPruebaUno[], int maxCiclistas)
{
    char nombreMenorTiempo[FYC];
    int menorTiempo;
    int ciclista;

    for (int i = 0; i < maxCiclistas; i++)
    {
        if (i == 0)
        {
            menorTiempo = tiempoPruebaUno[i];
            strcpy(nombreMenorTiempo, nombres[i]);
            ciclista = i;
            continue;
        }
        if (tiempoPruebaUno[i] < menorTiempo)
        {
            menorTiempo = tiempoPruebaUno[i];
            strcpy(nombreMenorTiempo, nombres[i]);
            ciclista = i;
        }
    };

    printf("El ciclista con menor tiempo en la primera prueba es %s (%ds).\n", nombreMenorTiempo, tiempoPruebaUno[ciclista]);
};

void calculo_mayor_vuelta(char nombres[][FYC], int tiempoPruebaUno[], int vueltasPruebaDos[], int maxCiclistas)
{
    char nombreMayorVuelta[FYC];
    int mayorVuelta;
    int ciclista;

    for (int i = 0; i < maxCiclistas; i++)
    {
        if (i == 0)
        {
            mayorVuelta = vueltasPruebaDos[i];
            strcpy(nombreMayorVuelta, nombres[i]);
            ciclista = i;
            continue;
        }
        if (mayorVuelta < vueltasPruebaDos[i])
        {
            mayorVuelta = vueltasPruebaDos[i];
            strcpy(nombreMayorVuelta, nombres[i]);
            ciclista = i;
        }
    };

    printf("El ciclista con mayor numero de vueltas en la segunda prueba es %s (%d),\ncon un tiempo de %ds en la segunda prueba.\n", nombreMayorVuelta, vueltasPruebaDos[ciclista], tiempoPruebaUno[ciclista]);
};
*/
/*
// Ej. 3 (22/9/26): Cantidad indefinida de movimientos de pasajeros, c/u compuestos por 3 arrays:
//                   .a - motivoViaje: 1-Placer, 2-Negocios, 3-Otros.
//                   .b - destino: 1-America, 2-Europa, 3-Otros.
//                   .c - clase: 1-Primera, 2-Turista.
// Se debe calcular:
//               - 1 : % de pasajeros clase turista que viajan a America o Europa.
//               - 2 : % de pasajeros clase primera que viajan por placer.
void carga(int motivoViaje[], int destino[], int clase[], int *totalPasajeros, int *advance);

int cargaMotivo(int motivoViaje[], int i);
int cargaDestino(int destino[], int i);
int cargaClase(int clase[], int i);

void calcularPorcentajes(int totalPasajeros, int motivoViaje[], int destino[], int clase[]);

int main(void)
{
    int motivoViaje[100];
    int destino[100];
    int clase[100];

    int totalPasajeros = 0;
    int advance;

    printf("/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\nA continuación se le solicitará los datos correspondientes a movimientos de pasajeros, respetando un maximo de 100 pasajeros.\nIngrese un caracter diferente a los solicitados para terminar la aplicación.\nEl pasajero con datos incompletos no se incluirá en los calculos.\n");
    carga(motivoViaje, destino, clase, &totalPasajeros, &advance);
    if (advance != 0 && totalPasajeros != 0)
    {
        calcularPorcentajes(totalPasajeros, motivoViaje, destino, clase);
    }
    else if (advance == 0 && totalPasajeros != 0)
    {
        calcularPorcentajes(totalPasajeros, motivoViaje, destino, clase);
    }
    printf("---Total pasajeros: %d---", totalPasajeros);
    return 0;
};

void carga(int motivoViaje[], int destino[], int clase[], int *totalPasajeros, int *advance)
{
    int loop = 1;
    int i = 0;
    int didCharge;

    do
    {
        printf("-----------------------------------------------------\nA continuación se cargarán los datos del pasajero n°%d.\n", i + 1);
        didCharge = cargaMotivo(motivoViaje, i);
        if (didCharge != 0)
        {
            didCharge = cargaDestino(destino, i);
            if (didCharge != 0)
            {
                didCharge = cargaClase(clase, i);
                if (didCharge != 0)
                {
                    printf("Los datos del pasajero n°%d se cargaron correctamente!\n", i + 1);
                    printf("[%d %d %d]\n", motivoViaje[i], destino[i], clase[i]);
                    i++;
                }
                else
                {
                    *advance = 0;
                    loop = 0;
                }
            }
            else
            {
                *advance = 0;
                loop = 0;
            }
        }
        else
        {
            *advance = 0;
            loop = 0;
        }
    } while (loop);
    *totalPasajeros = i;
};

int cargaMotivo(int motivoViaje[], int i)
{
    int input;

    printf("Motivo:\n1 -> Placer.\n2 -> Negocios.\n3 -> Otros.\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        motivoViaje[i] = input;
        printf("Motivo: Placer.\n-----------------------------------------------------\n");
        break;
    case 2:
        motivoViaje[i] = input;
        printf("Motivo: Negocios.\n-----------------------------------------------------\n");
        break;
    case 3:
        motivoViaje[i] = input;
        printf("Motivo: Otros.\n-----------------------------------------------------\n");
        break;
    default:
        input = 0;
        printf("Se ingresó un caracter diferente a los indicados. Se finalizará la aplicación.\n------------------------------------------------------------------------------\n");
        break;
    }

    return input;
};

int cargaDestino(int destino[], int i)
{
    int input;

    printf("Destino:\n1 -> America.\n2 -> Europa.\n3 -> Otros.\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        destino[i] = input;
        printf("Destino: America.\n-----------------------------------------------------\n");
        break;
    case 2:
        destino[i] = input;
        printf("Destino: Europa.\n-----------------------------------------------------\n");
        break;
    case 3:
        destino[i] = input;
        printf("Destino: Otros.\n-----------------------------------------------------\n");
        break;
    default:
        input = 0;
        printf("Se ingresó un caracter diferente a los indicados. Se finalizará la aplicación.\n------------------------------------------------------------------------------\n");
        break;
    }

    return input;
};

int cargaClase(int clase[], int i)
{
    int input;

    printf("Clase:\n1 -> Primera.\n2 -> Turista.\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        clase[i] = input;
        printf("Clase: America.\n-----------------------------------------------------\n");
        break;
    case 2:
        clase[i] = input;
        printf("Clase: Europa.\n-----------------------------------------------------\n");
        break;
    default:
        input = 0;
        printf("Se ingresó un caracter diferente a los indicados. Se finalizará la aplicación.\n------------------------------------------------------------------------------\n");
        break;
    }

    return input;
};

void calcularPorcentajes(int totalPasajeros, int motivoViaje[], int destino[], int clase[])
{

    int turistaAoE = 0;
    int primeraPlacer = 0;
    double promedioTuristaAoE, promedioPrimeraPlacer;

    for (int i = 0; i < totalPasajeros; i++)
    {
        if (destino[i] == 1 || destino[i] == 2)
        {
            if (clase[i] == 2)
            {
                turistaAoE++;
            }
        }
    }

    for (int i = 0; i < totalPasajeros; i++)
    {
        if (clase[i] == 1)
        {
            if (motivoViaje[i] == 1)
            {
                primeraPlacer++;
            }
        }
    }

    promedioTuristaAoE = ((double)turistaAoE / (double)totalPasajeros) * 100.0;
    promedioPrimeraPlacer = ((double)primeraPlacer / (double)totalPasajeros) * 100.0;

    printf("La cantidad de pasajeros que viajaron a America o Europa en clase turista es de %d, representando al %.1f%% del total.\n", turistaAoE, promedioTuristaAoE);
    printf("La cantidad de pasajeros que viajaron en primera, por placer, es de %d, representando al %.1f%% del total.\n", primeraPlacer, promedioPrimeraPlacer);
    printf("/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
};
*/
/*
// Ingresa nombre de alumno, guarda un array de las calificaciones (1-5). Calcula promedio. Al finalizar muestra nombre, notas y promedio.
void ingreso(char nombre[], int notas[], int tamañoNotas, int *notasTotales);
double promedio(int notas[], int notasTotales);
void mostrar(char nombre[], int notas[], double promedioCliente, int notasTotales);
int main(void)
{
    char nombre[50];
    int tamañoNotas = 5;
    int notasTotales = tamañoNotas;
    int notas[tamañoNotas];
    double promedioCliente;

    ingreso(nombre, notas, tamañoNotas, &notasTotales);
    promedioCliente = promedio(notas, notasTotales);
    mostrar(nombre, notas, promedioCliente, notasTotales);

    return 0;
}

void ingreso(char nombre[], int notas[], int tamañoNotas, int *notasTotales)
{
    int i = 0;

    printf("Ingrese el nombre del alumno.\n");
    scanf("%49s", nombre);
    printf("Ingrese las notas del alumno (Entre 1 y 5 notas):\n");
    printf("De ser menos de 5 notas, ingrese un numero negativo para finalizar la carga.\n");

    do
    {
        printf("Nota numero %d: ", i + 1);
        scanf("%d", &notas[i]);
        if (notas[i] < 0)
        {
            printf("Se finaliza la carga de notas.\n");
            *notasTotales = i;
            i = tamañoNotas;
        }
        else if (notas[i] >= 0 && notas[i] <= 10)
        {
            i++;
        }
        else
        {
            printf("Input erroneo, intente ingresando un numero entre 0 y 10.\n");
        }
    } while (i < tamañoNotas);
};

double promedio(int notas[], int notasTotales)
{
    int suma = 0;
    double promedio;

    for (int i = 0; i < notasTotales; i++)
    {
        suma = suma + notas[i];
    };

    promedio = suma / notasTotales;
    return promedio;
};

void mostrar(char nombre[], int notas[], double promedioCliente, int notasTotales)
{
    printf("El alumno %s, con notas ", nombre);
    for (int i = 0; i < notasTotales; i++)
    {
        if (i = notasTotales - 1)
        {
            printf("y %d, ", notas[i]);
        }
        else
        {
            printf("%d, ", notas[i]);
        }
    };
    printf("tiene como promedio final %f", promedioCliente);
};
*/
/*
// Carga de 10 numeros, funcion que muestra los valores e indices (luego de cada carga), y devolución del valor mas grande.
void ingreso(int numeros[10], int tamañoNumeros);
void mostrar(int numeros[10], int i);
void mayor_numero(int numeros[10], int tamañoNumeros);
int main(void)
{
    int input;
    int tamañoNumeros = 10;
    int numeros[tamañoNumeros];

    printf("Ingrese 10 numeros:\n");
    ingreso(numeros, tamañoNumeros);
    mayor_numero(numeros, tamañoNumeros);

    return 0;
}

void ingreso(int numeros[10], int tamañoNumeros)
{
    for (int i = 0; i < tamañoNumeros; i++)
    {
        scanf("%d", &numeros[i]);
        mostrar(numeros, i);
    }

    return;
}

void mostrar(int numeros[10], int i)
{
    printf("El numero ingreasdo es %d, y habita la posición %d.\n", numeros[i], i + 1);
    return;
};

void mayor_numero(int numeros[10], int tamañoNumeros)
{
    int mayorNumero = 0;

    for (int i = 0; i < tamañoNumeros; i++)
    {
        if (mayorNumero < numeros[i])
        {
            mayorNumero = numeros[i];
        };
    };

    printf("El mayor numero del array es %d.\n", mayorNumero);

    return;
};
*/