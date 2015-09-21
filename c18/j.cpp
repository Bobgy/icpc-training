#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
template<class T> T sqr(T x) {return x*x;}
#define pi acos(-1)
#define INF 100000000
#define debug(x) cerr<<#x"="<<(x)<<"\n";
#define foreach(it,v) for (__typeof((v).begin()) it=(v).begin();it!=(v).end();it++)

int n,K=5,idx,m;
int ans;

struct point {
    int x[5];
    bool operator < (const point &u) const {
        return x[idx]<u.x[idx];
    }
};

point po[210000],p;

struct kdtree {
    point pt[210000];
	point mx[210000];
	point my[210000];
    int son[210000];
    void build(int l,int r,int rt=1,int dep=0) {
        if (l>r) return;
        son[rt]=r-l;
        son[rt*2]=son[rt*2+1]=-1;
        idx=dep%K;
        int mid=(l+r)/2;
        nth_element(po+l,po+mid,po+r+1);
        pt[rt]=po[mid];
        build(l,mid-1,rt*2,dep+1);
        build(mid+1,r,rt*2+1,dep+1);
		mx[rt]=pt[rt];
		my[rt]=pt[rt];
		if (~son[rt*2]) 
			for (int i=0;i<K;i++) {
				mx[rt].x[i]=max(mx[rt].x[i],mx[rt*2].x[i]);
				my[rt].x[i]=min(my[rt].x[i],my[rt*2].x[i]);
			}
		if (~son[rt*2+1]) {
			for (int i=0;i<K;i++) {
				mx[rt].x[i]=max(mx[rt].x[i],mx[rt*2+1].x[i]);
				my[rt].x[i]=min(my[rt].x[i],my[rt*2+1].x[i]);
			}
		}
    }

    void query(int rt=1,int dep=0) {
        if (son[rt]==-1) return;
		int ok=1;
        for (int i=0;i<K;i++) if (mx[rt].x[i]>p.x[i]) {
			ok=0;
			break;
		}
		if (ok) {
			ans+=son[rt]+1;
			return;
		}
		for (int i=0;i<K;i++) if (my[rt].x[i]>p.x[i]) return;
		int flag=1;
		for (int i=0;i<K;i++) if (pt[rt].x[i]>p.x[i]) {
			flag=0;
			break;
		}
		ans+=flag;
		int dim=dep%K,x=rt*2,y=rt*2+1; 
        if (~son[x]) {
			query(x,dep+1);
		}
        if (~son[y]) {
			if (pt[rt].x[dim]<=p.x[dim]) query(y,dep+1);
		}
    }
} kd;

int main() {
	int tt;
	scanf("%d",&tt);
    while (tt--) {
		scanf("%d%d",&n,&m);
        for (int i=0;i<n;i++)
            for (int j=0;j<K;j++)
                scanf("%d",&po[i].x[j]);
        kd.build(0,n-1);
        int t;
		ans=0;
        for (scanf("%d",&t);t--;) {
            point ask;
            for (int j=0;j<K;j++) {
				scanf("%d",&ask.x[j]);
				ask.x[j]^=ans;
			//	assert(ask.x[j]>=1 && ask.x[j]<=50000);
			}
			ans=0;
			p=ask;
            kd.query();
			printf("%d\n",ans);
        }
    }
}
