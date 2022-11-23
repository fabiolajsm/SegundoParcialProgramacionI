#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "Ventas.h"

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
