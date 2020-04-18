#include<bits/stdc++.h>

using namespace std;
#define MAXN 560005

#define DEBUG
#define MAXS 41943040
typedef unsigned int UI;
char PATH_IN[50]   = "test_data_10000_50000.txt",
     PATH_OUT[50]  = "result2.txt";
struct Edges{
	int s,t,nxt;
	Edges(int _s,int _t,int _nxt):s(_s),t(_t),nxt(_nxt){}
	Edges(){s = t  = nxt = 0;}
}e[MAXN];
int e_tot = 0,head[MAXN];
void add(int u,int v){
	e[++e_tot] = Edges(u,v,head[u]);
	head[u] = e_tot;
}

FILE *f;
//char dis[28010][28010];
set<UI, less<UI> > adj[MAXN];
UI path[8];
UI deg[MAXN];
UI ru[MAXN];
UI START,max_all,cur_all,cnt,n;
UI ver[2 * MAXN],from[MAXN], to[MAXN];
int vLen,tot;
char buf[MAXS];
UI numbers[MAXN];
inline void analyse(char *buf,int len = MAXS)
{
    numbers[++tot]=0;
    for (register char *p=buf;*p && p-buf<len;p++)
        /*if (*p<'0' || *p>'9')
            numbers[++tot]=0;
        else
        	numbers[tot]=(numbers[tot]<<3)+(numbers[tot]<<1)+((*p)^48);*/
            //numbers[tot] = numbers[tot] * 10 + *p - '0';
        (*p<'0' || *p>'9')? numbers[++tot]=0:numbers[tot] = numbers[tot] * 10 + *p - '0';
}
inline void fread_analyse()
{
    freopen(PATH_IN,"rb",stdin);
    int len = fread(buf,1,MAXS,stdin);
    buf[len] = '\0';
    analyse(buf,len);
}
inline void write(UI x){
   // if(x<0) x=-x , putchar('-');
    static UI sta[35];
    UI top = 0;
    do{
        sta[top++] = x % 10 , x /= 10;
    }while(x);
    while(top) fputc(sta[--top]+'0',f);
    return ;
}

inline void write_circuit()
{
    //fprintf(f,"%d",ver[path[0]]);
    write(ver[path[0]]);
    /*iii=1;
    while(iii<cur_all)
    {
        fprintf(f,",%d",ver[path[iii]]);
        iii++;
    }*/
    for(register UI i = 1;i<cur_all;++i){
		fputc(',',f),write(ver[path[i]]);
	}
    //fprintf(f,"\n");
	fputc('\n',f);
    cnt++;
}

inline bool FIND(UI *NUM){

    for(register UI i=0;i<cur_all;++i){
		if(path[i] == *NUM)return false;
	}
    return true;
}

void travel(UI *cur)
{
    path[cur_all]=*cur; ++cur_all;
	
    if(cur_all==max_all)
    {
        if(adj[*cur].find(START)!=adj[*cur].end())
        {
            write_circuit();
        }
        --cur_all;
        return;
    }

    register auto v = adj[*cur].begin();
    register auto ed = adj[*cur].end();
    while( v!=ed ){
        if(*v<=START){ ++v; continue; }
        
        //if(dis[*v][START]>(max_all-cur_all+1)){++v;continue;}
        if(deg[*v]==0){++v;continue;}
        if(ru[*v] == 0){++v;continue;}
        UI next = *v;
        if(FIND(&next)){
            travel(&next);
        }
        ++v;
    }

    --cur_all;

}

inline UI newIdx(UI *x){
    return lower_bound(ver + 1, ver + vLen + 1, *x) - ver;
}

inline void func(){
    for(START=1;START<=n;++START){
            cur_all=0;
            if(deg[START]==0)continue;
            if(ru[START] == 0)continue;
            travel(&START);
    }
}

UI a,b,tp;
int j1 = 1, j2 = 1;
inline void process1(){
    sort(ver + 1, ver + j2); // nlogn
    vLen = unique(ver + 1, ver + j2) - ver - 1;
}
inline void process2(){
    for(register int k = 1; k < j1; ++k){
        a = newIdx(&from[k]);
		b = newIdx(&to[k]);
		n = max(n, max(a, b));
		adj[a].insert(b);
		++deg[a];
		++ru[b];
		add(b,a);
    }
}
bool vis[MAXN];
inline void init(){
	queue<UI>q;
	for(register UI i=1;i<=n;++i){
		if(ru[i] == 0 || deg[i] == 0){q.push(i);vis[i] = 1;}
		
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		register auto v = adj[u].begin();
	    register auto ed = adj[u].end();
	    while( v!=ed ){
	        --ru[*v];
	        if(ru[*v] == 0 && !vis[*v]){q.push(*v);vis[*v] = 1;}
	        ++v;
	    }
	    for(int i=head[u];i;i = e[i].nxt){
			int v = e[i].t;
			--deg[v];
			if(deg[v] == 0 && !vis[v]){q.push(v);vis[v] = 1;}
		}
	}
}
int main()
{
#ifdef DEBUG
   clock_t start_t,end_t;
    start_t = clock();
#endif

	fread_analyse();
    //FILE *in = fopen(PATH_IN,"r");
    //while(fscanf(in,"%d,%d,%d",&a,&b,&tp)!=EOF) {
    for(register int i=1;i<=tot;i+=3){
	    from[j1] = numbers[i];
        to[j1++] = numbers[i+1];
        ver[j2++] = numbers[i];
        ver[j2++] = numbers[i+1];
    }
    //fclose(in);*/
	process1();
	process2();
    //thread pr1(process1);
    //pr1.join();
    //thread pr2(process2);
    //pr2.join();
	
	init();
	//thread pr3(init);
	//pr3.join();
	
    f = fopen(PATH_OUT,"w+");
    fprintf(f,"       \n");
    max_all=3;
    //thread fir(func);
    //fir.join();
    func();
	
    ++max_all;
    //thread sec(func);
    //sec.join();
	func();
    ++max_all;
    //thread thr(func);
    //thr.join();
	func();
    ++max_all;
    //thread fort(func);
    //fort.join();
	func();
    ++max_all;
    //thread fif(func);
    //fif.join();
	func();
    rewind(f);//fprintf(f,"%d",cnt);
	write(cnt);
    fclose(f);

#ifdef DEBUG
    end_t=clock();
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("%f seconds\n",total_t);
#endif

    return 0;
}

