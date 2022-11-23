#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "LinkedList.h"

int controller_cargarVentasDesdeTexto(char *path, LinkedList *pListVentas);
int controller_generarIDVenta(void);
int controller_guardarVentasFormatoTexto(char *path, LinkedList *pListaVentas);
int controller_guardarVentasFormatoBinario(char *path, LinkedList *pListaVentas);

#endif /* CONTROLLER_H_ */