#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "tdas/list.h"

//DEFINICIONES PARA CAMBIAR DE COLOR EL TEXTO DE LA CONSOLA
#define ROJO printf("\x1b[31m");
#define VERDE printf("\x1b[32m");
#define AMARILLO printf("\x1b[33m");
#define BLANCO printf("\x1b[m");

//ESTRUCTURA DE PARA LOS PACIENTES
typedef struct
{
  char *nombre;
  int edad;
  char *sintoma;
  time_t fechaHora;
  int prioridad;
  char *cadenaPrioridad;
} tipoPaciente;

//ESTRUCTURA PARA LAS DIFERENTES PRIORIDADES
typedef struct
{
  List *listaAlta;
  List *listaMedia;
  List *listaBaja;
} tipoListas;

//FUNCION QUE SE IMPRIME SI LAS FUNCIONAS SE REALIZARON CON EXITO
void EXITO()
{
  VERDE
  printf("Apriete cualquier botón para continuar");
  while ((getchar()) != '\n');
}

//FUNCION QUE SE IMPRIME SI EN ALGUN MOMENTO HUBO ALGUN ERROR
void ERROR()
{
  ROJO
  printf("CUIDADO ALGO HA PRODUCIDO UN ERROR\n");
  printf("Apriete cualquier botón para continuar");
  while ((getchar()) != '\n');
}

//FUNCION QUE MUESTRA EL MENU DEL SISTEMA
void mostrarMenu()
{
  printf("========================================\n");
  printf("    Sistema de Gestión de Pacientes\n");
  printf("========================================\n");
  printf("(1) Para ingresar un paciente\n");
  printf("(2) Para asignar prioridad a un paciente\n");
  printf("(3) Mostrar lista de espera\n");
  printf("(4) Atender al siguiente paciente\n");
  printf("(5) Mostrar paciente por prioridad\n");
  printf("(6) Salir del programa\n");
}

//FUNCION QUE INICIALIZA LAS LISTAS DE PRIORIDAD
tipoListas *inicializarListas()
{
  tipoListas *listas = (tipoListas *) malloc(sizeof(tipoListas));
  listas->listaAlta = list_create();
  listas->listaMedia = list_create();
  listas->listaBaja = list_create();
  return listas;
}

//FUNCION QUE CONVIERTE UNA CADENA DE CARACTERES A MAYUSCULAS
void mayuscula(char *cadena)
{
  while((*cadena) != '\0')
  {
    *cadena = toupper(*cadena);
    cadena++;
  }
  *cadena = '\0';
}

//FUNCION QUE VERIFICA SI UNA CADENA DE CARACTERES ES NUMERICA
int esNumerica(char *cadena)
{
  while((*cadena) != '\0')
  {
    if(!isdigit(*cadena))
      return 0;
    cadena++;
  }
  return 1;
}

//FUNCION QUE CONVIERTE UNA CADENA A NUMEROS
int strToNum(char *cadena)
{
  int numero = 0;
  while((*cadena) != '\0')
  {
    numero = numero * 10 + (*cadena - '0');
      cadena++;
  }
  return numero;    
}

//FUNCION QUE LEE LOS DATOS DEL PACIENTE Y LOS GUARDA EN  LA LISTA DE PRIORIDAD BAJA
void registrarPaciente(List *lista)
{
  tipoPaciente *paciente = (tipoPaciente *) malloc(sizeof(tipoPaciente));
  //NOMBRE
  char *nombre = (char *) malloc(sizeof(char) * 50);
  printf("Ingrese el nombre del paciente : ");
  fscanf(stdin, "%29[^\n]s", nombre);
  while ((getchar()) != '\n');
  mayuscula(nombre);
  paciente->nombre = nombre;
  
  ///EDAD
  char *cadenaEdad = (char *) malloc(sizeof(char) * 4);
  printf("Ingrese la edad del paciente : ");
  fscanf(stdin, "%3[^\n]s", cadenaEdad);
  while ((getchar()) != '\n');
  while (1)
  {
    if(!esNumerica(cadenaEdad))
    {
      ROJO
      printf("ERROR Ingrese una edad valida\n");
      BLANCO
      printf("Ingrese la edad del paciente : ");
      fscanf(stdin, "%3s", cadenaEdad);
      while ((getchar()) != '\n');
      continue;
    }
    break;
  }
  paciente->edad = strToNum(cadenaEdad);
  
  //SINTOMA
  char *sintoma = (char *) malloc(sizeof(char) * 50);
  printf("Ingrese el síntoma del paciente : ");
  fscanf(stdin, "%29[^\n]s", sintoma);
  paciente->sintoma = sintoma;
  while ((getchar()) != '\n');
  
  //HORA
  struct tm *temp;
  time(&paciente->fechaHora);
  temp = localtime(&paciente->fechaHora);
  temp->tm_hour = (temp->tm_hour + 20) % 24;
  paciente->fechaHora = mktime(temp);
  
  //PRIORIDAD
  paciente->prioridad = 3;
  paciente->cadenaPrioridad = "BAJA";

  //AGREGAR PACIENTE A LA LISTA
  list_pushBack(lista, paciente);
  EXITO();
}

