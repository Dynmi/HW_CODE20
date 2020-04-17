#include<bits/stdc++.h>
const int MAXN = 5600005;
using namespace std;
typedef unsigned int UI;
typedef list<int> NodeList;
unordered_map<UI,int>mp;
UI remap[MAXN];
vector<UI>Stack;
vector<bool>Blocked;
vector<NodeList> B;
struct Ans{
	vector<UI>ans;
	Ans(vector<UI> _ans):ans(_ans){}
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
int S = 1;//_10000_50000
int mp_tot = 0;
char PATH_IN[100]   = "test_data_10000_50000.txt",
     PATH_OUT[100]  = "my_result0.txt";
struct Edges{
	int s,t,nxt;
	Edges(int _s,int _t,int _nxt):s(_s),t(_t),nxt(_nxt){}
	Edges(){s = t = nxt = 0;}
}e[MAXN];
int head[MAXN],e_tot = 0;
inline void add(int u,int v){
	e[++e_tot] = Edges(u,v,head[u]);
	head[u] = e_tot;
}
/*inline void read(UI &x){
    x=0;char s=getchar();
    while(s<'0'||s>'9'){s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	return ;
}*/
inline void write(UI x){
   // if(x<0) x=-x , putchar('-');
    static UI sta[35];
    UI top = 0;
    do{
        sta[top++] = x % 10 , x /= 10;
    }while(x);
    while(top) putchar(sta[--top]+'0');
    return ;
}
inline void printans(){
	freopen(PATH_OUT,"w",stdout);
	UI len = Set.size();
	write(len);
	putchar('\n');
	for(auto it = Set.begin(),ed = Set.end();it!=ed;++it){
		for(auto ait = it->ans.begin(),aed = it->ans.end();ait!=aed;++ait){
			if(ait!=it->ans.begin())putchar(',');
			write(*ait);
			
		}
		putchar('\n');
	}
}


inline void output(){
	if(Stack.size()>=3 && Stack.size()<=7){
		vector<UI>tmp,ans;
		tmp = Stack;
		int len = tmp.size();
		unsigned long long minn = 4294967295llu;
		int pos = 0;
		for(register int i=0;i<len;++i)	if(remap[tmp[i]]<minn){minn = remap[tmp[i]];pos = i;}
		for(register int i=pos;i<len;++i) ans.push_back(remap[tmp[i]]);
		for(register int i=0;i<pos;++i) ans.push_back(remap[tmp[i]]);
		Set.insert(Ans(ans));
		return;
	}else return;
	return;
}
void unblock(int u){
	//cout<<u<<endl;
	Blocked[u-1] = false;
	while(!B[u-1].empty()){
		int v = B[u-1].front();
		B[u-1].pop_front();
		if(Blocked[v-1]){
			unblock(v);
		}
	}
} 
int circuit(int fa,int u,int l){
	
	int flag = 0;
	Stack.push_back(u);//24285
	//if(remap[S] == 587 && remap[u] == 12340)cout<<"fa="<<remap[fa]<<endl;
	//if(remap[S]==587 && remap[u] == 29110 && Blocked[mp[29110]-1] == false)cout<<"l="<<l<<"u = "<<remap[u];
	Blocked[u-1] = true;
	
	for(int i=head[u];i;i=e[i].nxt){
		int v = e[i].t;
		//if(remap[u] == 25083 && S == 5562){cout<<l<<" v="<<remap[v]<<endl;}
	//	if(remap[v] == 29110 && S == 5562)cout<<"S = "<<remap[S]<<"l="<<l<<"blv = "<<Blocked[v-1]<<" "<<endl;
		if(v == S){
			//if(l>7 || l<=2){flag = 1;continue;}
			output();
			flag = 2;
		}else if(v>S && !Blocked[v-1]){
		//	if(remap[v] == 29110 && S == 5562)cout<<"S = "<<remap[S]<<"l="<<l<<"blv = "<<Blocked[v-1]<<" "<<endl;
			if(l > 7){
				flag = 1;
				//Blocked[u] = false;
				continue;
			}
			else {
				flag = circuit(u,v,l+1);
			}
		}
	}
	
	if(flag == 2 || flag == 1){
		unblock(u);
	}else{
		for(int i=head[u];i;i=e[i].nxt){
			int v = e[i].t;
			auto it = std::find(B[v-1].begin(),B[v-1].end(),u);
			if(it == B[v-1].end()){
				B[v-1].push_back(u);
			}
		} 
	}
	
	Stack.pop_back();
	return flag;
}
void run(){
	Stack.clear();
	S = 1;
	//cout<<S<<endl;
	Blocked.resize(mp_tot+10);
	B.resize(mp_tot+10);
	while(S<mp_tot){
		for(int i = S;i<=mp_tot;++i){
			Blocked[i-1] = false;
			B[i-1].clear();
		} 
		//cout<<S<<endl;
		circuit(0,S,1);	
		++S;
		write(S);
		putchar('\n');
	}
	return;
}
int main(){
	freopen(PATH_IN,"r",stdin);
	UI u,v,w;
	while(scanf("%d,%d,%d",&u,&v,&w)!=EOF){
	//	read(u);read(v);read(w);
		//cout<<"yes"<<endl;
		if(mp[u] == 0){
			mp[u] = ++mp_tot;
			remap[mp_tot] = u;
		}
		if(mp[v] == 0){
			mp[v] = ++mp_tot;
			remap[mp_tot] = v;
		}
		add(mp[u],mp[v]);
	}
	//cout<<mp[587]<<endl;
	//cout<<mp_tot<<" " <<e_tot<<endl;
	run(); 
	printans();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
//5562
/*
1,2,100
1,3,100
2,4,90
3,4,50
4,1,95
2,5,95
5,4,90
4,6,30
6,7,29
7,4,28
*/
