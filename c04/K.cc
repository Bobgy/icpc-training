#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<int(n);++i)
#define X first
#define Y second
#define out(x) cerr<<#x"="<<x<<endl
typedef vector<int> vi;
//二维几何
typedef double NUM;
const double eps = 2e-8;
const double PI = acos(-1);
const double TWO_PI = 2*PI;
inline int dcmp(NUM x, NUM rel=1.0)   {
    return abs(x)<eps*fabs(rel) ? 0 : x<0 ? -1 : 1;
}
inline double zero(double x) {
    return dcmp(x)==0 ? 0 : x;
}
double normalizeAngle(double rad, double center = PI) {     //将角度标准化到区间 [center-PI,center+PI)
    return rad-TWO_PI*floor((rad+PI-center)/TWO_PI);
}
struct Point {
    NUM x, y;
    Point(NUM xx=0, NUM yy=0):    x(xx), y(yy)    {}
    void read() {cin>>x>>y;}
    void print() {cout<<fixed<<setprecision(12)<<x<<" "<<y;}
};
typedef Point Vector;
typedef vector<Point> Polygon;
Vector operator+(Vector A, Vector B)        {return Vector(A.x+B.x, A.y+B.y);}
Vector operator-(Point A, Point B)          {return Vector(A.x-B.x, A.y-B.y);}
Vector operator*(Vector A, NUM p)           {return Vector(A.x*p, A.y*p);}
Vector operator/(Vector A, NUM p)           {return Vector(A.x/p, A.y/p);}
bool operator<(const Point &a, const Point &b) {
    return dcmp(a.x-b.x)<0 || (dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)<0);
}
bool operator == (const Point a, const Point b) {
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}

