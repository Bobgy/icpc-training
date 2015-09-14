#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;
typedef long long ll;
ll f[12][2100];

int main() {
	while (scanf("%d%d%d%d",&n,&m,&L,&R)==4) {
		memset(f,0,sizeof(f));
		for (int i=L;i<=m+R;i++) f[0][i]=i-L+1;

	}
}
