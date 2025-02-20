#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define INF INT_MAX  

// Función para encontrar el nodo con la distancia mínima no visitado
int minDistancia(int dist[], int visitado[], int V) {
    int min = INF, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Función recursiva para imprimir la ruta más corta
void imprimirRuta(int padre[], int j) {
    if (padre[j] == -1) {
        printf("%d", j);
        return;
    }
    imprimirRuta(padre, padre[j]);
    printf(" -> %d", j);
}

// Función de Dijkstra para calcular la distancia y ruta más corta
void dijkstra(int **grafo, int V, int origen) {
    int dist[V], visitado[V], padre[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visitado[i] = 0;
        padre[i] = -1;
    }
    dist[origen] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistancia(dist, visitado, V);
        if (u == -1) break;
        visitado[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visitado[v] && grafo[u][v] != INF && dist[u] != INF &&
                dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
                padre[v] = u;
            }
        }
    }

    printf("\nResultados del Algoritmo de Dijkstra (Desde Nodo %d):\n", origen);
    printf("Nodo Destino\tDistancia Minima\tCamino Más Corto\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t\t", i);
        if (dist[i] == INF)
            printf("NC\t\t\t-\n");
        else {
            printf("%d\t\t\t", dist[i]);
            imprimirRuta(padre, i);
            printf("\n");
        }
    }
}

// Función para leer la matriz de adyacencia de forma más rápida
void leerMatriz(int **grafo, int V) {
    printf("\nIngrese la matriz de adyacencia (use NC para no conectado):\n");
    for (int i = 0; i < V; i++) {
        printf("Fila %d: ", i);
        for (int j = 0; j < V; j++) {
            char entrada[10];
            scanf("%s", entrada);
            grafo[i][j] = (strcmp(entrada, "NC") == 0) ? INF : atoi(entrada);
        }
    }
}

int main() {
    int V, origen;
    printf("Ingrese la cantidad de nodos: ");
    scanf("%d", &V);

    // Crear la matriz de adyacencia dinámicamente
    int **grafo = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        grafo[i] = (int *)malloc(V * sizeof(int));
    }

    // Leer la matriz de adyacencia de forma rápida
    leerMatriz(grafo, V);

    // Pedir el nodo de origen
    printf("\nIngrese el nodo de origen: ");
    scanf("%d", &origen);

    // Ejecutar el algoritmo de Dijkstra
    dijkstra(grafo, V, origen);

    // Liberar la memoria de la matriz
    for (int i = 0; i < V; i++) {
        free(grafo[i]);
    }
    free(grafo);
    
    return 0;
}
