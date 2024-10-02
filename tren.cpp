#include <iostream>
#include <list>
#include <string>
#include <limits>
#include <algorithm>
#include <iterator>
bool volverMenuprincipal = false;

using namespace std;

struct Amenidad
{
    string nombre;
    int cantidad;
    Amenidad* siguiente;

    Amenidad(string nombre, int cantidad) : nombre(nombre), cantidad(cantidad), siguiente(nullptr) {}
};

struct Parada {
    int id;
    std::string nombre;
};

struct Vagon
{
    string nombre;
    Vagon* siguiente;
    Vagon* anterior;
    list<string> pasajeros;
    Amenidad* amenidades;

    Vagon(string nombre) : nombre(nombre), siguiente(nullptr), anterior(nullptr), amenidades(nullptr) {}


void agregarpasajero(string nombrepasajero) //agregamos pasajeros
    {
        pasajeros.push_back(nombrepasajero);
        cout<<"El pasajero: "<<nombrepasajero<<" fue agregado al vagon: "<<nombre<<" correctamente"<<endl;
    }


void mostrarpasajeros() //nos muestra los pasajeros en el vagon
    {
        if (pasajeros.empty())
        {
            cout<<"No hay pasajeros en el vagon: "<<nombre<<endl;
            return;
        }
        cout<<"Pasajeros en el vagon: "<<nombre<<endl;
        for(const auto& pasajero:pasajeros)
        {
            cout<<"- "<<pasajero<<endl;
        }
    }

void eliminarpasajero(string nombrepasajero) //con esta funcion eliminamos pasajeros
    {
        pasajeros.remove(nombrepasajero);
        cout<<"El pasajero: "<<nombrepasajero<<" fue correctamente eliminado de el vagon: "<<nombre<<endl;
    };


void agregarAmenidad(Vagon* actual, string nombre, int cantidad) { //aquí vamos a agregar amenidades
        Amenidad* nuevaAmenidad = new Amenidad(nombre, cantidad);

        if (actual->amenidades == nullptr) // si la amanidad es igual a null va a hacer igual a amanidad nueva
        {
            actual->amenidades = nuevaAmenidad;
            actual->amenidades->siguiente = actual->amenidades;
        } else
        {
            Amenidad* temp = actual->amenidades; //si ya tiene amanidades lo agrega al final de la lista
            while (temp->siguiente != actual->amenidades) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevaAmenidad;
            nuevaAmenidad->siguiente = actual->amenidades;
        }

        cout << "Amenidad '" << nombre << "' agregada al vagon actual." << endl;
    }


void mostrarAmenidades(Vagon* actual) //muestra la amenidad actual
    {
        if (actual->amenidades == nullptr) //se fija si hay algo si esta vacio tira el mensaje de que no hay amanidades.
        {
            cout << "No hay amenidades en este vagon." << endl;
            return;
        }
        Amenidad* actualAmenidad = actual->amenidades; //Aqui el puntero avanza al siguiente nodo en la lista
        do
        {
            cout << "Nombre: " << actualAmenidad->nombre << ", Cantidad: " << actualAmenidad->cantidad << endl;
            actualAmenidad = actualAmenidad->siguiente;
        } while (actualAmenidad != actual->amenidades);
    }


void eliminarAmenidad(string nombre) { //aquí vamos a eliminar amanodades
        if (amenidades == nullptr) //si es igaul a nulo pone qye no hay amanidades
        {
            cout << "No hay amenidades en este vagon." << endl;
            return;
        }

        Amenidad* temp = amenidades;
        Amenidad* anterior = nullptr;// se recorre la lista para ver si esta esa amenidad
        bool encontrado = false;
        do {
            if (temp->nombre == nombre)
            {
                encontrado = true;
                break;
            }
            anterior = temp;
            temp = temp->siguiente;
        } while (temp != amenidades);

        if (!encontrado) //aqui es para decir si hay amanidades, si no hay manda el mensaje
        {
            cout << "La amenidad '" << nombre << "' no se encontro en este vagon." << endl;
            return;
        }

        if (temp == amenidades && temp->siguiente == amenidades) // si la amenidad es la unica en la lista se elimina el nodo y el vagón queda sin amanidades
        {
            delete amenidades;
            amenidades = nullptr;
        } else if (temp == amenidades)
         {
            Amenidad* ultimo = amenidades; //aquí la amenidad es la primera de la lista entonces se elimina, se busca el ultimo nodo y se conesta con el que le 
            while (ultimo->siguiente != amenidades) {// seguia al que eliminamos 
                ultimo = ultimo->siguiente;
            }
            amenidades = amenidades->siguiente;
            ultimo->siguiente = amenidades;
            delete temp;
        } else 
        {
            anterior->siguiente = temp->siguiente;//la amenidad esta en madio solo se elimina no hay que ajustar nada como el caso anterior
            delete temp;
        }
    }



void modificarAmenidad() { //modificar amenidades 
        if (amenidades == nullptr) // nos hay amanidades 
        {
            cout << "No hay amenidades en este vagon." << endl;
            return;
        }

        string nombre_amenidad;
        cout << "Ingrese el nombre de la amenidad que desea modificar: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nombre_amenidad);

        Amenidad* actual = amenidades;

        do {
            if (actual->nombre == nombre_amenidad)
            {
                int opcion_modificar;
                cout << "Que desea modificar en la amenidad '" << nombre_amenidad << "'?" << endl;
                cout << "1 : Nombre de la Amenidad"<<endl;
                cout << "2 : Cantidad de la Amenidad"<<endl;;
                cout << "Ingrese una opcion: ";
                cin >> opcion_modificar;
                while (cin.fail() || (opcion_modificar < 1 || opcion_modificar > 2))
                {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Opcion no valida. Intente de nuevo: ";
                    cin >> opcion_modificar;
                }

                switch (opcion_modificar) { //aquí vamos a modificar el nombfre de la amanidad
                    case 1: {
                        string nuevoNombre;
                        cout << "Ingrese el nuevo nombre de la amenidad: ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, nuevoNombre);
                        actual->nombre = nuevoNombre;
                        cout << "Nombre de la amenidad modificado correctamente." << endl;
                        break;
                    }
                    case 2: {
                        int nuevaCantidad; //aquí vamos a madificar la cantidad e la amanidad
                        cout << "Ingrese la nueva cantidad de la amenidad: ";
                        cin >> nuevaCantidad;
                        actual->cantidad = nuevaCantidad; 
                        cout << "Cantidad de la amenidad modificada correctamente." << endl;
                        break;
                    }
                    default:
                        cout << "Opcion no valida." << endl;
                        break;
                }
                return;
            }
            actual = actual->siguiente;
        } while (actual != amenidades); 

        cout << "La amenidad '" << nombre_amenidad << "' no se encontro en este vagon." << endl;
    }
};

