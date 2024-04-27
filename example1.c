#include <stdlib.h>
#include <stdio.h>
// o sa indexez totul de la 0
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
void canbe(GPH *graf, int nrv, int matr_drum[][100])
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
                    matr_drum[i][j] = 1;
                else
                    matr_drum[i][j] = 0;
                free(stack1->array);
                free(stack1);
                free(stack2->array);
                free(stack2);
            }
        }
    }
}

int main()
{
    int nrv;
    int edg_nr;
    int src, dest;
    int i, j;
    int vertex1, vertex2;
    int matr_drum[100][100];

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful");
    scanf("%d", &edg_nr);

    GPH *graf = create_graf(nrv);

    insert_edges(graf, edg_nr, nrv);

    printf("care vreti sa fie primul restaurant? tastati 1 pentru restaurantul 1 s.a.m.d..\n");
    scanf("%d", &vertex1);
    printf("care vreti sa fie al doilea restaurant? tastati 1 pentru restaurantul 1 s.a.m.d..\n");
    scanf("%d", &vertex1);

    canbe(graf, nrv, matr_drum);

    if (matr_drum[vertex1][vertex2] == 1 && matr_drum[vertex2][vertex1] == 1)
    {
        printf("exista drum intre cele doua restaurante");
    }
    else
    {
        printf("nu exista drum intre cele doua restaurante");
    }
    return 0;
}
