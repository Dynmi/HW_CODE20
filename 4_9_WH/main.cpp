#include <algorithm>
#include <set>
#include <vector>
#include <thread>
using namespace std;
#define MAXN 560010
//#define DEBUG

typedef unsigned int UI;

set<UI, less<UI> > adj[MAXN];   // adj[i]是一个有序集合,包含了节点i的所有流出节点
UI START;
vector<UI> path;              // 存储路径的栈
UI deg[MAXN];                 // 节点的出度
UI max_all,cur_all;
UI cnt,n;                       // 总共几条回路
vector<UI>::iterator w_iter;

UI ver[2 * MAXN];
UI from[MAXN], to[MAXN];
int vLen;

char PATH_IN[100]   = "/data/test_data.txt",
     PATH_OUT[100]  = "/projects/student/result.txt",
     PATH_TEMP[] = "/projects/student/tmp.txt";

FILE *tmp= fopen(PATH_TEMP,"w+");

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
        if(adj[cur].find(START)!=adj[cur].end())
        {
            write_circuit(out);
        }
        path.pop_back(); cur_all--;
        return;
    }

    set<UI, less<UI> >::iterator v = adj[cur].begin();
    while(*v<START && v!=adj[cur].end()){    v++;    }
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


void func(){
    for(START=1;START<=n;START++){
            cur_all=0; path.clear();
            travel(tmp,START);
        }
}


int main()
{
//#ifdef DEBUG
//    clock_t start_t,end_t;
//  start_t = clock();
//#endif

    UI a,b,tp;
    FILE *in = fopen(PATH_IN,"r");

    //read in data
    int j1 = 1, j2 = 1;
    while(fscanf(in,"%d,%d,%d",&a,&b,&tp)!=EOF) {
        from[j1] = a;
        to[j1++] = b;
        ver[j2++] = a;
        ver[j2++] = b;
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

    
    max_all=3;
    thread fir(func);
    fir.join();

    max_all++;
    thread sec(func);
    sec.join();

    max_all++;
    thread thr(func);
    thr.join();

    max_all++;
    thread fort(func);
    fort.join();

    max_all++;
    thread fif(func);
    fif.join();
    

    rewind(tmp);
    FILE *f  = fopen(PATH_OUT,"w");

    fprintf(f,"%d\n",cnt);
    char line[100];
    while( fscanf(tmp,"%s",line)!=EOF ){
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

// cd "/home/dynmi/Documents/HW_CODE20/4_8/" && g++ -O3 main.cpp -o main -lpthread && "/home/dynmi/Documents/HW_CODE20/4_8/"main