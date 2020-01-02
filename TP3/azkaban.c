#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_azkaban.h"
#define POSICION_COMANDOS 1
#define POSICION_FECHA_LIBERAR 3
#define POSICION_FECHA 2
#define POSICION_CONDUCTA 4
#define POSICION_NOMBRE_ARCHIVO 2
#define CANT_MINIMA_ARGS 1
#define CANT_ARGS_COMANDO_AYUDA 2
#define CANT_ARGS_COMANDO_PERDONABLES 3
#define CANT_ARGS_COMANDO_LIBERAR 5
#define CANT_ARGS_COMANDO_ACTUALIZAR 3
#define CANT_ARGS_COMANDO_MOSTRAR_LIBERADOS 3
#define FUNCIONO 0

int main(int argc,char *argv[]){
	if (argc>CANT_MINIMA_ARGS){
		if(es_comando_valido(argv[POSICION_COMANDOS])){
			if(es_comando(argv[POSICION_COMANDOS],COMANDO_AYUDA)){
				system("clear");
				if (argc==CANT_ARGS_COMANDO_AYUDA){
					imprimir_ayuda();
				}else{
					imprimir_ingreso_mal_comandos();
				}
			}else if(es_comando(argv[POSICION_COMANDOS],COMANDO_PERDONABLES)){
				system("clear");
				int perdonables;
				if (argc==CANT_ARGS_COMANDO_PERDONABLES){
					perdonables=crear_archivo_perdonables(argv[POSICION_NOMBRE_ARCHIVO]);
					if (perdonables==FUNCIONO){
						imprimir_funciono_comando();
					}else{
						imprimir_no_funciono_comando();
					}
				}else{
					imprimir_ingreso_mal_comandos();
				}
			}else if(es_comando(argv[POSICION_COMANDOS],COMANDO_LIBERAR)){
				system("clear");
				int liberar;
				if (argc==CANT_ARGS_COMANDO_LIBERAR){
					int fecha_ingresada=atoi(argv[POSICION_FECHA_LIBERAR]);
					if(es_fecha_valida(fecha_ingresada)&&es_conducta_valida(argv[POSICION_CONDUCTA])){
						if(!existe_el_archivo(argv[POSICION_FECHA_LIBERAR])){
							liberar=crear_archivo_liberados(argv[POSICION_NOMBRE_ARCHIVO],argv[POSICION_FECHA_LIBERAR],argv[POSICION_CONDUCTA]);
							if (liberar==FUNCIONO){
								imprimir_funciono_comando();
							}else{
								imprimir_no_funciono_comando();
							}
						}else{
							printf("Error. El archivo ya existe y no se puede sobreescribir.\n");
						}
					}else{
						imprimir_ingreso_mal_comandos();
					}
				}else{
					imprimir_ingreso_mal_comandos();
				}
			}else if(es_comando(argv[POSICION_COMANDOS],COMANDO_ACTUALIZAR)){
				system("clear");
				int actualizar_crucio;
				int actualizar_imperius;
				if (argc==CANT_ARGS_COMANDO_ACTUALIZAR){
					int fecha_ingresada=atoi(argv[POSICION_FECHA]);
					if(es_fecha_valida(fecha_ingresada)){
						actualizar_crucio=actualizacion_archivo_crucio(argv[POSICION_FECHA]);
						actualizar_imperius=actualizacion_archivo_imperius(argv[POSICION_FECHA]);
						if (actualizar_crucio==FUNCIONO&&actualizar_imperius==FUNCIONO){
							imprimir_funciono_comando();
						}else{
							imprimir_no_funciono_comando();
						}
					}else{
						imprimir_ingreso_mal_comandos();
					}
				}else{
					imprimir_ingreso_mal_comandos();
				}
			}else if(es_comando(argv[POSICION_COMANDOS],COMANDO_MOSTRAR_LIBERADOS)){
				system("clear");
				if (argc==CANT_ARGS_COMANDO_MOSTRAR_LIBERADOS){
					int fecha_ingresada=atoi(argv[POSICION_FECHA]);
					if(es_fecha_valida(fecha_ingresada)){
						mostrar_liberados(argv[POSICION_FECHA]);
					}else{
						imprimir_ingreso_mal_comandos();
					}
				}else{
					imprimir_ingreso_mal_comandos();
				}
			}
		}else{
			system("clear");
			imprimir_ingreso_mal_comandos();
		}
	}else{
		system("clear");
		imprimir_mensaje_no_comandos();
		imprimir_ayuda();
	}
}