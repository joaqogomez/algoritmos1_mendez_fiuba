#include <stdio.h>
#include <stdbool.h>
/*Precondiciones: 1)El usuario debe ingresar sus datos. En caso de no estar en los rangos validos, se debe solicitar hasta que estos sean validos.
				  2)Los alumnos pueden ser campeones si tienen 17 años o mas. En caso de ser menores, el programa no continuara pidiendo datos.
				  3)Para evaluar quien es el campeon, se toma en cuenta la inteligencia, luego la fuerza y por ultimo la capacidad magica.
				   En caso de ser todos los valores iguales, se mantiene el campeon vigente.
				  4)Cuando el programa pida al usuario ingresar numeros o caracteres, este lo hara segun corresponda.
Postcondiciones: 1)El programa debe devolver,en caso que haya campeon, el numero de orden en el cual el alumno puso sus datos.
				 2)Si ningun alumno cumple con las condiciones para ser campeon, el programa avisa que no lo hay.
*/
const int MINIMO_EDAD= 17;
const int MINIMO_INTELIGENCIA= 0;
const int MAXIMO_INTELIGENCIA= 10;
const int MINIMO_FUERZA= 0;
const int MAXIMO_FUERZA= 10;
const char CAPACIDAD_MAGICA_BUENA='B';
const char CAPACIDAD_MAGICA_REGULAR='R';
const char CAPACIDAD_MAGICA_MALA='M';
const char DETENER_CARGA='N';
	/*
*  Pide una respuesta al usuario para continuar ejecutando el programa.
 * Precondiciones: Se inicia el programa o se terminan de cargar los datos de un alumno.
 * Postcondiciones: Se devuelve un caracter.
	*/
void pedir_respuesta_para_continuar(char (*respuesta_para_continuar)){
	scanf(" %c", &(*respuesta_para_continuar));
}
	/*
 * Verifica el caracter ingresado para saber si debe continuar ejecutando o no el programa.
 * Precondiciones: Ingreso de un caracter.
 * Postcondiciones: Permite continuar o no el programa.
	*/	
bool ingreso_alumnos(char respuesta_para_continuar){

	if (respuesta_para_continuar==DETENER_CARGA){
		return false;
	}else{
		return true;
	}
}
	/*
 * Pide la edad del usuario.
 * Precondiciones: que el usuario haya ingresado un caracter que permita que corra el programa.
 * Postcondiciones: saber la edad del usuario.
	*/	
void pedir_edad(unsigned int (*edad_alumno)){
	printf("\nIngrese su edad: ");
	scanf(" %u", &(*edad_alumno));
}
	/*
 * Verifica la edad ingresada para saber si debe continuar ejecutando o no el programa.
 * Precondiciones: Ingreso de la edad del usuario.
 * Postcondiciones: Permite continuar o no el programa.
	*/	
bool verificar_edad(unsigned int edad_alumno){
	if (edad_alumno>=MINIMO_EDAD){
		return true;
	}else{
		return false;
	}
}
	/*
 * Verifica la inteligencia ingresada para saber si esta en el rango permitido o debe pedirla nuevamente.
 * Precondiciones: Ingreso de la inteligencia del usuario.
 * Postcondiciones: Permite continuar el programa o hace que el usuario vuelva a ingresar un valor.
	*/	
bool verificar_inteligencia(int (inteligencia_ingresada)){
	if (((inteligencia_ingresada)<MINIMO_INTELIGENCIA)||((inteligencia_ingresada)>MAXIMO_INTELIGENCIA)){
		return true;
	}else{
		return false;
	}
}
	/*
 * Pide la inteligencia del usuario.
 * Precondiciones: que el usuario haya ingresado una edad que permita que corra el programa.
 * Postcondiciones: devuelve un valor de inteligencia en el rango pedido.
	*/	
