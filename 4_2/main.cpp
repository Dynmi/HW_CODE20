#include <bits/stdc++.h>
#define MAXN 560010  
using namespace std;

set<int, less<int>> adj[MAXN];   // adj[i]是一个有序集合,包含了节点i的所有流出节点
int START;
vector<int> path;              // 存储路径的栈
int deg[MAXN];                 // 节点的出度
int max_all,cur_all;
int cnt,n;                       // 总共几条回路
vector<int>::iterator w_iter;

char PATH_IN[100]   = "/home/dynmi/Documents/HW_CODE20/4_2/test_data.txt",
     PATH_OUT[100]  = "/home/dynmi/Documents/HW_CODE20/4_2/result.txt";


// 将path写入到文件中
void write_circuit(FILE *out)
{
    w_iter = path.begin();
    fprintf(out,"%d",*w_iter);
    while( (++w_iter)!=path.end() ){
        fprintf(out,",%d",*w_iter);
    }
    fprintf(out,"\n");
    cnt++;
}


void travel(FILE *out,int cur)
{
    path.push_back(cur); cur_all++;

    if(cur_all==max_all)
    {
        if(adj[cur].find(START)!=adj[cur].end())
        {
            write_circuit(out);
        }
        path.pop_back(); cur_all--;
        return;
    }

    auto v = adj[cur].begin();
    while(*v<START && v!=adj[cur].end()){    v++;    }
    while( v!=adj[cur].end() ){
        int next = *v;
        if(deg[next]!=0 && find(path.begin(),path.end(),next)==path.end())
        {
            travel(out,next);
        }

        v++;
    }

    path.pop_back(); cur_all--;

}

int main()
{
    clock_t start_t,end_t;
    start_t = clock();

    int a,b,tp;
    FILE *in = fopen(PATH_IN,"r"),
         *tmp= fopen("/home/dynmi/Documents/HW_CODE20/4_2/tmp.txt","w+");

    //读入数据
    while(fscanf(in,"%d,%d,%d",&a,&b,&tp)!=EOF)
    {
        n = max(n,max(a,b));
        adj[a].insert(b);
        deg[a]++;
    }
    fclose(in);

    fprintf(tmp,"        \n");
    
    /*
    max_all=3;
    thread fir(func,tmp);
    max_all++;
    thread sec(func,tmp);
    max_all++;
    thread thr(func,tmp);
    max_all++;
    thread fort(func,tmp);
    max_all++;
    thread fif(func,tmp);
    fir.detach();
    sec.detach();
    thr.detach();
    fort.detach();
    fif.detach();
    */
    
    for(max_all=3;max_all<=7;max_all++){
        for(START=1;START<=n;START++){
            cur_all=0; path.clear();
            travel(tmp,START);
        }
    }
    rewind(tmp);

    FILE *OUT = fopen(PATH_OUT,"w");
    fprintf(OUT,"%d\n",cnt);
    char line[100];
    while( fscanf(tmp,"%s",line)!=EOF ){
        fprintf(OUT,"%s\n",line);
    }
    fclose(tmp); fclose(OUT);
    end_t=clock();
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("%f seconds\n",total_t);

    return 0;
}