void agregarVagon(Vagon*& cabeza, const string& nombreNuevoVagon, Vagon*& vagonactual) { //agregamos un vagón
    Vagon* nuevoVagon = new Vagon(nombreNuevoVagon);

    nuevoVagon->anterior = nullptr;


    if (cabeza == nullptr) //si la lista esta vacía, el vagon que añadimos va a hacer el primero
    {
        cabeza = nuevoVagon;
        vagonactual = cabeza;
        cout << "Vagon '" << nombreNuevoVagon << "' agregado correctamente como el primer vagon." << endl;
        return;
    }


    nuevoVagon->siguiente = vagonactual->siguiente;
    if (vagonactual->siguiente != nullptr) //aqui la lista tiene algo, por lo que el vagon que estamos añadiendo va después del que existe
    {
        vagonactual->siguiente->anterior = nuevoVagon;
    }
    vagonactual->siguiente = nuevoVagon;
    nuevoVagon->anterior = vagonactual;

    cout << "Vagon '" << nombreNuevoVagon << "' agregado correctamente despues de "<< vagonactual->nombre << "." << endl;
}


void eliminarVagon(Vagon*& cabeza, Vagon*& vagonActual) { //para eleminar el vagon 
    if (cabeza == nullptr)  //la lista esta vacia
    {
        cout << "No hay vagones en el tren." << endl;
        return;
    }
    
    Vagon* vagonAEliminar = vagonActual; //la lista tiene elementos y queremos eliminar el vagon aactual
    if (vagonActual->siguiente != nullptr)
    {
        vagonActual = vagonActual->siguiente;
    } else
    {
        vagonActual = vagonActual->anterior;
    }
    

    if (cabeza == vagonAEliminar) //estamos eliminando el primer vagon por lo que que ajustamos el nodo anteiror 
    { //para que quede viendo al siguiente del que estamos eliminando
        cabeza = cabeza->siguiente;

        if (cabeza != nullptr)
        {
            cabeza->anterior = nullptr;
        }
    } else //el vagon a eliminar no es la cabeza por lo que se hacen los ajustes necesarios para quitar el vagon y unir los demás
    {
        vagonAEliminar->anterior->siguiente = vagonAEliminar->siguiente;
        if (vagonAEliminar->siguiente != nullptr)
         {
            vagonAEliminar->siguiente->anterior = vagonAEliminar->anterior;
        }
    }


    if (vagonActual == nullptr) {
        cout << "Todos los vagones han sido eliminados." << endl;
    }


    delete vagonAEliminar;

    cout << "El vagon actual ha sido eliminado de el tren." << endl;
}


