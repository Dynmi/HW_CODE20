#include <iostream>
#include <cstdio>

const int maxe = 280001, maxv = 560002;

struct edge{
    int next, to, w;
}e[maxe];

int head[maxv]; // 以i为起点的 第一条边的存储位置
int cnt = 0;

inline void add(int u, int v, int w){
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt++;
    //    e[++tot] = edge(u, v, w, head[u]);
//    head[u] = tot;
}




inline void parseLine(char* line, int& from, int& to, int& amount){
    char* prev = line;
    while(*line != ',') line++;
    *line = '\0';
    from = atoi(prev);
    prev = line + 1;
    while(*line != ',') line++;
    *line = '\0';
    to = atoi(prev);
    prev = line + 1;
    amount = atoi(prev);
}


int main() {
    FILE *fp;
    char line[99]; // 3 * 32 + 2 + 1
    int from, to, amount;
    fp = fopen("test_data.txt", "r");
    assert(fp != nullptr);
    while(!feof(fp)){
        if(fgets(line, 99, fp) == nullptr) break;
        parseLine(line, from, to, amount);

//        printf("%d %d %d\n", from, to, amount);
    }
    fclose(fp);
    return 0;
}
