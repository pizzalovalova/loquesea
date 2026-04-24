#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float SaldoenCuenta = 0; //saldo inicial del usuario (Cuenta)
float Deposito; //Cantidad de dinero a depositar
float Retiro; //Cantidad de dinero a retirar

// Arrays para almacenar el historial de transacciones
float depositos[100];
float retiros[100];
int numDepositos = 0;
int numRetiros = 0;

struct Usuario{
    char usuario[20]; //Nombre del usuario
    char contrasena[20]; //Contrasena para usuario
    float SaldoAsignado; //Saldo inicial de la cuenta
};

// Usuarios predeterminados con saldo inicial asignado
struct Usuario usuarios[] = {
    {"mamoncito", "1234", 1250.0},
    {"mariamonte", "1085", 1500.0},
    {"manon", "9012", 2700.0},
    {"leo", "2511", 8080.0}
};

int NumDeUsuarios = 4; //num maximo de usuarios que se pueden autenticar, en este caso es 4 porque son los usuarios predeterminados que se han creado
int usuarioActual = -1; // Indice del usuario autenticado

void autenticacion(){ // Funcion para autenticar al usuario y que este pueda entrar
    printf("Por favor, autentiquese para continuar.\n\n");
   
    char UsuarioCliente[20];// usuario que ingresa el cliente para autenticarse 
    char ContrasenaCliente[20]; // contrasena que ingresa el cliente para autenticarse
    int intentos = 3; //max de intentos
    int autenticado = 0; //pa saber si inicio sesion o no
    
    while (intentos > 0 && !autenticado) { //permite que el cliente se autentique mientras tenga intentos disponibles y no haya sido autenticado
        printf("Ingrese su usuario: ");
        scanf("%s", UsuarioCliente);
        printf("Ingrese su contrasena: ");
        scanf("%s", ContrasenaCliente);
        
        for (int i = 0; i < NumDeUsuarios; i++) {
            if (strcmp(usuarios[i].usuario, UsuarioCliente) == 0 &&  //revisa si el usuario autorizado y el que ingreso el cliente es lo mismo
                strcmp(usuarios[i].contrasena, ContrasenaCliente) == 0) { // revisa si la contrasena autorizada y la que ingreso el cliente es lo mismo
                usuarioActual = i; // numero de usuario autenticado, o sea que dice cual de los 4 es
                SaldoenCuenta = usuarios[i].SaldoAsignado; // hace que el saldo existente sea el que se le asigno
                autenticado = 1; // muestra s esta autenticado, si esta en 1, significa que si esta
                printf("Autenticacion exitosa. Bienvenido %s!\n\n", usuarios[i].usuario);
                break;
            }
        }
        
        if (!autenticado) { 
            intentos--;
            if (intentos > 0) {
                printf("Usuario o contrasena incorrectos. Intentos restantes: %d\n\n", intentos);
            }
        }
    }
    
    if (!autenticado) {
        printf("Ha excedido el numero de intentos. Acceso denegado.\n");
        exit(1);
    }
}

void SaldoDisponible(){ //Funcion para mostrar el saldo disponible 
    printf("Su saldo disponible es de: %.2f\n", SaldoenCuenta);
}

void DepositoDin(){ //Funcion para realizar un deposito a la cuenta del usuario
    printf("Ingrese la cantidad de dinero a depositar: ");
    scanf("%f", &Deposito);
    SaldoenCuenta = SaldoenCuenta + Deposito; // suma la cantidad con el saldo actual
    depositos[numDepositos++] = Deposito; // registrar deposito
   
    char respuesta; // para saber si quiere repetir o no el deposito
    printf("Deposito exitoso. Su nuevo saldo es: %.2f\n", SaldoenCuenta);
    printf("Desea realizar otro deposito? (s/n): ");
    do //funcion para preguntar al usuario si desea realizar otro deposito, si la respuesta es diferente a s o n, se le volvera a preguntar hasta que ingrese una respuesta valida
    {
    scanf(" %c", &respuesta);
    if (respuesta == 's') {
        printf("cuanto desea depositar? \n");
        scanf("%f", &Deposito);
        SaldoenCuenta = SaldoenCuenta + Deposito; //suma la cantidad del deposito con el saldo ya existente
        depositos[numDepositos++] = Deposito; // registrar deposito
        printf("Deposito exitoso. Su nuevo saldo es: %.2f\n", SaldoenCuenta);
        printf("Desea realizar otro deposito? (s/n): ");
        scanf(" %c", &respuesta);
    }
    } while (respuesta != 's' && respuesta != 'n');
    
}