void modificarVagon(Vagon*& cabeza, Vagon*& vagonActual) { //modificamos el vagon en el que estamos
    if (cabeza == nullptr) // la lista esta vacia
    {
        cout << "No existen vagones en el tren" << endl;
        return;
    }

    if (vagonActual == nullptr)
     {
        cout << "El vagon no tiene definicion." << endl;
        return;
    }

    cout << "Informacion del vagon actual:" << endl;
    cout << "Nombre de el vagon: " << vagonActual->nombre << endl;

    string nuevoNombre;
    cout << "Ingrese un nuevo nombre para el vagon '" << vagonActual->nombre << "': ";
    cin >> nuevoNombre;

    vagonActual->nombre = nuevoNombre;

    cout << "Nombre de el vagon '" << vagonActual->nombre << "' modificado correctamente." << endl;
}

int verVagones(Vagon* cabeza) { //aqui es para ver los vagones que tenemos creados
    if (cabeza == nullptr) 
    {
        cout << "No hay vagones en el tren." << endl;
        return 0;
    }

    Vagon* temp = cabeza;
    cout << "Vagones en el tren:" << endl;
    while (temp != nullptr) {
        cout << temp->nombre;
        if (temp->siguiente != nullptr) {
            cout << " <-> ";
        }
        temp = temp->siguiente;
    }
    cout << endl;
    return 1;
}




void LimpiarPantalla() { //limpia la panatalla 
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Linux o macOS
    #endif
}

