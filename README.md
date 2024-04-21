# Sistema de Gestión de Pacientes en Hospital
## Descripción
Este sistema permite a los usuarios gestionar la atención de pacientes en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera, y más. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones críticas reciban atención lo más pronto posible.

## Como compilar y ejecutar
Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/P4bl0AGT/Sistema-de-Gesti-n-de-Pacientes-en-Hospital`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Run" para compilar y ejecutar la aplicación.

# Funcionalidades
## Funcionando correctamente:
* Registrar pacientes con sus respetivos datos y prioridad Baja
* Asignar prioridad al paciente y ordenar
* Mostrar la lista de espera ordenada por prioridad y hora de registro
* atender al siguiente paciente en orden de prioridad y hora
* Mostrar la lista de pacientes de una prioridad
## Problemas conocidos:
* Al ingresar un paciente que su nombre lleve tildes (Aylén) al momento de asignar prioridad debe llevar la tilde si no el sistema no reconocerá que se trata del mismo paciente
* Si dos pacientes se llaman igual, al momento de asignar prioridad el programa tomará el primero en ser ingresado, por lo que se recomienda ingresar nombre y apellido del paciente
## A mejorar:
* Implementar una interfaz más amigable con el usuario.
* Permitir la edición de los datos de los pacientes.
* Permitir la eliminación de un paciente en específico en caso de que se ingrese mal

# Ejemplo de uso
## paso 1: Menú
* al comenzar el programa se mostrará un menú en el cual aparecerán todas las opciones que se pueden seleccionar en este programa


````
========================================
    Sistema de Gestión de Pacientes
========================================
(1) Para ingresar un paciente
(2) Para asignar prioridad a un paciente
(3) Mostrar lista de espera
(4) Atender al siguiente paciente
(5) Mostrar paciente por prioridad
(6) Salir del programa
Ingrese una opción :
````
## paso 2: registrar paciente:
* se selecciona la primera opción (1)
* se ingresa el nombre del paciente, la edad y el síntoma
````
Ingrese el nombre del paciente : Pablo Aguilera
Ingrese la edad del paciente : 19
Ingrese el síntoma del paciente : Gripe 
Apriete cualquier botón para continua
````
* se aprieta cualquier botón para volver al menú

## paso 3: asignar prioridad al paciente
* se selecciona la segunda opción (2)
* se ingresa el nombre del paciente al cual se le quiere cambiar la prioridad
* se ingresa la prioridad a la cual queremos cambiar de nuestro paciente
````
Ingrese el nombre del paciente a asignar prioridad : Pablo Aguilera
Ingrese la prioridad del paciente (1 = ALTA, 2 = MEDIO, 3 = BAJA): 1
Apriete cualquier botón para continuar
````
* se aprieta cualquier botón para volver al menú

## paso 4: ver lista de espera
* se selecciona la tercera opción (3)
* se mostrará la lista de espera de los pacientes que se han ingresado hasta ese momento con su respectiva prioridad
````
Pacientes con prioridad ALTA

Nombre del paciente = PABLO AGUILERA
Edad del paciente = 19
Síntoma del paciente = Gripe
Hora ingreso del paciente = Sun Apr 21 20:06:37 2024
Prioridad del paciente = ALTA 

No hay pacientes en la lista de prioridad MEDIA

No hay pacientes en la lista de prioridad BAJA

Apriete cualquier botón para continuar
````
* se aprieta cualquier botón para volver al menú

## paso 5: atender al siguiente paciente
* se selecciona la cuarta opción (4)
* se atiende al paciente con mayor prioridad y el primero en orden de llegada
````
Se atendió al siguiente paciente : 
Nombre del paciente = PABLO AGUILERA
Edad del paciente = 19
Síntoma del paciente = Gripe
Hora ingreso del paciente = Sun Apr 21 23:18:09 2024
Prioridad del paciente = BAJA 

Apriete cualquier botón para continuar
````

## paso 6: mostrar pacientes por prioridad
* se selecciona la quinta opción (5)
* ingresé la prioridad que quiere mostrar por pantalla
* se mostrará la prioridad seleccionada
````
Ingrese una prioridad (1 = ALTA, 2 = MEDIA, 3 = BAJA) : 1

No hay pacientes en la lista de prioridad ALTA

Apriete cualquier botón para continuar
````
## paso 7: salir del programa
* se selecciona la sexta opción (6)
* se sale del programa

````
Gracias por ocupar nuestro servicio :D
````
