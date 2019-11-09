#include "jrb.h"
#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int v, int *output);
void dropGraph(Graph graph);
void BFS(Graph graph, int start, int stop, int *parent, void (*printVertex)(int));
void printVertex();
void traverse(JRB tree)
{
    JRB node;
    jrb_traverse(node, tree)
    {
        printf("Key: %d \t Value: %d\n", jval_i(node->key), jval_i(node->val));
    }
}
int main()
{
    Graph graph = createGraph();
    int next = 0;
    int parent[30];
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 6);
    addEdge(graph, 6, 8);
    addEdge(graph, 8, 10);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 4, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 10, 5);
    addEdge(graph, 5, 9);
    addEdge(graph, 9, 13);
    addEdge(graph, 11, 13);
    addEdge(graph, 11, 12);
    addEdge(graph, 1, 11);
    while (next == 0)
    {
        int start, stop;
        printf("Nhap diem bat dau: ");
        scanf("%d", &start);
        printf("Nhap diem ket thuc: ");
        scanf("%d", &stop);
        BFS(graph, start, stop, parent, printVertex);
        int b[30];
        int i = 0;
        b[i++] = stop;
        int k = stop;
        while (parent[k] != start)
        {
            b[i++] = parent[k];
            k = parent[k];
        }
        b[i++] = start;
        printf("Quang duong di ngan nhat la: \n");
        for (int m = i - 1; m >= 0; m--)
        {
            printf("%d\t", b[m]);
        }
        printf("\nTiep tuc? :   ");
        scanf("%d", &next);
    }
}

void printVertex(int v)
{
    printf("%d\n", v);
}
void BFS(Graph graph, int start, int stop, int *parent, void (*printVertex)(int))
{
    int visited[30];
    for (int i = 0; i < 30; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }
    Dllist queue = new_dllist();
    dll_append(queue, new_jval_i(start));
    while (!dll_empty(queue))
    {
        Dllist node = dll_first(queue);
        int v = jval_i(node->val);
        dll_delete_node(node);
        if (visited[v] != 1)
        {
            visited[v] = 1;
            int output[30];
            if (v == stop)
                break;
            int n = getAdjacentVertices(graph, v, output);
            for (int i = 0; i < n; i++)
            {
                if (visited[output[i]] != 1)
                {
                    dll_append(queue, new_jval_i(output[i]));
                    if (parent[output[i]] == -1)
                        parent[output[i]] = v;
                }
            }
        }
    }

    printf("\n");
    /*for(int i = 0; i< numVisited;i++)
    {
        printf("%d \n",visitedVertex[i]);
    }*/
}

Graph createGraph()
{
    return make_jrb();
}

int adjacent(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph, v1);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    if (jrb_find_int(tree, v2) == NULL)
        return 0;
    else
        return 1;
}

void addEdge(Graph g, int v1, int v2)
{
    JRB tree, node;
    if (!adjacent(g, v1, v2))
    {
        node = jrb_find_int(g, v1);

        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(g, v1, new_jval_v(tree));
        }
        else
            tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));

        node = jrb_find_int(g, v2);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(g, v2, new_jval_v(tree));
        }
        else
            tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}
int getAdjacentVertices(Graph graph, int v, int *output)
{
    int i = 0;
    JRB node = jrb_find_int(graph, v);
    JRB tree = (JRB)jval_v(node->val);
    JRB temp;
    jrb_traverse(temp, tree)
    {
        output[i] = jval_i(temp->key);
        i++;
    }
    return i;
}
void dropGraph(Graph graph)
{
    JRB temp;
    jrb_traverse(temp, graph)
    {
        jrb_free_tree(temp);
    }
}