//FUNCION QUE MUESTRA UN PACIENTE
void mostrarPaciente(tipoPaciente *paciente)
{
  printf("Nombre del paciente = %s\n", paciente->nombre);
  printf("Edad del paciente = %i\n", paciente->edad);
  printf("Síntoma del paciente = %s\n", paciente->sintoma);
  printf("Hora ingreso del paciente = %s", ctime(&paciente->fechaHora));
  printf("Prioridad del paciente = %s \n\n", paciente->cadenaPrioridad);
}

//FUNCION QUE MUESTRA UNA LISTA DE PRIORIDAD EN ESPECIFICO
void mostrarLista(List *lista, char* prioridad)
{
  tipoPaciente *paciente = (tipoPaciente *)list_first(lista);
  size_t cont = 0;

  if(paciente == NULL)
  {
    AMARILLO
    printf("No hay pacientes en la lista de prioridad %s\n\n", prioridad);
    return;
  }

  BLANCO
  printf("Pacientes con prioridad %s\n\n", prioridad);
  while( paciente != NULL )
  {
    mostrarPaciente(paciente);
    paciente = list_next(lista);
    cont++;
  }  
}

//FUNCION QUE BUSCA SI EL PACIENTE EXISTE O NO EN LA LISTA DE ESPERA DE PRIORIDAD BAJA
tipoPaciente *existe(List *lista, char *nombre)
{
  tipoPaciente *paciente = (tipoPaciente *) list_first(lista);
  while(paciente != NULL)
  {
    if(strcmp(paciente->nombre, nombre) == 0)
      return paciente;
    paciente = (tipoPaciente *) list_next(lista);
  }
  return NULL;
}

//FUNCION QUE ELIMINA AL PACIENTE CON MAYOR PRIORIDAD Y POR ORDEN DE LLEGADA
void eliminarPaciente(List *lista, tipoPaciente *paciente)
{
  tipoPaciente *actual = (tipoPaciente *)list_first(lista);
  while(actual != NULL)
  {
    if(actual == paciente)
    {
      list_popCurrent(lista);
      return;
    }
    actual = (tipoPaciente *)list_next(lista);
  }
}

//FUNCION QUE COMPARA Y SIRVE PARA ORDENAR LOS PACIENTES POR ORDEN DE LLEGADA
int comparar(void *paciente1, void *paciente2)
{
  tipoPaciente *ptrPaciente1 = (tipoPaciente *) paciente1;
  tipoPaciente *ptrPaciente2 = (tipoPaciente *) paciente2;

  if(ptrPaciente1->fechaHora < ptrPaciente2->fechaHora)
    return 1;
  return 0;
}

//FUNCION QUE ASIGNA LA PRIORIDAD A LOS PACIENTES
void asignarPrioridad(tipoListas *listas)
{
  //NOMBRE
  char *nombre = (char *) malloc(sizeof(char) * 50);
  printf("Ingrese el nombre del paciente para asignar prioridad : ");
  fscanf(stdin, "%29[^\n]s", nombre);
  mayuscula(nombre);
  while ((getchar()) != '\n');

  //BUSCAR PACIENTE
  tipoPaciente *paciente = existe(listas->listaBaja, nombre);
  if(paciente == NULL)
  {
    ROJO
    printf("ERROR Ese paciente no existe ó al paciente ya se le asigno una prioridad\n");
    BLANCO
    printf("Apriete cualquier boton para continuar");
    while ((getchar()) != '\n');
    return;
  }

  //INGRESAR PRIORIDAD PARA CAMBIAR
  char *cadenaPrioridad = (char *) malloc(sizeof(char) * 4);
  printf("Ingrese la prioridad del paciente (1 = ALTA, 2 = MEDIA, 3 = BAJA): ");
  fscanf(stdin, "%3[^\n]s", cadenaPrioridad);
  while ((getchar()) != '\n');
  while (1)
  {
    if(!esNumerica(cadenaPrioridad) || strToNum(cadenaPrioridad) > 3)
    {
      printf("ERROR Ingrese una prioridad valida\n");
      printf("Ingrese la prioridad del paciente (1 = ALTA, 2 = MEDIA, 3 = BAJA): ");
      fscanf(stdin, "%3s", cadenaPrioridad);
      while ((getchar()) != '\n');
      continue;
    }
    break;
  }

  //CONVERTIR CADENA A NUMERO
  paciente->prioridad = strToNum(cadenaPrioridad);
  //VER EN QUE PRIORIDAD SE ENCUENTRA PARA METERLO EN LA LISTA CORRESPONDIENTE
  if(paciente->prioridad == 1)
  {
    paciente->cadenaPrioridad = "ALTA";
    eliminarPaciente(listas->listaBaja, paciente);
    list_sortedInsert(listas->listaAlta, paciente, comparar);
  }
  else if(paciente->prioridad == 2)
  {
    paciente->cadenaPrioridad = "MEDIA";
    eliminarPaciente(listas->listaBaja, paciente);
    list_sortedInsert(listas->listaMedia, paciente, comparar);
  }
  EXITO();
}

