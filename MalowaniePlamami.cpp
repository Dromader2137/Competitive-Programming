#include <iostream>
#include <vector>

struct Node {
    std::vector<Node*> con;
    int c, t, h;
};

struct Query {
    int v, h, c;
};

Node nodes[100007];

void flood(Node* v, int c, int h, int t);

void flood_neighbours(Node* v, int c, int h, int t)
{
    if(h==0) return;

    for(auto x : v->con)
    {
        flood(x, c, h - 1, t);
    }
}

void flood(Node* v, int c, int h, int t) {
    if(v->t >= t)
    {
        if(v->h < h)
        {
            v->h = h;
            flood_neighbours(v, c, h, t);
        }
    }
    else {
        v->c = c; v->h = h; v->t = t;
        flood_neighbours(v, c, h, t);
    }
}

std::vector<Query> queries;

int main()
{
    int N, M, Q;
    std::cin >> N >> M;
    for(int i = 0; i < M; ++i) {
        int a, b; std::cin >> a >> b;
        nodes[a].con.push_back(&nodes[b]);
        nodes[b].con.push_back(&nodes[a]);
    }
    std::cin >> Q;
    for(int i = 0; i < Q; ++i) {
        int v, d, c;
        std::cin >> v >> d >> c;
        queries.push_back({v,d,c});
    }

    for(int i = queries.size() - 1; i >= 0; --i)
    {
        flood(&nodes[queries[i].v], queries[i].c, queries[i].h, i + 1);
    }

    for(int i = 1; i <= N; ++i)
    {
        std::cout << nodes[i].c << "\n";
    }
}
