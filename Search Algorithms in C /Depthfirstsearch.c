#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODES 100
#define MAX_STACK_SIZE 100
#define MAX_NAME_LEN 20  

typedef struct {
    char name[MAX_NAME_LEN];
    char neighbors[MAX_NODES][MAX_NAME_LEN];
    int neighbor_count;
} Node;

typedef struct {
    char path[MAX_STACK_SIZE][MAX_NAME_LEN];
    int top;
} Stack;

void push(Stack *stack, char node[]) {
    if (stack->top < MAX_STACK_SIZE) {
        strcpy(stack->path[stack->top], node);
        stack->top++;
    }
}

void pop(Stack *stack) {
    if (stack->top > 0) {
        stack->top--;
    }
}

char* top(Stack *stack) {
    if (stack->top > 0) {
        return stack->path[stack->top - 1];
    }
    return NULL;
}

int is_in_path(Stack *stack, char node[]) {
    for (int i = 0; i < stack->top; i++) {
        if (strcmp(stack->path[i], node) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_visited(char visited[][MAX_NAME_LEN], int visited_count, char node[]) {
    for (int i = 0; i < visited_count; i++) {
        if (strcmp(visited[i], node) == 0) {
            return 1;
        }
    }
    return 0;
}

void depth_first_search(Node graph[], int graph_size, char start[], char goal[]) {
    Stack stack;
    stack.top = 0;

    char visited[MAX_NODES][MAX_NAME_LEN];
    int visited_count = 0;
    push(&stack, start);

    while (stack.top > 0) {
        char* current_node = top(&stack);
        if (!is_visited(visited, visited_count, current_node)) {
            strcpy(visited[visited_count], current_node);
            visited_count++;
        }

        if (strcmp(current_node, goal) == 0) {
            printf("Path: ");
            for (int i = 0; i < stack.top; i++) {
                printf("%s ", stack.path[i]);
            }
            printf("\n");
            return;
        }

        int node_found = 0;
        for (int i = 0; i < graph_size; i++) {
            if (strcmp(graph[i].name, current_node) == 0) {
                node_found = 1;

                int all_visited = 1;
                for (int j = 0; j < graph[i].neighbor_count; j++) {
                    if (!is_in_path(&stack, graph[i].neighbors[j]) && !is_visited(visited, visited_count, graph[i].neighbors[j])) {
                        push(&stack, graph[i].neighbors[j]);
                        all_visited = 0;
                        break;
                    }
                }
                if (all_visited) {
                    pop(&stack);
                }
                break;
            }
        }
        if (!node_found) {
            pop(&stack);
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
    printf("The Depth First Search path is: \n");
    depth_first_search(graph, 7, start, goal);

    return 0;
}
