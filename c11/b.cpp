#include<bits/stdc++.h>
using namespace std;

struct sa {
	int g,a,b,id;
	friend bool operator < (sa x,sa y) {
		return x.a*y.b>y.a*x.b;
	}
};
sa a[110000];
double ans[110000];

int main() {
	freopen("burrito.in","r",stdin);
	freopen("burrito.out","w",stdout);
	int n,A,B;
	scanf("%d%d%d",&n,&A,&B);
	for (int i=0;i<n;i++) {
		scanf("%d%d%d",&a[i].g,&a[i].a,&a[i].b);
		a[i].id=i;
	}
	sort(a,a+n);
	double aa=0,bb=0;
	for (int i=0;i<n;i++) {
		double t=a[i].g;
		if (a[i].b) t=min(t,(B-bb)/a[i].b);
		aa+=t*a[i].a;
		bb+=t*a[i].b;
		ans[a[i].id]=t;
	}
	if (aa<A) {
		puts("-1 -1");
		return 0;
	}
	printf("%.20lf %.20lf\n",aa,bb);
	for (int i=0;i<n;i++) printf("%.20lf%c",ans[i],i==n-1?'\n':' ');
}
