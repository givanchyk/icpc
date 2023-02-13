#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define pb push_back
int mod = 998224353;
const int INF = 4e18;
// int INF = 1e9;
void print(int x){
    cout << x << "\n";
}
void print(int x, int y){
    cout << x << ' ' << y << "\n";
}
void print(int x, int y, int z){
    cout << x << ' ' << y << ' ' << z << "\n";
}
void print(vector<int> x){
    for (auto val: x) cout << val << ' ';
    cout << endl;
}
void print(array<int, 2> x){
    cout << x[0] << ' ' << x[1] << endl;
}
void print(vector<vector<int>> x){
    for (auto val: x) print(val);
    
}
void print(vector<array<int, 2>> x){
    for (auto [a, b]: x) cout << a << ' ' << b << endl;
 
}
void print(set<int> x){
    for (auto val: x) cout << val << ' ';
    cout << endl;
}
void print(multiset<int> x){
    for (auto val: x) cout << val << ' ';
    cout << endl;
}
void print(map<int, int> &x){
    for (auto &[a, b]: x) cout << a << ' ' << b << endl;
}
int log2_floor(int i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}
int inv(int a, int b){
    return 1<a ? b - inv(b%a,a)*b/a : 1;
}
int inv(int a){
    return inv(a, mod);
}
vector<int> fact;
vector<int> ifact;
int bin(int N, int K){ 
    if (K>N) return 0;
    if (K<0) return 0;
    if (N<0) return 0;
    int res = 1;
    res *= fact[N]; res %= mod;
    res *= ifact[K]; res %= mod;
    res *= ifact[N-K]; res %= mod;
    return res;
}
void inv_init(int C = 1e6){
    fact.resize(C+1); fact[0] = 1;
    ifact.resize(C+1);
    for (int i=1; i<=C; i++) fact[i] = (i*fact[i-1])%mod;
    ifact[C] = inv(fact[C]);
    for (int i=C-1; i>=0; i--) ifact[i] = ((i+1)*ifact[i+1])%mod;
}
int binpow(int a, int b) {
    a %= mod;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}   
double EPS = 1e-11;
struct pt {
    double x, y, r;
};
struct line {
    double a, b, c;
    line() {}
    line(pt p, pt q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();
    }

    void norm()
    {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    double dist(pt p) const { return a * p.x + b * p.y + c; }
};
double DINF = 1e9;
void intersect(line l, pt p, pt &res1, pt &res2){
    double r, a, b, c;
    //x --> x - p.x
    //y --> y - p.y
    r = p.r; a = l.a; b = l.b; c = l.c + l.a*p.x + l.b*p.y;
    double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS)
        res1.x = DINF+1;
    else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
        res1.x = DINF+1;
    }
    else {
        double d = r*r - c*c/(a*a+b*b);
        double mult = sqrt (d / (a*a+b*b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        res1.x = ax + p.x;
        res2.x = bx + p.x;
        res1.y = ay + p.y;
        res2.y = by + p.y; 
        // cout << ax << ' ' << ay << '\n' << bx << ' ' << by << '\n';
    }
}
void intersect(pt p1, pt p2, pt &res1, pt &res2){
    //(x-x1)^2 + (y-y1)^2 = r1^2
    //(x-x2)^2 + (y-y2)^2 = r2^2
    //x(-2x1+2x2) + y(-2y1+2y2) + (x1^2+y1^2-r1^2 -x2^2-y2^2+r2^2) = 0;
    line l;
    l.a = -2*p1.x+2*p2.x;
    l.b = -2*p1.y+2*p2.y;
    l.c = p1.x*p1.x + p1.y*p1.y - p1.r*p1.r - p2.x*p2.x - p2.y*p2.y + p2.r*p2.r;  
    intersect(l, p1, res1, res2);
}
int N;
double R; double O;
pt center;
int check(double r, int final){
    center.r = r;
    vector<pt> circ;
    double firstr = (O+R-r)/2;
    double firstx = R - firstr;
    if (firstr<=0) return 1;
    if (r >= R-O) return 1;
    pt first{firstx, 0, firstr};
    circ.pb(first);
    // cout << firstx << ' ' << 0 << ' ' << firstr << "\n";
    for (int i=1; i<N; i++){
        pt last = circ.back();
        double low = 0; double high = R; pt res; 
        while (high-low>EPS){
            double rc = (high+low)/2;
            // double rc = 1.310;
            pt center_adj = center;center_adj.r += rc;
            pt last_adj = last; last_adj.r += rc;
            pt res1; pt res2;
            intersect(center_adj, last_adj, res1, res2);
            res = res1;
            line centerline(center, last);

            if (centerline.dist(res)<0){
                res = res2;
            }
            res.r = rc;
            double distcheck = sqrt(res.x*res.x + res.y*res.y) + rc;
            if (distcheck>R){
                high = rc;
            }
            else{
                low = rc;
            }
            // cout << distcheck << ' ' << R << "\n";
            // cout << res.x << ' ' << res.y << ' ' << res.r << "\n";
            // return 1;

        }

        // cout << res.x << ' ' << res.y << ' ' << res.r << "\n";
        // return 1;
        circ.pb(res);
    }
    if (final){
        printf("%.03f\n", r);
        for (int i=0; i<4; i++){
            printf("%.03f %.03f %.03f\n", circ[i].x, circ[i].y,circ[i].r);
        }
        return 0;
    }
    for (int i=2; i<N; i++){
        pt res1; pt res2;
        intersect(circ[0], circ[i], res1, res2);
        if (res1.x<DINF){
            return 0;
        }
    }
    return 1;
}


void solve() {
    
    cin >> R >> N >> O; R /= 2;
    center.x = -O; 
    center.y = 0; 
    // cout << check(3) << "\n";
    double low = 0; double high = R;
    while (high-low>EPS){
        double mid = (low+high)/2;
        if (check(mid, 0)) high = mid;
        else{
            low = mid;
        }
    }
    check(low, 1);
    // cout << low << "\n";
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    // inv_init();
    // int tt; cin >> tt;
    // for (int xx=1; xx<=tt; xx++)
    solve();
    
}