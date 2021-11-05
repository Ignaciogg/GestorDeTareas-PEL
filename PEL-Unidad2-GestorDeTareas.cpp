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
#include <vector>
using namespace std;

class Tarea{

    public:
         string id;
         string prioridad;
         string nombreT;
         string nombreU;
         string hora;
         string fecha;

    void verTareas();
    void crearTarea();
    void borrarTarea();
    void editarTarea(int num);
    void verUrgente();
    void exportarCSV();
    void anadirLog(string log);
    void verLog();

    string getid() {
        return id;
    }
    string getprio() {
        return prioridad;
    }
    string getnombreT() {
        return nombreT;
    }
    string getnombreU() {
        return nombreU;
    }
    string gethora() {
        return hora;
    }
    string getfecha() {
        return fecha;
    }
    
};

// VER TAREAS ACTUALES
void Tarea::verTareas(){

    ifstream archivo;
    string texto;

    try{
        archivo.open("tareas.txt", ios::in);
        if (archivo.fail()) {
            std::runtime_error ("tareas.txt no se pudo abrir.\n");
        }
    
        while(!archivo.eof()){
            getline(archivo,texto);
        
            replace(texto.begin(), texto.end(), ';', ' ');
            replace(texto.begin(), texto.end(), '_', ' ');
            cout << texto << endl;
        }
    }
    catch(...){
        throw std::runtime_error("Error en la funcion de ver tareas actuales.");
        archivo.close();
    }
    archivo.close();
}

// CREAR TAREA
void Tarea::crearTarea(){
    
    ofstream out_file;
    int prioridad;
    string ID, nombreNuevo, encargado, tiempo, fecha;

    try{
        cout << "\n" << "Ingrese el *ID* de la nueva Tarea:" << "\n";
        cin >> ID;

        cout << "Ingrese la *prioridad* de la nueva Tarea:" << "\n";
        cout << "(solo el numero): " << "\n";
        cin >> prioridad;

        cout << "\n" << "Ingrese el *nombre* de la nueva Tarea" << "\n";
        cout << "(debe ir con _ entre palabras): " << "\n";
        cin >> nombreNuevo;

        cout << "\n" << "Ingrese el *encargado/a* de la nueva Tarea:" << "\n";
        cin >> encargado;

        cout << "\n" << "Ingrese el *tiempo de finalizacion* de la nueva Tarea:" << "\n";
        cout << "(ej: 12:30): " << "\n";
        cin >> tiempo;

        cout << "\n" << "Ingrese el *la fecha* de la nueva Tarea:" << "\n";
        cout << "(ej: 23/04/2018): " << "\n";
        cin >> fecha;

        // Escribir el archivo.
        out_file.open("tareas.txt", ios::app);
        if (out_file.fail()) {
            std::runtime_error ("tareas.txt no se pudo abrir.\n");
        }
        // Agregamos el texto deseado.
        out_file <<  ID << ";" << "P" << prioridad << ";" << nombreNuevo << ";" << encargado << ";" << tiempo << ";" << fecha << ";"; 
        out_file.close();  // Cerramos el archivo con la nueva info.

        cout << "\n" << "Tarea anadida correctamente" << "\n";
    }catch(...){
        throw std::runtime_error("Error en la funcion de crear tarea.");
        out_file.close();
    }

}

// BORRAR TAREA
void Tarea::borrarTarea(){

    string linea, lineaBorrar, tarea;
    vector<string> vectTareas;
    ifstream archivo;
    bool encontrado = false;
    archivo.open("tareas.txt", ios::in);
    ofstream out("temp.txt");

    cout << "\n" << "Ahora, introduce la tarea que quieres borrar:" << "\n";
    cin >> lineaBorrar;
    
    if (archivo.fail()) {
        std::runtime_error ("tareas.txt no se pudo abrir.\n");
    }

    
    try{
        // Borramos la linea seleccionada
        while (getline(archivo, linea)){
            
            if (linea != lineaBorrar){
                 out << linea << endl;
            }
        }
        
    }catch(...){
        throw std::runtime_error("Error en la funcion de borrar tarea.");
        archivo.close();
        out.close();
    }

    // Pasamos temp.txt a tareas.txt
    archivo.close();
    out.close();
    remove("tareas.txt");
    rename("temp.txt","tareas.txt");

}

