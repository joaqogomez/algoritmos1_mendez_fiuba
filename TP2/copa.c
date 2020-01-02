#include "laberinto.h"
#include "copa.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define IZQUIERDA 'a'
#define ARRIBA 'w'
#define ABAJO 's'
#define DERECHA 'd'
#define POCIONES 'P'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define ESFINGE 'F'
#define ESCREGUTO 'E'
#define ACROMANTULA 'A'
#define BOGGART 'B'
const char JUGADOR='J',RIVAL='G',COPA='C';
const int MOVIMIENTO=1,VIDA_MAXIMA=50,VIDA_POCION=15,DISTANCIA_MINIMA=10,MINIMO_VER_COPA=15;
const int DANIO_ESCREGUTO=20,DANIO_ACROMANTULA=10,DANIO_BOGGART=15,DANIO_POR_MOVIMIENTO=3;
const int GANO_JUGADOR=1, PERDIO_JUGADOR=-1, SIGUE_JUEGO=0;
/*
 * Precondicion: Recibe la posicion aleatoria de los objetos previamente inicializados.
 * Postcondicion: Se encarga de verificar si los objetos estan posicionados en un lugar correcto (es decir un espacio vacio) y de ser asi,
 * pone al elemento en esa posicion de un laberinto secundario, que solo se utiliza para verificar posiciones.
 */
bool es_posicion_valida(char laberinto[TAMANIO][TAMANIO],coordenada_t posicion_a_verificar,char codigo){
	if (laberinto[posicion_a_verificar.fil][posicion_a_verificar.col]==VACIO){
		laberinto[posicion_a_verificar.fil][posicion_a_verificar.col]=codigo;
		return true;
	}else{
		return false;
	}
}
/*
 * Precondicion: La funcion recibe el laberinto original(el que solo tiene las paredes) y un laberinto al que le queremos poner paredes.
 * Postcondicion: Devuelve las paredes cargadas en el laberinto secundario.
 */
void inicializar_laberinto_secundario(char laberinto[TAMANIO][TAMANIO],char laberinto_secundario[TAMANIO][TAMANIO]){
	for (int i = 0; i < TAMANIO; ++i){
		for (int j = 0; j < TAMANIO; ++j){
			laberinto_secundario[i][j]=laberinto[i][j];
		}
	}
}
/*
 * Precondicion: Inicio del juego.
 * Postcondicion: Devuelve los valores inicializados correctamente. 
 */
void inicializar_copa(copa_t *copa, char letra){
	(copa->codigo)=letra;
	(copa->posicion)=posicion_aleatoria();
}
/*
 * Precondicion: Inicio del juego.
 * Postcondicion: Inicializa los valores de un obstaculo particular, devuelve los valores inicializados correctamente. 
 */
void inicializar_obstaculo(obstaculo_t obstaculos[TOTAL_OBSTACULOS],int tope_obstaculos,char letra, int cantidad_de_danio){
	(obstaculos[(tope_obstaculos)].codigo)=letra;
	(obstaculos[(tope_obstaculos)].danio)=cantidad_de_danio;
	(obstaculos[(tope_obstaculos)].posicion)=posicion_aleatoria();
}
/*
 * Precondicion: Inicio del juego.
 * Postcondicion: Llama a la funcion que inicializa cada obstaculo, devuelve los valores inicializados correctamente. 
 */
void inicializar_obstaculos(juego_t* juego,char laberinto_secundario[TAMANIO][TAMANIO]){
	(juego->tope_obstaculos)=0;
	do{
	inicializar_obstaculo(juego->obstaculos, juego->tope_obstaculos, ESCREGUTO, DANIO_ESCREGUTO);
	}while(!es_posicion_valida(laberinto_secundario,juego->obstaculos[(juego->tope_obstaculos)].posicion,juego->obstaculos[(juego->tope_obstaculos)].codigo));
	(juego->tope_obstaculos)++;
	do{
	inicializar_obstaculo(juego->obstaculos, juego->tope_obstaculos, ACROMANTULA, DANIO_ACROMANTULA);
	}while(!es_posicion_valida(laberinto_secundario,juego->obstaculos[(juego->tope_obstaculos)].posicion,juego->obstaculos[(juego->tope_obstaculos)].codigo));
	(juego->tope_obstaculos)++;
	do{
	inicializar_obstaculo(juego->obstaculos, juego->tope_obstaculos, BOGGART, DANIO_BOGGART);
	}while(!es_posicion_valida(laberinto_secundario,juego->obstaculos[(juego->tope_obstaculos)].posicion,juego->obstaculos[(juego->tope_obstaculos)].codigo));
	(juego->tope_obstaculos)++;
}
/*
 * Precondicion: Inicio del juego.
 * Postcondicion: Inicializa los valores de una ayuda particular, devuelve los valores inicializados correctamente. 
 */
