#include <bits/stdc++.h>
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
typedef unordered_map<string, int> umsi;
#define REP(i,n) for(int i=0; i<int(n); i++)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
int tot=0;
umsi D;
string d[312345];
int getWord(char *p){
	auto it=D.find(p);
	if(it==D.end()){
		int now=D.size();
		//d[now]=p;
		return D[p]=now;
	}
	return it->Y;
}
char buf[512345];
inline char toLower(char ch){
	return (ch>='A' && ch<='Z') ? ch-'A'+'a' : ch;
}
int n, m, a[312345];
void proc(char *s){
	char *p=NULL;
	bool inWord=0;
	for(;; ++s){
		*s=toLower(*s);
		if(*s>='a' && *s<='z'){
			if(inWord){
				//nothing
			} else {
				inWord=1;
				p=s;
			}
		} else {
			if(inWord){
				char tmp=*s;
				*s=0;
				if(p){
					int id=getWord(p);
					a[n++]=id;
				}
				*s=tmp;
				inWord=0;
			} else {
				//nothing
			}
			if(*s==0)break;
		}
	}
}
unordered_set<int> ban;
map<pii,int> cnt_pair;
unordered_map<int,int> cnt_word;
pii mk(int a, int b){
	return a<b ? pii(a,b) : pii(b,a);
}
int count_word(int id){
	auto it = cnt_word.find(id);
	if(it==cnt_word.end())return 0;
	return it->Y;
}
double P(int id){
	int num = count_word(id);
	return num/double(m);
}
double getPair(int id0, int id1){
	auto it = cnt_pair.find(mk(id0,id1));
	if(it==cnt_pair.end())return 0;
	return it->Y;
}
int main(){
	n=0;
	int L;
	scanf("%d ",&L);
	REP(i,L){
		gets(buf);
		proc(buf);
	}
	/*
	for(auto u: D){
		printf("%d %s\n", u.Y, u.X.data());
	}
	REP(i,n){
		printf("%s ", d[a[i]].data());
	}
	putchar('\n');
	*/
	int tt;
	scanf("%d ",&tt);
	while(tt--){
		gets(buf);
		ban.insert(getWord(buf));
	}
	m=0;
	REP(i,n)if(ban.find(a[i])==ban.end()){
		a[m++]=a[i];
	}
	REP(i,m)cnt_word[a[i]]++;
	REP(i,m-1)cnt_pair[mk(a[i],a[i+1])]++;
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%s",buf);
		int id0=getWord(buf);
		scanf("%s",buf);
		int id1=getWord(buf);
		if(count_word(id0)==0 || count_word(id1)==0)puts("0.0");
		else printf("%.10lf\n", getPair(id0,id1)/double(m-1)/P(id0)/P(id1));
	}
}