void editarEnVagon(Vagon*& cabeza, Vagon* vagonactual) { //editamos los vagaones 
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n-+-+-+-+-+-+ Menu de Edicion +-+-+-+-+-+-+-+-\n";
        cout << "1. Pasajeros\n";
        cout << "2. Amenidades\n";
        cout << "3. Vagones\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            // Submenu para pasajeros
            int subopcion = -1;
            while (subopcion != 0) {
                cout << "\n--- Gestion de Pasajeros ---\n";
                cout << "1. Agregar pasajero\n"; 
                cout << "2. Eliminar pasajero\n";
                cout << "3. Mostrar pasajeros\n";
                cout << "0. Volver\n";
                cout << "Opcion: ";
                cin >> subopcion;

                switch (subopcion) {
                case 1: {
                    string nombrePasajero;
                    vagonactual->mostrarpasajeros();
                    cout << "Ingrese el nombre del pasajero: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nombrePasajero);
                    LimpiarPantalla();
                    vagonactual->agregarpasajero(nombrePasajero);
                    break;
                }
                case 2: {
                    string nombrePasajero;
                    vagonactual->mostrarpasajeros();
                    cout << "Ingrese el nombre del pasajero a eliminar: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nombrePasajero);
                    LimpiarPantalla();
                    vagonactual->eliminarpasajero(nombrePasajero);
                    break;
                }
                case 3:
                    LimpiarPantalla();
                    vagonactual->mostrarpasajeros();
                    break;
                default:
                    if(subopcion != 0){
                        LimpiarPantalla();
                        cout << "Opcion no valida." << endl;
                    }
                    break;
                }
            }
            break;
        }
        case 2: {
            // Submenu para amenidades
            int subopcionA=-1;
            while (subopcionA != 0) {
                cout << "\n--- Gestion de Amenidades ---\n";
                cout << "1. Agregar amenidad\n";
                cout << "2. Eliminar amenidad\n";
                cout << "3. Mostrar amenidades\n";
                cout << "4. Modificar amenidad\n";
                cout << "0. Volver\n";
                cout << "Opcion: ";
                cin >> subopcionA;

                switch (subopcionA) {
                case 1: {
                    string nombreAmenidad;
                    int cantidad;
                    cout << "Ingrese el nombre de la amenidad: ";
                    vagonactual->mostrarAmenidades(vagonactual);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nombreAmenidad);
                    cout << "Ingrese la cantidad: ";
                    cin >> cantidad;
                    LimpiarPantalla();
                    vagonactual->agregarAmenidad(vagonactual, nombreAmenidad, cantidad);
                    break;
                }
                case 2: {
                    string nombreAmenidad;
                    vagonactual->mostrarAmenidades(vagonactual);
                    cout << "Ingrese el nombre de la amenidad a eliminar: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nombreAmenidad);
                    LimpiarPantalla();
                    vagonactual->eliminarAmenidad(nombreAmenidad);
                    break;
                }
                case 3:
                    LimpiarPantalla();
                    vagonactual->mostrarAmenidades(vagonactual);
                    break;
                case 4:
                    LimpiarPantalla();
                    vagonactual->modificarAmenidad();
                    break;
                default:
                    if (subopcionA != 0){
                        LimpiarPantalla();
                        cout << "Opcion no valida." << endl;
                    }
                    break;
                }
            }
            break;
        }
        case 3: {

            int subopcionv=-1;
            while (subopcionv != 0) {
                cout << "\n--- Gestion de Vagones ---\n";
                cout << "1. Agregar vagon\n";
                cout << "2. Eliminar vagon\n";
                cout << "3. Mostrar vagones\n";
                cout << "4. Modificar vagones\n";
                cout << "0. Volver\n";
                cout << "Opcion: ";
                cin >> subopcionv;
                string nuevoNombre;

                switch (subopcionv) {
                case 1: {
                    string nombreAmenidad;
                    int cantidad;
                    cout << "Ingrese el nombre de la amenidad: ";
                    vagonactual->mostrarAmenidades(vagonactual);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nombreAmenidad);
                    cout << "Ingrese la cantidad: ";
                    cin >> cantidad;
                    LimpiarPantalla();
                    vagonactual->agregarAmenidad(vagonactual, nombreAmenidad, cantidad);
                    break;
                }
                case 2: {
                    string nombreAmenidad;
                    verVagones(vagonactual);
                    cout << "Ingrese el nombre del vagon a eliminar: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nombreAmenidad);
                    LimpiarPantalla();
                    eliminarVagon(cabeza, vagonactual);
                    break;
                }
                case 3:
                    LimpiarPantalla();
                    verVagones(vagonactual);
                    break;
                case 4:
                    cout << "Ingrese el nuevo nombre del vagon: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, nuevoNombre);
                    vagonactual->nombre = nuevoNombre;
                    LimpiarPantalla();
                    cout << "Nombre del vagon "<<nuevoNombre<<" modificado correctamente." << endl;
                    break;
                default:
                    if (subopcionv != 0){
                        LimpiarPantalla();
                        cout << "Opcion no valida." << endl;
                    }
                    break;
                }
            }
            break;

            
        }
        case 0:
            LimpiarPantalla();
            cout << "Saliendo de la edicion del vagon." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            break;
        }
    }
}

