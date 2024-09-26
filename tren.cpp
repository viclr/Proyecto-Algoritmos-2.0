#include <iostream>
#include <list>
#include <string>
bool volverMenuprincipal = false;

using namespace std;

struct Amenidad
{
    string nombre;
    int cantidad;
    Amenidad* siguiente;

    Amenidad(string nombre, int cantidad) : nombre(nombre), cantidad(cantidad), siguiente(nullptr) {}
};


struct Vagon
{
    string nombre;
    Vagon* siguiente;
    Vagon* anterior;
    list<string> pasajeros;
    Amenidad* amenidades;

    Vagon(string nombre) : nombre(nombre), siguiente(nullptr), anterior(nullptr), amenidades(nullptr) {}


void agregarpasajero(string nombrepasajero)
    {
        pasajeros.push_back(nombrepasajero);
        cout<<"El pasajero: "<<nombrepasajero<<" fue agregado al vagon: "<<nombre<<" correctamente"<<endl;
    }


void mostrarpasajeros()
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

void eliminarpasajero(string nombrepasajero)
    {
        pasajeros.remove(nombrepasajero);
        cout<<"El pasajero: "<<nombrepasajero<<" fue correctamente eliminado de el vagon: "<<nombre<<endl;
    };


void agregarAmenidad(Vagon* actual, string nombre, int cantidad) {
        Amenidad* nuevaAmenidad = new Amenidad(nombre, cantidad);

        if (actual->amenidades == nullptr)
        {
            actual->amenidades = nuevaAmenidad;
            actual->amenidades->siguiente = actual->amenidades;
        } else
        {
            Amenidad* temp = actual->amenidades;
            while (temp->siguiente != actual->amenidades) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevaAmenidad;
            nuevaAmenidad->siguiente = actual->amenidades;
        }

        cout << "Amenidad '" << nombre << "' agregada al vagon actual." << endl;
    }


void mostrarAmenidades(Vagon* actual)
    {
        if (actual->amenidades == nullptr)
        {
            cout << "No hay amenidades en este vagon." << endl;
            return;
        }
        Amenidad* actualAmenidad = actual->amenidades;
        do
        {
            cout << "Nombre: " << actualAmenidad->nombre << ", Cantidad: " << actualAmenidad->cantidad << endl;
            actualAmenidad = actualAmenidad->siguiente;
        } while (actualAmenidad != actual->amenidades);
    }


void eliminarAmenidad(string nombre) {
        if (amenidades == nullptr)
        {
            cout << "No hay amenidades en este vagon." << endl;
            return;
        }

        Amenidad* temp = amenidades;
        Amenidad* anterior = nullptr;
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

        if (!encontrado)
        {
            cout << "La amenidad '" << nombre << "' no se encontro en este vagon." << endl;
            return;
        }

        if (temp == amenidades && temp->siguiente == amenidades)
        {
            delete amenidades;
            amenidades = nullptr;
        } else if (temp == amenidades)
         {
            Amenidad* ultimo = amenidades;
            while (ultimo->siguiente != amenidades) {
                ultimo = ultimo->siguiente;
            }
            amenidades = amenidades->siguiente;
            ultimo->siguiente = amenidades;
            delete temp;
        } else
        {
            anterior->siguiente = temp->siguiente;
            delete temp;
        }
    }



void modificarAmenidad() {
        if (amenidades == nullptr)
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

                switch (opcion_modificar) {
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
                        int nuevaCantidad;
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

void agregarVagon(Vagon*& cabeza, const string& nombreNuevoVagon, Vagon*& vagonactual) {
    Vagon* nuevoVagon = new Vagon(nombreNuevoVagon);

    nuevoVagon->anterior = nullptr;


    if (cabeza == nullptr) 
    {
        cabeza = nuevoVagon;
        vagonactual = cabeza;
        cout << "Vagon '" << nombreNuevoVagon << "' agregado correctamente como el primer vagon." << endl;
        return;
    }


    nuevoVagon->siguiente = vagonactual->siguiente;
    if (vagonactual->siguiente != nullptr) 
    {
        vagonactual->siguiente->anterior = nuevoVagon;
    }
    vagonactual->siguiente = nuevoVagon;
    nuevoVagon->anterior = vagonactual;

    cout << "Vagon '" << nombreNuevoVagon << "' agregado correctamente despues de "<< vagonactual->nombre << "." << endl;
}


void eliminarVagon(Vagon*& cabeza, Vagon*& vagonActual) {
    if (cabeza == nullptr) 
    {
        cout << "No hay vagones en el tren." << endl;
        return;
    }
    
    Vagon* vagonAEliminar = vagonActual;
    if (vagonActual->siguiente != nullptr)
    {
        vagonActual = vagonActual->siguiente;
    } else
    {
        vagonActual = vagonActual->anterior;
    }
    

    if (cabeza == vagonAEliminar)
    {
        cabeza = cabeza->siguiente;

        if (cabeza != nullptr)
        {
            cabeza->anterior = nullptr;
        }
    } else
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


void modificarVagon(Vagon*& cabeza, Vagon*& vagonActual) {
    if (cabeza == nullptr) 
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

void verVagones(Vagon* cabeza) {
    if (cabeza == nullptr) 
    {
        cout << "No hay vagones en el tren." << endl;
        return;
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
}

//Aquí estoy intentado hacer el menú de todas las cosas//
void Menu_para_administrar_informacion(//aquí hay que llamas a las listas correspondiendtes)
{
    int opcion = 0;
    while (opcion != 6)
    {
        cout << "\n-+-+-+-+-+-+ Menu del tren +-+-+-+-+-+-+-+-\n";
        cout << "1: Detalles de los pasajeros.\n";
        cout << "2: Detalles de los vagones.\n";
        cout << "3: Detalles de las estaciones.\n";
        cout << "4: Detalles de las amenidades.\n";
        cout << "5: Moverse por el vagon.\n";
        cout << "6: Salir al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1: {
                int opcion1;
                cout << "\n-+-+-+-+Administrar lista de pasajeros+-+-+-" << endl;
                cout << "1. Agregar pasajero" << endl;
                cout << "2. Mostrar todos los pasajeros" << endl;
                cout << "3. Eliminar pasajero" << endl;
                cout << "Elija una opcion: ";
                cin >> opcion1;

                switch (opcion1) {
                    case 1: {
                        string nombre;
                        int edad;
                        string vagon;

                        cout << "Ingrese el nombre del pasajero: ";
                        cin >> nombre;
                        cout << "Ingrese la edad del pasajero: ";
                        cin >> edad;
                        cout << "Ingrese el vagon donde se asignará al pasajero: ";
                        cin >> vagon;

                        // Aquí hay que llamar la función que agrega el pasajero
                        listaPasajeros.agregarPasajero(nombre, edad, vagon, listaDoble);
                        break;
                    }
                    case 2: {
                        // muestra todos los pajeros
                        //hay que poner las función de llamar pasajeros;
                        break;
                    }
                    case 3: {
                        string nombreEliminar;
                        string vagonEliminar;

                        cout << "Ingrese el nombre del pasajero que desea eliminar: ";
                        cin >> nombreEliminar;
                        cout << "Ingrese el vagon del pasajero: ";
                        cin >> vagonEliminar;

                        // Llamar la función que elimina al pasajero
                        listaPasajeros.BorrarPasajeroPorNombreYVagon(nombreEliminar, vagonEliminar, listaDoble);
                        break;
                    }
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                }
                break;
            }

            case 2: {
                int opcion2;
                cout << "\n-+-+-+-+Administrar lista de vagones+-+-+-" << endl;
                cout << "1. Agregar vagon" << endl;
                cout << "2. Mostrar todos los vagones" << endl;
                cout << "3. Eliminar vagon" << endl;
                cout << "Elija una opcion: ";
                cin >> opcion2;

                switch (opcion2) {
                    case 1: {
                        string color;
                        cout << "Ingrese el color del nuevo vagon: ";
                        cin >> color;

                        int nuevoId = listaAmenidades.cantidadTotalDeAmenidades() + 1;
                        listaDoble.insertar(color, nuevoId);
                        break;
                    }
                    case 2: {
                        // Mostrar todos los vagones
                        listaDoble.mostrarTodosLosVagones();
                        break;
                    }
                    case 3: {
                        string colorEliminar;
                        cout << "Ingrese el color del vagon a eliminar: ";
                        cin >> colorEliminar;

                        // Llamar la función que elimina el vagon
                        listaDoble.eliminar(colorEliminar);
                        break;
                    }
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                }
                break;
            }

            case 3: {
                // Aquí se vamos a gestionar las estaciones
                // se agrega las funciones correspondientes para agregar, mostrar y eliminar estaciones
                cout << "\nAdministrar lista de estaciones" << endl;
                break;
            }

            case 4: {
                // Aquí se deberan gestionar las amenidades
                // Agregar las funciones correspondientes para agregar, mostrar y eliminar amenidades
                cout << "\nAdministrar lista de amenidades" << endl;
                break;
            }

            case 5: {
                // Función para moverse por los vagones
                //hay que llamar a la duncio par amovernos en los vagones;
                break;
            }

            case 6:
                cout << "Saliendo del menu." << endl;
                break;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    }
}

