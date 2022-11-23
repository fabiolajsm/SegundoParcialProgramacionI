#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct Node {
	void *pElement;
	struct Node *pNextNode;
}typedef Node;

struct LinkedList {
	Node *pFirstNode;
	int size;
}typedef LinkedList;

/**
 * @fn LinkedList* ll_newLinkedList(void)
 * @brief Esta función crea un nuevo LinkedList en memoria de manera dinámica
 * @param void
 * @return LinkedList* Retorna NULL si no se pudo conseguir espacio en memoria o el puntero al espacio reservado
 * */
LinkedList* ll_newLinkedList(void);
/**
 * @fn int ll_len(LinkedList *this)
 * @brief Esta función retorna la cantidad de elementos de la lista
 * @param this LinkedList* Puntero a la lista de elementos
 * @return int Retorna -1 si el puntero es NULL o la cantidad de elementos de la lista
 * */
int ll_len(LinkedList *this);
/**
 * @fn Node* test_getNode(LinkedList *this, int nodeIndex)
 * @brief Esta función permite realizar el test de la función getNode, esta funcion es privada
 * @param this LinkedList* Puntero a la lista de elementos
 * @param nodeIndex int Indice del nodo a obtener
 * @return Node* Retorna NULL si hubo un error y pElement si funcionó bien
 * */
Node* test_getNode(LinkedList *this, int nodeIndex);
/**
 * @fn int test_addNode(LinkedList *this, int nodeIndex, void *pElement)
 * @brief Esta función permite realizar el test de la función addNode, esta funcion es privada
 * @param this LinkedList* Puntero a la lista de elementos
 * @param nodeIndex int Ubicacion donde se agregará el nuevo nodo
 * @param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * @return int Retorna -1 si hubo un error y 0 si funcionó bien
 * */
int test_addNode(LinkedList *this, int nodeIndex, void *pElement);
/**
 * @fn int ll_add(LinkedList *this, void *pElement)
 * @brief Agrega un elemento a la lista
 * @param this LinkedList* Puntero a la lista
 * @param pElement void* Puntero al elemento a ser agregado
 * @return int Retorna -1 si hubo un error y 0 si funcionó bien
 * */
int ll_add(LinkedList *this, void *pElement);
/**
 * @fn void* ll_get(LinkedList *this, int index)
 * @brief Obtiene un elemento a la lista según su index(ubicación)
 * @param this LinkedList* Puntero a la lista
 * @param index int Ubicacion del elemento a obtener
 * @return int Retorna NULL si hubo un error y pElement si funcionó bien
 * */
void* ll_get(LinkedList *this, int index);
/**
 * @fn int ll_indexOf(LinkedList *this, void *pElement)
 * @brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 * @param this LinkedList* Puntero a la lista
 * @param pElement void* Puntero al elemento
 * @return int Retorna -1 si hubo un error y el indice del elemento si funcionó bien
 * */
int ll_indexOf(LinkedList *this, void *pElement);
/**
 * @fn int ll_remove(LinkedList *this, int index)
 * @brief Elimina un elemento de la lista
 * @param this LinkedList* Puntero a la lista
 * @param index int Ubicación del elemento a eliminar
 * @return int Retorna -1 si hubo un error y 0 si funcionó bien
 * */
int ll_remove(LinkedList *this, int index);
/**
 * @fn int ll_count(LinkedList *this, int (fn)(void *element))
 * @brief Indica la suma de los retornos de todos los elementos de la lista pasados por la función criterio
 * @param this LinkedList* Puntero a la lista
 * @param  int (fn)(void *element) Puntero a la funcion criterio
 * @return int Retorna -1 si hubo un error y la suma de los retornos de la función criterio si funcionó bien
 * */
int ll_count(LinkedList *this, int (fn)(void *element));
/**
 * @fn int ll_set(LinkedList *this, int index, void *pElement)
 * @brief Modifica un elemento de la lista
 * @param this LinkedList* Puntero a la lista
 * @param index int Ubicacion del elemento a modificar
 * @param pElement void* Puntero al nuevo elemento
 * @return int Retorna -1 si hubo un error y 0 si funcionó bien
 * */
int ll_set(LinkedList *this, int index, void *pElement);
/**
 * @fn int ll_clear(LinkedList *this)
 * @brief Elimina todos los elementos de la lista
 * @param this LinkedList* Puntero a la lista
 * @return int Retorna -1 si hubo un error y 0 si funcionó bien
 * */
int ll_clear(LinkedList *this);
/**
 * @fn int ll_clear(LinkedList *this)
 * @brief Elimina todos los elementos de la lista y la lista
 * @param this LinkedList* Puntero a la lista
 * @return int Retorna -1 si hubo un error y 0 si funcionó bien
 * */
