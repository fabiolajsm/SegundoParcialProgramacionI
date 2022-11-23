#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

LinkedList* ll_newLinkedList(void) {
	LinkedList *this = (LinkedList*) malloc(sizeof(LinkedList*));
	if (this != NULL) {
		this->pFirstNode = NULL;
		this->size = 0;
	}
	return this;
}

int ll_len(LinkedList *this) {
	int retorno = -1;
	if (this != NULL) {
		retorno = this->size;
	}
	return retorno;
}

/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o si el indice es menor a 0
 *  o mayor al largo de la lista y (pNode) si funcionó correctamente
 */
static Node* getNode(LinkedList *this, int nodeIndex) {
	Node *auxNode = NULL;

	if (this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this)) {
		auxNode = this->pFirstNode;

		for (int i = 0; i < nodeIndex; i++) {
			if (i != nodeIndex) {
				auxNode = auxNode->pNextNode;
			} else {
				break;
			}
		}
	}

	return auxNode;
}

Node* test_getNode(LinkedList *this, int nodeIndex) {
	return getNode(this, nodeIndex);
}

static int addNode(LinkedList *this, int nodeIndex, void *pElement) {
	int retorno = -1;
	Node *auxNode = (Node*) malloc(sizeof(Node*));
	Node *auxPrevNode = NULL;

	if (auxNode != NULL && this != NULL && nodeIndex >= 0 && pElement != NULL
			&& nodeIndex <= ll_len(this)) {
		auxNode->pElement = pElement;
		if (nodeIndex == 0) { // es el primero a agregar
			auxNode->pNextNode = this->pFirstNode;
			this->pFirstNode = auxNode;
			this->size++;
			retorno = 0;
		} else {
			auxPrevNode = getNode(this, nodeIndex - 1);
			if (auxPrevNode != NULL) {
				auxNode->pNextNode = auxPrevNode->pNextNode;
				auxPrevNode->pNextNode = auxNode;
				this->size++;
				retorno = 0;
			}
		}
	}
	return retorno;
}

int test_addNode(LinkedList *this, int nodeIndex, void *pElement) {
	return addNode(this, nodeIndex, pElement);
}

int ll_add(LinkedList *this, void *pElement) {
	int retorno = -1;

	if (this != NULL && pElement != NULL) {
		if (addNode(this, ll_len(this), pElement) == 0) {
			retorno = 0;
		}
	}

	return retorno;
}

void* ll_get(LinkedList *this, int index) {
	void *pRetorno = NULL;
	Node *auxNode = NULL;

	if (this != NULL && index >= 0 && index < ll_len(this)) {
		auxNode = getNode(this, index);
		if (auxNode != NULL) {
			pRetorno = auxNode->pElement;
		}
	}
	return pRetorno;
}

