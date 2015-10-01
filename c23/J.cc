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
#define REP(i,n) for(int i=0; i<int(n); i++)
#define RER(i,L,R) for(int i=L;i<=int(R);++i)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
char buf[1123];
int g[1123][1123];
bool lt(int x, int y){
	if(g[x][y])return g[x][y]<0;
	printf("1 %d %d\n", x, y);
	fflush(stdout);
	scanf("%s", buf);
	bool res = strcmp(buf,"YES")==0;
	g[x][y]=res ? -1 : 1;
	g[y][x]=-g[x][y];
	return g[x][y]<0;
}
int main(){
	int n;
	scanf("%d",&n);
	vi a(1,1);
	RER(i,2,n){
		if(lt(i,a.front())){
			a.insert(a.begin(),i);
		} else if(lt(a.back(), i)){
			a.insert(a.end(),i);
		} else {
			int L=1, R=a.size()-1;
			while(L<R){
				int M=(L+R)/2;
				if(!lt(a[M-1],i)){
					R=M-1;
				} else if(!lt(i,a[M])){
					L=M+1;
				} else L=R=M;
			}
			a.insert(a.begin()+L,i);
		}
		/*
		fprintf(stderr, "RES: ");
		REP(i,a.size())fprintf(stderr, "%d%c", a[i], " \n"[i+1==a.size()]);
		*/
	}
	printf("0 ");
	REP(i,a.size())printf("%d%c",a[i]," \n"[i+1==a.size()]);
	fflush(stdout);
}