void inicializar_ayuda(ayuda_t ayudas[TOTAL_AYUDAS],int tope_ayudas,char letra, int vida_que_recupera){
	(ayudas[(tope_ayudas)].codigo)=letra;
	(ayudas[(tope_ayudas)].vida_a_recuperar)=vida_que_recupera;
	(ayudas[(tope_ayudas)].posicion)=posicion_aleatoria();
}
/*
 * Precondicion: Inicio del juego.
 * Postcondicion: Llama a la funcion que inicializa cada ayuda, devuelve los valores inicializados correctamente. 
 */
void inicializar_ayudas(juego_t* juego,char laberinto_secundario[TAMANIO][TAMANIO]){
	(juego->tope_ayudas)=0;
	do{
		inicializar_ayuda(juego->ayudas, juego->tope_ayudas, IMPEDIMENTA, 0);
	}while(!es_posicion_valida(laberinto_secundario,juego->ayudas[(juego->tope_ayudas)].posicion,juego->ayudas[(juego->tope_ayudas)].codigo));
	(juego->tope_ayudas)++;
	do{
		inicializar_ayuda(juego->ayudas, juego->tope_ayudas, RIDDIKULUS, 0);
	}while(!es_posicion_valida(laberinto_secundario,juego->ayudas[(juego->tope_ayudas)].posicion,juego->ayudas[(juego->tope_ayudas)].codigo));
	(juego->tope_ayudas)++;
	do{
		inicializar_ayuda(juego->ayudas, juego->tope_ayudas, POCIONES, VIDA_POCION);
	}while(!es_posicion_valida(laberinto_secundario,juego->ayudas[(juego->tope_ayudas)].posicion,juego->ayudas[(juego->tope_ayudas)].codigo));
	(juego->tope_ayudas)++;
	do{
		inicializar_ayuda(juego->ayudas, juego->tope_ayudas, POCIONES, VIDA_POCION);
	}while(!es_posicion_valida(laberinto_secundario,juego->ayudas[(juego->tope_ayudas)].posicion,juego->ayudas[(juego->tope_ayudas)].codigo));
	(juego->tope_ayudas)++;
	do{
		inicializar_ayuda(juego->ayudas, juego->tope_ayudas, POCIONES, VIDA_POCION);
	}while(!es_posicion_valida(laberinto_secundario,juego->ayudas[(juego->tope_ayudas)].posicion,juego->ayudas[(juego->tope_ayudas)].codigo));
	(juego->tope_ayudas)++;
	do{
		inicializar_ayuda(juego->ayudas, juego->tope_ayudas, ESFINGE, 0);
	}while(!es_posicion_valida(laberinto_secundario,juego->ayudas[(juego->tope_ayudas)].posicion,juego->ayudas[(juego->tope_ayudas)].codigo));
	(juego->tope_ayudas)++;
}

/*
 * Precondicion: Inicio del juego.
 * Postcondicion: Devuelve los valores inicializados correctamente. 
 */
void inicializar_rival(rival_t *rival,char letra, int pasos){
	(rival->codigo)=letra;
	(rival->posicion)=posicion_aleatoria();
	(rival->cantidad_pasos)=0;
}
/*
 * Precondicion: Inicio del juego.
 * Postcondicion: Devuelve los valores inicializados correctamente. 
 */
void inicializar_jugador(jugador_t *jugador,char letra, int vida_inicial, int tope){
	(jugador->codigo)=letra;
	(jugador->vida)=vida_inicial;
	(jugador->posicion)=posicion_aleatoria();
	(jugador->tope_ayudas)=tope;
}
/*
 * Precondicion: Recibe la posicion del jugador o del rival y la de la copa.
 * Postcondicion: Devuelve la distancia a la cual se encuentran los dos elementos. 
 */
