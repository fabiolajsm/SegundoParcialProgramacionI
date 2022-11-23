#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "utn.h"
#include "Ventas.h"
#include "Controller.h"
#define MODIFICACION_EXITOSA "Se modificó exitosamente\n"
#define ERROR_MODIFICACION "Error. No se pudo modificar\n"
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

int agregarVenta(LinkedList *pListaVentas) {
	int retorno = -1;
	eVenta *auxPunteroVenta = venta_new();
	int id;
	eFecha fecha;
	char modeloAuto[50];
	int cantidad;
	float precioUnitario;
	long int tarjetaCredito;

	if (pListaVentas != NULL) {
		if (utn_obtenerFecha(&fecha,
				"Ingrese fecha de venta en formato dd/mm/yyyy\n") == 0
				&& utn_obtenerModeloAuto(modeloAuto, 50,
						"Ingrese modelo de auto: \n",
						"Error. El modelo de auto tiene que tener mínimo una letra, y no puede tener caracteres especiales excepto el separador '-'\n",
						50) == 0
				&& utn_obtenerNumero(&cantidad, "Ingrese cantidad:\n",
						"Error. No puede ingresar más de 100 unidades y mínimo tiene que ingresar 1 unidad.\n",
						1, 100) == 0
				&& utn_obtenerFlotante(&precioUnitario,
						"Ingrese el precio unitario: \n",
						"Error. No puede tener un precio mayor a 100\n", 1, 100)
						== 0
				&& utn_obtenerTarjetaDeCredito(&tarjetaCredito,
						"Ingrese el número de la tarjeta de crédito, sólo aceptamos Masterd Card: \n",
						"Error. El número tiene que tener 16 numeros, sin espacios y empezar por 5100\n")
						== 0) {
			id = controller_generarIDVenta();
			if (id > 100) {
				if (venta_setId(auxPunteroVenta, id)
						&& venta_setFecha(auxPunteroVenta, fecha)
						&& venta_setModelo(auxPunteroVenta, modeloAuto)
						&& venta_setCantidad(auxPunteroVenta, cantidad)
						&& venta_setPrecioUnitario(auxPunteroVenta,
								precioUnitario)
						&& venta_setTarjetaCredito(auxPunteroVenta,
								tarjetaCredito)) {
					if (auxPunteroVenta != NULL
							&& ll_add(pListaVentas, auxPunteroVenta) == 0) {
						retorno = 0;
					}
				}
			}
		}
	}

	return retorno;
}

static int obtenerIndexPorId(LinkedList *pListaVentas, int idVenta) {
	int retorno = -1;
	int idObtenido;
	eVenta *auxPunteroVenta = NULL;

	for (int i = 0; i < ll_len(pListaVentas); i++) {
		auxPunteroVenta = (eVenta*) ll_get(pListaVentas, i);

		if (venta_getId(auxPunteroVenta, &idObtenido)) {
			if (idObtenido == idVenta) {
				retorno = ll_indexOf(pListaVentas, auxPunteroVenta);
				break;
			}
		}
	}

	return retorno;
}

/** \brief Eliminar venta
 *
 * \param pListaVentas LinkedList*
 * \return int
 *
 */
int eliminarVenta(LinkedList *pListaVentas) {
	int retorno = -1;
	int indexVenta;
	int idIngresado;
	int idVenta;
	eVenta *pVentaARemover = NULL;

	if (pListaVentas != NULL && listarVentas(pListaVentas) == 0) {
		if (utn_obtenerNumero(&idIngresado,
				"Ingrese el ID de la venta que quiere eliminar:\n",
				"Error. El ID tiene que ser un numero entero, mayor 0 y menor a 9000.\n",
				0, 9000) == 0) {
			indexVenta = obtenerIndexPorId(pListaVentas, idIngresado);
			pVentaARemover = ll_get(pListaVentas, indexVenta);

			if (pVentaARemover != NULL
					&& venta_getId(pVentaARemover, &idVenta)) {
				if (idVenta == idIngresado) {
					if (ll_remove(pListaVentas, indexVenta) == 0) {
						retorno = 0;
					}
				}
			} else {
				printf("Error. ID de la venta no fue encontrado.\n");
			}
		}
	}

	return retorno;
}

/** \brief Modificar venta
 *
 * \param pListaVentas LinkedList*
 * \return void
 *
 */
