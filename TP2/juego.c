#include "laberinto.h"
#include "copa.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define IZQUIERDA 'a'
#define ARRIBA 'w'
#define ABAJO 's'
#define DERECHA 'd'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define ESFINGE 'F'
#define GANO_JUGADOR 1
#define SIGUE_JUEGO 0
/*
 * Precondicion: Inicia el juego
 * Postcondicion: El procedimiento imprime la bienvenida para el usuario 
 */
void imprimir_bienvenida(){
	printf("\t\t\t\tBienvenido al laberinto\n\n");
	printf("-En este juego, vas a estar controlando a tu jugador que esta reprensentado por la letra J.\n");
	printf("-Tu objetivo es encontar la copa(C),que se encuentra oculta, antes que tu rival(G).\n");
	printf("-Vas a ir moviendo tu personaje por el laberinto, cuidalo de que no se choque con las paredes(#).\n");
	printf("-Pensa bien tus movimientos, ya que cada vez que te muevas vas a perder 3 puntos de vida.\n");
	printf("-No te preocupes, tambien vas a poder recuperar 15 puntos de vida tomando pociones(P).\n");
	printf("-En el camino podes encontrarte con muchas criaturas que van a atacarte y sacarte vida: escreguto(E),acromantula(A) y boggart(B).\n");
	printf("-El escreguto causa 20 puntos de daño,la acromantula 10 y el boggart 15.\n");
	printf("-Pero tambien vas a encontar ayudas como: esfinge(F) para poder ver la copa, riddikulus(R) para que el boggart no te dañe\n");
	printf("e impedimenta(I) para que no te dañe el escreguto.\n");
	printf("-Tambien vas a poder ver la copa cuando tengas 15 o menos puntos de vida.\n\n");
	printf("\t\t\t\tMucha suerte!\n\n");
}
/*
 * Precondicion: Inicia el juego. 
 * Postcondicion: Devuelve por referencia la direccion a la cual quiere moverse el usuario.
 */
void pedir_direccion(char *direccion){
	printf("Indique hacia donde quiere mover a su jugador w (Arriba), s (Abajo), a (Izquierda), d (Derecha) y presiona enter: ");
	scanf(" %c", direccion);
}
/*
 * Precondicion: Se debe haber movido el jugador una vez por lo menos.
 * Postcondicion: El procedimiento imprime las referencias que representan a cada objeto para que el usuario pueda saber que significa cada caracter durante el juego.
 */
void imprimir_referencias(){
	printf("Referencias: \n");
	printf("-Impedimenta: I (para que no te dañe el escreguto)\n");
	printf("-Pociones: P (suma 15 de vida)\n");
	printf("-Riddikulus: R (para que el boggart no te dañe) \n");
	printf("-Esfinge: F (para poder ver la copa) \n");
	printf("-Escreguto: E (causa 20 de daño)\n");
	printf("-Acromantula: A (causa 10 de daño)\n");
	printf("-Boggart: B (causa 15 de daño)\n");
	printf("-Jugador: J\n");
	printf("-Rival: G\n");
	printf("-Copa: C\n\n");
}
/*
 * Precondicion: Inicia el juego.
 * Postcondicion: El procedimiento imprime la cantidad de vida que tiene el jugador.
 */
void imprimir_nivel_de_vida(juego_t juego){
	printf("Tu nivel de vida es: %i\n\n\n", juego.jugador.vida);
}
/*
 * Precondicion: El jugador se encuentra en la misma posicion que un obstaculo o se quiere saber si tiene la esfinge para mostrar la copa.
 * Postcondicion: Verifica si el jugador posee la ayuda que se desea buscar. 
 */
bool jugador_tiene_en_mochila(ayuda_t ayudas[TOTAL_AYUDAS],int tope_ayudas,char buscado){
	bool tiene=false;
	for (int i = 0; i < tope_ayudas; ++i){
		if(ayudas[i].codigo==buscado){
			tiene=true;
		}
	}
	return tiene;
}

/*
 * Precondicion: No hay.
 * Postcondicion: Le muestra al usuario el contenido del vector ayudas del jugador. 
 */
void imprimir_contenido_mochila(juego_t juego){
	if(juego.jugador.tope_ayudas==0){
		printf("No tenes elementos en tu mochila\n\n");
	}else{
		printf("Tenes en la mochila:\n");
		if (jugador_tiene_en_mochila(juego.jugador.ayudas,juego.jugador.tope_ayudas,ESFINGE)){
			printf("*Esfinge\n");
		}
		if (jugador_tiene_en_mochila(juego.jugador.ayudas,juego.jugador.tope_ayudas,IMPEDIMENTA)){
			printf("*Impedimenta\n");
		}
		if (jugador_tiene_en_mochila(juego.jugador.ayudas,juego.jugador.tope_ayudas,RIDDIKULUS)){
			printf("*Riddikulus\n");
		}
	}
}
int main(){
	juego_t juego;
	char direccion;
	char laberinto[TAMANIO][TAMANIO];
	srand((unsigned int)time(NULL));
	inicializar_laberinto(&juego);
	system("clear");
	imprimir_bienvenida();
	imprimir_contenido_mochila(juego);
	imprimir_nivel_de_vida(juego);
	actualizar_laberinto(juego, laberinto);
	mostrar_laberinto(laberinto);
	while (estado_juego(juego)==SIGUE_JUEGO){
		pedir_direccion(&direccion);
		while(!es_movimiento_valido(&juego, direccion)){
			system("clear");
			imprimir_referencias();
			imprimir_contenido_mochila(juego);
			imprimir_nivel_de_vida(juego);
			mostrar_laberinto(laberinto);
			if ((direccion!=IZQUIERDA)&&(direccion!=DERECHA)&&(direccion!=ABAJO)&&(direccion!=ARRIBA)){
				printf("Ingreso un caracter no valido\n");
			}else{
				printf("Movimiento invalido, todavia no descubrimos como atravesar paredes.\n");
			}
			pedir_direccion(&direccion);
		}
		mover_jugador(&juego.jugador, direccion);
		if(estado_juego(juego)==SIGUE_JUEGO){
			mover_rival(&juego);
		}
		system("clear");
		imprimir_referencias();
		actualizar_juego(&juego);
		actualizar_laberinto(juego, laberinto);
		imprimir_contenido_mochila(juego);
		imprimir_nivel_de_vida(juego);
		mostrar_laberinto(laberinto);
	}
	if (estado_juego(juego)==GANO_JUGADOR){
		printf("Ganaste :)\n");
	}else{
		printf("Perdiste :( Suerte la proxima.\n");
	}
}