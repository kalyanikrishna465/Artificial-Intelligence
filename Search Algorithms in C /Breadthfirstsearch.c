#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_QUEUE_SIZE 100
#define MAX_NAME_LENGTH 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    char neighbors[MAX_NODES][MAX_NAME_LENGTH];
    int neighbor_count;
} Node;

typedef struct {
    char queue[MAX_QUEUE_SIZE][MAX_NODES][MAX_NAME_LENGTH];
    int path_lengths[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initialize_queue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int is_queue_empty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, char path[MAX_NODES][MAX_NAME_LENGTH], int path_length) {
    if (q->rear < MAX_QUEUE_SIZE) {
        memcpy(q->queue[q->rear], path, path_length * MAX_NAME_LENGTH);
        q->path_lengths[q->rear] = path_length;
        q->rear++;
    }
}

void dequeue(Queue *q, char path[MAX_NODES][MAX_NAME_LENGTH], int *path_length) {
    if (!is_queue_empty(q)) {
        memcpy(path, q->queue[q->front], MAX_NODES * MAX_NAME_LENGTH);
        *path_length = q->path_lengths[q->front];
        q->front++;
    }
}

int is_in_path(char path[MAX_NODES][MAX_NAME_LENGTH], int path_length, char node[]) {
    for (int i = 0; i < path_length; i++) {
        if (strcmp(path[i], node) == 0) {
            return 1;
        }
    }
    return 0;
}

void breadth_first_search(Node graph[], int graph_size, char start[], char goal[]) {
    Queue queue;
    initialize_queue(&queue);

    char initial_path[MAX_NODES][MAX_NAME_LENGTH] = {0};
    strcpy(initial_path[0], start);
    enqueue(&queue, initial_path, 1);

    while (!is_queue_empty(&queue)) {
        char current_path[MAX_NODES][MAX_NAME_LENGTH] = {0};
        int current_path_length = 0;
        dequeue(&queue, current_path, &current_path_length);

        char *current_node = current_path[current_path_length - 1];

        if (strcmp(current_node, goal) == 0) {
            printf("BFS path: ");
            for (int i = 0; i < current_path_length; i++) {
                printf("%s ", current_path[i]);
            }
            printf("\n");
            return;
        }

        for (int i = 0; i < graph_size; i++) {
            if (strcmp(graph[i].name, current_node) == 0) {
                for (int j = 0; j < graph[i].neighbor_count; j++) {
                    if (!is_in_path(current_path, current_path_length, graph[i].neighbors[j])) {
                        char new_path[MAX_NODES][MAX_NAME_LENGTH] = {0};
                        memcpy(new_path, current_path, current_path_length * MAX_NAME_LENGTH);
                        strcpy(new_path[current_path_length], graph[i].neighbors[j]);
                        enqueue(&queue, new_path, current_path_length + 1);
                    }
                }
                break;
            }
        }
    }

    printf("No path found from %s to %s.\n", start, goal);
}

int main() {
    Node graph[MAX_NODES] = {
        {"S", {"A", "B"}, 2},
        {"A", {"B", "D"}, 2},
        {"B", {"A", "C"}, 2},
        {"C", {"B", "E"}, 2},
        {"D", {"A", "G"}, 2},
        {"E", {"C"}, 1},
        {"G", {"D"}, 1}
    };

    char start[] = "S";
    char goal[] = "G";

    breadth_first_search(graph, 7, start, goal);

    return 0;
}