void RetiroDin(){ //Funcion para realizar un retiro de la cuenta del usuario
    printf("Ingrese la cantidad de dinero a retirar: ");
    scanf("%f", &Retiro);
    if (Retiro <= SaldoenCuenta) { //revisa si en la cuenta existen los fondos para retirar
        SaldoenCuenta = SaldoenCuenta - Retiro; // resta la cantidad con el saldo actual
        retiros[numRetiros++] = Retiro; // registrar retiro
        printf("Retiro exitoso. Su nuevo saldo es: %.2f\n", SaldoenCuenta);
    } else {
        printf("Fondos insuficientes para retirar. no se puede hacer el retiro.\n"); // en el caso de que no existan los fondos, le manda este mensaje de que no se puede hacer al usuario
    }
char respuesta; // para saber si quiere repetir o no el retiro
    do //funcion para preguntar al usuario si desea realizar otro retiro, si la respuesta es diferente a s o n, se le volvera a preguntar hasta que ingrese una respuesta valida
    {
    printf("Desea realizar otro retiro? (s/n): ");
    scanf(" %c", &respuesta);
    if (respuesta == 's') {
        printf("cuanto desea retirar? \n");
        scanf("%f", &Retiro);
        if (Retiro <= SaldoenCuenta) {
            SaldoenCuenta = SaldoenCuenta - Retiro; // resta la cantidad con el saldo actual
            retiros[numRetiros++] = Retiro; // registrar retiro
            printf("Retiro exitoso. Su nuevo saldo es: %.2f\n", SaldoenCuenta);
        } else {
            printf("Fondos insuficientes para retirar. no se puede hacer el retiro.\n"); // lo mismo que arriba
        }
    }
    } while (respuesta != 's' && respuesta != 'n'); //revisa si el usuario quiere o no realizar otro retiro, si la respuesta es diferente a s o n, se le volvera a preguntar hasta que ingrese una respuesta valida

}

void Historial(){//Funcion Extra. Yo en este caso la estoy haciendo para mostrar un boletin que muestre las informaciones, que permiten mantener una historia de las transacciones
      float totalDepositos = 0;
    float totalRetiros = 0;

    // Sumar todos los depositos
    for(int i = 0; i < numDepositos; i++){
        totalDepositos += depositos[i];
    }

    // Sumar todos los retiros
    for(int i = 0; i < numRetiros; i++){
        totalRetiros += retiros[i];
    }

    printf("\n========== HISTORIAL DE CUENTA ==========\n");
    printf("Usuario:              %s\n", usuarios[usuarioActual].usuario);
    printf("Saldo inicial:        %.2f\n", usuarios[usuarioActual].SaldoAsignado);
    printf("Saldo actual:         %.2f\n", SaldoenCuenta);

    printf("\n--------- Detalle de Transacciones ---------\n");
    printf("Depositos:\n");
    for(int i = 0; i < numDepositos; i++){
        printf("  %d. Deposito  %.2f\n", i+1, depositos[i]);
    }
    printf("Retiros:\n");
    for(int i = 0; i < numRetiros; i++){
        printf("  %d. Retiro    %.2f\n", i+1, retiros[i]);
    }

    printf("\n------------ Resumen ------------\n");
    printf("Depositos realizados: %d  |  Total depositado: %.2f\n", numDepositos, totalDepositos);
    printf("Retiros realizados:   %d  |  Total retirado:   %.2f\n", numRetiros, totalRetiros);
    printf("Diferencia neta:      %.2f\n", totalDepositos - totalRetiros);
    printf("=========================================\n");
}
    


int main(){
    printf("========== BIENVENIDO AL CAJERO DIGITAL ==========\n");
    autenticacion();
    int opcion;
    do
    {
        printf("\n========== MENU ==========\n");
        printf("Que desea hacer?\n 1. Consultar saldo disponible\n 2. Realizar un deposito\n 3. Realizar un retiro\n 4. Ver historial de cuenta\n 5. Salir\n");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
            SaldoDisponible();
            break;
        case 2:
            DepositoDin();
            break;
        case 3:
            RetiroDin();
            break;
        case 4:
            Historial();
            break;
        case 5:
            printf("Gracias por usar el cajero digital. Pase un buen dia.\n");
            break;
        default:
            printf("Opcion no valida.\n");
            break;
        }   
    } while (opcion != 5); // Permite que el usuario siga usando el cajero digital hasta que decida salir, si la opcion es diferente a 1,2,3,4 o 5, se le volvera a mostrar el menu hasta que ingrese una opcion valida
    return 0;
}