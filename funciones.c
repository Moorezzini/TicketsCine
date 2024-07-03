#include "funciones.h"
#include <stdio.h>
#include <string.h>

void ingresarCliente(char clientes[][2][MAX_LONGITUD], int *numClientes) {
    if (*numClientes >= MAX_CLIENTES) {
        printf("No se pueden ingresar más clientes.\n");
        return;
    }
    printf("Ingrese el nombre del cliente: ");
    fgets(clientes[*numClientes][0], MAX_LONGITUD, stdin);
    clientes[*numClientes][0][strcspn(clientes[*numClientes][0], "\n")] = 0; // Elimina el salto de línea
    printf("Ingrese el ID del cliente: ");
    fgets(clientes[*numClientes][1], MAX_LONGITUD, stdin);
    clientes[*numClientes][1][strcspn(clientes[*numClientes][1], "\n")] = 0; // Elimina el salto de línea
    (*numClientes)++;
    printf("Cliente ingresado con éxito.\n");
}

void verPeliculas(char peliculas[][4][MAX_LONGITUD], char horarios[][MAX_HORARIOS][MAX_LONGITUD], int numPeliculas) {
    printf("Películas disponibles:\n");
    for (int i = 0; i < numPeliculas; i++) {
        printf("%d. %s\n", i + 1, peliculas[i][0]);
        printf("   Horarios:\n");
        for (int j = 0; j < MAX_HORARIOS; j++) {
            printf("   %d. %s\n", j + 1, horarios[i][j]);
        }
    }
}

void buscarPelicula(char peliculas[][4][MAX_LONGITUD], int numPeliculas) {
    char nombre[MAX_LONGITUD];
    printf("Ingrese el nombre de la película a buscar: ");
    fgets(nombre, MAX_LONGITUD, stdin);
    nombre[strcspn(nombre, "\n")] = 0; // Elimina el salto de línea

    for (int i = 0; i < numPeliculas; i++) {
        if (strcasecmp(peliculas[i][0], nombre) == 0) {
            printf("Película encontrada:\n");
            printf("Título: %s\n", peliculas[i][0]);
            printf("Director: %s\n", peliculas[i][1]);
            printf("Género: %s\n", peliculas[i][2]);
            printf("Año: %s\n", peliculas[i][3]);
            return;
        }
    }
    printf("Película no encontrada.\n");
}

void comprarTicket(char peliculas[][4][MAX_LONGITUD], char horarios[][MAX_HORARIOS][MAX_LONGITUD], float precios[], char reservas[][3][MAX_LONGITUD], int *numCompras) {
    int peliculaSeleccionada;
    int tipoEntrada;
    int horarioSeleccionado;
    char nombreCliente[MAX_LONGITUD];
    int cantidadEntradas;
    float total = 0.0;

    printf("Seleccione la película:\n");
    for (int i = 0; i < MAX_PELICULAS; i++) {
        printf("%d. %s\n", i + 1, peliculas[i][0]);
    }
    scanf("%d", &peliculaSeleccionada);
    getchar();  // Limpia el buffer de entrada

    printf("Seleccione el tipo de entrada:\n");
    printf("1. General ($%.2f)\n2. Niños ($%.2f)\n3. Mayores ($%.2f)\n", precios[0], precios[1], precios[2]);
    scanf("%d", &tipoEntrada);
    getchar();  // Limpia el buffer de entrada

    printf("Seleccione el horario:\n");
    for (int i = 0; i < MAX_HORARIOS; i++) {
        printf("%d. %s\n", i + 1, horarios[peliculaSeleccionada - 1][i]);
    }
    scanf("%d", &horarioSeleccionado);
    getchar();  // Limpia el buffer de entrada

    printf("Ingrese la cantidad de entradas: ");
    scanf("%d", &cantidadEntradas);
    getchar();  // Limpia el buffer de entrada

    printf("Ingrese el nombre del cliente: ");
    fgets(nombreCliente, MAX_LONGITUD, stdin);
    nombreCliente[strcspn(nombreCliente, "\n")] = 0; // Elimina el salto de línea

    for (int i = 0; i < cantidadEntradas; i++) {
        snprintf(reservas[*numCompras][0], MAX_LONGITUD, "%s", peliculas[peliculaSeleccionada - 1][0]);
        snprintf(reservas[*numCompras][1], MAX_LONGITUD, "%s", horarios[peliculaSeleccionada - 1][horarioSeleccionado - 1]);
        snprintf(reservas[*numCompras][2], MAX_LONGITUD, "%s", nombreCliente);
        (*numCompras)++;
        total += precios[tipoEntrada - 1];
    }

    printf("Ticket(s) comprado(s) con éxito.\n");
    generarFactura(reservas, *numCompras, total);
}

