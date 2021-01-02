//Gianluca Capelo 83/19
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() {
    _raiz = nullptr;
    _cardinal = 0;
}

template<class T>
void Conjunto<T>:: destruir(Nodo* n) {
    if (n!=nullptr) {
        destruir(n->izq);
        destruir(n->der);
        delete n;
    }
}
template <class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    //assert(false);
    if(_cardinal == 0){
        return false;
    }
    else{
        Nodo* actual = _raiz;
        while ((actual != nullptr) && (actual->valor != clave)) {
            if (clave < actual->valor) {
                actual = actual->izq;
            }
            else {
                actual = actual->der;
            }
        }
        return (actual != nullptr);
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    //assert(false);
    if(_cardinal == 0){
        _raiz = new Nodo(clave);
        _cardinal++;
    }
    else {
        Nodo* ant = nullptr;
        Nodo* actual = _raiz;
        while ((actual != nullptr) && (actual->valor != clave)) {
            if (clave < actual->valor) {
                ant = actual;
                actual = actual->izq;
            } else {
                ant = actual;
                actual = actual->der;
            }
        }
        if (actual == nullptr) {
            if (ant->valor > clave) {
                actual = new Nodo(clave);
                ant->izq = actual;
                actual->padre = ant;
            }
            else {
                actual = new Nodo(clave);
                ant->der = actual;
                actual->padre = ant;
            }
            _cardinal++;
        }
    }
}
template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(_cardinal == 0){
        return ;
    }
    else {
        Nodo *actual = _raiz;
        while ((actual != nullptr) && (actual->valor != clave)) {
            if (clave < actual->valor) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }
        if (actual->valor == clave) {
            if (_cardinal == 1) {
                delete actual;
                _raiz = nullptr;
            }
            else {
                eliminar(actual);
            }
            _cardinal--;
        }
    }
}

template <class T>
void Conjunto<T>::eliminar(Nodo* actual) {
    bool esHoja = (actual->izq == nullptr) && (actual->der== nullptr);
    if (esHoja){
        bool esHijoIzquierdo = actual->valor < actual->padre->valor;
        bool esHijoDerecho =  actual->valor > actual->padre->valor;
        if (esHijoIzquierdo){
            actual->padre->izq = nullptr;
        }
        else if (esHijoDerecho){
            actual->padre->der = nullptr;
        }
        else{ // es el duplicado
            if(actual->padre->izq != nullptr && actual->padre->der != nullptr){
                if(actual->padre->izq->valor == actual->valor){
                    actual->padre->izq = nullptr;
                }
                else{
                    actual->padre->der = nullptr;
                }
            }
            else{
                if(actual->padre->izq != nullptr){
                    actual->padre->izq = nullptr;
                }
                else{
                    actual->padre->der = nullptr;
                }

            }
        }
        delete actual;
    }
    else if(actual->der != nullptr){  // tiene hijo derecho
        Nodo* Sucesor = actual->der;
        while (Sucesor->izq != nullptr ) {
            Sucesor = Sucesor->izq;
        }
        actual->valor = Sucesor->valor;

        eliminar(Sucesor);
    }
    else {
        Nodo* Predecesor = actual->izq;
        while (Predecesor->der != nullptr ) {
            Predecesor = Predecesor->der;
        }

        actual->valor = Predecesor->valor;
        eliminar(Predecesor);

    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    //assert(false);
    Nodo* actual = _raiz;
    while (actual->valor != clave) {
        if (clave < actual->valor) {
            actual = actual->izq;
        }
        else {
            actual = actual->der;
        }
    }
    Nodo* sig = actual->padre;
    if (actual->der != nullptr){
        actual = actual->der;
        while (actual->izq != nullptr ) {
            actual = actual->izq;
        }
        return actual->valor;
    }
    while(sig->der == actual){
        actual = sig;
        sig = sig->padre;
    }
    return sig->valor ;

}

template <class T>
const T& Conjunto<T>::minimo() const {
    //assert(false);
    Nodo* actual = _raiz;
    while (actual->izq != nullptr ) {
        actual = actual->izq;
    }
    return actual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    //assert(false);
    Nodo* actual = _raiz;
    while (actual->der != nullptr ) {
        actual = actual->der;
    }
    return actual->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    //assert(false);
    return _cardinal;
}
template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}