NUM Dot(Vector A, Vector B)                 {return A.x*B.x + A.y*B.y;}                     //计算两个向量之间的点积
double Length(Vector A)                     {return sqrt(Dot(A,A));}                        //计算向量的模
double Angle(Vector A, Vector B)            {return acos(Dot(A,B)/Length(A)/Length(B));}    //计算两个向量之间的夹角
NUM Cross(Vector A, Vector B)               {return A.x*B.y - A.y*B.x;}                     //计算两个向量之间的叉积
NUM Area2(Point A, Point B, Point C)        {return Cross(B-A,C-A);}                        //计算三角形A,B,C的有向面积
double angle(Vector v)                      {return atan2(v.y, v.x);}                       //计算向量的极角
double torad(double deg)                    {return deg/180.0*PI;}                       //角度转化为弧度
Vector Rotate(Vector A, double rad) {                                                       //向量逆时针旋转rad
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
Vector Normal(Vector A) {           //计算向量的单位法向量(确保A不是零向量)
    double L=Length(A);
    return Vector(-A.y/L, A.x/L);
}
//Hash a line: Ax+By+C=0 which A,B,C all can be integers, define g=gcd(A,B,C)/sgn(A,B), then A/=g,B/=g,C/=g
//define sgn(A,B,C)=A==0?SGN(b):SGN(A)  SGN(x)=x<0?-1:1
struct Line {
    Point p;
    Vector v;
    double ang;
    Line()  {}
    Line(Point p, Vector v):p(p),v(v) {ang=atan2(v.y,v.x);}
    Point point(double t) {
        return p+v*t;
    }
    Line move(double d) {
        return Line(p+Normal(v)*d, v);
    }
    bool operator<(Line L) const {
        return dcmp(ang-L.ang)<0;
    }
    static Line getLine(double x1, double y1, double x2, double y2) {
        Point a=Point(x1,y1);
        Point b=Point(x2,y2);
        return Line(a, b-a);
    }
};
double add_eps(double x, double eps){
    if(x>0)return x+max(x, 1.0)*eps;
    else return x-min(x, -1.0)*eps;
}
struct Sample{
    int x, n;
    vector<pair<double, double> > a;
    void read(){
        a.clear();
        scanf("%d%d",&x,&n);
        REP(i,n){
            int y; scanf("%d", &y);
            a.push_back(make_pair(double(y), 0.0));
        }
        REP(i,n){
            scanf("%lf", &a[i].Y);
            a[i].Y/=100;
        }
        int j=0;
        REP(i,n)if(dcmp(a[i].Y)>0)
            a[j++]=a[i];
        a.erase(a.begin()+j, a.end());
        sort(a.begin(), a.end());
    }
    double calc_dis(double y){
        double res=0;
        REP(i,a.size())
            res+=a[i].Y*fabs(a[i].X-y);
        return res;
    }
    pair<double, double> get_range(double threshold){
        double k=-1.0, dis=calc_dis(a[0].X), L, R;
        bool enter=0, leave=0;
        if(dis<=threshold){
            L=a[0].X-(threshold-dis);
            enter=1;
        }
        REP(i,a.size()-1){
            k+=2*a[i].Y;
            double d=a[i+1].X-a[i].X, ndis;
            ndis=dis+k*d;
            if(!enter){
                if(dcmp(threshold-ndis, threshold)>=0){
                    L=a[i].X+(threshold-dis)/k;
                    enter=1;
                }
            } else if(!leave){
                if(dcmp(threshold-ndis, threshold)<=0){
                    R=a[i].X+(threshold-dis)/k;
                    leave=1;
                }
            }
            dis=ndis;
        }
        k+=2*a.back().Y;
        if(!enter)return make_pair(1.0, -1.0);
        if(!leave)R=a.back().X+threshold-dis;
        return make_pair(L, R);
    }
} s[112345];
int n;
vector<Point> halfplaneIntersection(vector<Line> L);       // 半平面交主过程
bool test(double threshold){
    vector<Line> lines;
    REP(i,n){
        auto rg = s[i].get_range(threshold);
        if(rg.X>rg.Y)return false;
        //k*x+b>=rg.X && k*x+b<=rg.Y
        double t=1.0/(s[i].x*double(s[i].x)+1);
        lines.push_back(Line(Point(s[i].x*t*rg.X, t*rg.X), Vector(1.0, -s[i].x)));
        lines.push_back(Line(Point(s[i].x*t*rg.Y, t*rg.Y), Vector(-1.0, s[i].x)));
    }
    return !halfplaneIntersection(lines).empty();
}
int main(){
    while(scanf("%d",&n)==1 && n){
        REP(i,n)s[i].read();
        double L=0, R=1e9;
        while((R-L)>1e-3){
            double M=L+(R-L)/2.0;
            if(test(M))R=M;
            else L=M;
        }
        printf("%.1lf\n", L+(R-L)/2.0);
    }
}
Point getLineIntersection(Point P, Vector v, Point Q, Vector w) {   //计算两个直线(P,v)和(Q,w)之间的交点
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}

//半平面交
inline bool onLeft(const Line& L, const Point& p) {         //点p在有向直线L的左边(不包括在线上)
    return Cross(L.v, p-L.p) > 0;
}
Point getLineIntersection(Line a, Line b) {                         //计算两个直线a和b之间的交点
    return getLineIntersection(a.p, a.v, b.p, b.v);
}
vector<Point> halfplaneIntersection(vector<Line> L) {       // 半平面交主过程
    int n = L.size();
    sort(L.begin(), L.end()); // 按极角排序

    int first, last;         // 双端队列的第一个元素和最后一个元素的下标
    vector<Point> p(n);      // p[i]为q[i]和q[i+1]的交点
    vector<Line> q(n);       // 双端队列
    vector<Point> ans;       // 结果

    q[first=last=0] = L[0];  // 双端队列初始化为只有一个半平面L[0]
    for (int i = 1; i < n; i++) {
        while (first < last && !onLeft(L[i], p[last-1])) last--;
        while (first < last && !onLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if (fabs(Cross(q[last].v, q[last-1].v)) < eps) { // 两向量平行且同向，取内侧的一个
            last--;
            if (onLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if (first < last) p[last-1] = getLineIntersection(q[last-1], q[last]);
    }
    while (first < last && !onLeft(q[first], p[last-1])) last--; // 删除无用平面
    if (last - first <= 1) return ans; // 空集
    p[last] = getLineIntersection(q[last], q[first]); // 计算首尾两个半平面的交点

    // 从deque复制到输出中
    for (int i = first; i <= last; i++) ans.push_back(p[i]);
    return ans;
}
