#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "LinkedList.h"
#include "Controller.h"
#include "Ventas.h"
#define MENSAJE_MENU "Seleccione una opción:\n1. Alta de venta.\n2. Baja de venta.\n3. Modificación venta.\n4. Listar ventas.\n5. Guardar archivo.\n6. Generar informe de ventas.\n7. Salir.\n"

int main(void) {
	int mostrarMenu = 1;
	int opcion;
	int confirmacion;
	int seHicieronCambios = 0;
	LinkedList *listaVentas = ll_newLinkedList();

	if (controller_cargarVentasDesdeTexto("data.csv", listaVentas) == -1) {
		printf("Error. No se pudo cargar el archivo de ventas.\n");
	}

	while (mostrarMenu) {
		if (utn_obtenerNumero(&opcion,
		MENSAJE_MENU, "Error. Opción inválida.\n", 1, 7) == 0) {
			switch (opcion) {
			case 1:
				if (controller_agregarVenta(listaVentas) == 0) {
					printf("Se dio de alta la venta exitosamente\n");
					seHicieronCambios = 1;
				} else {
					printf("Error. No se pudo dar de alta la venta\n");
				}
				break;
			case 2:
				if (controller_eliminarVenta(listaVentas) == 0) {
					seHicieronCambios = 1;
					printf("Se eliminó la venta exitosamente\n");
				} else {
					printf("No se eliminó ninguna venta\n");
				}
				break;
			case 3:
				if (controller_modificarVenta(listaVentas) == 0) {
					seHicieronCambios = 1;
				}
				break;
			case 4:
				if (listarVentas(listaVentas) == -1) {
					printf("No se pudieron listar las ventas\n");
				}
				break;
			case 5:
				if (guardarArchivoVentasSubmenu(listaVentas) == 0) {
					seHicieronCambios = 0;
				}
				break;
			case 6:
				if (controller_generarInformeVentasFormatoTexto("informes.txt",
						listaVentas) == 0) {
					printf("Se generó exitosamente el informe de ventas\n");
				} else {
					printf("No se pudo generar el informe de ventas\n");
				}
				break;
			case 7:
				if (seHicieronCambios) {
					if (utn_obtenerNumero(&confirmacion,
							"Seguro desea salir sin guardar los cambios?\n1. Si.\n2. No.\n",
							"Error. Opción inválida, tiene que elegir un número del 1 al 2.\n",
							1, 2) == 0 && confirmacion == 1) {
						printf("Hasta luego;)\n");
						mostrarMenu = 0;
					}
				} else {
					mostrarMenu = 0;
					printf("Menu cerrado, no se realizaron nuevos cambios\n");
				}
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}
