#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "LinkedList.h"

/**
 * @fn int controller_cargarVentasDesdeTexto(char *, LinkedList *)
 * @brief Esta función carga las ventas que existen en un archivo con formato texto
 * @param path Nombre del archivo a usar
 * @param pListVentas Puntero de la LinkedList en donde se van a cargar las ventas
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int controller_cargarVentasDesdeTexto(char *path, LinkedList *pListVentas);
/**
 * @fn int controller_generarIDVenta(void)
 * @brief Esta función genera un nuevo ID de venta
 * @param void
 * @return Retorna el un nuevo ID para una venta.
 * */
int controller_generarIDVenta(void);
/**
 * @fn int controller_guardarVentasFormatoTexto(char *, LinkedList *)
 * @brief Esta función guarda las ventas que existen en la LinkedList en un archivo con formato de texto
 * @param path Nombre del archivo a usar
 * @param pListaVentas Puntero de la LinkedList en donde están las ventas
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int controller_guardarVentasFormatoTexto(char *path, LinkedList *pListaVentas);
/**
 * @fn int controller_guardarVentasFormatoBinario(char *, LinkedList *)
 * @brief Esta función guarda las ventas que existen en la LinkedList en un archivo con formato binario
 * @param path Nombre del archivo a usar
 * @param pListaVentas Puntero de la LinkedList en donde están las ventas
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int controller_guardarVentasFormatoBinario(char *path, LinkedList *pListaVentas);
/**
 * @fn int controller_agregarVenta(LinkedList *pListaVentas)
 * @brief Esta función pide los datos de una venta y la agrega en la LinkedList si todos los datos son validos
 * @param pListaVentas Puntero de la LinkedList en donde se va a agregar la venta
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int controller_agregarVenta(LinkedList *pListaVentas);
/**
 * @fn int  controller_eliminarVenta(LinkedList *pListaVentas)
 * @brief Esta función pide el ID de una venta y si es valido y el usuario confirma su baja, elimina la venta de la LinkedList
 * @param pListaVentas Puntero de la LinkedList en donde se va a eliminar la venta
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int controller_eliminarVenta(LinkedList *pListaVentas);
/**
 * @fn int controller_modificarVenta(LinkedList *pListaVentas)
 * @brief Esta función pide el ID de una venta y si es valido y muestra un submenú que permite modificar los datos de la venta seleccionada
 * @param pListaVentas Puntero de la LinkedList en donde se encuentra la venta a modificar
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int controller_modificarVenta(LinkedList *pListaVentas);
/**
 * @fn int controller_guardarVentasFormatoTexto(char *, LinkedList *)
 * @brief Esta función genera un informe de ventas en formato texto
 * @param path Nombre del archivo a generar
 * @param pListaVentas Puntero de la LinkedList en donde se encuentran las ventas
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int controller_generarInformeVentasFormatoTexto(char *path,
		LinkedList *pListaVentas);
/**
 * @fn int listarVentas(LinkedList *pListVentas)
 * @brief Esta función lista las ventas que se encuentran en una LinkedList
 * @param pListaVentas Puntero de la LinkedList en donde se encuentran las ventas
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int listarVentas(LinkedList *pListVentas);
/**
 * @fn int guardarArchivoVentasSubmenu(LinkedList *pListaVentas)
 * @brief Esta función muestra un submenú con las opciones de guardado de un archivo
 * @param pListaVentas Puntero de la LinkedList en donde se encuentran las ventas
 * @return Retorna 0 si se realizó bien la función y -1 si hubo un error.
 * */
int guardarArchivoVentasSubmenu(LinkedList *pListaVentas);

#endif /* CONTROLLER_H_ */