void comprarMultiplesTickets(char peliculas[][4][MAX_LONGITUD], char horarios[][MAX_HORARIOS][MAX_LONGITUD], float precios[], char reservas[][3][MAX_LONGITUD], int *numCompras) {
    int cantidadTickets;
    printf("Ingrese la cantidad de tickets a comprar: ");
    scanf("%d", &cantidadTickets);
    getchar();  // Limpia el buffer de entrada

    for (int i = 0; i < cantidadTickets; i++) {
        printf("Compra de ticket %d\n", i + 1);
        comprarTicket(peliculas, horarios, precios, reservas, numCompras);
    }
}

void verCompras(char reservas[][3][MAX_LONGITUD], int numCompras) {
    printf("Compras realizadas:\n");
    for (int i = 0; i < numCompras; i++) {
        printf("%d. Película: %s, Horario: %s, Cliente: %s\n", i + 1, reservas[i][0], reservas[i][1], reservas[i][2]);
    }
}

void generarFactura(char reservas[][3][MAX_LONGITUD], int numCompras, float total) {
    printf("Generando factura...\n");
    for (int i = 0; i < numCompras; i++) {
        printf("Factura %d:\n", i + 1);
        printf("Película: %s\n", reservas[i][0]);
        printf("Horario: %s\n", reservas[i][1]);
        printf("Cliente: %s\n", reservas[i][2]);
    }
    printf("Total a pagar: $%.2f\n", total);
}

void guardarDatos(char clientes[][2][MAX_LONGITUD], int numClientes, char reservas[][3][MAX_LONGITUD], int numCompras) {
    FILE *archivoClientes = fopen("archivoClientes.txt", "w");
    FILE *archivoReservas = fopen("archivoReservas.txt", "w");

    if (archivoClientes != NULL) {
        for (int i = 0; i < numClientes; i++) {
            fprintf(archivoClientes, "%s,%s\n", clientes[i][0], clientes[i][1]);
        }
        fclose(archivoClientes);
    }

    if (archivoReservas != NULL) {
        for (int i = 0; i < numCompras; i++) {
            fprintf(archivoReservas, "%s,%s,%s\n", reservas[i][0], reservas[i][1], reservas[i][2]);
        }
        fclose(archivoReservas);
    }
}

void cargarDatos(char clientes[][2][MAX_LONGITUD], int *numClientes, char reservas[][3][MAX_LONGITUD], int *numCompras) {
    FILE *archivoClientes = fopen("archivoClientes.txt", "r");
    FILE *archivoReservas = fopen("archivoReservas.txt", "r");

    char linea[MAX_LONGITUD * 2];
    *numClientes = 0;
    *numCompras = 0;

    if (archivoClientes != NULL) {
        while (fgets(linea, sizeof(linea), archivoClientes)) {
            char *token = strtok(linea, ",");
            snprintf(clientes[*numClientes][0], MAX_LONGITUD, "%s", token);
            token = strtok(NULL, ",");
            snprintf(clientes[*numClientes][1], MAX_LONGITUD, "%s", token);
            clientes[*numClientes][1][strcspn(clientes[*numClientes][1], "\n")] = 0; // Elimina el salto de línea
            (*numClientes)++;
        }
        fclose(archivoClientes);
    }

    if (archivoReservas != NULL) {
        while (fgets(linea, sizeof(linea), archivoReservas)) {
            char *token = strtok(linea, ",");
            snprintf(reservas[*numCompras][0], MAX_LONGITUD, "%s", token);
            token = strtok(NULL, ",");
            snprintf(reservas[*numCompras][1], MAX_LONGITUD, "%s", token);
            token = strtok(NULL, ",");
            snprintf(reservas[*numCompras][2], MAX_LONGITUD, "%s", token);
            reservas[*numCompras][2][strcspn(reservas[*numCompras][2], "\n")] = 0; // Elimina el salto de línea
            (*numCompras)++;
        }
        fclose(archivoReservas);
    }
}
