#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int parserGuardarVentasTexto(FILE *pArchivo, LinkedList *pListaVentas) {
	int retorno = -1;
	eVenta *auxPunteroVenta = NULL;

	int id;
	eFecha fecha;
	char modelo[50];
	int cantidad;
	float precioUnitario;
	long int tarjetaCredito;

	if (pListaVentas != NULL && pArchivo != NULL) {
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
	}
	return retorno;
}

int parserGuardarVentasFormatoBinario(FILE *pArchivo, LinkedList *pListaVentas) {
	int retorno = -1;
	int largoLista = ll_len(pListaVentas);
	eVenta *auxPunteroVenta = NULL;

	if (pListaVentas != NULL && pArchivo != NULL) {
		for (int i = 0; i < largoLista; i++) {
			auxPunteroVenta = ll_get(pListaVentas, i);
			if (auxPunteroVenta != NULL) {
				fwrite(auxPunteroVenta, sizeof(eVenta), 1, pArchivo);
				retorno = 0;
			}
		}
	}
	return retorno;
}

// Funciones criterio
static int buscarCantidadesVendidas(void *this) {
	eVenta *pVenta;
	int cantidadVendida;
	int retorno = 0;

	if (this != NULL) {
		pVenta = (eVenta*) this;
		if (pVenta != NULL && venta_getCantidad(pVenta, &cantidadVendida)) {

			if (cantidadVendida > 0) {
				retorno = cantidadVendida;
			}
		}
	}
	return retorno;
}
static int buscarVentasMayoresADiezMil(void *this) {
	eVenta *pVenta;
	float precioUnitario;
	int cantidad;
	int precioTotal;
	int retorno = 0;

	if (this != NULL) {
		pVenta = (eVenta*) this;
		if (pVenta != NULL && venta_getPrecioUnitario(pVenta, &precioUnitario)
				&& venta_getCantidad(pVenta, &cantidad)) {
			precioTotal = precioUnitario * cantidad;
			if (precioTotal > 10000) {
				retorno = 1;
			}
		}
	}
	return retorno;
}
static int buscarVentasMayoresAVeinteMil(void *this) {
	eVenta *pVenta;
	float precioUnitario;
	int cantidad;
	int precioTotal;
	int retorno = 0;

	if (this != NULL) {
		pVenta = (eVenta*) this;
		if (pVenta != NULL && venta_getPrecioUnitario(pVenta, &precioUnitario)
				&& venta_getCantidad(pVenta, &cantidad)) {
			precioTotal = precioUnitario * cantidad;
			if (precioTotal > 20000) {
				retorno = 1;
			}
		}
	}
	return retorno;
}
static int buscarVentasPorModeloElegido(void *this) {
	eVenta *pVenta;
	char modeloElegido[30] = "Mentor";
	char modelo[50];
	int cantidad;
	int retorno = 0;

	if (this != NULL) {
		pVenta = (eVenta*) this;
		if (pVenta != NULL && venta_getModelo(pVenta, modelo)) {
			if (strcmp(modeloElegido, modelo) == 0) {
				if (venta_getCantidad(pVenta, &cantidad)) {
					retorno = cantidad;
				}
			}
		}
	}
	return retorno;
}
static int convertirNumeroAString(char *pString, int numero) {
	int retorno = -1;
	if (pString != NULL) {
		sprintf(pString, "%d", numero);
		retorno = 0;
	}
	return retorno;
}

int parserGenerarInformeVentasTexto(FILE *pArchivo, LinkedList *pListaVentas) {
	int retorno = -1;
	// Unidades vendidas en total
	char textoUnidadesVendidas[] = "- Cantidad de unidades vendidas en total: ";
	char textoUnidadesVendidasEnTotal[10];
	int unidadesVendidasEnTotal = 0;
	// Cantidad de ventas por un monto mayor a diez mil
	char textoMayoresADiezMil[] =
			"\n- Cantidad de ventas por un monto mayor a $10.000: ";
	char textoTotalMayoresADiezMil[10];
	int cantidadMayoresADiezMil = 0;
	// Cantidad de ventas por un monto mayor a veinte mil
	char textoMayoresAVeinteMil[] =
			"\n- Cantidad de ventas por un monto mayor a $20.000: ";
	char textoTotalMayoresAVeinteMil[10];
	int cantidadMayoresAVeinteMil = 0;
	// Cantidad de ventas por modelo elegido
	char textoCantidadPorModelo[] =
			"\n- Cantidad del modelo 'Mentor' vendidos: ";
	char textoCantidadPorModeloTotal[10];
	int cantidadDeModeloElegido = 0;

	if (pArchivo != NULL && pListaVentas != NULL) {
		// Convertimos a los datos a string
		unidadesVendidasEnTotal = ll_count(pListaVentas,
				buscarCantidadesVendidas);
		cantidadMayoresADiezMil = ll_count(pListaVentas,
				buscarVentasMayoresADiezMil);
		cantidadMayoresAVeinteMil = ll_count(pListaVentas,
				buscarVentasMayoresAVeinteMil);
		cantidadDeModeloElegido = ll_count(pListaVentas,
				buscarVentasPorModeloElegido);
		if (convertirNumeroAString(textoUnidadesVendidasEnTotal,
				unidadesVendidasEnTotal) == 0
				&& convertirNumeroAString(textoTotalMayoresADiezMil,
						cantidadMayoresADiezMil) == 0
				&& convertirNumeroAString(textoTotalMayoresAVeinteMil,
						cantidadMayoresAVeinteMil) == 0
				&& convertirNumeroAString(textoCantidadPorModeloTotal,
						cantidadDeModeloElegido) == 0) {
			// Concatenamos los textos con su valor
			strcat(textoUnidadesVendidas, textoUnidadesVendidasEnTotal);
			strcat(textoMayoresADiezMil, textoTotalMayoresADiezMil);
			strcat(textoMayoresAVeinteMil, textoTotalMayoresAVeinteMil);
			strcat(textoCantidadPorModelo, textoCantidadPorModeloTotal);
			// Escribimos en el archivo
			fputs("******************\n", pArchivo);
			fputs("Informe de ventas\n", pArchivo);
			fputs("******************\n", pArchivo);
			fputs(textoUnidadesVendidas, pArchivo);
			fputs(textoMayoresADiezMil, pArchivo);
			fputs(textoMayoresAVeinteMil, pArchivo);
			fputs(textoCantidadPorModelo, pArchivo);
			fputs("\n******************", pArchivo);
			retorno = 0;
		}
	}
	return retorno;
}
