#ifndef PARSER_H_
#define PARSER_H_
#include "LinkedList.h"

int parserVentasDesdeTexto(FILE *pArchivo, LinkedList *pListVentas);
int parserGuardarVentasTexto(FILE *pArchivo, LinkedList *pListVentas);
int parserGenerarInformeVentasTexto(FILE *pArchivo, LinkedList *pListaVentas);
int parserGuardarVentasFormatoBinario(FILE *pArchivo, LinkedList *pListaVentas);

#endif /* PARSER_H_ */
