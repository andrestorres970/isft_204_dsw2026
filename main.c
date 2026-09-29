#include <stdio.h>
#include <string.h> // Quitar el '\n' del final de fgets(): nombre[strcspn(nombre, "\n")] = '\0';
// #include <math.h>

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