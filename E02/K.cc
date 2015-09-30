#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define REP(i,n) for(int i=0;i<int(n);++i)
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
    #define out(x) (cerr<<#x"="<<x<<endl,(x))
#else
    #define out(x) (x)
    #undef assert
    #define assert(x) while(!(x))puts("sdlkfjdsl")
#endif
char s[51234], t[51234];
LL c[3], mCost, sum, ans;
const int MOD = 1e9+7;
int cnt(char s[]){
    int ss=0;
    for(char *p=s;*p;++p)
        ss|=1<<(*p-'x');
    return __builtin_popcount(ss);
}
struct Status {
    int to[3];
    LL cost;
    Status(int x, int y, int z){
        to[0]=x;
        to[1]=y;
        to[2]=z;
        cost=0;
    }
    Status(){}
    bool build() {
        memset(to, -1, sizeof to);
        bool ok=1;
        cost=0;
        int L=strlen(s);
        REP(i,L){
            int ss = s[i] - 'x';
            if(~to[ss] && to[ss]!=t[i]-'x'){
                ok=0;
                break;
            }
            to[ss]=t[i]-'x';
        }
        return ok;
    }
    int size() {
        return (to[0]!=-1) + (to[1]!=-1) + (to[2]!=-1);
    }
    void add_cost(LL x){
        if(cost<=mCost)cost+=x;
    }
    bool move(int i) {
        if(to[i]==-1)return 0;
        int j=(i+1)%3;
        if(~to[j] && to[j]!=to[i])return 0;
        to[j]=to[i];
        to[i]=-1;
        add_cost(c[i]);
        return 1;
    }
    int get_empty() const {
        REP(i,3)if(to[i]==-1)return i;
        return -1;
    }
    bool merge() {
        assert(size()==2);
        REP(i,3)if(~to[i] && ~to[(i+1)%3]){
            return move(i);
        }
        return false;
    }
    void gao1() {
        assert(size()==1);
        REP(i,3)if(~to[i]){
            move(i);
            break;
        }
    }
    void gao2() {
        assert(size()==2);
        int id=get_empty();
        assert(~id);
        assert(move((id+2)%3));
    }
    bool ok() {
        REP(i,3)if(~to[i] && to[i]!=i)return 0;
        return 1;
    }
} st;
void solve1(Status st) {
    assert(st.size()==2);
    REP(i,6){
        Status tmp=st;
        if(tmp.merge()){
            REP(j,6){
                if(tmp.ok() && tmp.cost<=mCost){
                    LL cc = (mCost - tmp.cost) / (2 * sum) % MOD;
                    ans = (ans + (cc + 2) * (cc + 1) % MOD * LL(5e8+4)) % MOD;
                }
                tmp.gao1();
            }
        }
        st.gao2();
    }
}
void solve2(Status st) {
    assert(st.size()==2);
    out("solve2");
    REP(i,6){
        if(st.ok())break;
        st.gao2();
    }
    if (st.ok() && st.cost<=mCost) {
        ans = (ans + ((mCost-st.cost)/(2*sum)+1)) % MOD;
    }
}
int dfs(Status st){
    int res = st.ok();
    REP(i,3){
        Status tmp=st;
        if(tmp.move(i) && tmp.cost<=mCost){
            res += dfs(tmp);
        }
    }
    return res;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        sum=ans=0;
        REP(i,3)scanf("%lld",c+i),sum+=c[i];
        scanf("%lld",&mCost);
        scanf("%s%s",s,t);
        int tt = cnt(t);
        if(!st.build()){
            puts("0");
            continue;
        }
        //int res=dfs(st);
        switch(out(tt)){
            case 1: {
                if(st.size()==3){
                    REP(i,3){
                        Status tmp = st;
                        if(tmp.move(i))solve1(tmp);
                    }
                } else if(st.size()==2) solve1(st);
                else {
                    assert(st.size()==1);
                    while(!st.ok())st.gao1();
                    if(st.cost<=mCost){
                        ans = (ans + ((mCost-st.cost)/sum+1)) % MOD;
                    }
                }
                break;
            }
            case 2: {
                out(st.size());
                if(st.size()==1)ans=0;
                else if(st.size()==3){
                    REP(i,3){
                        Status tmp = st;
                        if(tmp.move(i))solve2(tmp);
                    }
                } else solve2(st);
                break;
            }
            case 3: {
                if(strcmp(s,t)==0)ans=1;
                else ans=0;
                break;
            }
            default:
                assert(0);
        }
        //assert(ans==res);
        printf("%lld\n", ans);
    }
}
