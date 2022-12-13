#include <math.h>
#include <thread>
#include <mutex> 
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <future>

std::mutex mtx;
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
struct Nodo {
    T val;
    Nodo<T>* padre = NULL;
    Nodo<T>* nodos[2];
    int estado = 0;
    Nodo(T a, Nodo<T>* pdr) {
        val = a;
        nodos[0] = nodos[1] = 0;
        padre = pdr;
    }

};
////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class AVL {
private:
    int IZQUIERDO = 0, DERECHO = 1;
    Nodo<T>* actual;
    int contador;

public:
    int altura;
    Nodo<T>* raiz;
    AVL() { raiz = NULL; actual = NULL; contador = 0; altura = 0; }
    //~AVL() { Podar(raiz); }
    void Insertar(T dat);
    void Borrar(T dat);
    bool Buscar(T dat);
    // Comprobar si es un nodo hoja:
    bool EsHoja(Nodo<T>* r) { return !r->nodos[1] && !r->nodos[0]; }
    // Contar número de nodos:
    const int AlturaArbol();
    // Calcular altura de un dato:
    int Altura(T dat);
    int& ValorActual() { return actual->val; }

private:
    // Funciones de equilibrado:
    void Equilibrar(Nodo<T>* nodo, int, bool);
    void RSI(Nodo<T>* nodo);
    void RSD(Nodo<T>* nodo);
    void RDI(Nodo<T>* nodo);
    void RDD(Nodo<T>* nodo);
    // Funciones auxiliares
    void Podar(Nodo<T>*&);
    void auxContador(Nodo<T>*);
    void auxAltura(Nodo<T>*, int);
};
template<class T>
void AVL<T>::Podar(Nodo<T>*& nodo) {
    if (nodo) {
        Podar(nodo->nodos[0]);
        Podar(nodo->nodos[1]);
        delete nodo;
        nodo = NULL;
    }
}

template <class T>
void AVL<T>::Insertar(T dat)
{
    Nodo<T>* padre = NULL;

    //cout << "Insertar: " << dat << endl;
    actual = raiz;
    // Buscar el dato en el árbol, manteniendo un puntero al nodo padre
    while (actual && dat != actual->val) {
        padre = actual;
        if (dat > actual->val) actual = actual->nodos[1];
        else if (dat < actual->val) actual = actual->nodos[0];
    }
    if (actual) return;
    if (!padre) raiz = new Nodo<T>(dat, NULL);
    else if (dat < padre->val) {
        padre->nodos[0] = new Nodo<T>(dat, padre);
        Equilibrar(padre, IZQUIERDO, true);
    }
    else if (dat > padre->val) {
        padre->nodos[1] = new Nodo<T>(dat, padre);
        Equilibrar(padre, DERECHO, true);
    }
}

template <class T>
void AVL<T>::Equilibrar(Nodo<T>* nodo, int rama, bool nuevo)
{
    bool salir = false;

    while (nodo && !salir) {
        if (nuevo)
            if (rama == IZQUIERDO) nodo->estado -= 1;
            else                  nodo->estado += 1;
        else
            if (rama == IZQUIERDO) nodo->estado++;
            else                  nodo->estado--;
        if (nodo->estado == 0) salir = true;

        else if (nodo->estado == -2) { // Rotar a derechas y salir:
            if (nodo->nodos[0]->estado == 1) RDD(nodo);
            else RSD(nodo);
            salir = true;
        }
        else if (nodo->estado == 2) {  // Rotar a izquierdas y salir:
            if (nodo->nodos[1]->estado == -1) RDI(nodo);
            else RSI(nodo);
            salir = true;
        }
        if (nodo->padre)
            if (nodo->padre->nodos[1] == nodo) rama = DERECHO; else rama = IZQUIERDO;
        nodo = nodo->padre;
    }
}

template<class T>
void AVL<T>::RDD(Nodo<T>* nodo)
{
    //cout << "RDD" << endl;
    Nodo<T>* Padre = nodo->padre;
    Nodo<T>* P = nodo;
    Nodo<T>* Q = P->nodos[0];
    Nodo<T>* R = Q->nodos[1];
    Nodo<T>* B = R->nodos[0];
    Nodo<T>* C = R->nodos[1];

    if (Padre)
        if (Padre->nodos[1] == nodo) Padre->nodos[1] = R;
        else Padre->nodos[0] = R;
    else raiz = R;

    // Reconstruir árbol:
    Q->nodos[1] = B;
    P->nodos[0] = C;
    R->nodos[0] = Q;
    R->nodos[1] = P;

    // Reasignar padres:
    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;


    switch (R->estado) {
    case -1: Q->estado = 0; P->estado = 1; break;
    case 0:  Q->estado = 0; P->estado = 0; break;
    case 1:  Q->estado = -1; P->estado = 0; break;
    }
    R->estado = 0;
}

