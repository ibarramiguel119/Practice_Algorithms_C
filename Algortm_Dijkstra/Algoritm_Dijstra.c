#include <stdio.h>
#include <limits.h> // Para usar INT_MAX
#include <stdbool.h> // Para usar bool

#define V 5 // Número de vértices en el grafo

// Función para encontrar el vértice con la distancia mínima, entre los
// vértices que no han sido procesados aún
int minDistancia(int dist[], bool visitado[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (visitado[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Función que implementa el algoritmo de Dijkstra
void dijkstra(int grafo[V][V], int src) {
    int dist[V]; // dist[i] almacenará la distancia más corta desde src hasta i
    bool visitado[V]; // visitado[i] será verdadero si el vértice i ha sido procesado

    // Inicializar todas las distancias como INFINITO y visitado[] como falso
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visitado[i] = false;

    // La distancia desde el nodo origen a sí mismo es 0
    dist[src] = 0;

    // Buscar la ruta más corta para todos los vértices
    for (int count = 0; count < V - 1; count++) {
        // Seleccionar el vértice de distancia mínima que aún no ha sido procesado
        int u = minDistancia(dist, visitado);

        // Marcar el vértice seleccionado como procesado
        visitado[u] = true;

        // Actualizar el valor dist[] de los vértices adyacentes al vértice seleccionado
        for (int v = 0; v < V; v++)
            // Actualiza dist[v] si no está en visitado, hay un borde de u a v y el
            // peso total del camino desde src a v a través de u es menor que el valor actual de dist[v]
            if (!visitado[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v])
                dist[v] = dist[u] + grafo[u][v];
    }

    // Imprimir el arreglo de distancias
    printf("Vertice \t Distancia desde el origen\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

int main() {
    // Grafo representado en una matriz de adyacencia
    int grafo[V][V] = {
        {0, 10, 0, 30, 100},
        {10, 0, 50, 0, 0},
        {0, 50, 0, 20, 10},
        {30, 0, 20, 0, 60},
        {100, 0, 10, 60, 0}
    };

    // Ejecutar el algoritmo de Dijkstra desde el vértice 0
    dijkstra(grafo, 0);

    return 0;
}