int calcular_distancia(coordenada_t posicion_participante,coordenada_t posicion_copa){
	int suma_filas=0;
	int suma_columnas=0;
	suma_filas=abs(posicion_participante.fil-posicion_copa.fil);
	suma_columnas=abs(posicion_participante.col-posicion_copa.col);
	return (suma_columnas+suma_filas);
}
/*
 * Precondicion: Recibe la posicion del jugador o del rival y la de la copa.
 * Postcondicion: Devuelve si estos elementos se encuentran o no a distancia manhattan. 
 */
bool esta_distancia_manhattan(coordenada_t posicion_participante,coordenada_t posicion_copa){
	return (calcular_distancia(posicion_participante, posicion_copa)>DISTANCIA_MINIMA);
}
/*
 * Inicializará todas las estructuras con los valores correspondientes,
 * creará el laberinto, posicionará todos los elementos, etc.
 */
void inicializar_laberinto(juego_t* juego){
	char laberinto_secundario[TAMANIO][TAMANIO];
	inicializar_paredes_laberinto(juego->laberinto_original);
	inicializar_laberinto_secundario(juego->laberinto_original,laberinto_secundario);
	do{
		inicializar_copa(&juego->copa,COPA);
	}while(!es_posicion_valida(laberinto_secundario,juego->copa.posicion,juego->copa.codigo));
	inicializar_obstaculos(juego,laberinto_secundario);
	inicializar_ayudas(juego,laberinto_secundario);
	do{
		inicializar_rival(&juego->rival, RIVAL, 0);
	}while((!es_posicion_valida(laberinto_secundario,juego->rival.posicion,juego->rival.codigo))||(!esta_distancia_manhattan(juego->rival.posicion,juego->copa.posicion)));
	do{
		inicializar_jugador(&juego->jugador, JUGADOR, VIDA_MAXIMA, 0);
	}while((!es_posicion_valida(laberinto_secundario,juego->jugador.posicion,juego->jugador.codigo))||(!esta_distancia_manhattan(juego->jugador.posicion,juego->copa.posicion)));
}
/*
 * Precondicion: Recibe la posicion del jugador o del rival a la cual se quieren mover.
 * Postcondicion: Verifica que esa posicion a la que se quiere mover este dentro del tablero. 
 */
bool esta_dentro_del_tablero(int fila,int columna){
	return (((fila>=0)&&(fila<TAMANIO))&&((columna>=0)&&(columna<TAMANIO)));
}
/*
 * Determinará si el caracter ingresado es válido, esto es, es el caracter ‘a’ o 
 * ‘s’ o ‘d’ o ‘w’ y además el jugador puede moverse en esa dirección, o sea, 
 * hay pasillo.
 */
bool es_movimiento_valido(juego_t* juego, char tecla){
	coordenada_t posicion_a_verificar;
	posicion_a_verificar.fil=(juego->jugador.posicion.fil);
	posicion_a_verificar.col=(juego->jugador.posicion.col);
	switch(tecla){
        case ARRIBA:
        (posicion_a_verificar.fil)-=MOVIMIENTO;
        break;
        case ABAJO:
        (posicion_a_verificar.fil)+=MOVIMIENTO;
        break;
        case IZQUIERDA:
        (posicion_a_verificar.col)-=MOVIMIENTO;
        break;
        case DERECHA:
        (posicion_a_verificar.col)+=MOVIMIENTO;
        break;
        default:
        return false;
    }
    return ((juego->laberinto_original[posicion_a_verificar.fil][posicion_a_verificar.col]!=PARED)&&(esta_dentro_del_tablero(posicion_a_verificar.fil,posicion_a_verificar.col)));
}
/*
 * Moverá el jugador hacia la dirección especificada.
 * Dicho movimiento es válido.
 */