template <class T>
void AVL<T>::RDI(Nodo<T>* nodo)
{
    //cout << "RDI" << endl;
    Nodo<T>* Padre = nodo->padre;
    Nodo<T>* P = nodo;
    Nodo<T>* Q = P->nodos[1];
    Nodo<T>* R = Q->nodos[0];
    Nodo<T>* B = R->nodos[0];
    Nodo<T>* C = R->nodos[1];

    if (Padre)
        if (Padre->nodos[1] == nodo) Padre->nodos[1] = R;
        else Padre->nodos[0] = R;
    else raiz = R;

    // Reconstruir árbol:
    P->nodos[1] = B;
    Q->nodos[0] = C;
    R->nodos[0] = P;
    R->nodos[1] = Q;

    // Reasignar padres:
    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->estado) {
    case -1: P->estado = 0; Q->estado = 1; break;
    case 0:  P->estado = 0; Q->estado = 0; break;
    case 1:  P->estado = -1; Q->estado = 0; break;
    }
    R->estado = 0;
}

template <class T>
void AVL<T>::RSD(Nodo<T>* nodo)
{
    //cout << "RSD" << endl;
    Nodo<T>* Padre = nodo->padre;
    Nodo<T>* P = nodo;
    Nodo<T>* Q = P->nodos[0];
    Nodo<T>* B = Q->nodos[1];

    if (Padre)
        if (Padre->nodos[1] == P) Padre->nodos[1] = Q;
        else Padre->nodos[0] = Q;
    else raiz = Q;

    // Reconstruir árbol:
    P->nodos[0] = B;
    Q->nodos[1] = P;

    // Reasignar padres:
    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->estado = 0;
    Q->estado = 0;
}

template <class T>
void AVL<T>::RSI(Nodo<T>* nodo)
{
    //cout << "RSI" << endl;
    Nodo<T>* Padre = nodo->padre;
    Nodo<T>* P = nodo;
    Nodo<T>* Q = P->nodos[1];
    Nodo<T>* B = Q->nodos[0];

    if (Padre)
        if (Padre->nodos[1] == P) Padre->nodos[1] = Q;
        else Padre->nodos[0] = Q;
    else raiz = Q;

    // Reconstruir árbol:
    P->nodos[1] = B;
    Q->nodos[0] = P;

    // Reasignar padres:
    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->estado = 0;
    Q->estado = 0;
}

template <class T>
int AVL<T>::Altura(T dat)
{
    int altura = 0;
    actual = raiz;


    while (actual) {
        if (dat == actual->val) return altura;
        else {
            altura++;
            if (dat > actual->val) actual = actual->nodos[1];
            else if (dat < actual->val) actual = actual->nodos[0];
        }
    }
    return -1;
}
template <class T>

void AVL<T>::auxContador(Nodo<T>* nodo)
{
    contador++;
    if (nodo->nodos[0]) auxContador(nodo->nodos[0]);
    if (nodo->nodos[1])   auxContador(nodo->nodos[1]);
}

template<class T>
const int AVL<T>::AlturaArbol()
{
    altura = 0;

    auxAltura(raiz, altura);
    return altura;
}

template<class T>
void AVL<T>::auxAltura(Nodo<T>* nodo, int a)
{
    if (nodo->nodos[0]) auxAltura(nodo->nodos[0], a + 1);
    if (nodo->nodos[1])   auxAltura(nodo->nodos[1], a + 1);

    if (EsHoja(nodo) && a > altura) altura = a;
}


template <class T>
void AVL<T>::Borrar(T dat) {
    Nodo<T>* padre = NULL;
    Nodo<T>* nodo;
    int aux;

    actual = raiz;
    while (actual) {
        if (dat == actual->val) {
            if (EsHoja(actual)) {
                if (padre)
                    if (padre->nodos[1] == actual) padre->nodos[1] = NULL;
                    else if (padre->nodos[0] == actual) padre->nodos[0] = NULL;
                delete actual;
                actual = NULL;
                if ((padre->nodos[1] == actual && padre->estado == 1) || (padre->nodos[0] == actual && padre->estado == -1)) {
                    padre->estado = 0;
                    actual = padre;
                    padre = actual->padre;
                }
                if (padre)
                    if (padre->nodos[1] == actual) Equilibrar(padre, DERECHO, false);
                    else                         Equilibrar(padre, IZQUIERDO, false);
                return;
            }
            else {
                padre = actual;
                if (actual->nodos[1]) {
                    nodo = actual->nodos[1];
                    while (nodo->nodos[0]) {
                        padre = nodo;
                        nodo = nodo->nodos[0];
                    }
                }
                else {
                    nodo = actual->nodos[0];
                    while (nodo->nodos[1]) {
                        padre = nodo;
                        nodo = nodo->nodos[1];
                    }
                }
                aux = actual->val;
                actual->val = nodo->val;
                nodo->val = aux;
                actual = nodo;
            }
        }
        else {
            padre = actual;
            if (dat > actual->val) actual = actual->nodos[1];
            else if (dat < actual->val) actual = actual->nodos[0];
        }
    }
}
template <class T>
bool AVL<T>::Buscar(T dat) {
    Nodo<T>* p = &raiz;
    for (p; *p && (*p)->val != dat; p = &((*p)->nodos[dat > (*p)->val]));
    return *p;
}