//FUNCION QUE MUESTRA LA LISTA DE ESPERA
void mostrarListaEspera(tipoListas *listas)
{
  mostrarLista(listas->listaAlta, "ALTA");
  mostrarLista(listas->listaMedia, "MEDIA");
  mostrarLista(listas->listaBaja, "BAJA");
  EXITO();
}

//FUNCION QUE ATIENDE Y MUESTRA AL PACIENTE CON MAYOR PRIORIDAD Y POR ORDEN DE LLEGADA
void atenderSiguientePaciente(tipoListas *listas)
{
  tipoPaciente *paciente = (tipoPaciente *) list_first(listas->listaAlta);
  if(paciente != NULL)
  {
    printf("Se atendio al siguiente paciente : \n");
    mostrarPaciente(paciente);
    list_popCurrent(listas->listaAlta);
    EXITO();
    return;
  }

  paciente = (tipoPaciente *) list_first(listas->listaMedia);
  if(paciente != NULL)
  {
    printf("Se atendio al siguiente paciente : \n");
    mostrarPaciente(paciente);
    list_popCurrent(listas->listaMedia);
    EXITO();
    return;
  }

  paciente = (tipoPaciente *) list_first(listas->listaBaja);
  if(paciente != NULL)
  {
    printf("Se atendio al siguiente paciente : \n");
    mostrarPaciente(paciente);
    list_popCurrent(listas->listaBaja);
    EXITO();
    return;
  }
  printf("NO HAY PACIENTES PARA ATENDER\n");
  EXITO();
}

//FUNCION QUE MUESTRA UNA LISTA DE PRIORIDAD EN ESPECIFICO
void mostrarPacientePrioridad(tipoListas *listas)
{
  char *cadenaPrioridad = (char *) malloc(sizeof(char) * 2);
  printf("Ingrese una prioridad (1 = ALTA, 2 = MEDIA, 3 = BAJA) : ");
  fscanf(stdin, "%3[^\n]s", cadenaPrioridad);
  while ((getchar()) != '\n');
  while (1)
  {
    if(!esNumerica(cadenaPrioridad) || strToNum(cadenaPrioridad) > 3)
    {
      ROJO
      printf("ERROR Ingrese una prioridad valida\n");
      BLANCO
      printf("Ingrese la prioridad del paciente (1 = ALTA, 2 = MEDIA, 3 = BAJA): ");
      fscanf(stdin, "%3s", cadenaPrioridad);
      while ((getchar()) != '\n');
      continue;
    }
    break;
  }
  printf("\n");
  if(strToNum(cadenaPrioridad) == 1)
    mostrarLista(listas->listaAlta, "ALTA");
  else if(strToNum(cadenaPrioridad) == 2)
    mostrarLista(listas->listaMedia, "MEDIA");
  else
    mostrarLista(listas->listaBaja, "BAJA");

  EXITO();
}

//MAIN
int main()
{  
  tipoListas *listas = inicializarListas();
  char opcion;
  while(1)
  {
    BLANCO
    system("clear");
    mostrarMenu();
    printf("Ingrese una opcion : ");
    fscanf(stdin, "%c", &opcion);
    while ((getchar()) != '\n');
    printf("\n");
    
    if( opcion == '1')
      registrarPaciente(listas->listaBaja);
    else if( opcion == '2')
      asignarPrioridad(listas);
    else if( opcion == '3')
      mostrarListaEspera(listas);
    else if( opcion == '4')
      atenderSiguientePaciente(listas);
    else if( opcion == '5')
      mostrarPacientePrioridad(listas);
    else if( opcion == '6')
      break;  
    else
      ERROR();
  }
  printf("Gracias por ocupar nuestro servicio :D");
  exit(EXIT_SUCCESS);
}