int ll_deleteLinkedList(LinkedList *this);
/**
 * @fn int ll_isEmpty(LinkedList *this)
 * @brief Indica si la lista esta o no vacia
 * @param this LinkedList* Puntero a la lista
 * @return int Retorna 0 si no esta vacia y 1 si sí está vacia
 * */
int ll_isEmpty(LinkedList *this);
/**
 * @fn int ll_push(LinkedList *this, int index, void *pElement)
 * @brief Inserta un nuevo elemento en la lista en la posicion indicada
 * @param this LinkedList* Puntero a la lista
 * @param index int Ubicación donde se agregara el nuevo elemento
 * @param pElement void* Puntero al nuevo elemento
 * @return int Retorna -1 si hubo error y 0 si funcionó correctamente
 * */
int ll_push(LinkedList *this, int index, void *pElement);
/**
 * @fn void* ll_pop(LinkedList *this, int index)
 * @brief Elimina el elemento de la posicion indicada y retorna su puntero
 * @param this LinkedList* Puntero a la lista
 * @param index int int Ubicación del elemento eliminar
 * @return void* Retorna NULL si hubo error y pElement si funcionó correctamente
 * */
void* ll_pop(LinkedList *this, int index);
/**
 * @fn int ll_contains(LinkedList *this, void *pElement)
 * @brief Indica si la lista contiene o no el elemento pasado como parametro
 * @param this LinkedList* Puntero a la lista
 * @param pElement void* Puntero del elemento a verificar
 * @return int Retorna 1 si contiene el elemento y 0 si no lo contiene
 * */
int ll_contains(LinkedList *this, void *pElement);
/**
 * @fn int ll_containsAll(LinkedList *this, LinkedList *this2)
 * @brief Indica si todos los elementos de la lista (this2) están contenidos en la lista (this)
 * @param this LinkedList* Puntero a la lista
 * @param this2 LinkedList* Puntero a la lista
 * @return int Retorna -1 si hubo algún error, 1 si estan contenidas y 0 si no estan en la lista.
 * */
int ll_containsAll(LinkedList *this, LinkedList *this2);
/**
 * @fn LinkedList* ll_subList(LinkedList *this, int from, int to)
 * @brief Crea y retorna una nueva lista con los elementos indicados
 * @param this LinkedList* Puntero a la lista
 * @param from int Indice desde el cual se copian los elementos en la nueva lista
 * @param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * @return LinkedList* Retorna NULL si hubo error y el puntero a la nueva lista si funcionó bien
 * */
LinkedList* ll_subList(LinkedList *this, int from, int to);
/**
 * @fn LinkedList* ll_subList(LinkedList *this, int from, int to)
 * @brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 * @param this LinkedList* Puntero a la lista
 * @return LinkedList* Retorna NULL si hubo error y el puntero a la nueva lista si funcionó bien
 * */
LinkedList* ll_clone(LinkedList *this);
/**
 * @fn int ll_sort(LinkedList *this, int (*pFunc)(void*, void*), int order)
 * @brief Ordena los elementos de la lista utilizando la funcion criterio que reciba como parametro
 * @param this LinkedList* Puntero a la lista
 * @param pFunc (*pFunc) Puntero a la funcion criterio
 * @param order int 0 Indica orden descendente y 1 Indica orden ascendente
 * @return int Retorna -1 si hubo algún error y 0 si funcionó bien
 * */
int ll_sort(LinkedList *this, int (*pFunc)(void*, void*), int order);
/**
 * @fn LinkedList* ll_filter(LinkedList *this, int (fn)(void *element)
 * @brief Crea y retorna una nueva lista con los elementos filtrados según la función criterio pasada por parametro
 * @param this LinkedList* Puntero a la lista
 * @param pFunc (*pFunc) Puntero a la funcion criterio
 * @return LinkedList* Retorna NULL si hubo error y el puntero a la nueva lista con los elementos filtrados si funcionó bien
 * */
LinkedList* ll_filter(LinkedList *this, int (fn)(void *element));
/**
 * @fn LinkedList* ll_map(LinkedList *this, void (fn)(void *element))
 * @brief Itera todos los elementos de la lista this y modifica cada elemento según la funión criterio (si es necesario) quedando la lista modificada
 * @param this LinkedList* Puntero a la lista
 * @param pFunc (*pFunc) Puntero a la funcion criterio
 * @return LinkedList* Retorna NULL si hubo error y el puntero a la lista con los elementos modificados si funcionó bien
 * */
LinkedList* ll_map(LinkedList *this, void (fn)(void *element));

#endif /* LINKEDLIST_H_ */
