#ifndef VENTAS_H_
#define VENTAS_H_

typedef struct {
	int dia;
	int mes;
	int anio;
} eFecha;

typedef struct {
	int id;
	eFecha fecha;
	char modelo[50];
	int cantidad;
	float precioUnitario;
	long int tarjetaCredito;
} eVenta;

eVenta* venta_new(void);
eVenta* venta_newParametros(char *idStr, char *fechaStr, char *modeloStr,
		char *cantidadStr, char *precioUnitarioStr, char *tarjetaCreditoStr);

int venta_setId(eVenta *this, int id);
int venta_getId(eVenta *this, int *pId);

int venta_setStringFecha(eVenta *this, char *fecha);
int venta_setFecha(eVenta *this, eFecha fecha);
int venta_getFecha(eVenta *this, eFecha *pFecha);

int venta_setModelo(eVenta *this, char *modelo);
int venta_getModelo(eVenta *this, char *pModelo);

int venta_setCantidad(eVenta *this, int cantidad);
int venta_getCantidad(eVenta *this, int *pCantidad);

int venta_setPrecioUnitario(eVenta *this, float precioUnitario);
int venta_getPrecioUnitario(eVenta *this, float *pPrecio);

int venta_setTarjetaCredito(eVenta *this, long int tarjetaCredito);
int venta_getTarjetaCredito(eVenta *this, long int *pTarjetaCredito);

#endif /* VENTAS_H_ */
