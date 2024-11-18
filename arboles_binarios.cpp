/******************************************************************************

Ejemplo hehco en clase
Arbol binario
Dr. Ismael Dominguez

*******************************************************************************/
#include <iostream>
using namespace std;

struct Nodo {
	int id;
	string nombre;
	Nodo *izq;
	Nodo *der;
};

//void mostrar(Nodo *&);
//void mostrar2(Nodo *&);
//void buscar(Nodo *&, int);
//void eliminar(Nodo *&lista, int d);
void insertar(int, string, Nodo *);
void recorrerPos( Nodo *);
Nodo *raiz= NULL;

int main() {

	int id,op=0;
	string na;

	do {

		cout<<"1. Insertar"<<endl;
		cout<<"2. Mostrar"<<endl;
		cout<<"3. Buscar"<<endl;
		cout<<"4. Eliminar"<<endl;
		cout<<"0. Salir"<<endl;
		cin>>op;

		switch(op)
		{
		case 1:
			cout<<"Id?: ";
			cin>>id;
			cout<<"nombre?: ";
			cin>>na;
			insertar(id,na, raiz);
			break;
		case 2:
			
			recorrerPos(raiz);
			break;
		case 3:
			
			//buscar(lista, id);
			break;
		case 4:
			// eliminar(lista, id);
			break;
		default:
			break;
		}

	} while(op!=0);

	return 0;
}

void insertar(int d,string n, Nodo *aux ) {
	Nodo *nuevo = new Nodo();
	nuevo->id = d;
	nuevo->nombre = n;

	if(raiz==NULL) // si es el primero raiz se coloca en el nuevo
	{
		raiz=nuevo;
		return;
	}

	while((aux != NULL)) {
		if( nuevo->id > aux->id)
		{
			if(aux->der==NULL)  //si la rama derecha esta libre se enlaza el nuevo
			{
				aux->der=nuevo;
				return;
			}
			else
				aux= aux->der;
		}
		else if( nuevo->id < aux->id) //si la rama izqu esta libre se enlaza el nuevo
		{
			if(aux->izq==NULL)
			{
				aux->izq=nuevo;
				return;
			}
			else
				aux=aux->izq;
		}
		else if(nuevo->id == aux->id)
		{
			cout<<"El Id "<<nuevo->id<<" ya esta en el arbol"<<endl;
			return;
		}
	}
}

/*void mostrar(Nodo *&lista){
    // Crear un nodo auxiliar
    Nodo *actual = new Nodo();
    // Igualar el nodo auxiliar a la lista
    actual = lista;
    // Recorrer la lista
    while(actual != NULL){
        // Mostrar los elementos de la lista
        cout<<"ID"<<" -> "<<actual->ID<<endl;
        cout<<"Nombre"<<" -> "<<actual->nombre<<endl;
        // Avanzar al siguiente nodo
        actual = actual->siguiente;
    }
}*/

// void mostrar2(Nodo *aux){
//     if (lista == NULL) return;

//     cout<<"**ID"<<" -> "<<lista->ID<<endl;
//     cout<<"**Nombre"<<" -> "<<lista->nombre<<endl;
//     mostrar2(aux->izq);

// }

void recorrerPos(Nodo *aux)
{
	if (aux==NULL) return;

	recorrerPos(aux->izq);

	///imprimir valores del nodo
	cout<<"***************"<<endl;
	cout<<"**Id: "<<" -> "<<aux->id<<endl;
	cout<<"**Nombre: "<<" -> "<<aux->nombre<<endl;
	cout<<"**Creado en: "<<aux<<endl;
	cout<<"***************"<<endl;

	recorrerPos(aux->der);


}
