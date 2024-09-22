#include <stdio.h>

// Función auxiliar para intercambiar dos elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función para particionar el arreglo utilizando el último elemento como pivote
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Se elige el último elemento como pivote
    int i = low - 1;       // Índice del elemento más pequeño

    // Recorremos desde el primer elemento hasta el penúltimo
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) { // Si el elemento actual es menor o igual al pivote
            i++;               // Incrementamos el índice
            swap(&arr[i], &arr[j]); // Intercambiamos los elementos
        }
    }
    swap(&arr[i + 1], &arr[high]); // Colocamos el pivote en su posición correcta
    return i + 1; // Retornamos el índice del pivote
}

// Función recursiva de QuickSort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Obtenemos el índice de partición
        int pi = partition(arr, low, high);

        // Ordenamos los elementos antes y después de la partición
        quickSort(arr, low, pi - 1);  // Lado izquierdo del pivote
        quickSort(arr, pi + 1, high); // Lado derecho del pivote
    }
}

// Función para imprimir el arreglo
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Arreglo original: \n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Arreglo ordenado: \n");
    printArray(arr, n);

    return 0;
}