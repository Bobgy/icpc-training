#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
int main(){
    int T;
    scanf("%d",&T);
    REP(tt,T){
        int W, H, x, xe, ye;
        double u, tant, tana, sint, sina, dx, dy, h;
        scanf("%d%d%d%d%d%lf", &W, &H, &x, &xe, &ye, &u);
        dx=xe-W; dy=ye-H;
        sint=dx/hypot(dx, dy);
        sina=sint/u; tana=sina/sqrt(1-sina*sina);
        if(dy==0){
            if(W-H*tana>x)h=H;
            else {
                puts("Impossible");
                continue;
            }
        } else {
            tant=dx/dy;
            h=(W-x-H*tant)/(tana-tant);
            if(h>H){
                puts("Impossible");
                continue;
            }
        }
        printf("%.4lf\n", h);
    }
}
