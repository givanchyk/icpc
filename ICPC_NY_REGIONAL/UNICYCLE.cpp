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

void solve() {
    int n; cin >> n;
    mod = 100007;
    vector<int> dp(n+1, 0); dp[0] = 1;
    for (int i=1; i<n+1; i++){
        for (int j=1; j<=i; j++){
            dp[i] += j*dp[i-j];
            dp[i] %= mod;
        }
    }
    vector<int> dp2(n+1, 0);
    for (int i=1; i<n+1; i++){
        for (int j=1; j<=i; j++){
            dp2[i] += dp[i-j];
            dp2[i] += j*dp2[i-j];
            dp2[i] %= mod;
        }
    }
    int res = 0;
    for (int i=1; i<=n; i++){
        for (int j=i; j<=n; j++){
            res += dp[n-j];
            res += j*dp2[n-j];
            res %= mod;
        }
    }
    cout << res << "\n";

}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    // inv_init();
    // int tt; cin >> tt;
    // for (int xx=1; xx<=tt; xx++)
    solve();
    
}