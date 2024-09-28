#include <stdio.h>
#include <stdlib.h>

// Estructura de un nodo en el árbol de Huffman
struct Nodo {
    char dato;           // El carácter almacenado
    unsigned frecuencia; // Frecuencia del carácter
    struct Nodo *izq, *der; // Punteros a los hijos izquierdo y derecho
};

// Estructura para la cola de prioridad
struct ColaDePrioridad {
    unsigned tamano;
    unsigned capacidad;
    struct Nodo** array; // Arreglo de punteros a nodos
};

// Crear un nuevo nodo de Huffman
struct Nodo* crearNodo(char dato, unsigned frecuencia) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->frecuencia = frecuencia;
    nuevoNodo->izq = nuevoNodo->der = NULL;
    return nuevoNodo;
}

// Crear una cola de prioridad de un tamaño dado
struct ColaDePrioridad* crearColaDePrioridad(unsigned capacidad) {
    struct ColaDePrioridad* cola = (struct ColaDePrioridad*)malloc(sizeof(struct ColaDePrioridad));
    cola->tamano = 0;
    cola->capacidad = capacidad;
    cola->array = (struct Nodo**)malloc(cola->capacidad * sizeof(struct Nodo*));
    return cola;
}

// Intercambiar dos nodos
void intercambiarNodo(struct Nodo** a, struct Nodo** b) {
    struct Nodo* temp = *a;
    *a = *b;
    *b = temp;
}

// Reorganizar la cola de prioridad (montículo)
void reorganizar(struct ColaDePrioridad* cola, int idx) {
    int menor = idx;
    int izq = 2 * idx + 1;
    int der = 2 * idx + 2;

    if (izq < cola->tamano && cola->array[izq]->frecuencia < cola->array[menor]->frecuencia)
        menor = izq;

    if (der < cola->tamano && cola->array[der]->frecuencia < cola->array[menor]->frecuencia)
        menor = der;

    if (menor != idx) {
        intercambiarNodo(&cola->array[menor], &cola->array[idx]);
        reorganizar(cola, menor);
    }
}

// Comprueba si la cola de prioridad tiene un solo elemento
int tamanoUnico(struct ColaDePrioridad* cola) {
    return (cola->tamano == 1);
}

// Extraer el nodo con la menor frecuencia
struct Nodo* extraerMinimo(struct ColaDePrioridad* cola) {
    struct Nodo* temp = cola->array[0];
    cola->array[0] = cola->array[cola->tamano - 1];
    --cola->tamano;
    reorganizar(cola, 0);
    return temp;
}

// Insertar un nodo en la cola de prioridad
void insertarCola(struct ColaDePrioridad* cola, struct Nodo* nodo) {
    ++cola->tamano;
    int i = cola->tamano - 1;

    while (i && nodo->frecuencia < cola->array[(i - 1) / 2]->frecuencia) {
        cola->array[i] = cola->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    cola->array[i] = nodo;
}

// Construir la cola de prioridad inicial
void construirCola(struct ColaDePrioridad* cola) {
    int n = cola->tamano - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        reorganizar(cola, i);
}

// Crear una cola de prioridad a partir de los datos y sus frecuencias
struct ColaDePrioridad* crearConstruirCola(char dato[], int frecuencia[], int tamano) {
    struct ColaDePrioridad* cola = crearColaDePrioridad(tamano);
    for (int i = 0; i < tamano; ++i)
        cola->array[i] = crearNodo(dato[i], frecuencia[i]);
    cola->tamano = tamano;
    construirCola(cola);
    return cola;
}

// Construir el árbol de Huffman
struct Nodo* construirArbolHuffman(char dato[], int frecuencia[], int tamano) {
    struct Nodo *izq, *der, *top;
    struct ColaDePrioridad* cola = crearConstruirCola(dato, frecuencia, tamano);

    while (!tamanoUnico(cola)) {
        izq = extraerMinimo(cola);
        der = extraerMinimo(cola);

        top = crearNodo('$', izq->frecuencia + der->frecuencia);
        top->izq = izq;
        top->der = der;

        insertarCola(cola, top);
    }

    return extraerMinimo(cola);
}

// Imprimir los códigos de Huffman para cada carácter
void imprimirCodigos(struct Nodo* raiz, int arr[], int top) {
    if (raiz->izq) {
        arr[top] = 0;
        imprimirCodigos(raiz->izq, arr, top + 1);
    }

    if (raiz->der) {
        arr[top] = 1;
        imprimirCodigos(raiz->der, arr, top + 1);
    }

    if (!(raiz->izq) && !(raiz->der)) {
        printf("%c: ", raiz->dato);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Función principal para construir el árbol de Huffman y generar los códigos
void Huffman(char dato[], int frecuencia[], int tamano) {
    struct Nodo* raiz = construirArbolHuffman(dato, frecuencia, tamano);

    int arr[100], top = 0;
    imprimirCodigos(raiz, arr, top);
}

int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int frecuencia[] = { 5, 9, 12, 13, 16, 45 };

    int tamano = sizeof(arr) / sizeof(arr[0]);

    Huffman(arr, frecuencia, tamano);

    return 0;
}
