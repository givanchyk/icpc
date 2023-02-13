#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define pb push_back
int mod = 998244353;
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
    // invn.resize(C+1);
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
    pt(){};
    pt(double a, double b){
        x = a;
        y = b;
    }
    void show(){
        cout << x << ' ' << y << "\n";
    }
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
    line perp(pt p){
        line l(p, pt(p.x+a, p.y+b));
        return l;
    }
    void norm()
    {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    double dist(pt p) const { return a * p.x + b * p.y + c; }
    void show(){
        cout << a << ' ' << b << ' ' << c  << "\n";
    }
};
int N;
vector<array<int, 2>> d = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
int inside(int x, int y){
    return 0<=x && x<10 && y>=0 && y<10;
}
vector<vector<int>> v;
vector<vector<array<int, 2>>> adj;
vector<int> touched;
vector<int> order;
int rem;
int call;
int checkadj(int x){
    int xval = v[x/9][x%9];
    for (auto [y, w]: adj[x]){
        // cout << y << ' ' << w << "\n";
        int yval = v[y/9][y%9];
        if (!yval) continue;
        if (xval+yval!=10 && w==0) return 0;   
        if (xval+yval>=10 && w==1) return 0;
        if (xval+yval<=10 && w==2) return 0;
    }
    // if (!left && tsum!=req[row][col]) return 0;
    // if (tsum > req[row][col]) return 0;
    return 1;
}
int checkrow(int x){
    int row = x/9; int col = x%9;   
    for (int i=0; i<N; i++){
        if (i==col) continue;
        if (v[row][i]==v[row][col]) return 0;
    }
    return 1;
}
int checkcol(int x){
    int row = x/9; int col = x%9;
    for (int i=0; i<N; i++){
        if (i==row) continue;
        if (v[i][col]==v[row][col]) return 0;
    }
    return 1;
}
int check33(int x){
    int row = x/9; int col = x%9;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            int c1 = 3*(row/3)+i; int c2 = 3*(col/3)+j;
            if (c1==row && c2==col) continue;
            if (v[3*(row/3)+i][3*(col/3)+j]==v[row][col]){
                return 0;
            }
        }
    }
    return 1;
}
int solve(int index){
    if (index>=rem) return 1;
    int x = order[index];
    int row = x/N; int col = x%N;
    // cout << x << "\n";
    // if (req[row][col] || v[row][col]) cout << "here\n";
    // if (v[row][col]) return solve(index+1);
    // cout << x << "\n";
    for (int i=1; i<=N; i++){
        int ok = 1;
        v[row][col] = i;
        ok &= checkrow(x);
        ok &= checkcol(x);
        ok &= check33(x);
        ok &= checkadj(x);

        if (!ok) continue;
        if (solve(index+1)) return 1;  

    }
    v[row][col] = 0;
    return 0;
}
int recalc(){
    int bestval = -INF;
    int best = -1;
    for (int x=0; x<N*N; x++){
        int row = x/N; int col = x%N;
        if (touched[x]) continue;
        int s1 = 0; int s2 = 0; int s3 = 0;
        for (int i=0; i<N; i++){
            if (touched[x-x%N+i]) s1++;
            if (touched[x%N+N*i]) s2++;

        }
        // for (auto [dx, dy]: d){
        //     // if (inside(row+dx, col+dy) && req[row+dx][col+dy]) s3++;
        // }
        int res = max(s1, s2)*max(s1, s2) + min(s1, s2)*min(s1, s2) + s3*3;
        if (res>bestval){
            bestval = res;
            best = x;
        }
    }
    return best;
}
void solve() {
    N = 9;
    int K; cin >> K; cout << K << "\n";
    rem = N*N; call = 0;
    v = vector<vector<int>>(N, vector<int>(N, 0));
    touched = vector<int>(N*N, 0);
    order = vector<int>(N*N, 0);
    adj = vector<vector<array<int, 2>>>(N*N);
    vector<array<int, 2>> rowc = {{0, 1}, {1, 2}, {3, 4}, {4, 5}, {6, 7}, {7, 8}};
    map<char, int> m;
    m['='] = 0; m['<'] = 1; m['>'] = 2;
    for (int i=0; i<3; i++){
        vector<vector<int>> c1(3, vector<int>(6, 0));
        vector<vector<int>> c2(2, vector<int>(9, 0));
        string s1, s2, s3, s4, s5; cin >> s1 >> s2 >> s3 >> s4 >> s5;
        // cout << s1 << "\n";
        for (int j=0; j<6; j++) c1[0][j] = m[s1[j]];
        for (int j=0; j<9; j++) c2[0][j] = m[s2[j]];
        for (int j=0; j<6; j++) c1[1][j] = m[s3[j]];
        for (int j=0; j<9; j++) c2[1][j] = m[s4[j]];
        for (int j=0; j<6; j++) c1[2][j] = m[s5[j]];
        for (int a=0; a<3; a++){
            for (int j=0; j<6; j++){
                auto [x, y] = rowc[j];
                adj[27*i+9*a+x].pb({27*i+9*a+y, c1[a][j]});
                adj[27*i+9*a+y].pb({27*i+9*a+x, c1[a][j]});
            }
        }
        for (int a=0; a<2; a++){
            for (int j=0; j<9; j++){
                adj[27*i+9*a+j].pb({27*i+9*a+9+j, c2[a][j]});
                adj[27*i+9*a+9+j].pb({27*i+9*a+j, c2[a][j]});
            }
        }        
    }
    // cout << rem << "\n";

    for (int i=0; i<rem; i++){
        order[i] = recalc();
        touched[order[i]] = 1;
    }
    // print(order);
    cout << solve(0) << "\n";
    // // cout << call << "\n";
    // for (int i=0; i<10; i++){
    //     for (int j=0; j<10; j++){
    //         if (req[i][j]) v[i][j] = req[i][j];
    //     }
    // }
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << v[i][j] << ' ';
        }
        cout << "\n";
    }

}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    // inv_init();
    int tt; cin >> tt;
    for (int xx=1; xx<=tt; xx++)
    solve();
    
}