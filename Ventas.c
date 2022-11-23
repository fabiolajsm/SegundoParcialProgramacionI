#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "Ventas.h"
#include "Controller.h"
#define ERROR_GUARDADO "No se pudo guardar el archivo\n"

eVenta* venta_new(void) {
	eVenta *aux = NULL;
	aux = (eVenta*) malloc(sizeof(eVenta));
	return aux;
}

eVenta* venta_newParametros(char *idStr, char *fechaStr, char *modeloStr,
		char *cantidadStr, char *precioUnitarioStr, char *tarjetaCreditoStr) {
	eVenta *auxVenta = venta_new();

	if (auxVenta != NULL) {
		long int tarjetaCreditoMapeadaANumber = strtol(tarjetaCreditoStr,
				&tarjetaCreditoStr, 10);
		if (venta_setId(auxVenta, atoi(idStr))
				&& venta_setStringFecha(auxVenta, fechaStr)
				&& venta_setModelo(auxVenta, modeloStr)
				&& venta_setCantidad(auxVenta, atoi(cantidadStr))
				&& venta_setPrecioUnitario(auxVenta, atof(precioUnitarioStr))
				&& venta_setTarjetaCredito(auxVenta,
						tarjetaCreditoMapeadaANumber)) {
			return auxVenta;
		} else {
			free(auxVenta);
		}
	}
	return auxVenta;
}

int venta_setId(eVenta *this, int id) {
	int retorno = 0;

	if (this != NULL && id > 0) {
		this->id = id;
		retorno = 1;
	}
	return retorno;
}
int venta_getId(eVenta *this, int *pId) {
	int retorno = 0;

	if (this != NULL && pId != NULL) {
		*pId = this->id;
		retorno = 1;
	}
	return retorno;
}

static int mappearTextoAFecha(char *fechaStr, eFecha *pFecha) {
	int retorno = -1;
	char auxFechaStr[10];
	eFecha fechaMapeada;

	if (fechaStr != NULL && pFecha != NULL) {
		strcpy(auxFechaStr, fechaStr);

		fechaMapeada.dia = atoi(strtok(auxFechaStr, "/"));
		fechaMapeada.mes = atoi(strtok(NULL, "/"));
		fechaMapeada.anio = atoi(strtok(NULL, "/"));
		*pFecha = fechaMapeada;
		retorno = 0;
	}
	return retorno;
}
int venta_setStringFecha(eVenta *this, char *fecha) {
	int retorno = 0;
	eFecha auxFecha;

	if (this != NULL) {
		if (mappearTextoAFecha(fecha, &auxFecha) == 0) {
			this->fecha = auxFecha;
			retorno = 1;
		}
	}
	return retorno;
}
int venta_setFecha(eVenta *this, eFecha fecha) {
	int retorno = 0;

	if (this != NULL) {
		this->fecha = fecha;
		retorno = 1;
	}
	return retorno;
}
int venta_getFecha(eVenta *this, eFecha *pFecha) {
	int retorno = 0;

	if (this != NULL && pFecha != NULL) {
		*pFecha = this->fecha;
		retorno = 1;
	}
	return retorno;
}

int venta_setModelo(eVenta *this, char *modelo) {
	int retorno = 0;
	if (this != NULL) {
		strcpy(this->modelo, modelo);
		retorno = 1;
	}
	return retorno;
}
int venta_getModelo(eVenta *this, char *pModelo) {
	int retorno = 0;

	if (this != NULL && pModelo != NULL) {
		strcpy(pModelo, this->modelo);
		retorno = 1;
	}
	return retorno;
}

int venta_setCantidad(eVenta *this, int cantidad) {
	int retorno = 0;

	if (this != NULL) {
		this->cantidad = cantidad;
		retorno = 1;
	}
	return retorno;
}
int venta_getCantidad(eVenta *this, int *pCantidad) {
	int retorno = 0;

	if (this != NULL && pCantidad != NULL) {
		*pCantidad = this->cantidad;
		retorno = 1;
	}
	return retorno;
}

