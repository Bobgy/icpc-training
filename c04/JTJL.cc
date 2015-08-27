#include<bits/stdc++.h>
#define eps 1e-7
#define rep(i,j,k) for(i=j;i<=k;i++)
using namespace std;
typedef long long LL;
const int MAXN = 2E5 + 10;
const int MAXM = 101;
int n;
LL m[MAXN],P[MAXN][MAXM],_y[MAXN][MAXM];
double INF;

struct Point{
	double x,y;
} Org[MAXN],_O[MAXN],X,Y,_tmp[MAXM];

bool operator < (const Point &a ,const Point &b){
	return a.x<b.x;
}

vector <Point> F[MAXN];

int Work(double del){
	vector<Point> down;
	down.push_back((Point){Org[1].x-1,-INF});
	for(int i = 1; i <= n; i++){
		Org[i].y = -2;
		for(int j = 1; j < F[i].size() - 1; j++)
			if (F[i][j].y <= del){
				Org[i].y = (F[i][j-1].x - F[i][j].x) / (F[i][j-1].y - F[i][j].y) * (del - F[i][j].y) + F[i][j].x;
				break;
			}
		if (Org[i].y == -2)
			return false;
		if (i!=1){
			int t = down.size();
			Point *P = &down[t - 2], *Q = &down[t - 1];
			while (t >= 2 && (Org[i].x - (*Q).x) * ((*Q).y - (*P).y) - (Org[i].y - (*Q).y) * ((*Q).x - (*P).x) < 0){
				down.pop_back();
				--t;
				P = &down[t - 2];
				Q = &down[t - 1];
			}
		}
		down.push_back(Org[i]);
	}

	vector<Point> up;
	up.push_back((Point){Org[1].x-1,INF});
	for(int i = 1; i <= n; i++){
		Org[i].y = -2;
		for(int j = F[i].size() - 2; j > 0; j--)
			if (F[i][j].y <= del){
				Org[i].y = (F[i][j+1].x - F[i][j].x) / (F[i][j+1].y - F[i][j].y) * (del - F[i][j].y) + F[i][j].x;
				break;
			}
		if (Org[i].y == -2)
			return false;
		if (i!=1){
			int t = up.size();
			Point *P = &up[t - 2], *Q = &up[t - 1];
			while (t >= 2 && (Org[i].x - (*Q).x) * ((*Q).y - (*P).y) - (Org[i].y - (*Q).y) * ((*Q).x - (*P).x) > 0){
				up.pop_back();
				--t;
				P = &up[t - 2];
				Q = &up[t - 1];
			}
		}
		up.push_back(Org[i]);
	}

	down.push_back((Point){Org[n].x+1, -INF});
	up.push_back((Point){Org[n].x+1, INF});

	int j = 1;
	for (int i = 1; i < up.size()-1; ++i){
		while (down[j].x < up[i].x)
			j++;
		if (fabs(down[j].x-up[i].x)<=eps)
			continue;
		if ((up[i].y-down[j-1].y)*(down[j].x-down[j-1].x)-(up[i].x-down[j-1].x)*(down[j].y-down[j-1].y) < 0){
			return false;
		}
	}

	j = 1;
	for (int i = 1; i < down.size()-1; ++i){
		while (up[j].x < down[i].x)
			j++;
		if (fabs(up[j].x-down[i].x)<=eps)
			continue;
		if ((down[i].y-up[j-1].y)*(up[j].x-up[j-1].x)-(down[i].x-up[j-1].x)*(up[j].y-up[j-1].y) > 0){
			return false;
		}
	}
	return true;
}

int main(){
	while(scanf("%d",&n),n){
		INF = 1E250;
		double Ymax=0;
		int i,j,k;
		rep(i,1,n){
			F[i].clear();
			scanf("%lf%lld",&Org[i].x,&m[i]);
			rep(j,1,m[i])
				scanf("%lf",&(_tmp[j].x));
			rep(j,1,m[i])
				scanf("%lf",&(_tmp[j].y));
			sort(_tmp+1,_tmp+1+m[i]);
			_tmp[0].x=_tmp[1].x-100;
			_tmp[m[i]+1].x=_tmp[m[i]].x+100;
			rep(j,0,m[i]+1){
				double sum=0;
				rep(k,1,m[i])
					sum+=_tmp[k].y*fabs(_tmp[k].x-_tmp[j].x);
				F[i].push_back((Point){_tmp[j].x,sum});
				Ymax=max(Ymax,sum);
			}
		}
		double high=Ymax*100000, low=0, mid;
		for(int _ = 0; _ < 100; _++){
			mid = (high + low) / 2;
			if (Work(mid))
				high = mid;
			else
				low = mid;
		}
		printf("%.1lf\n", mid/100);
	}
}