// MENU EDITAR TAREA
static int menuEditar(){

    int editar = 0;
    try{
            cout << "\n" << "Selecciona el dato que quieras editar:" << "\n";
            cout << "  1 - Prioridad" << "\n";
            cout << "  2 - Nombre tarea" << "\n";
            cout << "  3 - Encargado" << "\n";
            cout << "  4 - Hora" << "\n";
            cout << "  5 - Fecha" << "\n";
             
            cin >> editar;

            if(editar<6 && editar>0){
                cout << "Numero introducido correcto: " << editar << "\n";
            }else
                throw(editar);

    }catch(int editar){
        throw std::runtime_error("Numero incorrecto en el menu de edicion.");
        cout << "El numero introducido debe estar entre 1 y 5." << "\n";
    }
    return editar;
}

// EDITAR TAREA
void Tarea::editarTarea(int num){
    
    string linea, id,prio,nomT,nomU,h,f;
    ifstream archivo;
    archivo.open("tareas.txt", ios::in);
    if (archivo.fail()) {
        std::runtime_error ("tareas.txt no se pudo abrir.\n");
    }
    ofstream out("temp.txt");
    Tarea tarea;

    try{
        cout << "\n" << "Ahora, introduce la tarea que quieres editar:" << "\n";
        cin >> linea;
        switch(num){
        case 0:
            cout << "\n" << "*editar id*" << "\n";
            cout << "\n" << "Introduzca el nuevo id: " << "\n";
            cin >> id;

            cout << "\n" << "id editado" << "\n";

        break;
        case 1:
            cout << "\n" << "*editar prioridad*" << "\n";
            cout << "\n" << "Introduzca la nueva prioridad: " << "\n";
            cin >> prio;

            out << "\n" << "prioridad editada" << "\n";
        break;
        case 2:
            cout << "\n" << "*editar nombre Tarea*" << "\n";
            cout << "\n" << "Introduzca el nuevo nombre: " << "\n";
            cin >> nomT;
            
            out << "\n" << "nombre tarea editado" << "\n";
        break;
        case 3:
            cout << "\n" << "*editar nombre Encargado*" << "\n";
            cout << "\n" << "Introduzca el nuevo nombre: " << "\n";
            cin >> nomU;

            out << "\n" << "nombre encargado editado" << "\n";
        break;
        case 4:
            cout << "\n" << "*editar hora*" << "\n";
            cout << "\n" << "Introduzca la nueva hora: " << "\n";
            cin >> h;

            out << "\n" << "hora editada" << "\n";
        break;
        case 5:
            cout << "\n" << "*editar fecha*" << "\n";
            cout << "\n" << "Introduzca la nueva fecha: " << "\n";
            cin >> f;

            out << "\n" << "fecha editada" << "\n";
        break;
        }
    }catch(...){
        throw std::runtime_error("Error en la funcion de editar");
    }

    
}

