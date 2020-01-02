#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define COMANDO_AYUDA "ayuda"
#define COMANDO_PERDONABLES "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIBERADOS "mostrar_liberados"
#define CONDUCTA_BUENA "B"
#define CONDUCTA_REGULAR "R"
#define CONDUCTA_MALA "M"
#define BUENA 'B'
#define REGULAR 'R'
#define MALA 'M'
#define PRIMER_MES 1
#define ULTIMO_MES 12
#define FALLO -1
#define FUNCIONO 0
#define LECTURA "r"
#define ESCRITURA "w"
#define EXTENSION_ARCHIVO_TEXTO ".txt"
#define PREFIJO_ARCHIVO_LIBERADOS "liberados_"
#define NO_HAY_LIBERADOS 0
#define HAY_LIBERADOS 1
#define ARCHIVO_CRUCIO "crucio.dat"
#define ARCHIVO_IMPERIUS "imperius.dat"
#define ARCHIVO_CRUCIO_ACTUALIZADO "crucioactual.dat"
#define ARCHIVO_IMPERIUS_ACTUALIZADO "imperiusactual.dat"
#define LEER_SECUENCIAL 1
#define ESCRIBIR_SECUENCIAL 1
typedef struct preso{
	char nombre[MAX_NOMBRE];
	unsigned edad;
	char conducta;
	unsigned pabellon;
	unsigned celda;
	char fecha[MAX_FECHA];
	int maldicion_realizada;
}preso_t;