AVL<int>* AYUDA;

void fa(int a, int b) {
    mtx.lock();
    for (int i = a; i < b; i++) {
        AYUDA->Insertar((rand() % b) + 1);
    }
    mtx.unlock();
}

int main() {
    AVL<int> tree;
    srand(time(NULL));
    unsigned t0, t1;
    float time;

    t0 = clock();
    for (int i = 0; i < 200; i++) {
        tree.Insertar(i);
    }
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time 200 elementos: " << time << endl;
    AVL<int>tree_0;
    t0 = clock();
    for (int i = 0; i < 2000; i++) {
        tree_0.Insertar(i);
    }
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time 2000 elementos: " << time << endl;
    AVL<int>tree_1;
    t0 = clock();
    for (int i = 0; i < 20000; i++) {
        tree_1.Insertar(i);
    }
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time 20000 elementos: " << time << endl;
    AVL<int>tree_2;
    t0 = clock();
    for (int i = 0; i < 2000000; i++) {
        tree_2.Insertar(i);
    }
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time 2000000 elementos: " << time << endl;
    AVL<int>tree_3;
    t0 = clock();
    for (int i = 0; i < 20000000; i++) {
        tree_3.Insertar(i);
    }
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time 20000000 elementos: " << time << endl;



    AVL<int>tree_4;
    t0 = clock();
    AYUDA = &tree_4;
    thread th1(fa, 0, 50);
    thread th2(fa, 50, 10);
    thread th3(fa, 100, 150);
    thread th4(fa, 150, 200);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    tree_4 = *AYUDA;
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "con 4 threads" << endl;
    cout << "Execution Time 200 elementos: " << time << endl;

    AVL<int>tree_5;
    AYUDA = &tree_5;
    t0 = clock();
    thread th5(fa, 0, 500);
    thread th6(fa, 500, 1000);
    thread th7(fa, 1000, 1500);
    thread th8(fa, 1500, 2000);
    th5.join();
    th6.join();
    th7.join();
    th8.join();
    tree_5 = *AYUDA;
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "con 4 threads" << endl;
    cout << "Execution Time 2000 elementos: " << time << endl;

    AVL<int>tree_6;
    t0 = clock();
    AYUDA = &tree_6;
    thread th9(fa, 0, 5000);
    thread th10(fa, 5000, 10000);
    thread th11(fa, 10000, 15000);
    thread th12(fa, 15000, 20000);
    th9.join();
    th10.join();
    th11.join();
    th12.join();
    tree_6 = *AYUDA;
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "con 4 threads" << endl;
    cout << "Execution Time 20000 elementos: " << time << endl;

    AVL<int>tree_7;
    t0 = clock();
    AYUDA = &tree_7;
    thread th13(fa, 0, 500000);
    thread th14(fa, 500000, 1000000);
    thread th15(fa, 1000000, 1500000);
    thread th16(fa, 1500000, 2000000);
    th13.join();
    th14.join();
    th15.join();
    th16.join();
    t1 = clock();
    tree_7 = *AYUDA;
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "con 4 threads" << endl;
    cout << "Execution Time 2000000 elementos: " << time << endl;

    AVL<int>tree_8;
    t0 = clock();
    AYUDA = &tree_8;
    thread th17(fa, 0, 5000000);
    thread th18(fa, 5000000, 10000000);
    thread th19(fa, 10000000, 15000000);
    thread th20(fa, 15000000, 20000000);
    th17.join();
    th18.join();
    th19.join();
    th20.join();
    tree_8 = *AYUDA;
    t1 = clock();
    time = (float(t1 - t0) / CLOCKS_PER_SEC);
    cout << "con 4 threads" << endl;
    cout << "Execution Time 20000000 elementos: " << time << endl;
    return 0;
}