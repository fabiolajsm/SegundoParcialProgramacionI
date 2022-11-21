#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Parser.h"
#include "Ventas.h"

/** \brief Carga los datos de las ventas desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pListVentas LinkedList*
 * \return int
 *
 */
int controller_cargarVentasDesdeTexto(char *path, LinkedList *pListVentas) {
	int retorno = -1;
	FILE *pArchivo = NULL;

	if (path != NULL && pListVentas != NULL) {
		pArchivo = fopen(path, "r");
		if (pArchivo != NULL
				&& parserVentasDesdeTexto(pArchivo, pListVentas) == 0) {
			retorno = 0;
		}
		fclose(pArchivo);
	}
	return retorno;
}

static int controller_obtenerIdDesdeTexto(void) {
	int retorno = -1;
	FILE *pArchivo = NULL;
	char id[10];

	pArchivo = fopen("idsGenerados.txt", "r");
	if (pArchivo != NULL) {
		while (!feof(pArchivo)) {
			fscanf(pArchivo, "%[^\n]\n", id);
		}
		retorno = atoi(id);
	}
	fclose(pArchivo);
	return retorno;
}

/** \brief Genera un nuevo ID y lo guarda en el archivo idsGenerados.txt (modo texto).
 *
 * \param void
 * \return int
 *
 */
int controller_generarIDVenta(void) {
	int retorno = -1;
	int id = 101;
	FILE *pArchivo = NULL;
	int ultimoId;

	pArchivo = fopen("idsGenerados.txt", "w");
	if (pArchivo != NULL) {
		ultimoId = controller_obtenerIdDesdeTexto();
		if (!ultimoId) {
			fprintf(pArchivo, "%d\n", id);
			retorno = id;
		} else {
			ultimoId++;
			fprintf(pArchivo, "%d\n", ultimoId);
			retorno = ultimoId;
		}
	}

	fclose(pArchivo);
	return retorno;
}

/** \brief Guarda los datos de las ventas en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pListaVentas LinkedList*
 * \return int
 *
 */
int controller_guardarVentasFormatoTexto(char *path, LinkedList *pListaVentas) {
	int retorno = -1;
	FILE *pArchivo = NULL;
	eVenta *auxPunteroVenta = NULL;

	int id;
	eFecha fecha;
	char modelo[50];
	int cantidad;
	float precioUnitario;
	long int tarjetaCredito;

	pArchivo = fopen(path, "w");
	if (path != NULL && pListaVentas != NULL && pArchivo != NULL) {
		fprintf(pArchivo,
				"ID_Venta,Fecha_Venta,Modelo_Auto,Cantidad,Precio_Unitario,Tarjeta_De_Credito\n");

		for (int i = 0; i < ll_len(pListaVentas); i++) {
			auxPunteroVenta = ll_get(pListaVentas, i);
			if (venta_getId(auxPunteroVenta, &id)
					&& venta_getFecha(auxPunteroVenta, &fecha)
					&& venta_getModelo(auxPunteroVenta, modelo)
					&& venta_getCantidad(auxPunteroVenta, &cantidad)
					&& venta_getPrecioUnitario(auxPunteroVenta, &precioUnitario)
					&& venta_getTarjetaCredito(auxPunteroVenta,
							&tarjetaCredito)) {
				fprintf(pArchivo, "%d,%d/%d/%d,%s,%d,%f,%ld\n", id, fecha.dia,
						fecha.mes, fecha.anio, modelo, cantidad, precioUnitario,
						tarjetaCredito);
				retorno = 0;
			}
		}
		fclose(pArchivo);
	}
	return retorno;
}

/** \brief Guarda los datos de las ventas en el archivo binario.
 *
 * \param path char*
 * \param pListaVentas LinkedList*
 * \return int
 *
 */
int controller_guardarVentasFormatoBinario(char *path, LinkedList *pListaVentas) {
	int retorno = -1;
	FILE *pArchivo = NULL;
	eVenta *auxPunteroVenta = NULL;
	int largoLista = ll_len(pListaVentas);

	pArchivo = fopen(path, "wb");
	if (path != NULL && pListaVentas != NULL && pArchivo != NULL) {
		for (int i = 0; i < largoLista; i++) {
			auxPunteroVenta = ll_get(pListaVentas, i);
			fwrite(auxPunteroVenta, sizeof(eVenta), 1, pArchivo);
			retorno = 0;
		}
	}

	return retorno;
}