bool es_comando_valido(char* comando_ingresado){
	return ((strcmp(comando_ingresado,COMANDO_PERDONABLES)==0)||(strcmp(comando_ingresado,COMANDO_AYUDA)==0)||(strcmp(comando_ingresado,COMANDO_LIBERAR)==0)||(strcmp(comando_ingresado,COMANDO_ACTUALIZAR)==0)||(strcmp(comando_ingresado,COMANDO_MOSTRAR_LIBERADOS)==0));
}
bool es_comando(char* comando_ingresado,char* comando_a_comparar){
	return (strcmp(comando_ingresado,comando_a_comparar)==0);
}
bool es_conducta_valida(char* conducta_ingresada){
	return ((strcmp(conducta_ingresada,CONDUCTA_BUENA)==0)||(strcmp(conducta_ingresada,CONDUCTA_REGULAR)==0)||(strcmp(conducta_ingresada,CONDUCTA_MALA)==0));
}
bool es_fecha_valida(int fecha_ingresada){
	int mes=fecha_ingresada%100;
	return ((mes>=PRIMER_MES)&&(mes<=ULTIMO_MES));
}
/*
	*Precondicion: La funcion recibe los tres archivos ya abiertos correctamente.
	*Postcondicion: Devuelve el archivo perdonables con los alumnos que deben estar alli.
*/
void escribir_archivo_perdonables(FILE* perdonables,FILE* crucio,FILE* imperius){
	preso_t preso_crucio;
	preso_t preso_imperius;
	size_t leidos_crucio=fread(&preso_crucio,sizeof(preso_t),LEER_SECUENCIAL,crucio);
	size_t leidos_imperius=fread(&preso_imperius,sizeof(preso_t),LEER_SECUENCIAL,imperius);
	while((leidos_crucio>0)&&(leidos_imperius>0)){
		if(strcmp(preso_crucio.nombre,preso_imperius.nombre)==0){
			leidos_crucio=fread(&preso_crucio,sizeof(preso_t),LEER_SECUENCIAL,crucio);
			leidos_imperius=fread(&preso_imperius,sizeof(preso_t),LEER_SECUENCIAL,imperius);
		}else if (strcmp(preso_crucio.nombre,preso_imperius.nombre)<=0){
			fwrite(&preso_crucio,sizeof(preso_t),ESCRIBIR_SECUENCIAL,perdonables);
			leidos_crucio=fread(&preso_crucio,sizeof(preso_t),LEER_SECUENCIAL,crucio);
		}else{
			fwrite(&preso_imperius,sizeof(preso_t),ESCRIBIR_SECUENCIAL,perdonables);
			leidos_imperius=fread(&preso_imperius,sizeof(preso_t),LEER_SECUENCIAL,imperius);
		}
	}
	while(leidos_crucio>0){
		fwrite(&preso_crucio,sizeof(preso_t),ESCRIBIR_SECUENCIAL,perdonables);
		leidos_crucio=fread(&preso_crucio,sizeof(preso_t),LEER_SECUENCIAL,crucio);
	}
	while(leidos_imperius>0){
		fwrite(&preso_imperius,sizeof(preso_t),ESCRIBIR_SECUENCIAL,perdonables);
		leidos_imperius=fread(&preso_imperius,sizeof(preso_t),LEER_SECUENCIAL,imperius);
	}
}
int crear_archivo_perdonables(char* nombre_archivo){
	FILE* archivo_perdonables=fopen(nombre_archivo,ESCRITURA);
	if (archivo_perdonables==NULL){
		return FALLO;
	}
	FILE* archivo_crucio=fopen(ARCHIVO_CRUCIO,LECTURA);
	if (archivo_crucio==NULL){
		fclose(archivo_perdonables);
		return FALLO;
	}
	FILE* archivo_imperius=fopen(ARCHIVO_IMPERIUS,LECTURA);
	if (archivo_imperius==NULL){
		fclose(archivo_perdonables);
		fclose(archivo_crucio);
		return FALLO;
	}
	escribir_archivo_perdonables(archivo_perdonables,archivo_crucio,archivo_imperius);
	fclose(archivo_perdonables);
	fclose(archivo_crucio);
	fclose(archivo_imperius);
	return FUNCIONO;
}
/*
	*Precondicion: La funcion recibe la fecha de liberacion ingresada por el usuario y la que posee el preso.
	*Postcondicion: Devuelve si el preso cuenta con la fecha minima para salir.
*/
bool tiene_fecha_minima(char* fecha_ingresada,char* fecha_preso){
	return (strcmp(fecha_ingresada,fecha_preso)>=0);
}
/*
	*Precondicion: La funcion recibe la conducta ingresada por el usuario y la que posee el preso.
	*Postcondicion: Devuelve si el preso tiene la conducta minima para que el preso sea liberado.
*/
bool tiene_conducta_minima(char* conducta_ingresada,char conducta_preso){
	bool tiene=false;
	switch(conducta_preso){
		case BUENA:
			tiene=true;
		break;
		case REGULAR:
			if ((strcmp(conducta_ingresada,CONDUCTA_MALA)==0)||(strcmp(conducta_ingresada,CONDUCTA_REGULAR)==0)){
				tiene=true;
			}
		break;
		case MALA:
			if (strcmp(conducta_ingresada,CONDUCTA_MALA)==0){
				tiene=true;
			}
		break;
	}
	return tiene;
}
/*
	*Precondicion: La funcion recibe los dos archivos ya abiertos correctamente ,y la fecha y conducta que ingresa el usuario.
	*Postcondicion: Devuelve el archivo liberados con los alumnos que deben estar alli.
*/
void escribir_archivo_liberados(FILE* perdonables,FILE* liberados,char* fecha_ingresada,char* conducta_ingresada){
	preso_t preso_perdonable;
	size_t leidos_perdonable=fread(&preso_perdonable,sizeof(preso_t),LEER_SECUENCIAL,perdonables);
	while(leidos_perdonable>0){
		if(tiene_fecha_minima(fecha_ingresada,preso_perdonable.fecha)&&tiene_conducta_minima(conducta_ingresada,preso_perdonable.conducta)){
			fprintf(liberados,"%s\n",preso_perdonable.nombre);
		}
		leidos_perdonable=fread(&preso_perdonable,sizeof(preso_t),LEER_SECUENCIAL,perdonables);
	}
}
/*
	*Precondicion: La funcion recibe la fecha que ingresa el usuario para armar el nombre del archivo liberados que se desea.
	*Postcondicion: Devuelve el nombre con la forma correcta.
*/
void generar_nombre_archivo_liberados(char* nombre_archivos_liberados,char* fecha_ingresada){
	strcpy(nombre_archivos_liberados,PREFIJO_ARCHIVO_LIBERADOS);
	strcat(nombre_archivos_liberados,fecha_ingresada);
	strcat(nombre_archivos_liberados,EXTENSION_ARCHIVO_TEXTO);
}
int crear_archivo_liberados(char* nombre_archivo,char* fecha_ingresada,char* conducta_ingresada){
	FILE* archivo_perdonables=fopen(nombre_archivo,LECTURA);
	if(archivo_perdonables==NULL){
		return FALLO;
	}
	char nombre_archivos_liberados[MAX_NOMBRE];
	generar_nombre_archivo_liberados(nombre_archivos_liberados,fecha_ingresada);
	FILE* archivo_liberados=fopen(nombre_archivos_liberados,ESCRITURA);
	if(archivo_liberados==NULL){
		fclose(archivo_perdonables);
		return FALLO;
	}
	escribir_archivo_liberados(archivo_perdonables,archivo_liberados,fecha_ingresada,conducta_ingresada);
	fclose(archivo_perdonables);
	fclose(archivo_liberados);
	return FUNCIONO;
}
bool existe_el_archivo(char* fecha_ingresada){
	bool existe=true;
	char nombre_archivos_liberados[MAX_NOMBRE];
	generar_nombre_archivo_liberados(nombre_archivos_liberados,fecha_ingresada);
	FILE* archivo_liberados=fopen(nombre_archivos_liberados,LECTURA);
	if(archivo_liberados==NULL){
		existe=false;
	}
	return existe;
}
void imprimir_funciono_comando(){
	printf("El comando funciono correctamente.\n");
}
void imprimir_no_funciono_comando(){
	printf("Hubo algun error al abrir los archivos o intento abrir un archivo que no existe.\n");
}
/*
	*Precondicion: La funcion recibe los tres archivos ya abiertos correctamente.
	*Postcondicion: Devuelve el archivo crucio_actualizado o imperius_actualizado con los alumnos que deben estar alli.
*/
void escribir_archivo_actualizado(FILE* liberados,FILE* maleficio,FILE* archivo_actualizado){
	preso_t preso_maleficio;
	preso_t preso_a_liberar;
	size_t leidos_maleficio=fread(&preso_maleficio,sizeof(preso_t),LEER_SECUENCIAL,maleficio);
	int leido_liberado=fscanf(liberados,"%[^\n]\n",preso_a_liberar.nombre);
	while ((leidos_maleficio>0)&&(leido_liberado>0)){
		if (strcmp(preso_maleficio.nombre,preso_a_liberar.nombre)==0){
			leidos_maleficio=fread(&preso_maleficio,sizeof(preso_t),LEER_SECUENCIAL,maleficio);
			leido_liberado=fscanf(liberados,"%[^\n]\n",preso_a_liberar.nombre);
		}else if(strcmp(preso_maleficio.nombre,preso_a_liberar.nombre)>0){
			leido_liberado=fscanf(liberados,"%[^\n]\n",preso_a_liberar.nombre);
		}else{
			fwrite(&preso_maleficio,sizeof(preso_t),ESCRIBIR_SECUENCIAL,archivo_actualizado);
			leidos_maleficio=fread(&preso_maleficio,sizeof(preso_t),LEER_SECUENCIAL,maleficio);
		}
	}
	while(leidos_maleficio>0){
		fwrite(&preso_maleficio,sizeof(preso_t),ESCRIBIR_SECUENCIAL,archivo_actualizado);
		leidos_maleficio=fread(&preso_maleficio,sizeof(preso_t),LEER_SECUENCIAL,maleficio);
	}
}
int actualizacion_archivo_crucio(char* fecha_ingresada){
	char nombre_archivos_liberados[MAX_NOMBRE];
	generar_nombre_archivo_liberados(nombre_archivos_liberados,fecha_ingresada);
	FILE* archivo_liberados=fopen(nombre_archivos_liberados,LECTURA);
	if(archivo_liberados==NULL){
		return FALLO;
	}
	FILE* archivo_crucio=fopen(ARCHIVO_CRUCIO,LECTURA);
	if (archivo_crucio==NULL){
		fclose(archivo_liberados);
		return FALLO;
	}
	FILE* archivo_crucio_actual=fopen(ARCHIVO_CRUCIO_ACTUALIZADO,ESCRITURA);
	if (archivo_crucio_actual==NULL){
		fclose(archivo_liberados);
		fclose(archivo_crucio);
		return FALLO;
	}
	escribir_archivo_actualizado(archivo_liberados,archivo_crucio,archivo_crucio_actual);
	fclose(archivo_liberados);
	fclose(archivo_crucio);
	fclose(archivo_crucio_actual);
	remove(ARCHIVO_CRUCIO);
	rename(ARCHIVO_CRUCIO_ACTUALIZADO,ARCHIVO_CRUCIO);
	return FUNCIONO;
}

