#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Parser.h"
#include "Ventas.h"
#include "utn.h"
#define MODIFICACION_EXITOSA "Se modificó exitosamente\n"
#define ERROR_MODIFICACION "Error. No se pudo modificar\n"

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

int controller_agregarVenta(LinkedList *pListaVentas) {
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
int controller_eliminarVenta(LinkedList *pListaVentas) {
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
void controller_modificarVenta(LinkedList *pListaVentas) {
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

int controller_generarInformeVentasFormatoTexto(char *path,
		LinkedList *pListaVentas) {
	int retorno = -1;
	FILE *pArchivo = NULL;

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

	pArchivo = fopen(path, "wt");
	if (path != NULL && pListaVentas != NULL && pArchivo != NULL) {
		unidadesVendidasEnTotal = ll_count(pListaVentas,
				buscarCantidadesVendidas);
		cantidadMayoresADiezMil = ll_count(pListaVentas,
				buscarVentasMayoresADiezMil);
		cantidadMayoresAVeinteMil = ll_count(pListaVentas,
				buscarVentasMayoresAVeinteMil);
		cantidadDeModeloElegido = ll_count(pListaVentas,
				buscarVentasPorModeloElegido);

		// Convertimos a los datos a string
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
	fclose(pArchivo);
	return retorno;
}
