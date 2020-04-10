#include <algorithm>
#include <set>
#include <vector>
#include <thread>
using namespace std;
#define MAXN 560005

#define DEBUG

typedef unsigned int UI;

set<UI, less<UI> > adj[MAXN];
UI path[8];
UI deg[MAXN];
UI START,max_all,cur_all,cnt,n;
UI ver[2 * MAXN],from[MAXN], to[MAXN];
int vLen;
UI iii;

char PATH_IN[]   = "/home/dynmi/Documents/HW_CODE20/4_10_WH_v2/test_data.txt",
     PATH_OUT[]  = "/home/dynmi/Documents/HW_CODE20/4_10_WH_v2/result.txt";

FILE *f;

inline void write_circuit()
{
    fprintf(f,"%d",ver[path[0]]);
    iii=1;
    while(iii<cur_all)
    {
        fprintf(f,",%d",ver[path[iii]]);
        iii++;
    }
    fprintf(f,"\n");
    cnt++;
}

inline bool FIND(UI *NUM){
    iii=0;
    while(iii<cur_all){
        if(path[iii]==*NUM){return 0;}
        iii++;
    }
    return 1;
}

void travel(UI *cur)
{
    path[cur_all]=*cur; cur_all++;

    if(cur_all==max_all)
    {
        if(adj[*cur].find(START)!=adj[*cur].end())
        {
            write_circuit();
        }
        cur_all--;
        return;
    }

    auto v = adj[*cur].begin();
    while( v!=adj[*cur].end() ){
        if(*v<=START){ v++;continue; }
        UI next = *v;
        if(deg[next]!=0 && FIND(&next))
        {
            travel(&next);
        }
        v++;
    }

    cur_all--;

}

inline UI newIdx(UI *x){
    return std::lower_bound(ver + 1, ver + vLen + 1, *x) - ver;
}

void func(){
    for(START=1;START<=n;START++){
            cur_all=0;
            travel(&START);
    }
}

UI a,b,tp;
int j1 = 1, j2 = 1;
void process1(){
    sort(ver + 1, ver + j2); // nlogn
    vLen = std::unique(ver + 1, ver + j2) - ver - 1;
}
void process2(){
    for(int k = 1; k < j1; k++){
        a = newIdx(&from[k]);
        b = newIdx(&to[k]);  // logn
        n = max(n, max(a, b));
        adj[a].insert(b);
        deg[a]++;
    }
}

int main()
{
#ifdef DEBUG
   clock_t start_t,end_t;
    start_t = clock();
#endif


    FILE *in = fopen(PATH_IN,"r");
    while(fscanf(in,"%d,%d,%d",&a,&b,&tp)!=EOF) {
        from[j1] = a;
        to[j1++] = b;
        ver[j2++] = a;
        ver[j2++] = b;
    }
    fclose(in);

    thread pr1(process1);
    pr1.join();
    thread pr2(process2);
    pr2.join();

    f = fopen(PATH_OUT,"w+");
    fprintf(f,"       \n");
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

    rewind(f);fprintf(f,"%d",cnt);
    fclose(f);

#ifdef DEBUG
    end_t=clock();
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("%f seconds\n",total_t);
#endif

    return 0;
}
