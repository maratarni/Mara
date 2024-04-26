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
    if (g == NULL)
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
    printf("adauga %d muchii(de la 1 la %d)\n", edg_nr, nrv);
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
void canbe(GPH *g, int nrv, STK *s1, STK *s2)
{
    int *canbe = calloc(nrv, sizeof(int));
    if (canbe == NULL)
    {
        printf("Eroare la alocarea memoriei pentru vectorul canbe.\n");
        exit(1);
    }

    wipe(g, nrv);

    for (int i = 0; i < nrv; i++)
    {
        wipe(g, nrv);
        DFS(g, s2, i);

        int ans = 1;

        for (int k = 0; k < nrv && ans; k++)
        {
            if ((s1->array[k] != s2->array[k]))
            {
                ans = 0;
            }
        }
        if (ans)
            canbe[i] = 1;
    }

    free(canbe);
}

int main()
{
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int ans = 1;

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv, s1, s2);
}