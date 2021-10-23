/* Ignacio Gil Garzon - Práctica Individual Gestor de Tareas
Descripción: 
                 - Clase Tarea: Nombre de la tarea(string), Tiempo de finalización (datetime), Persona encargada 
                 - Funcionalidades: Crear tarea, Borrar tarea, Editar tarea, Ver tarea más urgente
                 - Requerimientos técnicos: Uso del Free Space para, al menos, guardar una variable.
                   Deben existir funciones que reciban/utilicen los pasos por referencia.
                   Se deben controlar, mediante excepciones, todos los posibles errores que sean susceptibles de aparecer.*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>
using namespace std;

class Tarea{

    public:
         string nombre;

    void verTareas();
    void crearTarea();
    void borrarTarea();
    void editarTarea();
    void verUrgente();
    void anadirLog(string log);
    void verLog();

    string getnombre() {
        return nombre;
    }
};

// VER TAREAS ACTUALES
void Tarea::verTareas(){

    ifstream archivo;
    string texto;
    char cero = '0';
    archivo.open("tareas.txt", ios::in);

    if(archivo.fail()){
        cout << "No se pudo abrir el archivo." << "\n";
        exit(1);
    }
    
    while(!archivo.eof()){
        getline(archivo,texto);
        
        replace(texto.begin(), texto.end(), ';', ' ');
        for(int i = 0; i<texto.length(); i++){
            if(texto[i] == cero){
                cout << texto << endl;
            }
        }
   
    }
    archivo.close();
}

// CREAR TAREA
void Tarea::crearTarea(){
    
    ofstream out_file;
    int prioridad;
    string nombreNuevo, encargado, tiempo;

    cout << "Ingrese la *prioridad* de la nueva Tarea:" << "\n";
    cin >> prioridad;

    cout << "\n" << "Ingrese el *nombre* de la nueva Tarea" << "\n";
    cout << "(debe ir con _ entre palabras): " << "\n";
    cin >> nombreNuevo;

    cout << "\n" << "Ingrese el *encargado/a* de la nueva Tarea:" << "\n";
    cin >> encargado;

    cout << "\n" << "Ingrese el *tiempo de finalizacion* de la nueva Tarea:" << "\n";
    cout << "(ej: 12:30): " << "\n";
    cin >> tiempo;

    // Escribir el archivo.
    out_file.open("tareas.txt", ios::app); // Abre el archivo y le indica que lo agregado se añada y no sobreescriba.
    out_file << "\n" << prioridad << ";" << nombreNuevo << ";" << encargado << ";" << tiempo << ";"; // Agregamos el texto deseado.
    out_file.close();  // Cerramos el archivo con la nueva info.

    cout << "\n" << "Tarea anadida correctamente" << "\n";

}

// BORRAR TAREA
void Tarea::borrarTarea(){

    int opcion = 0;
    ofstream out_file;
    cout << "¿Estas seguro de que quieres borrar todos los datos?" << "\n";
    cout << " 1-Si // 2-No " << "\n";
    cin >> opcion;

    switch (opcion) {

        case 1:
            cout << "\n" << "ELIMINANDO" << "\n";
            out_file.open("tareas.txt", ios::out);
            out_file << "" << endl; // Vaciamos
            out_file.close();
            cout << "\n" << "-ELIMINADO-" << "\n";
        break;

        case 2:
            cout << "\n" << "NO ELIMINAS NADA" << "\n";
        break;
    }
}

// VER EDITAR TAREA
void Tarea::editarTarea(){

}

// VER URGENTE
void Tarea::verUrgente(){

}

// **METODO AÑADIR LOG**
void Tarea::anadirLog(string log){
    ofstream out_file;
    time_t * rawtime = new time_t;
    struct tm * timeinfo;
    time(rawtime);
    timeinfo = localtime(rawtime);


    out_file.open("logTotal.txt", ios::app);
    out_file << log << " -- " << asctime(timeinfo);
    out_file.close();
    
    return;
}

// **METODO VER LOG**
void Tarea::verLog(){
    ifstream archivo;
    string texto;
    archivo.open("logTotal.txt", ios::in);

    if(archivo.fail()){
        cout << "No se pudo abrir el archivo." << "\n";
        exit(1);
    }
    
    while(!archivo.eof()){
        getline(archivo,texto);
        replace(texto.begin(), texto.end(), ';', ' ');
        cout << texto << endl;
    }
    archivo.close();
}

// **MENU PRINCIPAL**
static int imprimir_menu(){

    int opcion = 0;
        cout << "\n" << "  1 - Ver lista de Tareas actual" << "\n";
        cout << "  2 - Crear nueva Tarea" << "\n";
        cout << "  3 - Borrar Tarea" << "\n";
        cout << "  4 - Editar Tarea" << "\n";
        cout << "  5 - Ver Tarea mas urgente" << "\n";
        cout << "  6 - " << "\n";
        cout << "  7 - " << "\n";
        cout << "  8 - Ver log de la sesion actual" << "\n";
        cout << "  0 - Salir del programa" << "\n";
             
        cin >> opcion;

        return opcion;
}

int main(int argc, char *argv[]){

    string nombre;
    int opcion = 1;
    Tarea tarea;

    string log = "0";

    cout << "   ---  Bienvenido al programa de Gestion de Tareas  ---   " << "\n\n";

    // Bucle para mantener activo el programa.
    while (opcion != 0) {

            // Mostramos el Menu principal y damos valor de opcion para switch.
            opcion = imprimir_menu();

            switch (opcion) {

                case 1:
                    cout << "\n" << "**VER LISTA DE TAREAS**" << "\n\n";
                    tarea.verTareas();
                    log = "VER LISTA DE TAREAS  ";
                    tarea.anadirLog(log);
                break;

                case 2:
                    cout << "\n" << "**CREAR UNA NUEVA TAREA**" << "\n\n";
                    tarea.crearTarea();
                    log = "CREAR UNA NUEVA TAREA";
                    tarea.anadirLog(log);
                break;

                case 3: 
                    cout << "\n" << "**BORRAR UNA TAREA**" << "\n\n";
                    tarea.borrarTarea();
                    log = "BORRAR UNA TAREA     ";
                    tarea.anadirLog(log);
                break;

                case 4:
                    cout << "\n" << "**EDITAR UNA TAREA**" << "\n";
                    tarea.editarTarea();
                    log = "EDITAR UNA TAREA     ";
                    tarea.anadirLog(log);
                break;

                case 5: 
                    cout << "\n" << "**VER TAREA MAS URGENTE**" << "\n";
                    tarea.verUrgente();
                    log = "VER TAREA MAS URGENTE";
                    tarea.anadirLog(log);
                break;

                case 6:
                    
                break;

                case 7:
                    
                break;

                case 8:
                    log = "IMPRIMIR LOG         ";
                    tarea.anadirLog(log);
                    cout << "\n" << "**IMPRIMIR LOG**" << "\n";
                    tarea.verLog();
                break;

                case 0:
                    cout << "\n" << "**HASTA PRONTO**" << "\n";
                break;

            default:
                cout << "\n" << "**OPCIÓN INCORRECTA**" << "\n";
            }
    }
    return 0;
}