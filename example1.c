#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;

} NODE;

typedef struct Graph
{
    int vertices;
    int *visited;
    struct Node **adj_list;

} GPH;

typedef struct stack
{
    int top;
    int stack_cap;
    int *array;

} STK;

NODE *create_node(int v)
{
    NODE *newnode = malloc(sizeof(NODE)); // new_node
    newnode->data = v;
    newnode->next = NULL;
    return newnode;
}

void add_edge(GPH *graf, int src, int dest)
{
    NODE *newnode = create_node(dest);
    newnode->next = graf->adj_list[src];
    graf->adj_list[src] = newnode;

    newnode = create_node(src);
    newnode->next = graf->adj_list[dest];
    graf->adj_list[dest] = newnode;
}

GPH *create_graf(int v)
{
    int i;
    GPH *graf = malloc(sizeof(GPH));
    if (graf == NULL)
    {
        printf("nu exita graf");
        exit(1);
    }

    graf->vertices = v;
    graf->adj_list = malloc(v * sizeof(NODE *));
    graf->visited = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++)
    {
        graf->adj_list[i] = NULL;
        graf->visited[i] = 0;
    }
    return graf;
}

STK *create_stack(int stack_cap)
{
    STK *stack = malloc(sizeof(STK));
    stack->array = malloc(stack_cap * sizeof(int));
    stack->top = -1;
    stack->stack_cap = stack_cap;

    return stack;
}
void push(int pushedvalue, STK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushedvalue;
}

void DFS(GPH *graf, STK *stack, int vertices_number)
{
    NODE *adj_list = graf->adj_list[vertices_number];
    NODE *aux = adj_list;

    graf->visited[vertices_number] = 1;
    push(vertices_number, stack);

    while (aux != NULL)
    {
        int connected_vertex = aux->data;
        if (graf->visited[connected_vertex] == 0)
        {
            DFS(graf, stack, connected_vertex);
        }

        aux = aux->next;
    }
}
void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest, i;
    printf("adauga %d muchii(de la 0 la %d)\n", edg_nr, nrv - 1);
    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        // int adj[100][100] = {0};
        // adj[src][dest] = 1;
        // adj[dest][src] = 1;
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->visited[i] = 0;
    }
}
void canbe(GPH *graf, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        for (int j = 0; j < nrv; j++)
        {
            if (i != j)
            {
                STK *stack1 = create_stack(2 * nrv);
                STK *stack2 = create_stack(2 * nrv);
                DFS(graf, stack1, i);
                wipe(graf, nrv);
                DFS(graf, stack2, j);
                if (graf->visited[i] && graf->visited[j])
                    printf("1 ");
                else
                    printf("0 ");
                free(stack1->array);
                free(stack1);
                free(stack2->array);
                free(stack2);
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int main()
{
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vertex1, vertex2;

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful");
    scanf("%d", &edg_nr);

    GPH *graf = create_graf(nrv);

    insert_edges(graf, edg_nr, nrv);

    // printf("care vreti sa fie nodurile intre care vreti sa verificati daca exista drum sau nu?\n");
    // scanf("%d%d", &vertex1, &vertex2);

    canbe(graf, nrv);
    printf("daca in ,,matricea de adiacenta'' afisata intre nodurile dorite avem 1 inseamna ca exista drum si asa am aratat daca exista drum intre cele doua restaurante dorite");
}