// VER URGENTE
void Tarea::verUrgente(){

    cout << "\n" << "Esta es la lista de tareas mas urgentes actualmente:" << "\n\n";
    
    ifstream archivo;
    string texto,texto2,texto3,texto4,texto5;
    string uno = "P1", dos = "P2", tres = "P3", cuatro = "P4", cinco = "P5";
    bool b1 = false, b2 = false, b3 = false, b4 = false;
    
    try{
        archivo.open("tareas.txt", ios::in);
        if (archivo.fail()) {
            std::runtime_error ("tareas.txt no se pudo abrir.\n");
        }
    
        while(!archivo.eof()){
            getline(archivo,texto);
            replace(texto.begin(), texto.end(), ';', ' ');
            replace(texto.begin(), texto.end(), '_', ' ');

            // Bucle for que se dedica a ver si hay P1, sino P2, sino P3...
            // Si hay P1, las imprime, sino, guarda la línea de la Prio siguiente
            for(int i = 0; i<texto.length(); i++){
            
                if(texto[i] == uno[0] && texto[i+1] == uno[1]){
                    cout << texto << endl;
                    b1 = true;
                } 
                if(texto[i] == dos[0] && texto[i+1] == dos[1]){
                    texto2 = texto;
                    b2 = true;
                } 
                if(texto[i] == tres[0] && texto[i+1] == tres[1]){
                    texto3 = texto;
                    b3 = true;
                }
                if(texto[i] == cuatro[0] && texto[i+1] == cuatro[1]){
                    texto4 = texto;
                    b4 = true;
                }
                if(texto[i] == cinco[0] && texto[i+1] == cinco[1]){
                    texto5 = texto;
                }             
                
            }
        
        }

        // En el caso de que no exista ningún P1 y siguientes, imprime la linea previamente guardada
        if (b1 == false){
            cout << "No existe tarea de P1, la siguiente tarea es:" << "\n\n";
            cout << texto2 << "\n";
        }
        if (b1 == false && b2 == false){
            cout << "No existe tarea de P2, la siguiente tarea es:" << "\n\n";
            cout << texto3 << "\n";
        }
        if (b1 == false && b2 == false && b3 == false){
            cout << "No existe tarea de P3, la siguiente tarea es:" << "\n\n";
            cout << texto4 << "\n";
        }
        if (b1 == false && b2 == false && b3 == false && b4 == false){
            cout << "No existe tarea de P4, la siguiente tarea es:" << "\n\n";
            cout << texto5 << "\n";
        }
    }catch(...){
        throw std::runtime_error("Error en la funcion de ver tarea mas urgente.");
    }
    
    archivo.close();

}

// EXPORTAR CSV
void Tarea::exportarCSV(){

    ifstream archivo;
    string texto;

    try{
        archivo.open("tareas.txt", ios::in);
        ofstream out("tareas.csv");

        if (archivo.fail()) {
            std::runtime_error ("tareas.txt no se pudo abrir.\n");
        }else{
            cout << "Archivo exportado." << "\n";
        }
        
        while(!archivo.eof()){
            getline(archivo,texto);
            out << texto << endl;
        }
    }catch(...){
        throw std::runtime_error("Error en la funcion exportar a CSV.");
    }
}

// METODO AÑADIR LOG
void Tarea::anadirLog(string log){
   
    ofstream out_file;
    // Free Space
    time_t *rawtime = new time_t;
    struct tm *timeinfo;
    time(rawtime);
    timeinfo = localtime(rawtime);


    out_file.open("logTotal.txt", ios::app);
    if (out_file.fail()) {
        std::runtime_error ("logTotal.txt no se pudo abrir.\n");
    }
    out_file << log << " -- " << asctime(timeinfo);
    out_file.close();
    
    return;
}

// METODO VER LOG
void Tarea::verLog(){
    ifstream archivo;
    string texto;
    archivo.open("logTotal.txt", ios::in);

    if (archivo.fail()) {
        std::runtime_error ("logTotal.txt no se pudo abrir.\n");
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
        cout << "  6 - Exportar el archivo principal a CSV" << "\n";
        cout << "  7 - Ver log de la sesion actual" << "\n";
        cout << "  0 - Salir del programa" << "\n";
             
        cin >> opcion;
        return opcion;
}

int main(int argc, char *argv[]){

    string nombre;
    int opcion = 1, num = 0;
    Tarea tarea;
    string log = "0";

    cout << "   ---  Bienvenido al programa de Gestion de Tareas  ---   " << "\n\n";

    // Bucle para mantener activo el programa.
    while (opcion != 0) {

            // Mostramos el Menu principal y damos valor de opcion para el switch.
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
                    cout << "\n" << "**BORRAR UNA TAREA**" << "\n";
                    cout << "\n" << "    Esta es la lista de tareas actual:" << "\n\n";
                    tarea.verTareas();
                    tarea.borrarTarea();
                    log = "BORRAR UNA TAREA     ";
                    tarea.anadirLog(log);
                break;

                case 4:
                    cout << "\n" << "**EDITAR UNA TAREA**" << "\n";
                    cout << "\n" << "    Esta es la lista de tareas actual:" << "\n\n";
                    tarea.verTareas();
                    num = menuEditar();
                    tarea.editarTarea(num);
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
                    cout << "\n" << "**EXPORTAR A CSV**" << "\n";
                    tarea.exportarCSV();
                    log = "EXPORTAR A CSV       ";
                    tarea.anadirLog(log);
                break;

                case 7:
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