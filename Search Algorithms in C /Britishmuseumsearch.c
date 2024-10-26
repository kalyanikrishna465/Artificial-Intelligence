#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_PATHS 100

typedef struct {
    char name[10];
    char neighbors[MAX_NODES][10];
    int neighbor_count;
} Node;

void find_all_paths(Node graph[], int graph_size, char start[], char goal[], char current_path[][10], int current_path_len, char all_paths[MAX_PATHS][MAX_NODES][10], int *path_count) {
    strcpy(current_path[current_path_len], start);
    current_path_len++;

    if (strcmp(start, goal) == 0) {
        printf("Path %d: ", *path_count + 1);
        for (int i = 0; i < current_path_len; i++) {
            printf("%s ", current_path[i]);
        }
        printf("\n");
        (*path_count)++;
        return;
    }

    for (int i = 0; i < graph_size; i++) {
        if (strcmp(graph[i].name, start) == 0) {
            for (int j = 0; j < graph[i].neighbor_count; j++) {
                int already_in_path = 0;
                for (int k = 0; k < current_path_len; k++) {
                    if (strcmp(current_path[k], graph[i].neighbors[j]) == 0) {
                        already_in_path = 1;
                        break;
                    }
                }
                if (!already_in_path) {
                    find_all_paths(graph, graph_size, graph[i].neighbors[j], goal, current_path, current_path_len, all_paths, path_count);
                }
            }
        }
    }
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

    char all_paths[MAX_PATHS][MAX_NODES][10] = {0};
    int path_count = 0;
    char current_path[MAX_NODES][10] = {0};
    int current_path_len = 0;

    printf("The British Museum Search paths are :\n");
    find_all_paths(graph, 7, start, goal, current_path, current_path_len, all_paths, &path_count);

    if (path_count == 0) {
        printf("No path found from %s to %s.\n", start, goal);
    }
    return 0;
}
