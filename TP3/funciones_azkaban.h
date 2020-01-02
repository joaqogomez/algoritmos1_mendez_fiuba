#include <stdbool.h>
#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define COMANDO_AYUDA "ayuda"
#define COMANDO_PERDONABLES "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIBERADOS "mostrar_liberados"
typedef struct preso{
	char nombre[MAX_NOMBRE];
	unsigned edad;
	char conducta;
	unsigned pabellon;
	unsigned celda;
	char fecha[MAX_FECHA];
	int maldicion_realizada;
}preso_t;

/*
	*Precondicion: La funcion recibe el comando que ingresa el usuario.
	*Postcondicion: Devuelve si es o no un comando valido.
*/
bool es_comando_valido(char* comando_ingresado);
/*
	*Precondicion: La funcion recibe el comando que ingresa el usuario,siendo este un comando valido,y un comando a comparar.
	*Postcondicion: Devuelve si es o no el comando con el que se quiere comparar.
*/
bool es_comando(char* comando_ingresado,char* comando_a_comparar);
/*
	*Precondicion: La funcion recibe la conducta que el usuario desea para liberar.
	*Postcondicion: Devuelve si es o no un caracter valido.
*/
bool es_conducta_valida(char* conducta_ingresada);
/*
	*Precondicion: La funcion recibe la fecha que el usuario desea para liberar.
	*Postcondicion: Devuelve si es o no una fecha valida.
*/
bool es_fecha_valida(int fecha_ingresada);
/*
	*Precondicion: El usuario introdujo de forma correcta el comando perdonables. Los archivos crucius.dat e imperius.dat se encuentran ordenados alfabeticamente.
	Ademas, los archivos crucius.dat e imperius.dat se encuentran en la misma carpeta que el programa.
	*Postcondicion: Se genera el archivo con aquellos prisioneros que se consideran perdonables. El nombre del archivo va a ser el que decida el usuario.
*/
int crear_archivo_perdonables(char* nombre_archivo);
/*
	*Precondicion: El usuario introdujo de forma correcta el comando liberar y tanto la fecha como la conducta son valores validos.
	 *El archivo perdonables debe estar en la misma carpeta que el programa.
	*Postcondicion: Se genera el archivo con aquellos prisioneros que se pueden liberar. El nombre del archivo va a ser liberables_ y la fecha que ingresa el usuario.
*/
int crear_archivo_liberados(char* nombre_archivo,char* fecha_ingresada,char* conducta_ingresada);
/*
	*Precondicion: Recibe la fecha que el usuario quiere crear el archivo liberados.
	*Postcondicion: Verifica si existe o no el archivo.
*/
bool existe_el_archivo(char* fecha_ingresada);
/*
	*Precondicion: El comando realizo su funcion correctamente.
	*Postcondicion: Imprime al usuario un mensaje en el que le explica que el comando que ingreso se ejecuto correctamente.
*/
void imprimir_funciono_comando();
/*
	*Precondicion: El comando no pudo realizar su funcion correctamente.
	*Postcondicion: Imprime al usuario un mensaje en el que le explica que el comando que ingreso no se ejecuto correctamente.
*/
void imprimir_no_funciono_comando();
/*
	*Precondicion: El usuario introdujo de forma correcta el comando actualizar y la fecha que ingreso es valida.
	*Los archivos crucio y liberados deben estar en la misma carpeta que el programa.
	*Postcondicion: Devuelve el archivo crucio actualizado, es decir sin los nombres de los presos que se liberaron.
*/
int actualizacion_archivo_crucio(char* fecha_ingresada);
/*
	*Precondicion: El usuario introdujo de forma correcta el comando actualizar y la fecha que ingreso es valida.
	*Los archivos imperius y liberados deben estar en la misma carpeta que el programa.
	*Postcondicion: Devuelve el archivo imperius actualizado, es decir sin los nombres de los presos que se liberaron.
*/
int actualizacion_archivo_imperius(char* fecha_ingresada);
/*
	*Precondicion: El usuario introdujo de forma correcta el comando mostrar_liberados y la fecha que ingreso es valida.
	*Postcondicion: Imprime al usuario los nombres de los presos liberados segun la fecha que ingreso.De existir algun problema, imprime que hubo un error.
*/
void mostrar_liberados(char* fecha_ingresada);
/*
	*Precondicion: El usuario introdujo de forma incorrecta un comando.
	*Postcondicion: Imprime al usuario un mensaje en el que le explica que ingreso mal un comando y la ayuda.
*/
void imprimir_ingreso_mal_comandos();
/*
	*Precondicion: El usuario introduce el comando ayuda o ingresa comandos incorrectamente.
	*Postcondicion: Imprime la informacion al usuario sobre lo que hace cada comando y como utilizarlos.
*/
void imprimir_ayuda();
/*
	*Precondicion: El usuario no ingresa ningun comando.
	*Postcondicion: Imprime al usuario un mensaje en el que le explica que no ingreso ningun comando.
*/
void imprimir_mensaje_no_comandos();
