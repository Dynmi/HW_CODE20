#include <utility>
#include <vector>
#include <set>
#include <queue>
#include <thread>

using namespace std;
#define MAXN 560005

// #define DEBUG
#define MAXS 41943040
typedef unsigned int UI;
UI max_all3=3,max_all4=4,max_all5 = 5,max_all6=6,max_all7=7;
char PATH_IN[50]   = "test_data_10000_50000.txt",
     PATH_OUT[50]  = "result4.txt";
struct Ans{
	vector<UI>ans;
	Ans(vector<UI> _ans):ans(std::move(_ans)){}
	Ans(){}
	bool operator< (const Ans& other)const {
		int len1 = this->ans.size();
		int len2 = other.ans.size();
		if(len1 == len2){
			for(int i=0;i<len1;++i){
				if(this->ans[i] == other.ans[i])continue;
				return this->ans[i] < other.ans[i];
			}
		}
		return len1<len2;
	}
};
set<Ans>Set;
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
vector<UI> adj[MAXN];
//set<UI, less<UI> > adj[MAXN];
UI path3[8],path4[8],path5[8],path6[8],path7[8];
UI deg[MAXN];
UI ru[MAXN];
UI START3,START4,START5,START6,START7,cnt,n;
UI ver[2 * MAXN],from[MAXN], to[MAXN];
UI cur_all3,cur_all4,cur_all5,cur_all6,cur_all7;
int vLen,tot,ans3,ans4,ans5,ans6,ans7;
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

inline void write_circuit3()
{
    vector<UI>tmp;
	for(register UI i=0;i<cur_all3;++i){
		tmp.push_back(ver[path3[i]]);
	} 
	Set.insert(Ans(tmp));
	++ans3;
}
inline void write_circuit4()
{
    vector<UI>tmp;
	for(register UI i=0;i<cur_all4;++i){
		tmp.push_back(ver[path4[i]]);
	} 
	Set.insert(Ans(tmp));
	++ans4; 
}
inline void write_circuit5()
{
    vector<UI>tmp;
	for(register UI i=0;i<cur_all5;++i){
		tmp.push_back(ver[path5[i]]);
	} 
	Set.insert(Ans(tmp));
	++ans5;
}
inline void write_circuit6()
{
    vector<UI>tmp;
	for(register UI i=0;i<cur_all6;++i){
		tmp.push_back(ver[path6[i]]);
	} 
	Set.insert(Ans(tmp));
	++ans6;
}
inline void write_circuit7()
{
    vector<UI>tmp;
	for(register UI i=0;i<cur_all7;++i){
		tmp.push_back(ver[path7[i]]);
	} 
	Set.insert(Ans(tmp));
	++ans7;
}
inline void printans(){
	f = fopen(PATH_OUT,"w");
	UI ans = ans3+ans4+ans5+ans6+ans7;
	write(ans);
	fputc('\n',f);
	for(auto it:Set){
		write(it.ans[0]);
		for(auto ait = it.ans.begin();ait!=it.ans.end();++ait){
			if(ait == it.ans.begin())continue;
			fputc(',',f);
			write(*ait);
		}
		fputc('\n',f);
	}
	fclose(f);
}
inline bool FIND3(UI *NUM){

    for(register UI i=0;i<cur_all3;++i){
		if(path3[i] == *NUM)return false;
	}
    return true;
}
inline bool FIND4(UI *NUM){

    for(register UI i=0;i<cur_all4;++i){
		if(path4[i] == *NUM)return false;
	}
    return true;
}
inline bool FIND5(UI *NUM){

    for(register UI i=0;i<cur_all5;++i){
		if(path5[i] == *NUM)return false;
	}
    return true;
}
inline bool FIND6(UI *NUM){

    for(register UI i=0;i<cur_all6;++i){
		if(path6[i] == *NUM)return false;
	}
    return true;
}
inline bool FIND7(UI *NUM){

    for(register UI i=0;i<cur_all7;++i){
		if(path7[i] == *NUM)return false;
	}
    return true;
}
void travel3(UI *cur)
{
    path3[cur_all3]=*cur; ++cur_all3;
	
    if(cur_all3==max_all3)
    {
        if(find(adj[*cur].begin(),adj[*cur].end(),START3)!=adj[*cur].end())
        {
            write_circuit3();
        }
        --cur_all3;
        return;
    }

    register auto v = adj[*cur].begin();
    register auto ed = adj[*cur].end();
    while( v!=ed ){
        if(*v<=START3){ ++v; continue; }
        
        //if(dis[*v][START]>(max_all-cur_all+1)){++v;continue;}
        if(deg[*v]==0){++v;continue;}
        if(ru[*v] == 0){++v;continue;}
        UI next = *v;
        if(FIND3(&next)){
            travel3(&next);
        }
        ++v;
    }

    --cur_all3;

}
void travel4(UI *cur)
{
    path4[cur_all4]=*cur; ++cur_all4;
	
    if(cur_all4==max_all4)
    {
        if(find(adj[*cur].begin(),adj[*cur].end(),START4)!=adj[*cur].end())
        {
            write_circuit4();
        }
        --cur_all4;
        return;
    }

    register auto v = adj[*cur].begin();
    register auto ed = adj[*cur].end();
    while( v!=ed ){
        if(*v<=START4){ ++v; continue; }
        
        //if(dis[*v][START]>(max_all-cur_all+1)){++v;continue;}
        if(deg[*v]==0){++v;continue;}
        if(ru[*v] == 0){++v;continue;}
        UI next = *v;
        if(FIND4(&next)){
            travel4(&next);
        }
        ++v;
    }

    --cur_all4;

}
void travel5(UI *cur)
{
    path5[cur_all5]=*cur; ++cur_all5;
	
    if(cur_all5==max_all5)
    {
         if(find(adj[*cur].begin(),adj[*cur].end(),START5)!=adj[*cur].end())
        {
            write_circuit5();
        }
        --cur_all5;
        return;
    }

    register auto v = adj[*cur].begin();
    register auto ed = adj[*cur].end();
    while( v!=ed ){
        if(*v<=START5){ ++v; continue; }
        
        //if(dis[*v][START]>(max_all-cur_all+1)){++v;continue;}
        if(deg[*v]==0){++v;continue;}
        if(ru[*v] == 0){++v;continue;}
        UI next = *v;
        if(FIND5(&next)){
            travel5(&next);
        }
        ++v;
    }

    --cur_all5;

}
void travel6(UI *cur)
{
    path6[cur_all6]=*cur; ++cur_all6;
	
    if(cur_all6==max_all6)
    {
         if(find(adj[*cur].begin(),adj[*cur].end(),START6)!=adj[*cur].end())
        {
            write_circuit6();
        }
        --cur_all6;
        return;
    }

    register auto v = adj[*cur].begin();
    register auto ed = adj[*cur].end();
    while( v!=ed ){
        if(*v<=START6){ ++v; continue; }
        
        //if(dis[*v][START]>(max_all-cur_all+1)){++v;continue;}
        if(deg[*v]==0){++v;continue;}
        if(ru[*v] == 0){++v;continue;}
        UI next = *v;
        if(FIND6(&next)){
            travel6(&next);
        }
        ++v;
    }

    --cur_all6;

}
void travel7(UI *cur)
{
    path7[cur_all7]=*cur; ++cur_all7;
	
    if(cur_all7==max_all7)
    {
         if(find(adj[*cur].begin(),adj[*cur].end(),START7)!=adj[*cur].end())
        {
            write_circuit7();
        }
        --cur_all7;
        return;
    }

    register auto v = adj[*cur].begin();
    register auto ed = adj[*cur].end();
    while( v!=ed ){
        if(*v<=START7){ ++v; continue; }
        
        //if(dis[*v][START]>(max_all-cur_all+1)){++v;continue;}
        if(deg[*v]==0){++v;continue;}
        if(ru[*v] == 0){++v;continue;}
        UI next = *v;
        if(FIND7(&next)){
            travel7(&next);
        }
        ++v;
    }

    --cur_all7;

}
inline UI newIdx(UI *x){
    return lower_bound(ver + 1, ver + vLen + 1, *x) - ver;
}

