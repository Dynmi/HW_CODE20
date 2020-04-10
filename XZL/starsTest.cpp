//
// Created by Zilin Xiao on 2020/4/9.
//


#include <algorithm>

const int maxe = 280010;
const int maxv = 560010;

char PATH_IN[] = "";
char PATH_OUT[] = "";
char PATH_TEMP[][10] = {
        "tmp3.out", // 0
        "tmp4.out", // 1
        "tmp5.out", // 2
        "tmp6.out", // 3
        "tmp7.out" // 4
};

typedef unsigned int UI;

struct Edge{
    UI next; // 与本边同起点的下一条边的存储位置
    UI to; // 本边终点
}edge[maxe];

int head[maxe];

int cnt = 0;

int maxn; // 离散化后顶点最大值

void add(int u, int v){
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

// 以上 链式前向星相关

//for(int i = head[1]; i != -1; i = edge[i].next){
//printf("%d, %d\n", 1, edge[i].to); // 按添加顺序逆序遍历
//}


UI from[maxv], to[maxv];
UI vertices[2 * maxv];
int vLen;

UI newIdx(UI x){
    return std::lower_bound(vertices + 1, vertices + vLen + 1, x) - vertices;
}

// 以上 离散化相关

int main(){

//    memset(head, -1, sizeof(head));
//
//    add(1, 3);
//    add(1, 2);
//    add(1, 4);



}

// Length of 3 (undirected)
//foreach v ∈ V do
//     foreach s, t ∈ N(v) do
//          if (s, t) ∈ E then
//              return (v, s, t) ;
//return “No triangle”;

void LengthOf3(){   // 先不考虑写入顺序
    for(int u = 1; u <= maxn; u++){

    }
}