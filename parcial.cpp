#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct libro {
    char titulo[50];
    char autor[50];
    int añodepublicacion;
    char editorial[50];
    char isbn[20];
    int numerodepaginas;
    libro *siguiente;
};


void guardarEnArchivo(libro *lista, const char *biblioteca);
void agregarLibro(libro *&lista);
void eliminarLibro(libro *&lista);
void buscarLibroPorTitulo(libro *lista);


void buscarLibroPorTitulo(libro *lista) {
    if (lista == nullptr) {
        cout << "La lista de libros esta vacia." << endl;
        return;
    }

    char titulo[50];
    cout << "Ingrese el titulo del libro que desea encontrar: ";
    cin.ignore(); 
    cin.getline(titulo, 50);

    bool encontrado = false;
    libro *actual = lista;

    while (actual != nullptr) {
        if (strstr(actual->titulo, titulo) != nullptr) { 
            cout << "\nTitulo: " << actual->titulo << endl;
            cout << "Autor: " << actual->autor << endl;
            cout << "Año de publicacion: " << actual->añodepublicacion << endl;
            cout << "Editorial: " << actual->editorial << endl;
            cout << "ISBN: " << actual->isbn << endl;
            cout << "Numero de paginas: " << actual->numerodepaginas << endl;
            cout << "----------------------" << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontraron libros con el titulo especificado." << endl;
    }
}

void agregarLibro(libro *&lista) {
    libro *nuevo = new libro;

    cout << "Ingrese el titulo del libro: ";
    cin.ignore();
    cin.getline(nuevo->titulo, 50);
    
    cout << "Ingrese el nombre del autor: ";
    cin.getline(nuevo->autor, 50);
    
    cout << "Ingrese el año de publicacion: ";
    cin >> nuevo->añodepublicacion;
    cin.ignore();

    cout << "Ingrese la editorial: ";
    cin.getline(nuevo->editorial, 50);

    cout << "Ingrese el codigo ISBN: ";
    cin.getline(nuevo->isbn, 20);

    cout << "Ingrese el numero de paginas: ";
    cin >> nuevo->numerodepaginas;
    cin.ignore();

    nuevo->siguiente = lista; 
    lista = nuevo;

    cout << "Libro agregado a la lista correctamente." << endl;
    //guardarEnArchivo(lista, "libros.txt");
}

void eliminarLibro(libro *&lista) {
    if (lista == nullptr) {
        cout << "La lista de libros esta vacia." << endl;
        return;
    }

    char titulo[50];
    cout << "Ingrese el titulo del libro que desea eliminar: ";
    cin.ignore();
    cin.getline(titulo, 50);

    libro *actual = lista;
    libro *anterior = nullptr;

    while (actual != nullptr && strcmp(actual->titulo, titulo) != 0) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        cout << "No se ha encontrado dicho libro." << endl;
        return;
    }

    if (anterior == nullptr) {
        lista = actual->siguiente; 
    } else {
        anterior->siguiente = actual->siguiente; 
    }

    delete actual; 
    cout << "Libro eliminado de la lista correctamente." << endl;
    guardarEnArchivo(lista, "biblioteca.txt");
}

void guardarEnArchivo(libro *lista, const char *biblioteca) {
    ofstream archivo(biblioteca);

    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    libro *actual = lista;
    while (actual != nullptr) {
        archivo << actual->titulo << endl;
        archivo << actual->autor << endl;
        archivo << actual->añodepublicacion << endl;
        archivo << actual->editorial << endl;
        archivo << actual->isbn << endl;
        archivo << actual->numerodepaginas << endl;
        actual = actual->siguiente;
    }

    archivo.close();
    cout << "Libros guardados en " << biblioteca << " correctamente." << endl;
}

void cargarDesdeArchivo(libro *&lista, const char *biblioteca) {
    ifstream archivo(biblioteca);

    if (!archivo) {
        cout << "No se pudo abrir el archivo para cargar los libros." << endl;
        return;
    }

    while (!archivo.eof()) {
        libro *nuevo = new libro;
        archivo.getline(nuevo->titulo, 50);
        archivo.getline(nuevo->autor, 50);
        archivo >> nuevo->añodepublicacion;
        archivo.ignore(); 
        archivo.getline(nuevo->editorial, 50);
        archivo.getline(nuevo->isbn, 20);
        archivo >> nuevo->numerodepaginas;
        archivo.ignore(); 
        
        nuevo->siguiente = lista;
        lista = nuevo;
    }

    archivo.close();
    cout << "Libros cargados desde " << biblioteca << " correctamente." << endl;
}

int main() {
    libro *lista = nullptr;
    cargarDesdeArchivo(lista, "biblioteca.txt");

    int opcion;
    do {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Agregar libro" << endl;
        cout << "2. Eliminar libro" << endl;
        cout << "3. Buscar libro por titulo" << endl;
        cout << "4. Salir del programa" << endl;
        cout << "Ingrese una de las opciones: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                agregarLibro(lista);
                break;
            case 2:
                eliminarLibro(lista);
                break;
            case 3:
                buscarLibroPorTitulo(lista);
                break;
            case 4: 
                break;
            default:
                cout << "La opcion que ha seleccionado es invalida. Por favor intentelo denuevo" << endl;
        }
    } while (opcion != 4);

    guardarEnArchivo(lista, "biblioteca.txt"); 
    return 0;
}