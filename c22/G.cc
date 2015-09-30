#include <bits/stdc++.h>
#define ONLINE_JUDGE
#ifdef ONLINE_JUDGE
	#define out(x)
#else
	#define out(x) cerr<<#x"="<<(x)<<endl
#endif
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
int n, k;
char s[16][16];
vi seq[16];
struct St{
	int id, msk;
	vi a;
	St(int id, int msk, vi a=vi(0)):id(id),msk(msk),a(a){}
	St(){}
	bool operator<(const St &r) const {
		if(id!=r.id)return id<r.id;
		if(msk!=r.msk)return msk<r.msk;
		return a<r.a;
	}
	void print(){
		#ifndef ONLINE_JUDGE
		fprintf(stderr,"=====\n%d %d\n", id, msk);
		REP(i,a.size())fprintf(stderr,"%c%c",a[i]+'A'," \n"[i+1==a.size()]);
		#endif
	}
};
map<St, St> pp;
vi proc(char *s){
	vi res;
	REP(i,k)res.pb(s[i]-'A');
	reverse(res.begin(), res.end());
	return res;
}
St st;
int pos[16];
bool try1(St now, int id){
	out(id);
	now.print();
	now.msk|=1<<id;
	vi tmp=seq[now.id], nxt=seq[id];
	reverse(nxt.begin(), nxt.end());
	for(auto u: now.a)tmp.pb(u);
	int j=0;
	memset(pos,-1,sizeof pos);
	REP(i,tmp.size())pos[tmp[i]]=i;
	now.a.clear();
	REP(i,nxt.size()){
		int t=pos[nxt[i]];
		if(~t && t<j){
			out("failed");
			return false;
		}
		if(~t){
			j=t;
			tmp[t]=-1;
		} else j=1000;
	}
	for(auto u: tmp)if(~u)now.a.pb(u);
	now.id = id;
	st=now;
	out("success");
	now.print();
	return true;
}
void print(St st){
	st.print();
	if(st.id==-1)return;
	print(pp[st]);
	putchar('A'+st.id);
}
int main(){
	//freopen("G.in", "r", stdin);
	scanf("%d%d",&n,&k);
	REP(i,n)scanf("%s",s[i]);
	REP(i,n)seq[i]=proc(s[i]);
	queue<St> q;
	REP(i,n){
		St tmp(i,1<<i);
		q.push(tmp);
		pp[tmp]=St(-1,0);
	}
	while(!q.empty()){
		St now=q.front();
		//now.print();
		q.pop();
		REP(i,n)if(~now.msk&(1<<i)){
			if(try1(now, i)){
				auto it=pp.find(st);
				if(it==pp.end()){
					pp[st]=now;
					q.push(st);
					if(st.msk==(1<<n)-1){
						out("found");
						print(st);
						putchar('\n');
						return 0;
					}
				}
			}
		}
	}
}