//Función para contabilizar la cantidad total de pasajeros en el tren
void numtotal_pasajeros(Vagon* cabeza) {
    if (cabeza == nullptr) { // la lsita esta vacia
        cout << "No hay pasajeros en el tren." << endl;
        return;
    }

    int total_pasajeros = 0;
    Vagon* temp = cabeza;
    while (temp != nullptr) {
        total_pasajeros += temp->pasajeros.size();
        temp = temp->siguiente;
    }

    cout << "Total de pasajeros en el Tren: " << total_pasajeros << endl;
}

//Funcion para encontrar el vagon con mas pasajeros
void vagon_maximo_pasajeros(Vagon* cabeza) {
    list<string> vagonesmax; // Crea una lista que almacena el vagon con mas pasajeros
    if (cabeza == nullptr) // En caso de que no hayan vagones en el tren
    {
        cout << "No hay pasajeros en el tren." << endl;
        return;
    }
    Vagon* temp = cabeza;
    int maxpasajeros = temp->pasajeros.size();
    vagonesmax.push_back(temp->nombre); // añade el primer vagon a la lista

    temp = temp->siguiente;
    while (temp != nullptr) {
        if (temp->pasajeros.size() > maxpasajeros) //Caso en el que se encuentra el número máximo de pasajeros
        {
            maxpasajeros = temp->pasajeros.size();
            vagonesmax.clear(); // Borrar la lista de vagones con más pasajeros
            vagonesmax.push_back(temp->nombre); // añade el nuevo vagon a la lista
        } else if (temp->pasajeros.size() == maxpasajeros) // Caso en el que el vagón tiene el mismo número máximo de pasajeros
        {
            vagonesmax.push_back(temp->nombre); // añade el vagon a la lista
        }
        temp = temp->siguiente;
    }
    if (vagonesmax.empty()) // caso en el que no hay pasajeros en el tren
    {
        cout << "No hay pasajeros en el tren." << endl;
        return;
    }
    for (list<string>::iterator x = vagonesmax.begin(); x != vagonesmax.end(); ++x) // Se crea un iterador para recorrer la lista de vagones y encontrar el que tiene más pasajeros
     {
        cout << "El vagon con mas pasajeros es el: " << *x << endl;
    }

    return;
}

