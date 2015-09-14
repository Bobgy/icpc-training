#include <bits/stdc++.h>
using namespace std;
#define out(x) cerr<<#x"="<<x<<endl
char buf[112];
typedef __int128 LL;
//typedef long long LL;
const long long MAXN = 1123456;
//const long long MAXN = 1123;
LL getInt128(){
    scanf("%s",buf);
    LL res=0;
    for(char *p=buf; *p; ++p)
        res=res*10+(*p-'0');
    return res;
}
map<LL, int> pa, pb, pg;
inline void test(LL &x, LL p, map<LL, int> &mp){
    while(x%p==0){
        x/=p;
        mp[p]++;
    }
}
void gao(LL &x, map<LL, int> &mp){
    test(x, 2, mp);
    for(LL i=3; i<=MAXN && i<=x; i+=2)
        test(x, i, mp);
    if(x>1 && x<MAXN*MAXN){
        mp[x]++;
        x=1;
    }
}
void test_sqr(LL &x, map<LL, int> &mp){
    if(x<=1)return;
    LL L=2, R=2;
    while(R*R<x)R*=2;
    while(L<R){
        LL M=L+(R-L)/2;
        if (x<=M*M) R = M;
        else L = M + 1;
    }
    if(L*L==x){
        mp[L]+=2;
        x=1;
    }
}
void test_cube(LL &x, map<LL, int> &mp){
    if(x<=1)return;
    LL L=2, R=2;
    while(R*R*R<x)R*=2;
    while(L<R){
        LL M=L+(R-L)/2;
        if (x<=M*M*M) R = M;
        else L = M + 1;
    }
    if(L*L*L==x){
        mp[L]+=3;
        x=1;
    }
}
void print(map<LL, int> &mp){
    /*
    puts("=======");
    for(auto u: mp){
        printf("(%lld, %d)\n", u.first, u.second);
    }
    */
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        LL a, b, g;
        a = getInt128();
        b = getInt128();
        g = __gcd(a, b);
        a /= g; b /= g;
        gao(g, pg);
        gao(a, pa);
        gao(b, pb);
        if(!pg.empty()){
            test(a, pg.rbegin()->first, pa);
            test(b, pg.rbegin()->first, pb);
        }
        test_sqr(a, pa);
        test_sqr(b, pb);
        test_sqr(g, pg);
        test_cube(a, pa);
        test_cube(b, pb);
        test_cube(g, pg);
        for(auto u: pg){
            pa[u.first]+=u.second;
            pb[u.first]+=u.second;
        }
        long long a0=1, a1=1;
        for(auto u: pa)a0*=u.second;
        for(auto u: pb)a1*=u.second;
        print(pa);
        print(pb);
        //out(a); out(b); out(g);
        printf("%lld %lld\n", a0, a1);
        pa.clear();
        pb.clear();
        pg.clear();
    }
}
