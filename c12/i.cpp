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
#define pb push_back
#define mp make_pair
#define X first
#define Y second
char s[2][1123];
int main(){
	REP(i,2)gets(s[i]);
	char *u = s[0], *v = s[1];
	int ans=0;
	while(*u && *v){
		if(*u==*v){
			++u;
			++v;
		} else if(*u=='L'){
			++v;
		} else if(*v=='L'){
			++u;
		} else {
			++u;
			++v;
		}
		ans++;
	}
	while(*u)++u,++ans;
	while(*v)++v,++ans;
	printf("%d\n", ans);
}