void mover_jugador(jugador_t* jugador, char direccion){
	switch(direccion){
        case ARRIBA:
        (jugador->posicion.fil)-=MOVIMIENTO;
        break;
        case ABAJO:
        (jugador->posicion.fil)+=MOVIMIENTO;
        break;
        case IZQUIERDA:
        (jugador->posicion.col)-=MOVIMIENTO;
        break;
        case DERECHA:
        (jugador->posicion.col)+=MOVIMIENTO;
        break;
    }
}
/*
 * Precondicion: Recibe la posicion del rival a la cual se quieren mover.
 * Postcondicion: Verifica que esa posicion a la que se quiere mover no sea una pared. 
 */
bool es_movimiento_valido_rival(juego_t *juego, char tecla){
	coordenada_t posicion_a_verificar;
	posicion_a_verificar.fil=(juego->rival.posicion.fil);
	posicion_a_verificar.col=(juego->rival.posicion.col);
	switch(tecla){
        case ARRIBA:
        (posicion_a_verificar.fil)-=MOVIMIENTO;
        break;
        case ABAJO:
        (posicion_a_verificar.fil)+=MOVIMIENTO;
        break;
        case IZQUIERDA:
        (posicion_a_verificar.col)-=MOVIMIENTO;
        break;
        case DERECHA:
        (posicion_a_verificar.col)+=MOVIMIENTO;
        break;
    }
    return (juego->laberinto_original[posicion_a_verificar.fil][posicion_a_verificar.col]!=PARED);
}
/*
 * Moverá el rival a la próxima posición.
 */
void mover_rival(juego_t* juego){
	bool se_movio=false;
	while(!se_movio){
		if(!se_movio){
			if((juego->rival.cantidad_pasos>=0)&&(juego->rival.cantidad_pasos<4)){
				if((es_movimiento_valido_rival(juego,DERECHA))&&(esta_dentro_del_tablero(juego->rival.posicion.fil,juego->rival.posicion.col+MOVIMIENTO))){
					(juego->rival.posicion.col)+=MOVIMIENTO;
					se_movio=true;
				}
				(juego->rival.cantidad_pasos)++;
			}
		}
		if(!se_movio){
			if((juego->rival.cantidad_pasos>=4)&&(juego->rival.cantidad_pasos<8)){
				if((es_movimiento_valido_rival(juego,ABAJO))&&(esta_dentro_del_tablero(juego->rival.posicion.fil+MOVIMIENTO,juego->rival.posicion.col))){
					(juego->rival.posicion.fil)+=MOVIMIENTO;
					se_movio=true;
				}
				(juego->rival.cantidad_pasos)++;
			}
		}
		if(!se_movio){
			if((juego->rival.cantidad_pasos>=8)&&(juego->rival.cantidad_pasos<12)){
				if((es_movimiento_valido_rival(juego,IZQUIERDA))&&(esta_dentro_del_tablero(juego->rival.posicion.fil,juego->rival.posicion.col-MOVIMIENTO))){
					(juego->rival.posicion.col)-=MOVIMIENTO;
					se_movio=true;
				}
				(juego->rival.cantidad_pasos)++;
			}
		}
		if(!se_movio){
			if((juego->rival.cantidad_pasos>=12)&&(juego->rival.cantidad_pasos<16)){
				if((es_movimiento_valido_rival(juego,ARRIBA))&&(esta_dentro_del_tablero(juego->rival.posicion.fil-MOVIMIENTO,juego->rival.posicion.col))){
					(juego->rival.posicion.fil)-=MOVIMIENTO;
					se_movio=true;
				}
				(juego->rival.cantidad_pasos)++;
			}
		}
		if(juego->rival.cantidad_pasos==16){
			juego->rival.cantidad_pasos=0;
		}
	}
}
/*
 * Precondicion: Recibe el juego y toma la posicion del jugador y ve las posiciones de las ayudas.
 * Postcondicion: Verifica si el jugador se encuentra en la misma posicion que una ayuda, de ser asi, devuelve por referencia la posicion en el vector 
 * de ayudas de la ayuda que se encuentra en la misma posicion que el jugador. 
 */
bool jugador_piso_ayuda(juego_t* juego,int *posicion){
	bool piso=false;
	for (int i = 0; i < (juego->tope_ayudas); ++i){
		if((juego->ayudas[i].posicion.fil==juego->jugador.posicion.fil)&&(juego->ayudas[i].posicion.col==juego->jugador.posicion.col)){
			piso=true;
			(*posicion)=i;
		}
	}
	return piso;
}
/*
 * Precondicion: Recibe el juego y toma la posicion del jugador y ve las posiciones de los obstaculos.
 * Postcondicion: Verifica si el jugador se encuentra en la misma posicion que un obstaculo, de ser asi, devuelve por referencia la posicion en el vector 
 * de obstaculos del obstaculo que se encuentra en la misma posicion que el jugador. 
 */
