#include<bits/stdc++.h>
#define INF 100000000
using namespace std;
#define out(x) (cerr<<#x"="<<x<<endl,x)
typedef long long ll;
using namespace rel_ops;

template <class VAL = ll> class Frac {
public:
	VAL num,den;
	Frac(){}
	Frac(const VAL &x, const VAL &y = 1){
		den=__gcd(x,y);
		num=x/den,den=y/den;
		if(den<0)num=-num,den=-den;
	}
	bool operator<(const Frac &r) const {
		return num*r.den<r.num*den;
	}
	bool operator>(const Frac &r) const {
		return r<*this;
	}
	Frac operator+(const Frac &r) const {
		return Frac(num*r.den+den*r.num,den*r.den);
	}
	Frac operator-(const Frac &r) const {
		return Frac(num*r.den-den*r.num,den*r.den);
	}
	Frac operator*(const Frac &r) const {
		return Frac(num*r.num,den*r.den);
	}
	Frac operator/(const Frac &r) const {
		return Frac(num*r.den,den*r.num);
	}
	Frac operator-() const {return Frac(-num,den);}
};

//typedef double flt;
typedef Frac<__int128> flt;

struct sg {
	int x,y,u,c,op,next;
};
struct sa {
	int x,y,u,c;
};
sa a[1100];
sg g[2100];
int d[110];
int v[110];
int fa[110];
int ls[110];
ll M,F,C;
int tot,n,m,S,T;

void add(int x,int y,int u,int c) {
	tot++;
	g[tot].x=x;g[tot].y=y;g[tot].u=u;g[tot].c=c;g[tot].op=tot+1;g[tot].next=ls[x];
	ls[x]=tot;
	tot++;
	g[tot].x=y;g[tot].y=x;g[tot].u=0;g[tot].c=-c;g[tot].op=tot-1;g[tot].next=ls[y];
	ls[y]=tot;
}

int spfa() {
	for (int i=1;i<=n;i++) {
		d[i]=INF;
		v[i]=0;
	}
	d[S]=0;
	v[S]=1;
	queue<int> Q;
	Q.push(S);
	while (!Q.empty()) {
		int x=Q.front();
		Q.pop();
		for (int t=ls[x];t;t=g[t].next) if (g[t].u>0) {
			int y=g[t].y;
			if (d[x]+g[t].c<d[y]) {
				d[y]=d[x]+g[t].c;
				fa[y]=t;
				if (!v[y]) {
					v[y]=1;
					Q.push(y);
				}
			}
		}
		v[x]=0;
	}
	if (d[T]==INF) return 0;
	return 1;
}
flt ans;
flt sqr(flt x){
	return x*x;
}
void change(int k) {
	int x=T;
	int mf=INF;
	while (x!=S) {
		int t=fa[x];
		mf=min(mf,g[t].u);
		x=g[t].x;
	}
	x=T;
	while (x!=S) {
		int t=fa[x];
		g[t].u-=mf;
		g[g[t].op].u+=mf;
		x=g[t].x;
	}
	if (k==0) M+=mf;
	else {
		flt x=(flt(M)-F-flt(C)*d[T])/(sqr(d[T])+1);
		if(x>0 && x<mf){
			ans=min(ans, sqr(flt(C)+flt(x)*d[T])+sqr(flt(M)-F-x));
		}
		F+=mf;
		C+=mf*d[T];
		ans=min(ans, sqr(C)+sqr(M-F));
	}
}
void print(__int128 x){
	if(x==0){
		putchar('0');
		return;
	}
	if(x/10)print(x/10);
	putchar('0'+x%10);
}
int main() {
	scanf("%d%d",&n,&m);
	scanf("%d%d",&S,&T);
	for (int i=0;i<m;i++) scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].u,&a[i].c);
	ans = flt(1e10);
	for (int k=0;k<2;k++) {
		tot=0;
		memset(ls,0,sizeof(ls));
		for (int i=0;i<m;i++) add(a[i].x,a[i].y,a[i].u,a[i].c);
		while (spfa()) change(k);
	}
	ans=min(ans, sqr(M));
	print(ans.num);
	putchar('/');
	print(ans.den);
	putchar('\n');
}
