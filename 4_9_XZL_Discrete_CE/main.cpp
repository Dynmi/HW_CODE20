#include <algorithm>
#include <set>
#include <vector>

#define MAXN 560010
// #define DEBUG

using namespace std;

typedef unsigned int UI;

set<UI, less<UI> > adj[MAXN];   // adj[i]是一个有序集合,包含了节点i的所有流出节点  升序
UI START;
vector<UI> path;              // 存储路径的栈
UI deg[MAXN];                 // 节点的出度
UI max_all,cur_all;
UI cnt;                       // 总共几条回路
vector<UI>::iterator w_iter;

UI ver[2 * MAXN];
UI from[MAXN], to[MAXN];
int vLen;

char PATH_IN[]   = "/data/test_data.txt",
     PATH_OUT[]  = "/projects/student/result.txt",
     PATH_TEMP[] = "tmp.out";


// 将path写入到文件中
void write_circuit(FILE *out)
{
    w_iter = path.begin();
    fprintf(out,"%d", ver[*w_iter]);
    while( (++w_iter)!=path.end() ){
        fprintf(out,",%d",ver[*w_iter]);
    }
    fprintf(out,"\n");
    cnt++;
}


void travel(FILE *out,UI cur)
{
    path.push_back(cur); cur_all++;
    if(cur_all==max_all)
    {
        if(adj[cur].find(START)!=adj[cur].end()){
            write_circuit(out);
        }
        path.pop_back(); cur_all--;
        return;
    }

    set<UI, less<UI> >::iterator v = adj[cur].begin();
    while(*v<START && v!=adj[cur].end()){    v++;    } // 每条循环转账中，ID（ID转为无符号整数后）最小的第一个输出；
    while( v!=adj[cur].end() ){
        UI next = *v;
        if(deg[next]!=0 && find(path.begin(),path.end(),next)==path.end())
        {
            travel(out,next);
        }
        v++;
    }
    path.pop_back(); cur_all--;

}

UI newIdx(UI x){
    return std::lower_bound(ver + 1, ver + vLen + 1, x) - ver;
}


int main()
{
//    #ifdef DEBUG
//    clock_t start_t,end_t;
//    start_t = clock();
//    #endif

    UI a,b,tp,n=0;
    FILE *in = fopen(PATH_IN,"r"),
         *tmp= fopen(PATH_TEMP,"w");

    //读入数据
    int j1 = 1, j2 = 1;
    while(fscanf(in,"%d,%d,%d",&a,&b,&tp)!=EOF) {
        from[j1] = a;
        to[j1++] = b;
        ver[j2++] = a;
        ver[j2++] = b;
//        n = max(n,max(a,b)); // 点的最大搜索范围
//        adj[a].insert(b);
//        deg[a]++;
    }
    sort(ver + 1, ver + j2); // nlogn
    vLen = std::unique(ver + 1, ver + j2) - ver - 1;

    for(int k = 1; k < j1; k++){
        a = newIdx(from[k]);
        b = newIdx(to[k]);  // logn
        n = max(n, max(a, b));
        adj[a].insert(b);
        deg[a]++;
    }

    fclose(in);

    for(max_all=3;max_all<=7;max_all++){
        for(START=1;START<=n;START++){
            cur_all=0; path.clear();
            travel(tmp,START);
        }
    } 
    fclose(tmp);

    FILE *f  = fopen(PATH_OUT,"w"),
        *tmp_= fopen(PATH_TEMP,"r");

    fprintf(f,"%d\n",cnt);
    char line[100];
    while( fscanf(tmp_,"%s",line)!=EOF ){
        fprintf(f,"%s\n",line);
    }
    fclose(tmp); fclose(f);

//#ifdef DEBUG
//    end_t=clock();
//    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//    printf("%f seconds\n",total_t);
//#endif


    return 0;
}