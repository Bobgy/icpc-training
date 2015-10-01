#include<bits/stdc++.h>
using namespace std;

vector<int> a[11000];
int h[11000];
double all[11000],now[11000];

int main() {
	int n,m,X,Y,Z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lf%lf",all+i,now+i);
	for (int i=0;i<m;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		h[y]++;
		a[x].push_back(y);
	}
	scanf("%d%d%d",&X,&Y,&Z);
	now[X]+=Y;
	queue<int> Q;
	for (int i=1;i<=n;i++) if (h[i]==0) Q.push(i);
	while (!Q.empty()) {
		int x=Q.front();
		Q.pop();
		for (auto y:a[x]) {
			h[y]--;
			if (now[x]>all[x]) now[y]+=(now[x]-all[x])/a[x].size();
			if (h[y]==0) Q.push(y);
		}
		if (now[x]>all[x]) now[x]=all[x];
	}
	printf("%.10lf\n",now[Z]);
}
