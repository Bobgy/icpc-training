#include<bits/stdc++.h>
#define INF 100000000
using namespace std;
const int N=110000;

vector<int> a[N];
int v[N];
int dmin[N];
int dmax[N];
int b[N];
int n;

void spfamax() {
	queue<int> Q;
	Q.push(1);
	memset(v,0,sizeof(v));
	for (int i=2;i<=n;i++) dmax[i]=-1;
	dmax[1]=0;
	v[1]=1;
	while (!Q.empty()) {
		int x=Q.front();
		Q.pop();
		for (int i=0;i<a[x].size();i++) {
			int y=a[x][i];
			int c=b[x]?b[x]:dmax[x];
			if (c>dmax[y]) {
				dmax[y]=c;
				if (!v[y]) {
					v[y]=1;
					Q.push(y);
				}
			}
		}
		v[x]=0;
	}
}

void spfamin() {
	queue<int> Q;
	Q.push(1);
	memset(v,0,sizeof(v));
	for (int i=2;i<=n;i++) dmin[i]=INF;
	dmin[1]=0;
	v[1]=1;
	while (!Q.empty()) {
		int x=Q.front();
		Q.pop();
		for (int i=0;i<a[x].size();i++) {
			int y=a[x][i];
			int c=b[x]?b[x]:dmin[x];
			if (c<dmin[y]) {
				dmin[y]=c;
				if (!v[y]) {
					v[y]=1;
					Q.push(y);
				}
			}
		}
		v[x]=0;
	}
}

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		int t;
		scanf("%d%d",b+i,&t);
		for (int j=0;j<t;j++) {
			int x;
			scanf("%d",&x);
			a[i].push_back(x);
		}
	}
	spfamax();
	spfamin();
	for (int i=1;i<=n;i++) {
		if (dmin[i]!=dmax[i]) printf("unknown ");
		else if (dmin[i]) printf("%d ",dmin[i]);
		else printf("sober ");
		if (b[i]) printf("%d\n",b[i]);
		else if (dmin[i]!=dmax[i]) printf("unknown\n");
		else if (dmin[i]) printf("%d\n",dmin[i]);
		else printf("sober\n");
	}
}
