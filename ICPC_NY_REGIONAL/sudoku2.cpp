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
vector<array<int, 2>> d = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int inside(int x, int y){
    return 0<=x && x<9 && y<=0 && y<9;
}
vector<vector<int>> v(9, vector<int>(9, 0));
vector<vector<array<int, 2>>> adj(81);
vector<vector<int>> rowcnt(9, vector<int>(10, 0));
vector<vector<int>> colcnt(9, vector<int>(10, 0));
vector<vector<vector<int>>> sqcnt(3, vector<vector<int>>(3, vector<int>(10, 0)));
vector<vector<int>> badval(10);
int solve(int x){
    if (x>=81) return 1;
    // cout << x << "\n";
    int row = x/9; int col = x%9;
    if (v[row][col]) return solve(x+1);
    for (int i=1; i<=9; i++){
        int ok = 1;
        if (rowcnt[row][i]) continue;
        if (colcnt[col][i]) continue;
        if (sqcnt[row/3][col/3][i]) continue;
        for (auto [y, w]: adj[x]){
            int wrow = y/9; int wcol = y%9; 
            if (v[wrow][wcol]==0) continue;
            if (max(i, v[wrow][wcol]) % min(i, v[wrow][wcol]) != w) ok = 0;
        }
        if (!ok) continue;
        v[row][col] = i;
        rowcnt[row][i]++;
        colcnt[col][i]++;
        sqcnt[row/3][col/3][i]++;
        if (solve(x+1)) return 1;  
        rowcnt[row][i]--;
        colcnt[col][i]--;
        sqcnt[row/3][col/3][i]--; 
    }
    v[row][col] = 0;
    return 0;
}
void solve() {
    int K; cin >> K;
    vector<array<int, 2>> rowc = {{0, 1}, {1, 2}, {3, 4}, {4, 5}, {6, 7}, {7, 8}};
    for (int i=0; i<3; i++){
        vector<vector<int>> c1(3, vector<int>(6, 0));
        vector<vector<int>> c2(2, vector<int>(9, 0));
        for (int j=0; j<6; j++) cin >> c1[0][j];
        for (int j=0; j<9; j++) cin >> c2[0][j];
        for (int j=0; j<6; j++) cin >> c1[1][j];
        for (int j=0; j<9; j++) cin >> c2[1][j];
        for (int j=0; j<6; j++) cin >> c1[2][j];
        for (int a=0; a<3; a++){
            for (int j=0; j<6; j++){
                auto [x, y] = rowc[j];
                if (c1[a][j]==9) continue;
                adj[27*i+9*a+x].pb({27*i+9*a+y, c1[a][j]});
                adj[27*i+9*a+y].pb({27*i+9*a+x, c1[a][j]});
            }
        }
        for (int a=0; a<2; a++){
            for (int j=0; j<9; j++){
                if (c2[a][j]==9) continue;
                adj[27*i+9*a+j].pb({27*i+9*a+9+j, c2[a][j]});
                adj[27*i+9*a+9+j].pb({27*i+9*a+j, c2[a][j]});
            }
        }        
    }
    for (int i=0;i<K; i++){
        int r, c, x; cin >> r >> c >> x; r--;c--;
        rowcnt[r][x]++;
        colcnt[c][x]++;
        sqcnt[r/3][c/3][x]++;
        v[r][c] = x;
    }
    // for (int i=0; i<9; i++){
    //     for (int j=0; j<9; j++){
    //         for (auto [x, y]: adj[i*9+j]){
    //             cout << i << ' ' << j << ' ' << (x/9) << ' ' << x%9 << ' ' << y << "\n";
    //         }
    //     }
    // }
    cout << solve(0) << "\n";
    for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            cout << v[i][j] << ' ';
        }
        cout << "\n";
    }

}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    // inv_init();
    // int tt; cin >> tt;
    // for (int xx=1; xx<=tt; xx++)
    solve();
    
}