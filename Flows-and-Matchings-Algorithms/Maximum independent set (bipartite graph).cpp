#include <bits/stdc++.h>

using namespace std;

/**
    U - unmatched vertexes from V1
    Z - vertexes which are in U or are connected to U by alternating paths

    MVC: (V1\Z)∪(V2∩Z)
    MIS: (V1∪V2)\MVC
**/

const int Nmax = 50000 + 1;
const int Mmax = 150000 + 1;
const int NIL = -1;

struct Edge
{
    int nod;
    int urm;
};

Edge Graph[2 * Mmax];
int head[2 * Nmax];

int match[2 * Nmax];
bool vis[2 * Nmax];
bool use[Nmax];

int V1, V2, E;
int countEdges;

void addEdge(int x, int y)
{
    Graph[countEdges] = {y, head[x]};
    head[x] = countEdges;
    countEdges++;
}

bool dfs(int nod)
{
    if (use[nod])
        return false;

    use[nod] = true;

    for (int p = head[nod]; p != NIL; p = Graph[p].urm)
    {
        int son = Graph[p].nod;

        if (!match[son])
        {
            match[nod] = son;
            match[son] = nod;

            return true;
        }
    }

    for (int p = head[nod]; p != NIL; p = Graph[p].urm)
    {
        int son = Graph[p].nod;

        if (dfs(match[son]))
        {
            match[nod] = son;
            match[son] = nod;

            return true;
        }
    }

    return false;
}

int Hopcroft_Karp()
{
    bool valid;

    do
    {
        valid = false;

        for (int i = 1; i <= V1; ++i)
            use[i] = false;

        for (int i = 1; i <= V1; ++i)
            if (!match[i])
                valid |= dfs(i);

    } while (valid);

    int matching = 0;

    for (int i = 1; i <= V1; ++i)
        if (match[i])
            matching++;

    return matching;
}

void mark(int nod, int side)
{
    if (side == 0) /// vertex from L
    {
        vis[nod] = 1;

        for (int p = head[nod]; p != NIL; p = Graph[p].urm)
        {
            int son = Graph[p].nod;

            if (!vis[son] && match[nod] != son) /// not a edge from the matching
                mark(son, side ^ 1);
        }
    }
    else
    {
        vis[nod] = 1;

        for (int p = head[nod]; p != NIL; p = Graph[p].urm)
        {
            int son = Graph[p].nod;

            if (!vis[son] && match[nod] == son) /// edge from the matching
                mark(son, side ^ 1);
        }
    }
}

int main()
{
    freopen("data.in", "r", stdin);

    scanf("%d %d %d", &V1, &V2, &E);

    for (int i = 1; i <= V1 + V2; ++i)
        head[i] = NIL;

    for (int i = 1; i <= E; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        addEdge(x, V1 + y);
        addEdge(V1 + y, x);
    }

    printf("Maximum independent set: %d\n", V1 + V2 - Hopcroft_Karp());

    for (int i = 1; i <= V1; ++i)
        if (!match[i])
            mark(i, 0);

    printf("Vertices from V1: ");

    for (int i = 1; i <= V1; ++i)
        if (vis[i])
            printf("%d ", i);

    printf("\n");

    printf("Vertices from V2: ");

    for (int i = 1; i <= V2; ++i)
        if (!vis[V1 + i])
            printf("%d ", i);

    printf("\n");

    return 0;
}
