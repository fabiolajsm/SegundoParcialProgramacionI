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

static Node* getNode(LinkedList *this, int nodeIndex) {
	Node *auxNode = NULL;

	if (this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this)) {
		auxNode = this->pFirstNode;
		for (int i = 0; i < nodeIndex; i++) {
			auxNode = auxNode->pNextNode;
		}
	}

	return auxNode;
}

static int addNode(LinkedList *this, int nodeIndex, void *pElement) {
	int retorno = -1;
	Node *auxNode = (Node*) malloc(sizeof(Node*));
	Node *auxPrevNode = NULL;

	if (auxNode != NULL && this != NULL && nodeIndex >= 0 && pElement != NULL
			&& nodeIndex <= ll_len(this)) {
		auxNode->pElement = pElement;

		if (nodeIndex == 0) {
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
	Node *auxNode = NULL;
	void *pRetorno = NULL;

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
				auxPrevNode->pNextNode = auxNode->pNextNode;
				this->size--;
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
	}
	return contador;
}
