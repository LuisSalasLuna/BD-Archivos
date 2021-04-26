#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;

class Profesor {
    int id;
    char nombre[10];
public:
    Profesor() {
        id = 0;
        for (int i = 0; i < 10; i++)
            nombre[i] = ' ';
    }
    Profesor(int _id, char _nombre[10]) {
        id = _id;
        for (int i = 0; i < 10; i++)
            nombre[i] = _nombre[i];
    }
    void Escribir() {
        ofstream escritura;
        escritura.open("profesores.txt", ios::app);
        escritura << id << "," << nombre << "\n";
        escritura.close();
    }
    Profesor& operator = (const Profesor& p);
    bool    operator ==(const Profesor& p) const;
    bool    operator <(const Profesor& p) const;
    friend ostream& operator << (ostream& o, const Profesor& p);
    friend istream& operator >> (istream& o, Profesor& p);
};
Profesor& Profesor::operator = (const Profesor& p) {
    if (this != &p) { //Comprueba que no se esté intentanod igualar un objeto a sí mismo
        if (p.id != 0) this->id = p.id;
        if (p.nombre != 0) {
            for (int i = 0; i < 10; i++)
                this->nombre[i] = p.nombre[i];
        }
    }
    return *this;
}
bool Profesor::operator == (const Profesor& p) const
{
    return this->id == p.id;
}
bool Profesor::operator < (const Profesor& p) const
{
    return this->id < p.id;
}
ostream& operator << (ostream& o, const Profesor& p) {
    o << "(" << p.id << ", " << p.nombre << ")";
    return o;
}
istream& operator >> (istream& i, Profesor& p)
{
    cout << "\n Ingrese id: ";
    i >> p.id;
    cout << " Ingrese nombre: ";
    i >> p.nombre;
    i.ignore();
    return i;
}

struct CNode
{
    Profesor valor;
    CNode* next;
    CNode(Profesor v) {
        valor = v;
        next = 0;
    }
};
class le
{
    CNode* head = nullptr;
public:
    bool add(Profesor valor);
    bool remove(Profesor valor);
    bool find(Profesor bus, CNode**& pos);
    void escribir();
    void print();
    ~le();
};
bool le::find(Profesor bus, CNode**& p)
{
    for (p = &head; *p && (*p)->valor < bus; p = &((*p)->next));
    return *p && (*p)->valor == bus; //Version reducida
}
bool le::add(Profesor x)
{
    CNode** p;
    if (find(x, p))
        return 0;
    CNode* n;
    n = new CNode(x);
    n->next = *p;
    *p = n;
    return 1;
}
bool le::remove(Profesor x)
{
    CNode** p;
    if (!find(x, p))
        return 0;
    CNode* t = *p;
    *p = t->next;
    delete t;
    return 1;
}
void le::escribir()
{
    ofstream escritura;
    escritura.open("profesores.txt", ios::out);
    escritura.close();
    for (CNode* t = head; t; t = t->next)
        (t->valor).Escribir();
}
void le::print(){
    for (CNode* t = head; t; t = t->next)
        cout << t->valor << "\n";
}
le::~le()
{
    while (head){
        remove(head->valor);
    }
}

void Agregar(le& LE) {
    Profesor val;
    cin >> val;
    LE.add(val);
    LE.escribir();
}
void Remover(le& LE) {

    int id;
    char nom[10] = "         ";
    cout << "\n Ingrese id: ";
    cin >> id;
    Profesor val(id, nom);
    LE.remove(val);
    LE.escribir();
}
void Imprimir(le& LE) {
    LE.print();
}
void Menu(le &LE) {
    int opcion;
    do {
        cout << "\n\t\t\t Estructura de registros\n" << endl;
        Imprimir(LE);
        cout << " \n Menu: " << endl;
        cout << " 1. Agregar" << endl;
        cout << " 2. Remover" << endl;
        cout << " 3. Imprimir" << endl;
        cout << " 4. Salir \n" << endl;
        cout << " Opci\242n: ";
        cin >> opcion;
        switch (opcion) {
        default:
            cout << " Ha ingresado una opci\242n no valida!\n\n";
            system("pause");
            system("CLS");
            break;
        case 1:
            Agregar(LE);
            system("CLS");
            break;
        case 2:
            Remover(LE);
            system("CLS");
            break;
        case 3:
            system("CLS");
            cout << "\n\n\t";
            Imprimir(LE);
            cout << "\n\n";
            system("pause");
            system("CLS");
            break;
        case 4:
            system("CLS");
            break;
        }
    } while (opcion != 4);
}

int string2int(string a) {
    int result = 0;
    int mult = 1;
    for (int i = a.size() - 1; i >= 0; i--) {
        int aux = (static_cast<int>(a[i]) - 48) * mult;
        result += aux;
        mult *= 10;
    }
    return result;
}
void Leer(le& prof) {
    string idNombre;
    //string liberador;
    ifstream extraccion;
    //int i = ObtenerTam();
    extraccion.open("profesores.txt", ios::in);
    while (!extraccion.eof()) {
        getline(extraccion, idNombre);
        for (int i = 0; i < idNombre.size(); i++) {
            if (idNombre[i] == ',') {
                int id = string2int(idNombre.substr(0, i));
                string aux = idNombre.substr(i + 1);
                char nombre[10] = {          };
                for (int i = 0; i < aux.size(); i++) {
                    nombre[i] = aux[i];
                }
                Profesor Prf(id, nombre);
                prof.add(Prf);
            }
        }


        //getline(extraccion, liberador);
    }
    extraccion.close();
    //return arr;
}

int main() {
    le Profesores;
    Leer(Profesores);
    Menu(Profesores);
    return 0;
}