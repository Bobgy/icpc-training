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
#define REP(i,n) for(int i=0; i<int(n); ++i)
#define RER(i,l,r) for(int i=l; i<=int(r); ++i)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
int f[2123][2123];
const int MOD = 258280327, int RT = 5;
int power(int x, int n){
	int res=1;
	for(; n; n>>=1, x=x*(LL)x % MOD)if(n&1)
		res = res*(LL)x % MOD;
	return res;
}
int inv(int x){return power(x, MOD-2);};
int P[2123];
void init(){
	P[0]=1;
	REP(i,2122)P[i+1]=P[i]*(LL)(i+1)%MOD;
}
bitset<MOD> vis;
bool check(int rt){
    vis.reset();
    LL res=1;
    bool ok=1;
    REP(i,MOD-1){
        res=res*rt%MOD;
        if(vis[res]){
            ok=0;
            break;
        }
        vis[res]=1;
    }
    return ok;
}
void find_rt(){
    int rt=-1;
    for(int i=2; i<100; ++i){
        if(check(i)){
            rt=i;
            break;
        } else {
            out(i);
        }
    }
    out(rt);
}
int main(){
    //find_rt();
	init();
	int T;
	scanf("%d",&T);
	while(T--){
		int n, x, y, p;
		scanf("%d%d%d",&n,&x,&y);
		p = x * (LL)inv(y) % MOD;
		REP(i,n)REP(j,n)f[i][j]=0;
		REP(i,n)f[0][i]=inv(i+1);
		REP(i,n-1){
			RER(j,i+1,n-1){
				f[i+1][j]=0;
				RER(k,1,j){
					LL t1 = f[i][j-k] * (LL)power(1-p, j-k+1)%MOD * inv(P[j-k])%MOD;
					LL t2 = power(p, k-1) * (LL)P[j-1]%MOD * inv(P[k-1])%MOD * j%MOD * inv(j+1)%MOD;
					//out(t1);
					//out(t2);
					f[i+1][j]=(f[i+1][j]+t1*t2%MOD+MOD)%MOD;
				}
			}
		}
		REP(i,n)REP(j,n){
			if(f[i][j]<0)f[i][j]+=MOD;
			//printf("%10d%c",f[i][j]," \n"[j+1==n]);
		}
		//puts("=========");
		REP(i,n){
			if(f[i][n-1]<0)f[i][n-1]+=MOD;
			printf("%d%c", f[i][n-1], " \n"[i+1==n]);
		}
	}
}
