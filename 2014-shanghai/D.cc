#include <bits/stdc++.h>
using namespace std;
#define ONLINE_JUDGE
#define REP(i,n) for(int i=0;i<int(n);++i)
#define X first
#define Y second
#define pb push_back
#ifndef ONLINE_JUDGE
    #define out(x) cout<<#x"="<<x<<endl
#else
    #define out(x)
#endif
const int INF=1e8;
int n, w, h;
typedef pair<int, int> pii;
typedef vector<int> vi;
pii p[112345];
int tot;
pii evt[212345];
vi yy;
inline int get_id(int y){
    return lower_bound(yy.begin(), yy.end(), y)-yy.begin();
}
vi cnt;

const int MAXN = 112345;
class SegTree{
private:
    int L, R, N, A;
    struct Node{
        int ma, now, tag, mi;
        bool same;
    } v[MAXN*4];
    inline void down(int x, int l, int m, int r){
        Node &lch=v[x*2], &rch=v[x*2+1];
        if(v[x].tag){
            lch.tag+=v[x].tag;
            rch.tag+=v[x].tag;
            lch.mi+=v[x].tag;
            rch.mi+=v[x].tag;
            v[x].tag=0;
            if(lch.mi>0)lch.now=0;
            if(rch.mi>0)rch.now=0;
        }
    }
    inline void up(int x, int l, int m, int r){
        Node &lch=v[x*2], &rch=v[x*2+1];
        v[x].now=max(lch.now, rch.now);
        v[x].mi=min(lch.mi, rch.mi);
        v[x].same=lch.same && rch.same && lch.mi==rch.mi;
    }
    void _print(int x, int l, int r){
        int m=(l+r)/2;
        if(l<r){
            _print(x*2, l, m);
            _print(x*2+1, m+1, r);
        }
        printf(
            "rg=[%d, %d], ma=%d, now=%d, tag=%d, mi=%d, same=%d\n",
            l, r, v[x].ma, v[x].now, v[x].tag, v[x].mi, (int)v[x].same
        );
    }
    void _build(int x, int l, int r){
        v[x].tag=0;
        v[x].mi=0;
        v[x].same=1;
        if(l==r){
            v[x].ma=cnt[r];
            v[x].now=v[x].ma;
            return;
        }
        int m=(l+r)/2;
        _build(x*2, l, m);
        _build(x*2+1, m+1, r);
        v[x].ma=max(v[x*2].ma, v[x*2+1].ma);
        v[x].now=v[x].ma;
    }
    void _update(int x, int l, int r, bool added=0){
        if(l>R || r<L)return;
        //printf("(%d, %d)\n", l, r);
        if(L<=l && r<=R){
            if(!added){
                v[x].tag+=A;
                v[x].mi+=A;
                added=1;
            }
            bool chg=(A==-1 && v[x].mi==0) || (A==1 && v[x].mi==1);
            if(chg){
                if(v[x].same){
                    v[x].now=v[x].mi ? 0 : v[x].ma;
                    return;
                }
                //continue;
            } else return;
        }
        int m=(l+r)/2;
        down(x, l, m, r);
        _update(x*2, l, m, added);
        _update(x*2+1, m+1, r, added);
        up(x, l, m, r);
    }
public:
    void build(int n){
        N=n;
        _build(1, 0, N);
    }
    int query(){
        return v[1].now;
    }
    void update(int l, int r, int a){
        out(l); out(r); out(a);
        L=l, R=r, A=a;
        _update(1, 0, N);
        print();
    }
    void print(){
#ifndef ONLINE_JUDGE
        puts("=========");
        _print(1, 0, N);
#endif
    }
} seg;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d",&n,&w,&h);
        yy.clear();
        REP(i,n){
            scanf("%d%d",&p[i].X,&p[i].Y);
            yy.pb(p[i].Y);
            yy.pb(p[i].Y+1);
            yy.pb(p[i].Y-h);
            yy.pb(p[i].Y-h+1);
        }
        yy.pb(-INF);
        yy.pb(INF);
        sort(p, p+n);
        sort(yy.begin(), yy.end());
        yy.erase(unique(yy.begin(), yy.end()), yy.end());
        cnt.resize(yy.size());
        REP(i,cnt.size())cnt[i]=0;
        REP(i,n){
            int y=p[i].Y;
            int id=get_id(y);
            cnt[id]++;
        }
        int j=0, sum=0;
        REP(i,yy.size()-1){
            for(; yy[j+1]<yy[i]+h; ++j)
                sum+=cnt[j+1];
            int tmp=sum;
            sum-=cnt[i];
            cnt[i]=tmp;
        }
        seg.build(cnt.size()-1);
        #ifndef ONLINE_JUDGE
        REP(i,cnt.size())printf("(%d,%d)%c", yy[i], cnt[i], " \n"[i+1==cnt.size()]);
        #endif
        tot=0;
        REP(i,n){
            evt[tot++]=pii(p[i].X, -i-1);
            evt[tot++]=pii(p[i].X-w, i+1);
        }
        sort(evt, evt+tot);
        int now=0, ans=0;
        seg.print();
        for(int i=0; i<tot;){
            out(now);
            int tmp=seg.query()+now;
            out(tmp);
            ans=max(ans, tmp);
            int xx=evt[i].X;
            for(; i<tot && evt[i].X==xx; ++i){
                int id=abs(evt[i].Y)-1, delta=evt[i].Y<0?-1:1;
                out(p[id].Y);
                out(delta);
                seg.update(get_id(p[id].Y-h+1), get_id(p[id].Y), delta);
                now+=delta;
            }
        }
        static int cs=0;
        printf("Case #%d: %d\n", ++cs, ans);
    }
}