int venta_setPrecioUnitario(eVenta *this, float precioUnitario) {
	int retorno = 0;

	if (this != NULL) {
		this->precioUnitario = precioUnitario;
		retorno = 1;
	}
	return retorno;
}
int venta_getPrecioUnitario(eVenta *this, float *pPrecio) {
	int retorno = 0;

	if (this != NULL && pPrecio != NULL) {
		*pPrecio = this->precioUnitario;
		retorno = 1;
	}
	return retorno;
}

int venta_setTarjetaCredito(eVenta *this, long int tarjetaCredito) {
	int retorno = 0;

	if (this != NULL) {
		this->tarjetaCredito = tarjetaCredito;
		retorno = 1;
	}
	return retorno;
}
int venta_getTarjetaCredito(eVenta *this, long int *pTarjetaCredito) {
	int retorno = 0;

	if (this != NULL && pTarjetaCredito != NULL) {
		*pTarjetaCredito = this->tarjetaCredito;
		retorno = 1;
	}
	return retorno;
}

static void listarVenta(eVenta *item) {
	int id;
	eFecha fecha;
	char modelo[50];
	int cantidad;
	float precioUnitario;
	long int tarjetaCredito;

	if (item != NULL && venta_getId(item, &id) == 1
			&& venta_getFecha(item, &fecha) == 1
			&& venta_getModelo(item, modelo) == 1
			&& venta_getCantidad(item, &cantidad) == 1
			&& venta_getPrecioUnitario(item, &precioUnitario) == 1
			&& venta_getTarjetaCredito(item, &tarjetaCredito) == 1) {
		printf("| %*d | %*s | %*d    |      %*.2f |  %ld  | %d/%d/%d \n", -3,
				id, -22, modelo, 5, cantidad, -10, precioUnitario,
				tarjetaCredito, fecha.dia, fecha.mes, fecha.anio);
	}
}

int listarVentas(LinkedList *pListVentas) {
	int retorno = -1;
	int largo = ll_len(pListVentas);

	if (pListVentas != NULL && largo > 0) {
		printf("\t\t\t\t- Listado de ventas -\n");
		printf(
				"===============================================================================================\n");
		printf("|%*s|%*s|%s|%*s|%*s|%*s|\n", -5, " ID", -24, "        Modelo",
				" Cantidad ", -13, " Precio Unitario ", -20,
				" Tarjeta de credito ", -13, " Fecha ");
		printf(
				"-----------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < largo; i++) {
			listarVenta((eVenta*) ll_get(pListVentas, i));
		}
		printf(
				"===============================================================================================\n");
		retorno = 0;
	}

	return retorno;
}

void guardarArchivoVentasSubmenu(LinkedList *pListaVentas) {
	int mostrarSubmenu = 1;
	int opcion;

	if (pListaVentas != NULL) {
		while (mostrarSubmenu) {
			if (utn_obtenerNumero(&opcion,
					"Seleccione como prefiere guardar el archivo:\n1. Formato texto.\n2. Formato binario.\n3. Salir.\n",
					"Error. Opción inválida.\n", 1, 3) == 0) {
				switch (opcion) {
				case 1:
					if (controller_guardarVentasFormatoTexto("data.csv",
							pListaVentas) == 0) {
						printf("Exitosamente guardado como formato de texto\n");
					} else {
						printf(ERROR_GUARDADO);
					}
					break;
				case 2:
					if (controller_guardarVentasFormatoBinario("data.bin",
							pListaVentas) == 0) {
						printf("Exitosamente guardado como formato binario\n");
					} else {
						printf(ERROR_GUARDADO);
					}
					break;
				case 3:
					printf("Submenú cerrado\n");
					mostrarSubmenu = 0;
					break;
				}
			}
		}
	}
}
