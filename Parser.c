#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Ventas.h"
#define LARGO 50

int parserVentasDesdeTexto(FILE *pArchivo, LinkedList *pListVentas) {
	int retorno = -1;
	eVenta *auxPunteroVenta = NULL;
	char id[LARGO];
	char fecha[100];
	char modelo[LARGO];
	char cantidad[LARGO];
	char precioUnitario[LARGO];
	char tarjetaCredito[LARGO];
	int lecturaCaracteres;

	if (pArchivo != NULL && pListVentas != NULL) {
		// lectura fantasma
		lecturaCaracteres = fscanf(pArchivo,
				"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, fecha, modelo,
				cantidad, precioUnitario, tarjetaCredito);
		while (feof(pArchivo) == 0) {
			// vuelvo a leer en cada vuelta
			lecturaCaracteres = fscanf(pArchivo,
					"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, fecha, modelo,
					cantidad, precioUnitario, tarjetaCredito);
			if (lecturaCaracteres == 6) {
				auxPunteroVenta = venta_newParametros(id, fecha, modelo,
						cantidad, precioUnitario, tarjetaCredito);
				// Utilizamos función de la biblioteca LinkedList para almacenar las ventas leídas del archivo
				if (auxPunteroVenta != NULL
						&& ll_add(pListVentas, auxPunteroVenta) == 0) {
					retorno = 0;
				}
			}
		}
	}
	return retorno;
}