void pedir_inteligencia(int (*inteligencia_ingresada)){
	printf("\nIngrese el valor de su inteligencia (este valor debe estar entre 0 y 10): ");
	scanf(" %i", &(*inteligencia_ingresada));
	while (verificar_inteligencia((*inteligencia_ingresada))){
		printf("\nEl valor ingresado es incorrecto. Ingrese el valor de su inteligencia (este valor debe estar entre 0 y 10): ");
		scanf(" %i", &(*inteligencia_ingresada));
	}
}
	/*
 * Verifica la fuerza ingresada para saber si esta en el rango permitido o debe pedirla nuevamente.
 * Precondiciones: Ingreso de la fuerza del usuario.
 * Postcondiciones: Permite continuar el programa o hace que el usuario vuelva a ingresar un valor.
	*/
bool verificar_fuerza(int (fuerza_ingresada)){
	if (((fuerza_ingresada)<MINIMO_FUERZA)||((fuerza_ingresada)>MAXIMO_FUERZA)){
		return true;
	}else{
		return false;
	}
}
	/*
 * Pide la fuerza del usuario.
 * Precondiciones: que el usuario haya ingresado una edad que permita que corra el programa.
 * Postcondiciones: devuelve un valor de fuerza en el rango pedido.
	*/	
void pedir_fuerza(int (*fuerza_ingresada)){
	printf("\nIngrese el valor de su fuerza (este valor debe estar entre 0 y 10): ");
	scanf(" %i", &(*fuerza_ingresada));
	while (verificar_fuerza((*fuerza_ingresada))){
		printf("\nEl valor ingresado es incorrecto. Ingrese el valor de su fuerza (este valor debe estar entre 0 y 10): ");
		scanf(" %i", &(*fuerza_ingresada));
	}
}
	/*
 * Verifica la capacidad magica ingresada para saber si esta en el rango permitido o debe pedirla nuevamente.
 * Precondiciones: Ingreso de la capacidad magica del usuario.
 * Postcondiciones: Permite continuar el programa o hace que el usuario vuelva a ingresar un valor.
	*/
bool verificar_capacidad_magica(char (capacidad_magica_ingresada)){
	if (((capacidad_magica_ingresada)==CAPACIDAD_MAGICA_BUENA)||((capacidad_magica_ingresada)==CAPACIDAD_MAGICA_REGULAR)||((capacidad_magica_ingresada)==CAPACIDAD_MAGICA_MALA)){
		return false;
	}else{
		return true;
	}
}
	/*
 * Pide la capacidad magica del usuario.
 * Precondiciones: que el usuario haya ingresado una edad que permita que corra el programa.
 * Postcondiciones: devuelve un valor de capacidad magica en el rango pedido.
	*/	
void pedir_capacidad_magica(char (*capacidad_magica_ingresada)){
	printf("\nIngrese el valor de su capacidad magica (este valor puede ser B (Buena) R(Regular)o M(Mala)): ");
	scanf(" %c", &(*capacidad_magica_ingresada));
	while (verificar_capacidad_magica((*capacidad_magica_ingresada))){
		printf("\nEl valor ingresado es incorrecto. Ingrese el valor de su capacidad magica (este valor puede ser B (Buena) R(Regular)o M(Mala)): ");
		scanf(" %c", &(*capacidad_magica_ingresada));
	}
}
	/*
 * Analiza los casos en los cuales los valores ingresados son mayores que los del campeon .
 * Precondiciones: que el usuario haya ingresado una edad que permita que corra el programa 
 * y, que los valores de la inteligencia y de la fuerza ingresados sean iguales a los del campeon .
 * Postcondiciones: permite que cambie el campeon o se mantenga.
	*/
