#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define pb push_back
int mod = 1e9+7;
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
int N = 8;
int inside(int x, int y){
    return 0<=x && x<N && 0<=y && y<N;
}
vector<array<int, 2>> jump = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
vector<vector<int>> adj;
vector<vector<int>> v;
vector<int> touched;
vector<int> rev;
int checkrow(int x){
    int row = x/8; int col = x%8;
    int sum = 0; int left = 0;
    for (int i=0; i<8; i++){
        if (v[row][i]==0) left++;
        sum += v[row][i];
    }
    if (left==0 && sum != 260) return 0;
    if (sum > 260) return 0;
    return 1;
}
int checkcol(int x){
    int row = x/8; int col = x%8;
    int sum = 0; int left = 0;
    for (int i=0; i<8; i++){
        if (v[i][col]==0) left++;
        sum += v[i][col];
    }
    if (left==0 && sum != 260) return 0;
    if (sum > 260) return 0;
    return 1;
}
int solve(int x, int val){
    if (val>=65) return 1;
    int row = x/N; int col = x%N;
    if (v[row][col] && v[row][col] != val) return 0;
    v[row][col] = val;
    int ok = 1;
    if (rev[val]!=-1 && rev[val] != x) ok = 0;
    if (!checkrow(x)) ok = 0;
    if (!checkcol(x)) ok = 0;
    if (!ok){
        if (!touched[x]) v[row][col] = 0;
        return 0;
    }
    // cout << x << "\n";
    for (int y: adj[x]){
        if (solve(y, val+1)) return 1;  
    }
    if (!touched[x]) v[row][col] = 0;
    return 0;
}
void solve() {
    adj = vector<vector<int>>(64);
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            for (auto [dx, dy]: jump){
                if (inside(i+dx, j+dy)){
                    adj[i*8+j].pb((i+dx)*8+(j+dy));
                }
            }
        }
    }
    int K; cin >> K;
    v = vector<vector<int>>(8, vector<int>(8, 0));
    rev = vector<int>(65, -1);
    touched = vector<int>(64, 0);
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            cin >> v[i][j];
            if (v[i][j]==-1) v[i][j] = 0;
            else{
                rev[v[i][j]] = 8*i+j;
                touched[8*i+j] = 1;
            }
        }
    }
    for (int i=0; i<64; i++){
        if (solve(i, 1)) break;
    }
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            cout << v[i][j] << ' ';
        }
        cout << "\n";
    }



}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    // mod = 1001113;
    // inv_init();
    int tt; cin >> tt;
    for (int xx=1; xx<=tt; xx++)
    solve();
    
}