void modificarVenta(LinkedList *pListaVentas) {
	int opcion;
	int esOpcionValida;
	int mostrarSubmenu = 1;

	int idVenta;
	eFecha fecha;
	char modeloAuto[50];
	int cantidad;
	float precioUnitario;
	long int tarjetaCredito;

	int indexVenta;
	eVenta *pVentaAModificar = NULL;

	if (pListaVentas != NULL && listarVentas(pListaVentas) == 0) {
		if (utn_obtenerNumero(&idVenta,
				"Ingrese el ID de la venta a modificar:\n",
				"Error. El ID tiene que ser un numero entero, mayor 0 y menor a 9000.\n",
				0, 9000) == 0) {
			indexVenta = obtenerIndexPorId(pListaVentas, idVenta);
			pVentaAModificar = ll_get(pListaVentas, indexVenta);

			if (pVentaAModificar != NULL) {
				while (mostrarSubmenu == 1) {
					esOpcionValida =
							utn_obtenerNumero(&opcion,
									"Seleccione que va a modificar:\n1. Modelo del auto\n2. Fecha de venta\n3. Cantidad de unidades\n4. Precio unitario\n5. Tarjeta de crédito\n6. Salir\n",
									"Error. Tiene que elegir una opción del 1 y al 6.\n",
									1, 6);
					if (esOpcionValida == 0) {
						switch (opcion) {
						case 1:
							if (utn_obtenerModeloAuto(modeloAuto, 50,
									"Ingrese modelo de auto: \n",
									"Error. El modelo de auto tiene que tener mínimo una letra, y no puede tener caracteres especiales excepto el separador '-'\n",
									50) == 0) {
								if (venta_setModelo(pVentaAModificar,
										modeloAuto)) {
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								printf(ERROR_MODIFICACION);
							}
							break;
						case 2:
							if (utn_obtenerFecha(&fecha,
									"Ingrese fecha de venta en formato dd/mm/yyyy\n")
									== 0) {
								if (venta_setFecha(pVentaAModificar, fecha)) {
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								printf(ERROR_MODIFICACION);
							}
							break;
						case 3:
							if (utn_obtenerNumero(&cantidad,
									"Ingrese cantidad:\n",
									"Error. No puede ingresar más de 100 unidades y mínimo tiene que ingresar 1 unidad.\n",
									1, 100) == 0) {
								if (venta_setCantidad(pVentaAModificar,
										cantidad)) {
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								printf(ERROR_MODIFICACION);
							}
							break;
						case 4:
							if (utn_obtenerFlotante(&precioUnitario,
									"Ingrese el precio unitario: \n",
									"Error. No puede tener un precio mayor a 100\n",
									1, 100) == 0) {
								if (venta_setPrecioUnitario(pVentaAModificar,
										precioUnitario)) {
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								printf(ERROR_MODIFICACION);
							}
							break;
						case 5:
							if (utn_obtenerTarjetaDeCredito(&tarjetaCredito,
									"Ingrese el número de la tarjeta de crédito, sólo aceptamos Masterd Card: \n",
									"Error. El número tiene que tener 16 numeros, sin espacios y empezar por 5100\n")
									== 0) {
								if (venta_setTarjetaCredito(pVentaAModificar,
										tarjetaCredito)) {
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								printf(ERROR_MODIFICACION);
							}
							break;
						case 6:
							mostrarSubmenu = 0;
							break;
						}
					}
				}
			} else {
				printf("Error. ID de venta no encontrado.\n");
			}
		}
	}
}

void guardarArchivoSubmenu(LinkedList *pListaVentas) {
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

void generarInformeVentas(LinkedList *pListaVentas) {
	int unidadesVendidasEnTotal = 0;
	int cantidadMayoresADiezMil = 0;
	int cantidadMayoresAVeinteMil = 0;
	int cantidadDeModeloElegido = 0;
	char modeloElegido[30] = "Mentor";

	if (pListaVentas != NULL) {
		unidadesVendidasEnTotal = ll_count(pListaVentas,
				buscarCantidadesVendidas);
		cantidadMayoresADiezMil = ll_count(pListaVentas,
				buscarVentasMayoresADiezMil);
		cantidadMayoresAVeinteMil = ll_count(pListaVentas,
				buscarVentasMayoresAVeinteMil);
		cantidadDeModeloElegido = ll_count(pListaVentas,
				buscarVentasPorModeloElegido);

		printf("******************\n");
		printf("Informe de ventas\n");
		printf("******************\n");
		printf("- Cantidad de unidades vendidas en total: %d\n",
				unidadesVendidasEnTotal); // cambiar el maximo de precio
		printf("- Cantidad de ventas por un monto mayor a $10.000: %d\n",
				cantidadMayoresADiezMil);
		printf("- Cantidad de ventas por un monto mayor a $20.000: %d\n",
				cantidadMayoresAVeinteMil);
		printf("- Cantidad del modelo '%s' vendidos: %d\n", modeloElegido,
				cantidadDeModeloElegido);
		printf("******************\n");
	}
}