int ll_indexOf(LinkedList *this, void *pElement) {
	int retorno = -1;
	int largoLinkedlist = ll_len(this);
	Node *auxNode;

	if (this != NULL && pElement != NULL && largoLinkedlist > 0) {
		for (int i = 0; i < largoLinkedlist; i++) {
			auxNode = getNode(this, i);
			if (auxNode != NULL && auxNode->pElement == pElement) {
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

int ll_remove(LinkedList *this, int index) {
	int retorno = -1;
	Node *auxNode = NULL;
	Node *auxPrevNode = NULL;

	if (this != NULL && index >= 0 && index < ll_len(this)) {
		auxNode = getNode(this, index);
		if (auxNode != NULL) {
			if (index == 0) {
				this->pFirstNode = auxNode->pNextNode;
				this->size--;
			} else {
				auxPrevNode = getNode(this, index - 1);
				if (auxPrevNode != NULL) {
					auxPrevNode->pNextNode = auxNode->pNextNode;
					this->size--;
				}
			}
		}
		free(auxNode);
		retorno = 0;
	}
	return retorno;
}

int ll_count(LinkedList *this, int (fn)(void *element)) {
	int contador = 0;
	int largoLista;
	void *pAuxElemento;

	if (this != NULL && fn != NULL) {
		largoLista = ll_len(this);
		if (largoLista > 0) {
			for (int i = 0; i < largoLista; i++) {
				pAuxElemento = ll_get(this, i);
				if (pAuxElemento != NULL) {
					contador += fn(pAuxElemento);
				}
			}
		}
	} else {
		return -1;
	}
	return contador;
}

int ll_set(LinkedList *this, int index, void *pElement) {
	int retorno = -1;
	Node *auxNode = NULL;

	if (this != NULL && index >= 0 && index < ll_len(this) && pElement != NULL) {
		auxNode = getNode(this, index);
		if (auxNode != NULL) {
			auxNode->pElement = pElement;
			retorno = 0;
		}
	}
	return retorno;
}

int ll_clear(LinkedList *this) {
	int retorno = -1;
	int largoLinkedList = ll_len(this);

	if (this != NULL && largoLinkedList > 0) {
		for (int i = 0; i < largoLinkedList; i++) {
			if (ll_remove(this, i) == 0) {
				retorno = 0;
			}
		}
	}
	return retorno;
}

int ll_deleteLinkedList(LinkedList *this) {
	int retorno = -1;

	if (this != NULL) {
		if (ll_clear(this) == 0) {
			free(this);
			retorno = 0;
		}
	}

	return retorno;
}

int ll_isEmpty(LinkedList *this) {
	int retorno = -1;

	if (this != NULL) {
		if (ll_len > 0 && this->pFirstNode != NULL) {
			// No está vacía
			retorno = 0;
		} else {
			// Está vacía
			retorno = 1;
		}
	}
	return retorno;
}

int ll_push(LinkedList *this, int index, void *pElement) {
	int retorno = -1;

	if (this != NULL && (index >= 0 && index <= ll_len(this))
			&& pElement != NULL) {
		if (addNode(this, index, pElement) == 0) {
			retorno = 0;
		}
	}

	return retorno;
}

void* ll_pop(LinkedList *this, int index) {
	void *retorno = NULL;
	void *pAuxElemento;

	if (this != NULL && index >= 0 && index < ll_len(this)) {
		pAuxElemento = ll_get(this, index);
		if (pAuxElemento != NULL) {
			if (ll_remove(this, index) == 0) {
				retorno = pAuxElemento;
			}
		}
	}
	return retorno;
}

int ll_contains(LinkedList *this, void *pElement) {
	int retorno = -1;

	if (this != NULL && pElement != NULL) {
		if (ll_indexOf(this, pElement) != -1) {
			retorno = 1; // Si contiene
		} else {
			retorno = 0; // No contiene
		}
	}

	return retorno;
}

int ll_containsAll(LinkedList *this, LinkedList *this2) {
	int retorno = -1;
	int len;

	if (this != NULL && this2 != NULL) { //ver si hay que validar que una list2 sea menor que list
		len = ll_len(this2);
		if (len == 0) {
			retorno = 0;
		} else {
			for (int i = 0; i < len; i++) {
				if (ll_contains(this, ll_get(this2, i)) == 0) {
					retorno = 0; //no contiene
					break;
				} else {
					retorno = 1; // contiene
				}
			}
		}
	}
	return retorno;
}

LinkedList* ll_subList(LinkedList *this, int from, int to) {
	LinkedList *subList = NULL;
	void *pAuxElement;

	if (this != NULL && to > from && to <= ll_len(this) && from >= 0
			&& from < ll_len(this)) {
		subList = ll_newLinkedList();

		if (subList != NULL) {
			for (int i = from; i < to; i++) {
				pAuxElement = ll_get(this, i);
				if (pAuxElement != NULL) {
					ll_add(subList, pAuxElement);
				}
			}
		}
	}
	return subList;
}

LinkedList* ll_clone(LinkedList *this) {
	LinkedList *cloneList = NULL;
	if (this != NULL) {
		cloneList = ll_subList(this, 0, ll_len(this));
	}
	return cloneList;
}

int ll_sort(LinkedList *this, int (*pFunc)(void*, void*), int order) {
	int retorno = -1;
	int estaOrdenado;
	int len;
	void *auxElement = NULL;
	void *auxElementDos = NULL;
	int retornoPFunc;

	if (this != NULL && pFunc != NULL && (order == 0 || order == 1)) {
		len = ll_len(this);
		while (estaOrdenado == 0) {
			estaOrdenado = 1;
			len--;
			for (int i = 0; i < len; i++) {
				auxElement = ll_get(this, i);
				auxElementDos = ll_get(this, i + 1);
				if (auxElement != NULL && auxElementDos != NULL) {
					retornoPFunc = pFunc(auxElement, auxElementDos);
					if ((retornoPFunc > 0 && order == 1)
							|| (retornoPFunc < 0 && order == 0)) {
						if (ll_set(this, i, auxElementDos) == 0
								&& ll_set(this, i + 1, auxElement) == 0) {
							estaOrdenado = 0;
						}
					}
				}
			}
		}
		retorno = 0;
	}

	return retorno;
}

// Funciones opcionales
LinkedList* ll_filter(LinkedList *this, int (fn)(void *element)) {
	LinkedList *filterList = NULL;
	int lenList;
	void *auxElement;

	if (this != NULL && fn != NULL) {
		filterList = ll_newLinkedList();
		lenList = ll_len(this);

		if (filterList != NULL && lenList > 0) {
			for (int i = 0; i < lenList; i++) {
				auxElement = ll_get(this, i);
				if (auxElement != NULL && fn(auxElement) == 1) {
					ll_add(filterList, auxElement);
				}
			}
		}
	}
	return filterList;
}

LinkedList* ll_map(LinkedList *this, void (fn)(void *element)) {
	int lenList;
	void *auxElement;

	if (this != NULL && fn != NULL) {
		lenList = ll_len(this);
		if (lenList > 0) {
			for (int i = 0; i < lenList; i++) {
				auxElement = ll_get(this, i);

				if (auxElement != NULL) {
					fn(auxElement);
				}
			}
		}
	}

	return this;
}

