#include <stdio.h>
#include <string.h>
#include "funciones.h"

#define MAX_PELICULAS 10
#define MAX_CLIENTES 5
#define MAX_LONGITUD 40
#define MAX_HORARIOS 4
#define MAX_RESERVAS 50

int main() {
    char peliculas[MAX_PELICULAS][4][MAX_LONGITUD] = {
        {"The Shawshank Redemption", "Frank Darabont", "Drama", "1994"},
        {"The Godfather", "Francis Ford Coppola", "Crime", "1972"},
        {"The Dark Knight", "Christopher Nolan", "Action", "2008"},
        {"12 Angry Men", "Sidney Lumet", "Drama", "1957"},
        {"Schindler's List", "Steven Spielberg", "Biography", "1993"},
        {"The Lord of the Rings", "Peter Jackson", "Fantasy", "2003"},
        {"Pulp Fiction", "Quentin Tarantino", "Crime", "1994"},
        {"The Good, the Bad and the Ugly", "Sergio Leone", "Western", "1966"},
        {"Fight Club", "David Fincher", "Drama", "1999"},
        {"Inception", "Christopher Nolan", "Sci-Fi", "2010"}
    };

    char horarios[MAX_PELICULAS][MAX_HORARIOS][MAX_LONGITUD] = {
        {"10:00 AM", "1:00 PM", "4:00 PM", "7:00 PM"},
        {"11:00 AM", "2:00 PM", "5:00 PM", "8:00 PM"},
        {"10:30 AM", "1:30 PM", "4:30 PM", "7:30 PM"},
        {"12:00 PM", "3:00 PM", "6:00 PM", "9:00 PM"},
        {"9:00 AM", "12:00 PM", "3:00 PM", "6:00 PM"},
        {"11:30 AM", "2:30 PM", "5:30 PM", "8:30 PM"},
        {"10:15 AM", "1:15 PM", "4:15 PM", "7:15 PM"},
        {"12:45 PM", "3:45 PM", "6:45 PM", "9:45 PM"},
        {"9:30 AM", "12:30 PM", "3:30 PM", "6:30 PM"},
        {"11:00 AM", "2:00 PM", "5:00 PM", "8:00 PM"}
    };

    float precios[] = {7, 3.5, 3}; // General, Niños, Mayores
    char clientes[MAX_CLIENTES][2][MAX_LONGITUD] = {0};
    char reservas[MAX_RESERVAS][3][MAX_LONGITUD] = {0};

    int numClientes = 0;
    int numCompras = 0;

    // Cargar datos desde los archivos
    cargarDatos(clientes, &numClientes, reservas, &numCompras);

    int opcion;

    do {
        printf("\nMenú de películas disponibles\n");
        printf("1. Ingresar un nuevo cliente\n");
        printf("2. Ver las películas\n");
        printf("3. Buscar película\n");
        printf("4. Comprar un ticket\n");
        printf("5. Comprar múltiples tickets\n");
        printf("6. Ver las compras realizadas\n");
        printf("7. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        getchar();  // Limpia el buffer de entrada

        switch (opcion) {
            case 1:
                ingresarCliente(clientes, &numClientes);
                break;
            case 2:
                verPeliculas(peliculas, horarios, MAX_PELICULAS);
                break;
            case 3:
                buscarPelicula(peliculas, MAX_PELICULAS);
                break;
            case 4:
                comprarTicket(peliculas, horarios, precios, reservas, &numCompras);
                break;
            case 5:
                comprarMultiplesTickets(peliculas, horarios, precios, reservas, &numCompras);
                break;
            case 6:
                verCompras(reservas, numCompras);
                break;
            case 7:
                printf("Saliendo del programa...\n");
                // Guardar datos en los archivos antes de salir
                guardarDatos(clientes, numClientes, reservas, numCompras);
                break;
            default:
                printf("Opción no válida, por favor intente nuevamente.\n");
        }
    } while (opcion != 7);

    return 0;
}