// Función para mostrar el reporte de comodidades por tipo
void reporteamenidadesportipo(Vagon* cabeza) {
    if (cabeza == nullptr) // Caso en el que no hay vagones en el tren
    {
        cout << "No hay vagones en el tren." << endl;
        return;
    }

    list<string> amenidades; // Crea una lista para almacenar las comodidades.
    Vagon* temp = cabeza;
    while (temp != nullptr) {
        Amenidad* amenidadTemp = temp->amenidades;
        if (amenidadTemp == nullptr) // Caso en el que no hay comodidades en el vagón
        {
            temp = temp->siguiente;
            continue;
        }
        do {
            if (find(amenidades.begin(), amenidades.end(), amenidadTemp->nombre) == amenidades.end()) //Agrega el servicio a la lista si aún no está en ella.
            {
                amenidades.push_back(amenidadTemp->nombre);
            }
            amenidadTemp = amenidadTemp->siguiente;
        } while (amenidadTemp != temp->amenidades);
        temp = temp->siguiente;
    }
    if (amenidades.empty()) // Caso en el que no hay comodidades en el tren
    {
        cout << "No hay amenidades en el tren." << endl;
        return;
    }

    int numAmenidades = amenidades.size();
    string matriz_amenidades[numAmenidades][2]; // Crea una matriz para almacenar las comodidades y su total.

    temp = cabeza;
    while (temp != nullptr) {
        Amenidad* amenidadTemp = temp->amenidades;
        if (amenidadTemp == nullptr) // Caso en el que no hay comodidades en el vagón
        {
            temp = temp->siguiente;
            continue;
        }
        do {
            for (int i = 0; i < numAmenidades; ++i) {
                if (matriz_amenidades[i][0] == amenidadTemp->nombre) // Aumenta el total de la amenidad si ya está en la matriz.
                {
                matriz_amenidades[i][1] = to_string(stoi(matriz_amenidades[i][1]) + amenidadTemp->cantidad); // to_string convierte el número entero en una cadena y stoi convierte la cadena en un número entero
                break;
             }
            else if (matriz_amenidades[i][0].empty()) // Agrega el servicio a la matriz si aún no está en ella.
            {
                matriz_amenidades[i][0] = amenidadTemp->nombre;
                matriz_amenidades[i][1] = to_string(amenidadTemp->cantidad); // to_string convierte el número entero en una cadena
                break;
            }
}
            amenidadTemp = amenidadTemp->siguiente;
        } while (amenidadTemp != temp->amenidades);
        temp = temp->siguiente;
    }

    cout << "Amenidades disponibles en el tren: " << endl;
    int y = 1;
    for (list<string>::iterator x = amenidades.begin(); x != amenidades.end(); ++x) // Se crea un iterador para recorrer la lista de servicios.
    {
        cout << y << " : " << *x << endl; // Muestra las comodidades en el tren.
        y++;
    }

    cout << "Seleccione una amenidad para obtener el total en todos los vagones: ";
    int opcion_amenidad;
    cin >> opcion_amenidad;

    while (cin.fail() || (opcion_amenidad < 1 || opcion_amenidad > numAmenidades)) // Validación de la opción, debe ser un número entero entre 1 y el número de comodidades
    {
        cin.clear(); // Borrar el error de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar la entrada incorrecta
        cout << "Opcion no valida. Intente de nuevo: ";
        cin >> opcion_amenidad;
    }
    cout << "Calculando total de " << matriz_amenidades[opcion_amenidad - 1][0] << " en todos los vagones..." << endl;


    temp = cabeza;
    while (temp != nullptr) {
        cout << "Vagon " << temp->nombre << ": ";
        Amenidad* amenidadTemp = temp->amenidades;
        if (amenidadTemp == nullptr) // Caso en el que no hay comodidades en el vagón
        {
            cout << "0 " << matriz_amenidades[opcion_amenidad - 1][0] << endl; // Imprime 0 si no hay servicios en el vagón
            temp = temp->siguiente;
            continue;
        }
        bool amenidadEncontrada = false; // Variable para comprobar si el servicio está en el vagón.
        do {
            if (amenidadTemp->nombre == matriz_amenidades[opcion_amenidad - 1][0]) // Muestra la amenidad y su total si está en el vagón.
            {
                cout << amenidadTemp->cantidad << " " << amenidadTemp->nombre << endl;
                amenidadEncontrada = true;// Cambia el valor del bool si se encuentra la amenidad.
            }
            amenidadTemp = amenidadTemp->siguiente;
        } while (amenidadTemp != temp->amenidades);
        if (!amenidadEncontrada) // Imprime 0 si el servicio no está en el vagón
        {
            cout << "0 " << matriz_amenidades[opcion_amenidad - 1][0] << endl;
    }
    temp = temp->siguiente;
}

    cout << "El total de la amenidad " << matriz_amenidades[opcion_amenidad - 1][0] << " en el tren: " << matriz_amenidades[opcion_amenidad - 1][1] << endl; // Muestra el total de las comodidades en el tren.
}

// Funcion para la cantidad de pasajeros por vagon
void pasajeros_por_vagon(Vagon* cabeza) {
    if (cabeza == nullptr) { //la funcion esta vacia
        cout << "No hay pasajeros en el tren." << endl;
        return;
    }

    Vagon* temp = cabeza; 
    while (temp != nullptr) { //recorrido para mostrar los pasajeros por vagón
        cout << "Vagon " << temp->nombre << ": " << temp->pasajeros.size() << " pasajeros" << endl;
        temp = temp->siguiente;
    }
    int total_pasajeros = 0; // calcula el total de pasajeros
    Vagon* temp2 = cabeza;
    while (temp2 != nullptr) {
        total_pasajeros += temp2->pasajeros.size();
        temp2 = temp2->siguiente;
    }
    cout << "Total de pasajeros en el Tren: " << total_pasajeros << endl;
}