bool jugador_piso_obstaculo(juego_t* juego,int *posicion){
	bool piso=false;
	for (int i = 0; i < (juego->tope_obstaculos); ++i){
		if((juego->obstaculos[i].posicion.fil==juego->jugador.posicion.fil)&&(juego->obstaculos[i].posicion.col==juego->jugador.posicion.col)){
			piso=true;
			(*posicion)=i;
		}
	}
	return piso;
}
/*
 * Precondicion: El jugador se encuentra en la misma posicion que una ayuda.
 * Postcondicion: Elimina del vector de ayudas la ayuda que esta en la misma posicion que el jugador. 
 */
void eliminar_del_vector_ayudas(ayuda_t ayudas[TOTAL_AYUDAS],int *tope_ayudas,int posicion_a_eliminar){
	for (int i = posicion_a_eliminar; i < (*tope_ayudas-1); ++i){
		ayudas[i]=ayudas[i+1];
	}
	(*tope_ayudas)--;
}
/*
 * Precondicion: El jugador se encuentra en la misma posicion que un obstaculo.
 * Postcondicion: Elimina del vector de obstaculos el obstaculo que esta en la misma posicion que el jugador. 
 */
void eliminar_del_vector_obstaculos(obstaculo_t obstaculos[TOTAL_OBSTACULOS],int *tope_obstaculos,int posicion_a_eliminar){
	for (int i = posicion_a_eliminar; i < (*tope_obstaculos-1); ++i){
		obstaculos[i]=obstaculos[i+1];
	}
	(*tope_obstaculos)--;
}
/*
 * Precondicion: El jugador se encuentra en la misma posicion que una ayuda.
 * Postcondicion: Agrega al vector de ayudas del jugador la ayuda que esta en la misma posicion que el jugador. 
 */
void agregar_mochila(ayuda_t ayudas_jugador[TOTAL_AYUDAS],int *tope_ayudas,ayuda_t ayuda_para_mochila){
	(ayudas_jugador[(*tope_ayudas)].codigo)=ayuda_para_mochila.codigo;
	(ayudas_jugador[(*tope_ayudas)].vida_a_recuperar)=ayuda_para_mochila.vida_a_recuperar;
	(*tope_ayudas)++;
}
/*
 * Precondicion: El jugador se encuentra en la misma posicion que un obstaculo o se quiere saber si tiene la esfinge para mostrar la copa.
 * Postcondicion: Verifica si el jugador posee la ayuda que se desea buscar. 
 */
bool jugador_tiene_ayuda(ayuda_t ayudas[TOTAL_AYUDAS],int tope_ayudas,char buscado){
	bool tiene=false;
	for (int i = 0; i < tope_ayudas; ++i){
		if(ayudas[i].codigo==buscado){
			tiene=true;
		}
	}
	return tiene;
}
/*
 * Actualizará el juego. Restará vida si el jugador está sobre un obstáculo 
 * o lo eliminará si cuenta con el hechizo, aprenderá hechizos y todo lo 
 * que pueda suceder luego de un turno.
 */
