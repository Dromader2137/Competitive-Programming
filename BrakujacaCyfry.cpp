#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

std::vector<int> D;

std::vector<std::pair<int, int>> NG[100007];
std::vector<std::pair<int, int>> RG[100007];
int Dst[100007];
int Rst[100007];

void BFS(int* dst, std::vector<std::pair<int, int>>* G) {
    std::queue<int> Q;
    Q.push(0);
    while(!Q.empty()) {
        int c = Q.front(); Q.pop();
        int pdst = dst[c];
        if(c == 0) pdst = 0;
        for(auto x : G[c]) {
            if(dst[x.first] <= pdst + 1) continue;
            else {
                dst[x.first] = pdst + 1;
                Q.push(x.first);
            }
        }
    }
}

std::vector<int> W;
void DFS(int v, int d, int max_d, bool start)
{
    //std::cout << v << " " << d << std::endl;

    if(d == max_d and !start) return;

    for(auto x : NG[v])
    {
        //std::cout << x.first << " " << Dst[x.first] << " " << Rst[x.first] << std::endl;
        if(Dst[x.first] == d + 1 and Dst[x.first] + Rst[x.first] == max_d)
        {
            //std::cout << x.first << " " << x.second << " " << Dst[x.first] << std::endl;
            W.push_back(x.second);
            DFS(x.first, d + 1, max_d, false);
            break;
        }
    }
}

int main() {
    std::string c; int n;
    std::cin >> c >> n;

    std::reverse(c.begin(), c.end());

    for(int i = 0; i < n; ++i) Dst[i] = 1000000000;
    for(int i = 0; i < n; ++i) Rst[i] = 1000000000;
    for(char x : c) D.push_back(x - '0');

    for(int i = 0; i < n; ++i) {
        for(int j : D) {
            if (j == 0 and i == 0) continue;
            NG[i].push_back({(i*10+j)%n,j});
            RG[(i*10+j)%n].push_back({i,j});
        }
    }

    /*for(int i = 0; i < n; ++i)
    {
        std::cout << i << " => ";
        for(auto x : NG[i]) std::cout << "{" << x.first << "," << x.second << "} ";
        std::cout << "\n     ";
        for(auto x : RG[i]) std::cout << "{" << x.first << "," << x.second << "} ";
        std::cout << "\n";
    }*/

    BFS(Dst, NG);
    BFS(Rst, RG);

    //for(int i = 0; i < n; ++i)
    //{
    //    std::cout << i << ": " << Dst[i] << " " << Rst[i] << "\n";
    //}

    if(Dst[0] == 1000000000)
    {
        std::cout << "nie istnieje";
        return 0;
    }

    int zero = Dst[0];
    Rst[0] = 0;
    DFS(0, 0, zero, true);

    //for(int i = 0; i < n; ++i) {
    //    std::cout << Dst[i].first << " " << Dst[i].second << " " << prev[i] << "\n";
    //}
    //

    for(int i = 0; i < W.size(); ++i) std::cout << W[i];
}
