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
const char *L[3] = {
	"APOR",
	"BMS",
	"DGJKTW"
};
char s[1123];
int main(){
	int n, pos=0, ans=0;
	scanf("%d ",&n);
	REP(i,n){
		scanf("%s", s);
		int id=-1;
		REP(i,3){
			for(const char *p=L[i]; *p; ++p)
				if(*p==s[0]){
					id=i;
					break;
				}
			if(~id)break;
		}
		ans+=abs(pos-id);
		pos=id;
	}
	printf("%d\n", ans);
}