inline void func3(){
    for(START3=1;START3<=n;++START3){
            cur_all3=0;
            if(deg[START3]==0)continue;
            if(ru[START3] == 0)continue;
            travel3(&START3);
    }
}
inline void func4(){
    for(START4=1;START4<=n;++START4){
            cur_all4=0;
            if(deg[START4]==0)continue;
            if(ru[START4] == 0)continue;
            travel4(&START4);
    }
}
inline void func5(){
    for(START5=1;START5<=n;++START5){
            cur_all5=0;
            if(deg[START5]==0)continue;
            if(ru[START5] == 0)continue;
            travel5(&START5);
    }
}
inline void func6(){
    for(START6=1;START6<=n;++START6){
            cur_all6=0;
            if(deg[START6]==0)continue;
            if(ru[START6] == 0)continue;
            travel6(&START6);
    }
}
inline void func7(){
    for(START7=1;START7<=n;++START7){
            cur_all7=0;
            if(deg[START7]==0)continue;
            if(ru[START7] == 0)continue;
            travel7(&START7);
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
		adj[a].push_back(b);
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

    for(register int i=1;i<=tot;i+=3){
	    from[j1] = numbers[i];
        to[j1++] = numbers[i+1];
        ver[j2++] = numbers[i];
        ver[j2++] = numbers[i+1];
    }

	process1();
	process2();

	init();

    thread fir(func3);
    
    thread sec(func4);
    
    thread thr(func5);
    

    thread fort(func6);

    thread fif(func7);
    fir.join();
    sec.join();
    thr.join();
    fort.join();
    fif.join();
    
	printans();
#ifdef DEBUG
    end_t=clock();
    double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("%f seconds\n",total_t);
#endif

    return 0;
}

