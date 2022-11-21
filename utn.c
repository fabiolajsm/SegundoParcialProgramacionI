#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ventas.h"

static int esNumero(char cadena[]) {
	int i = 0;
	int retorno = 1;
	if (cadena != NULL && strlen(cadena) > 0) {
		while (cadena[i] != '\0') {
			if (cadena[i] < '0' || cadena[i] > '9') {
				retorno = 0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

static int obtenerInt(int *pResultado) {
	int ret = -1;
	char buffer[1024];

	fgets(buffer, sizeof(buffer), stdin);
	buffer[strlen(buffer) - 1] = '\0';

	if (esNumero(buffer) == 1) {
		*pResultado = atoi(buffer);
		ret = 0;
	}
	return ret;
}

int utn_obtenerNumero(int *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo) {
	int ret = -1;
	int num;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (ret == -1) {
			printf("%s", mensaje);
			if (obtenerInt(&num) == 0) {
				if (num <= maximo && num >= minimo) {
					*pResultado = num;
					ret = 0;
					break;
				}
			}
			printf("%s", mensajeError);
		}
	}
	return ret;
}

static int obtenerShort(short *pResultado) {
	int ret = -1;
	char buffer[1024];

	fgets(buffer, sizeof(buffer), stdin);
	buffer[strlen(buffer) - 1] = '\0';

	if (esNumero(buffer) == 1) {
		*pResultado = atoi(buffer);
		ret = 0;
	}
	return ret;
}

int utn_obtenerNumeroShort(short *pResultado, char *mensaje, char *mensajeError,
		int minimo, int maximo) {
	int ret = -1;
	short num;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (ret == -1) {
			printf("%s", mensaje);
			if (obtenerShort(&num) == 0) {
				if (num <= maximo && num >= minimo) {
					*pResultado = num;
					ret = 0;
					break;
				}
			}
			printf("%s", mensajeError);
		}
	}
	return ret;
}

static int esTexto(char *cadena) {
	if (cadena == NULL || strlen(cadena) < 1)
		return 0;

	for (int i = 0; cadena[i] != '\0'; i++) {
		if ((cadena[i] < 'A' || cadena[i] > 'Z')
				&& (cadena[i] < 'a' || cadena[i] > 'z') && cadena[i] != ' ') {
			// Acá no es texto
			return 0;
		}
	}

	return 1;
}

static int obtenerString(char *pResultado, int longitud) {
	int retorno = -1;
	char buffer[1024];
	fgets(buffer, sizeof(buffer), stdin);

	if (pResultado != NULL && longitud > 0) {
		if (buffer[strnlen(buffer, sizeof(buffer)) - 1] == '\n') {
			buffer[strnlen(buffer, sizeof(buffer)) - 1] = '\0';
		}
		if (strnlen(buffer, sizeof(buffer)) <= longitud && esTexto(buffer)) {
			strncpy(pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}

int utn_obtenerTexto(char *pResultado, int largo, char *mensaje,
		char *mensajeError, int maxCaracteres) {
	int retorno = -1;
	int esTextoValido = 0;
	char auxTexto[1024];

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (esTextoValido == 0) {
			printf("%s", mensaje);
			if (obtenerString(auxTexto, sizeof(auxTexto)) == 0
					&& strnlen(auxTexto, sizeof(auxTexto)) <= maxCaracteres) {
				strncpy(pResultado, auxTexto, largo);
				esTextoValido = 1;
				retorno = 0;
				break;

			}
			printf("%s", mensajeError);
		}
	}
	return retorno;
}

static int esModeloAuto(char *cadena) {
	int retorno = 1;
	int contadorLetras = 0;
	if (cadena == NULL || strlen(cadena) < 1)
		return 0;

	for (int i = 0; cadena[i] != '\0'; i++) {
		if ((cadena[i] < 'A' || cadena[i] > 'Z')
				&& (cadena[i] < 'a' || cadena[i] > 'z') && cadena[i] != ' '
				&& cadena[i] != '-' && (cadena[i] < '0' || cadena[i] > '9')) {
			// Acá no es texto
			retorno = 0;
		} else if ((cadena[i] >= 'A' && cadena[i] <= 'Z')
				|| (cadena[i] >= 'a' && cadena[i] <= 'z')) {
			contadorLetras++;
		}
	}
	if (contadorLetras == 0) {
		// El modelo de auto mínimo tiene que tener una letra
		retorno = 0;
	}
	return retorno;
}

static int obtenerStringModeloAuto(char *pResultado, int longitud) {
	int retorno = -1;
	char buffer[1024];
	fgets(buffer, sizeof(buffer), stdin);

	if (pResultado != NULL && longitud > 0) {
		if (buffer[strnlen(buffer, sizeof(buffer)) - 1] == '\n') {
			buffer[strnlen(buffer, sizeof(buffer)) - 1] = '\0';
		}
		if (strnlen(buffer, sizeof(buffer)) <= longitud
				&& esModeloAuto(buffer)) {
			strncpy(pResultado, buffer, longitud);
			retorno = 0;
		}
	}
	return retorno;
}

int utn_obtenerModeloAuto(char *pResultado, int largo, char *mensaje,
		char *mensajeError, int maxCaracteres) {
	int retorno = -1;
	int esTextoValido = 0;
	char auxTexto[1024];

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (esTextoValido == 0) {
			printf("%s", mensaje);
			if (obtenerStringModeloAuto(auxTexto, sizeof(auxTexto)) == 0
					&& strnlen(auxTexto, sizeof(auxTexto)) <= maxCaracteres) {
				strncpy(pResultado, auxTexto, largo);
				esTextoValido = 1;
				retorno = 0;
				break;

			}
			printf("%s", mensajeError);
		}
	}
	return retorno;
}

static int esFlotante(char cadena[]) {
	int retorno = 1;
	int i = 0;
	int cantidadPuntos = 0;

	if (cadena == NULL || strlen(cadena) < 1)
		return 0;

	while (cadena[i] != '\0') {
		if (cadena[i] == '.' && cantidadPuntos < 1) {
			cantidadPuntos++;
		} else {
			if (cadena[i] < '0' || cadena[i] > '9' || cantidadPuntos > 1) {
				retorno = 0;
				break;
			}
		}
		i++;
	}
	return retorno;
}

static int obtenerFloat(float *pResultado) {
	int ret = -1;
	char buffer[1024];

	fgets(buffer, sizeof(buffer), stdin);
	buffer[strlen(buffer) - 1] = '\0';

	if (esFlotante(buffer) == 1) {
		*pResultado = atof(buffer);
		ret = 0;
	}
	return ret;
}

int utn_obtenerFlotante(float *pResultado, char *mensaje, char *mensajeError,
		float minimo, float maximo) {
	int ret = -1;
	float num;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (ret == -1) {
			printf("%s", mensaje);
			if (obtenerFloat(&num) == 0) {
				if (num <= maximo && num >= minimo) {
					*pResultado = num;
					ret = 0;
					break;
				}
			}
			printf("%s", mensajeError);
		}
	}
	return ret;
}
static int esFechaCorrecta(int dia, int mes, int anio) {
	int ret = 0;

	if (dia < 1) {
		printf("Error, el día no puede ser menor a 1.\n");
	} else if (mes > 12 || mes < 1) {
		printf("Error, el mes no puede ser menor a 1 ni mayor a 12.\n");
	} else if (anio < 1 && anio > 2022) {
		printf(
				"Error, el año no puede ser menor a 1 ni mayor al año actual (2022).\n");
	}

	switch (mes) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (dia > 31) {
			printf("Error, este mes no tiene más de 31 días.\n");
		} else {
			ret = 1;
		}
		break;
	case 2:
		if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
			if (dia > 0 && dia < 30) {
				ret = 1;
			} else {
				printf("Error, este mes no tiene más de 29 días.\n");
			}
		} else {
			if (dia > 0 && dia < 29) {
				ret = 1;
			} else {
				printf("Error, este mes no tiene más de 28 días.\n");
			}
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (dia > 30) {
			printf("Error, este mes no tiene más de 30 días.\n");
		} else {
			ret = 1;
		}
		break;
	}

	if (anio < 2022) {
		printf("Error, el año no puede ser menor al actual 2022.\n");
		ret = 0;
	}

	return ret;
}

int utn_obtenerFecha(eFecha *pFecha, char *mensaje) {
	int ret = -1;
	int esFechaValida = -1;
	int intentos = 5;
	int dia;
	int mes;
	int anio;
	eFecha aux;

	if (pFecha != NULL && mensaje != NULL) {
		printf("%s", mensaje);
		while (intentos > 0) {
			printf("Ingrese día:\n");
			obtenerInt(&dia);
			printf("Ingrese mes:\n");
			obtenerInt(&mes);
			printf("Ingrese año:\n");
			obtenerInt(&anio);
			if (esFechaCorrecta(dia, mes, anio) == 1) {
				esFechaValida = 0;
				break;
			}
			intentos--;
		}
		if (esFechaValida == 0) {
			aux.dia = dia;
			aux.mes = mes;
			aux.anio = anio;
			*pFecha = aux;
			ret = 0;
		}
		if (intentos == 0) {
			printf("Error, intentos acabados\n");
		}
	}
	return ret;
}

static int esTarjetaDeCredito(char cadena[]) {
	int i = 0;
	int retorno = 1;
	int contador = 0;
	if (cadena != NULL && strlen(cadena) > 0) {
		while (cadena[i] != '\0') {
			if (cadena[i] < '0' || cadena[i] > '9') {
				retorno = 0;
				break;
			}
			if (!(cadena[0] == '5' && cadena[1] == '1' && cadena[2] == '0'
					&& cadena[3] == '0')) {
				retorno = 0;
			} else {
				contador++;
			}
			i++;
		}
	}
	if (contador != 16) {
		retorno = 0;
	}
	return retorno;
}

static int obtenerTarjetaDeCredito(long int *pResultado) {
	int ret = -1;
	char buffer[1024];
	char *tarjetaCreditoStr;

	fgets(buffer, sizeof(buffer), stdin);
	buffer[strlen(buffer) - 1] = '\0';

	if (esTarjetaDeCredito(buffer) == 1) {
		*pResultado = strtol(buffer, &tarjetaCreditoStr, 10);
		ret = 0;
	}
	return ret;
}

int utn_obtenerTarjetaDeCredito(long int *pResultado, char *mensaje,
		char *mensajeError) {
	int retorno = -1;
	long int num;
	int intentos = 5;

	if (pResultado != NULL && mensaje != NULL && mensajeError != NULL) {
		while (intentos > 0) {
			printf("%s", mensaje);
			if (obtenerTarjetaDeCredito(&num) == 0) {
				*pResultado = num;
				retorno = 0;
				break;
			}
			printf("%s", mensajeError);
			intentos--;
		}
	}
	if (intentos == 0) {
		printf("Error, intentos acabados\n");
	}
	return retorno;
}
