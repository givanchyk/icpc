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
double EPS = 1e-12;
struct pt {
    double x, y;
};
struct line {
    double a, b, c;
    line() {}
    line(double a1, double b1, double c1){
        a = a1; b = b1; c = c1;
    }
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
double det(double a, double b, double c, double d) {
    return a*d - b*c;
} 
pt intersect(line m, line n) {
    pt res;
    double zn = det(m.a, m.b, n.a, n.b);
    res.x = -det(m.c, m.b, n.c, n.b) / zn;
    res.y = -det(m.a, m.c, n.a, n.c) / zn;
    return res;
}
void solve() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    pt p; pt q;
    line m; line n;
    cin >> p.x >> p.y >> m.a >> m.b >> m.c >> q.x >> q.y >> n.a >> n.b >> n.c;
    m.norm(); n.norm();
    if (m.dist(p)<0){
        m.a *= -1; m.b *= -1; m.c *= -1;
    }
    if (n.dist(q)<0){
        n.a *= -1; n.b *= -1; n.c *= -1;
    }
    line m2(m.a, m.b, m.c/2 - m.a*p.x/2 - m.b*p.y/2);
    line n2(n.a, n.b, n.c/2 - n.a*q.x/2 - n.b*q.y/2);
    m = m2;
    n = n2;
    // pt pn{m.a, m.b};
    line projl(p, pt{p.x+m.a, p.y+m.b});
    pt proj = intersect(projl, m);
    auto check = [&](double x, int mode=0){
        //parallel - (-m.b, m.a)
        //p2 = x*parallel + normal
        // pt p2{-x*m.b+m.a, x*m.a + m.b};
        
        pt inter1{proj.x + x*(-m.b), proj.y + x*m.a};  
        line l1(p, inter1); 
        // cout << inter1.x << ' ' << inter1.y << "\n";
        line l2(inter1, pt{inter1.x + l1.a, inter1.y + l1.b});
        pt inter2 = intersect(l2, n);
        // cout << inter2.x << ' ' << inter2.y << "\n";
        line l3(inter2, pt{inter2.x + l2.a, inter2.y + l2.b});
        // cout << l3.a << ' ' << l3.b << ' ' << l3.c << "\n";
        // cout << l3.dist(q) << "\n";
        if (mode){
            line res(inter1, inter2);
            printf("%.04f %.04f %.04f\n", res.a, res.b, res.c);
        }
        return abs(l3.dist(q));
    };
    // cout << inter.x << ' ' << inter.y << "\n";
    // cout << last.a << ' ' << last.b << ' ' << last.c << "\n";
    // cout << interN.x << ' ' << interN.y << "\n";

    // cout << inter.x - proj.x << ' ' << inter.y - proj.y << "\n";
    // cout << -m.b << ' ' << m.a << "\n";
    // cout << (inter.x - proj.x) / -m.b  << ' ' << (inter.y - proj.y) / m.a << "\n";
    // cout << check(0.281364) << "\n";
    // cout << check(0.29) << "\n";

    // cout << inter1.x << ' ' << inter1.y << "\n";
    // double low = -((int)rng()%(int)1e7); double high = (int)rng()%(int)1e7;
    // for (double i=1000; i<=0; i++){
    //     cout << check(i) << "\n";
    // }
    // for (double i=0; i<=1000; i++){
    //     cout << check(i) << "\n";
    // }
    // cout << rng()%1000000 << "\n";

    double low = 0; double high = 0;
    while (check(low)>1e-9){
        low = -(double)(rng()%1000000);
        high = (rng()%1000000);
        while (high-low>EPS){
            double mid1 = (low/3) + (low/3) + (high/3);
            double mid2 = (low/3) + (high/3) + (high/3);
            double vmid1 = check(mid1);
            double vmid2 = check(mid2);
            if (vmid2>vmid1){
                high = mid2;
            }
            else{
                low = mid1;
            }
        }
    }
    cout << check(low, 1) << "\n";




}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    // inv_init();
    // int tt; cin >> tt;
    // for (int xx=1; xx<=tt; xx++)
    solve();
    
}