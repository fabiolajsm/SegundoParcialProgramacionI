#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Parser.h"
#include "Ventas.h"
#include "utn.h"
#define MODIFICACION_EXITOSA "Se modificó exitosamente\n"
#define ERROR_MODIFICACION "Error. No se pudo modificar\n"
#define ERROR_GUARDADO "No se pudo guardar el archivo\n"

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

	if (path != NULL && pListaVentas != NULL) {
		pArchivo = fopen(path, "w");
		if (pArchivo != NULL
				&& parserGuardarVentasTexto(pArchivo, pListaVentas) == 0) {
			retorno = 0;
		}
	}
	fclose(pArchivo);

	return retorno;
}

/** \brief Guarda los datos de las ventas en el archivo binario(data.bin)
 *
 * \param path char*
 * \param pListaVentas LinkedList*
 * \return int
 *
 */
int controller_guardarVentasFormatoBinario(char *path, LinkedList *pListaVentas) {
	int retorno = -1;
	FILE *pArchivo = NULL;

	if (path != NULL && pListaVentas != NULL) {
		pArchivo = fopen(path, "wb");
		if (parserGuardarVentasFormatoBinario(pArchivo, pListaVentas) == 0) {
			retorno = 0;
		}
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
	int confirmacion;
	eVenta *pVentaARemover = NULL;

	if (ll_len(pListaVentas) < 1) {
		printf("No existen ventas\n");
		return -1;
	}

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
					if (utn_obtenerNumero(&confirmacion,
							"Seguro desea dar de baja a esta venta?\n1. Si.\n2. No.\n",
							"Error. Opción inválida, tiene que elegir un número del 1 al 2.\n",
							1, 2) == 0) {
						if (confirmacion == 1) {
							if (ll_remove(pListaVentas, indexVenta) == 0) {
								retorno = 0;
							}
						}
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
int controller_modificarVenta(LinkedList *pListaVentas) {
	int retorno = -1;
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

	if (ll_len(pListaVentas) < 1) {
		printf("No existen ventas\n");
		return -1;
	}

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
									retorno = 0;
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								retorno = -1;
								printf(ERROR_MODIFICACION);
							}
							break;
						case 2:
							if (utn_obtenerFecha(&fecha,
									"Ingrese fecha de venta en formato dd/mm/yyyy\n")
									== 0) {
								if (venta_setFecha(pVentaAModificar, fecha)) {
									printf(MODIFICACION_EXITOSA);
									retorno = 0;
								}
							} else {
								retorno = -1;
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
									retorno = 0;
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								retorno = -1;
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
									retorno = 0;
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								retorno = -1;
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
									retorno = 0;
									printf(MODIFICACION_EXITOSA);
								}
							} else {
								retorno = -1;
								printf(ERROR_MODIFICACION);
							}
							break;
						case 6:
							retorno = 0;
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
	return retorno;
}

int guardarArchivoVentasSubmenu(LinkedList *pListaVentas) {
	int retorno = -1;
	int mostrarSubmenu = 1;
	int opcion;

	if (ll_len(pListaVentas) < 1) {
		printf("No existen ventas\n");
		return -1;
	}

	if (pListaVentas != NULL) {
		while (mostrarSubmenu) {
			if (utn_obtenerNumero(&opcion,
					"Seleccione como prefiere guardar el archivo:\n1. Formato texto.\n2. Formato binario.\n3. Salir.\n",
					"Error. Opción inválida.\n", 1, 3) == 0) {
				switch (opcion) {
				case 1:
					if (controller_guardarVentasFormatoTexto("data.csv",
							pListaVentas) == 0) {
						retorno = 0;
						printf("Exitosamente guardado como formato de texto\n");
					} else {
						retorno = -1;
						printf(ERROR_GUARDADO);
					}
					break;
				case 2:
					if (controller_guardarVentasFormatoBinario("data.bin",
							pListaVentas) == 0) {
						retorno = 0;
						printf("Exitosamente guardado como formato binario\n");
					} else {
						retorno = -1;
						printf(ERROR_GUARDADO);
					}
					break;
				case 3:
					retorno = 0;
					printf("Submenú cerrado\n");
					mostrarSubmenu = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

int controller_generarInformeVentasFormatoTexto(char *path,
		LinkedList *pListaVentas) {
	int retorno = -1;
	FILE *pArchivo = NULL;

	if (ll_len(pListaVentas) < 1) {
		printf("No existen ventas\n");
		return -1;
	}

	if (path != NULL && pListaVentas != NULL) {
		pArchivo = fopen(path, "wt");
		if (parserGenerarInformeVentasTexto(pArchivo, pListaVentas) == 0) {
			retorno = 0;
		}
	}
	fclose(pArchivo);
	return retorno;
}