bool comparar_capacidad_magica(char (capacidad_magica_ingresada),char (capacidad_magica_campeon)){
	if ((capacidad_magica_ingresada)==(capacidad_magica_campeon)){
		return false;
	}else if((((capacidad_magica_ingresada)==CAPACIDAD_MAGICA_BUENA)&&((capacidad_magica_campeon)==CAPACIDAD_MAGICA_REGULAR))||(((capacidad_magica_ingresada)==CAPACIDAD_MAGICA_BUENA)&&((capacidad_magica_campeon)==CAPACIDAD_MAGICA_MALA))||(((capacidad_magica_ingresada)==CAPACIDAD_MAGICA_REGULAR)&&((capacidad_magica_campeon)==CAPACIDAD_MAGICA_MALA))){
		return true;
	}else{
		return false;
	}
}
	/*
 * Decide si el alumno ingresado es campeon o no, comparando valores.
 * Precondiciones: que el usuario haya ingresado una edad que permita que corra el programa 
 * y que haya ingresado correctamente los valores de inteligencia, fuerza y capacidad magica  .
 * Postcondiciones:devuelve el numero de alumno que es el campeon.
	*/	
void decidir_campeon(int (*alumno_campeon),int (*inteligencia_ingresada),int (*fuerza_ingresada),char (*capacidad_magica_ingresada),int (*contador_alumnos),int (*inteligencia_campeon),int (*fuerza_campeon),char (*capacidad_magica_campeon)){
	if ((*inteligencia_ingresada)>(*inteligencia_campeon)){
		(*inteligencia_campeon)=(*inteligencia_ingresada);
		(*fuerza_campeon)=(*fuerza_ingresada);
		(*capacidad_magica_campeon)=(*capacidad_magica_ingresada);
		(*alumno_campeon)=(*contador_alumnos);
	}else if ((*inteligencia_ingresada)==(*inteligencia_campeon)){
		if ((*fuerza_ingresada)>(*fuerza_campeon)){
			(*inteligencia_campeon)=(*inteligencia_ingresada);
			(*fuerza_campeon)=(*fuerza_ingresada);
			(*capacidad_magica_campeon)=(*capacidad_magica_ingresada);
			(*alumno_campeon)=(*contador_alumnos);
		}else if((*fuerza_ingresada)==(*fuerza_campeon)){
			if(comparar_capacidad_magica((*capacidad_magica_ingresada),(*capacidad_magica_campeon))){
				(*inteligencia_campeon)=(*inteligencia_ingresada);
				(*fuerza_campeon)=(*fuerza_ingresada);
				(*capacidad_magica_campeon)=(*capacidad_magica_ingresada);
				(*alumno_campeon)=(*contador_alumnos);
			}else{
				(*alumno_campeon)=(*alumno_campeon);
			}
		}
	}
}
int main(){
	int alumno_campeon=0;
	int contador_alumnos=0;
	char respuesta_para_continuar;
	unsigned int edad_alumno;
	int inteligencia_campeon=-1;
	int fuerza_campeon=-1;
	char capacidad_magica_campeon;
	int inteligencia_ingresada;
	int fuerza_ingresada;
	char capacidad_magica_ingresada;
	printf("Desea ingresar un alumno? (N para ​ NO​ , cualquier otra tecla para sí): ");
	pedir_respuesta_para_continuar(&respuesta_para_continuar);
	if (ingreso_alumnos(respuesta_para_continuar)){
		do{
			contador_alumnos++;
			pedir_edad(&edad_alumno);
				if (verificar_edad(edad_alumno)){
					pedir_inteligencia(&inteligencia_ingresada);
					pedir_fuerza(&fuerza_ingresada);
					pedir_capacidad_magica(&capacidad_magica_ingresada);
					decidir_campeon(&alumno_campeon,&inteligencia_ingresada, &fuerza_ingresada, &capacidad_magica_ingresada, &contador_alumnos, &inteligencia_campeon, &fuerza_campeon, &capacidad_magica_campeon);
				}
			printf("\nDesea ingresar otro alumno? (N para ​ NO​ , cualquier otra tecla para sí):");
			pedir_respuesta_para_continuar(&respuesta_para_continuar);
		}while(ingreso_alumnos(respuesta_para_continuar));
		if (alumno_campeon==0){
			printf("No hay campeón :(\n");
		}else{
			printf("El campeón es el número %i :)\n", (alumno_campeon));;
		}
	}else{
		printf("No hay campeón :(\n");
	}
}