void actualizar_juego(juego_t* juego){
	int posicion=-1;
	(juego->jugador.vida)-=DANIO_POR_MOVIMIENTO;
	if((juego->jugador.vida)>0){
		if(jugador_piso_ayuda(juego,&posicion)){
			switch(juego->ayudas[(posicion)].codigo){
        		case POCIONES:
        		(juego->jugador.vida)+=juego->ayudas[(posicion)].vida_a_recuperar;
        		if ((juego->jugador.vida)>VIDA_MAXIMA){
        			(juego->jugador.vida)=VIDA_MAXIMA;
        		}
        		eliminar_del_vector_ayudas(juego->ayudas,&(juego->tope_ayudas),posicion);
        		break;
        		case IMPEDIMENTA:
        		case RIDDIKULUS:
        		case ESFINGE:
        		agregar_mochila(juego->jugador.ayudas,&(juego->jugador.tope_ayudas),juego->ayudas[(posicion)]);
        		eliminar_del_vector_ayudas(juego->ayudas,&(juego->tope_ayudas),posicion);
        		break;
    		}
		}else if(jugador_piso_obstaculo(juego,&posicion)){
			switch(juego->obstaculos[(posicion)].codigo){
        		case ESCREGUTO:
        		if(!jugador_tiene_ayuda(juego->jugador.ayudas,juego->jugador.tope_ayudas,IMPEDIMENTA)){
        			(juego->jugador.vida)-=DANIO_ESCREGUTO;
        		}
        		eliminar_del_vector_obstaculos(juego->obstaculos,&(juego->tope_obstaculos),posicion);
        		break;
        		case ACROMANTULA:
        		(juego->jugador.vida)-=DANIO_ACROMANTULA;
        		eliminar_del_vector_obstaculos(juego->obstaculos,&(juego->tope_obstaculos),posicion);
       	 		break;
        		case BOGGART:
        		if(!jugador_tiene_ayuda(juego->jugador.ayudas,juego->jugador.tope_ayudas,RIDDIKULUS)){
        			(juego->jugador.vida)-=DANIO_BOGGART;
        		}
        		eliminar_del_vector_obstaculos(juego->obstaculos,&(juego->tope_obstaculos),posicion);
        		break;
    		}
		}
	}
}
/*
 * Devolverá el estado del juego, 1 ganado, 0 en curso, -1 perdido.
 */
int estado_juego(juego_t juego){
	if(((juego.jugador.vida)<=0)||((juego.rival.posicion.fil==juego.copa.posicion.fil)&&(juego.rival.posicion.col==juego.copa.posicion.col))){
		return PERDIO_JUGADOR;
	}else if((juego.jugador.posicion.fil==juego.copa.posicion.fil)&&(juego.jugador.posicion.col==juego.copa.posicion.col)){
		return GANO_JUGADOR;
	}else{
		return SIGUE_JUEGO;
	}
}
/*
 * Devolverá una coordenada aleatoria dentro del rango TAMANIOxTAMANIO.
 * No valida que dicha coordenada coincida con un pasillo ni que exista 
 * otro objeto en esa posición.
 */
coordenada_t posicion_aleatoria(){
	coordenada_t posicion;
	(posicion.fil)=rand()%TAMANIO;
	(posicion.col)=rand()%TAMANIO;
	return posicion;
}
/*
 * Precondicion: Recibe el elemento a insertar en el laberinto que se le mostrara al usuario.
 * Postcondicion: Devuelve la matriz con los elementos en su lugar correspondiente. 
 */
void insertar_elemento(char laberinto[TAMANIO][TAMANIO],coordenada_t posicion,char letra){
	laberinto[posicion.fil][posicion.col]=letra;
}
/*
 * Actualizará la matriz mostrada al usuario, con los elementos presentes 
 * en el juego.
 */
void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]){
	inicializar_laberinto_secundario(juego.laberinto_original,laberinto);
	for (int i = 0; i < (juego.tope_obstaculos) ; ++i){
		insertar_elemento(laberinto,juego.obstaculos[i].posicion,juego.obstaculos[i].codigo);
	}
	for (int j = 0; j < (juego.tope_ayudas) ; ++j){
		insertar_elemento(laberinto,juego.ayudas[j].posicion,juego.ayudas[j].codigo);
	}
	if((jugador_tiene_ayuda(juego.jugador.ayudas,juego.jugador.tope_ayudas,ESFINGE))||(juego.jugador.vida<=MINIMO_VER_COPA)){
		insertar_elemento(laberinto,juego.copa.posicion,juego.copa.codigo);
	}
	insertar_elemento(laberinto,juego.rival.posicion,juego.rival.codigo);
	insertar_elemento(laberinto,juego.jugador.posicion,juego.jugador.codigo);
}
/*
 * Mostrará el laberinto por pantalla.
 */
void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO]){
	for (int i = 0; i < TAMANIO; ++i){
		printf("\t\t\t");
		for (int j = 0; j < TAMANIO; ++j){
			printf(" %c", laberinto[i][j]);
		}
	printf("\n");	
	}
	printf("\n");
}