int actualizacion_archivo_imperius(char* fecha_ingresada){
	char nombre_archivos_liberados[MAX_NOMBRE];
	generar_nombre_archivo_liberados(nombre_archivos_liberados,fecha_ingresada);
	FILE* archivo_liberados=fopen(nombre_archivos_liberados,LECTURA);
	if(archivo_liberados==NULL){
		return FALLO;
	}
	FILE* archivo_imperius=fopen(ARCHIVO_IMPERIUS,LECTURA);
	if (archivo_imperius==NULL){
		fclose(archivo_liberados);
		return FALLO;
	}
	FILE* archivo_imperius_actual=fopen(ARCHIVO_IMPERIUS_ACTUALIZADO,ESCRITURA);
	if (archivo_imperius_actual==NULL){
		fclose(archivo_liberados);
		fclose(archivo_imperius);
		return FALLO;
	}
	escribir_archivo_actualizado(archivo_liberados,archivo_imperius,archivo_imperius_actual);
	fclose(archivo_liberados);
	fclose(archivo_imperius);
	fclose(archivo_imperius_actual);
	remove(ARCHIVO_IMPERIUS);
	rename(ARCHIVO_IMPERIUS_ACTUALIZADO,ARCHIVO_IMPERIUS);
	return FUNCIONO;

}
void mostrar_liberados(char* fecha_ingresada){
	int contador_liberados=0;
	preso_t preso_a_liberar;
	char nombre_archivos_liberados[MAX_NOMBRE];
	generar_nombre_archivo_liberados(nombre_archivos_liberados,fecha_ingresada);
	FILE* archivo_liberados=fopen(nombre_archivos_liberados,LECTURA);
	if(archivo_liberados==NULL){
		imprimir_no_funciono_comando();
		return;
	}	
	int leido_liberado=fscanf(archivo_liberados,"%[^\n]\n",preso_a_liberar.nombre);
	while (leido_liberado>0){
		contador_liberados++;
		if (contador_liberados==HAY_LIBERADOS){
			printf("Los prisioneros a liberar son:\n");
		}
		printf("-%s\n",preso_a_liberar.nombre);
		leido_liberado=fscanf(archivo_liberados,"%[^\n]\n",preso_a_liberar.nombre);
	}
	if(contador_liberados==NO_HAY_LIBERADOS){
		printf("No hay prisioneros para liberar\n");
	}
}
void imprimir_ayuda(){
	printf("\t\t\t\t\t\tAyuda\n\n");
	printf("El programa funciona con los siguientes comandos, estos se ingresan en la terminal de la siguiente forma:\n");
	printf("-Usted debera ingresar ./azkaban y luego escribir los comandos que desee utilizar.\n\n");
	printf("Los comandos son: \n\n");
	printf("-Perdonables:Crea un archivo con los datos de los presos a perdonar.Para llamar a este comando debera escribir perdonables\n");
	printf("y el nombre que quiera para el archivo con la extension .dat al final.\n\n");
	printf("-Liberar:Crea un archivo con los presos que deben ser liberados segun la fecha y la conducta que usted ingrese.\n");
	printf("Para llamar a este comando debera escribir liberar, el nombre que le haya dado al archivo perdonables con la extension .dat\n");
	printf("y luego la fecha de los presos que desea liberar ,con formato aaaamm, y la conducta minima que deben tener los presos.Esta conducta\n");
	printf("puede ser buena ('B'), regular('R') o mala('M').\n");
	printf("-Actualizar:Actualiza las listas de los presos quitando de ellas a aquellos presos que usted libero.\n");
	printf("Para llamar a este comando debera escribir actualizar y la fecha (formato aaaamm) del archivo que usted desea actualizar.\n\n");
	printf("-Mostrar liberados:Le va a mostrar los nombres de los prisioneros que van a ser liberados segun la fecha que usted introduzca.\n");
	printf("Para llamar a este comando debera escribir mostrar_liberados y la fecha (formato aaaamm) del archivo que usted desea ver.\n\n");
	printf("-Ayuda:Si quiere volver a ver como funciona el programa.\n");
	printf("Para llamar a este comando debera escribir ayuda.\n");
}
void imprimir_ingreso_mal_comandos(){
	printf("Usted ingreso incorrectamente los comandos.\n");
	printf("A continuacion, le muestro la ayuda para que vea como ingresar los comandos correctamente:\n\n");
	imprimir_ayuda();
}
void imprimir_mensaje_no_comandos(){
	printf("Usted no ingreso ningun comando.\n");
	printf("A continuacion, le muestro la ayuda para que vea como funciona el programa y sus comandos:\n\n");
}