void Menu_de_reportes(Vagon*& cabeza, Vagon*& vagonActual) {
    /*if (vagonActual == nullptr) // Case in which the current wagon is not specified
    {
        cout << "No se ha seleccionado ningún vagón actual." << endl;
        return;
    }*/

    int opcion_reportes;
    do {
        cout << "Menu de Reportes" << endl;
        cout << "1 : Reporte de amenidades totales por tipo" << endl;
        cout << "2 : Numero total de pasajeros" << endl;
        cout << "3 : Vagon con mas pasajeros" << endl;
        cout << "4 : Distribucion de pasajeros por vagon" << endl;
        cout << "5 : Volver al menu principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion_reportes;
        while (cin.fail() || (opcion_reportes < 1 || opcion_reportes > 5)) // Validación de la opción, debe ser un número entero entre 1 y 5
         {
            cin.clear(); // Borrar el error de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar la entrada incorrecta
            cout << "Opcion no valida. Intente de nuevo: ";
            cin >> opcion_reportes;
        }

        switch (opcion_reportes) {
            case 1: {
                cout << "Reporte de amenidades totales por tipo" << endl;
                reporteamenidadesportipo(cabeza); // Llama a la función para mostrar el reporte de comodidades por tipo
                break;
            }
            case 2: {
                cout << "------Reporte de Numero total de pasajeros------" << endl;
                numtotal_pasajeros(cabeza); // Llama a la función para mostrar el reporte del número total de pasajeros.
                break;
            }
            case 3: {
                cout << "------Reporte de vagon con mas pasajeros------" << endl;
                vagon_maximo_pasajeros(cabeza); // Llama a la función para mostrar el reporte del vagón con más pasajeros
                break;
            }
            case 4: {
                cout << "------Reporte de distribucion de pasajeros------" << endl;
                pasajeros_por_vagon(cabeza); // Llama a la función para mostrar el informe de la distribución de pasajeros.
                break;
            }
            case 5: {
                cout << "Volviendo al menu principal" << endl;
                break; //Salir al menú principal
            }
            default: {
                cout << "Opcion no valida" << endl;
                break;
            }
        }
    } while (opcion_reportes != 5); // Realiza un bucle mientras la opción sea diferente de 5.
}




void menu(Vagon* cabeza, Vagon*& vagonactual) {
    int opcion = -1;
    Vagon* vagonActual = nullptr;
    while (opcion != 0) {
        cout << "\n-+-+-+-+-+-+ Menu General +-+-+-+-+-+-+-+-\n";
        cout << "1. Administracion de informacion\n";
        cout << "2. Generacion de reportes\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            LimpiarPantalla();
            int hay = verVagones(cabeza);
            if (hay == 0) {
                string opc;
                cout << "\n¿Deseas agregar un vagon? (si/no)\n";
                cin >> opc;
                if (opc == "si") {
                    string nombre;
                    cout << "Inserte el nombre del vagon: ";
                    cin >> nombre;
                    LimpiarPantalla();
                    agregarVagon(cabeza, nombre, vagonactual);
                } else {
                    break;
                }
            } else {
                cout << "Elija que vagon quiere editar: ";
                string nombreVagon;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, nombreVagon);

                Vagon* temp = cabeza;
                while (temp != nullptr && temp->nombre != nombreVagon) {
                    temp = temp->siguiente;
                }

                if (temp != nullptr) {
                    vagonactual = temp;
                    editarEnVagon(cabeza,vagonactual);
                } else {
                    cout << "Vagon no encontrado." << endl;
                }
            }
            break;
        }
        case 2:
            LimpiarPantalla();
            Menu_de_reportes(cabeza, vagonActual);
            break;
        case 0:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            break;
        }
    }
}

int main() {
    Vagon* cabeza = nullptr;
    Vagon* vagonactual = nullptr;
    menu(cabeza, vagonactual);
    return 0;
}
