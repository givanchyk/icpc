#include <bits/stdc++.h>
using namespace std;
// #define int long long int
#define pb push_back
int mod = 998244353;
// const int INF = 4e18;
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
int call = 0;
void hanoi(int src, int dest, int help, int x, int color, vector<array<int, 3>> &res){//p1 to p3
    if (x==0) return;
    if (x==1){
        res.pb({src, dest, color});
        return;
    }
    hanoi(src, help, dest, x-1, color, res);
    res.pb({src, dest, color});
    hanoi(help, dest, src, x-1, color, res);
}
void move(int x, int color, vector<array<int, 3>> &res){
    if (x==1){
        if (color==0){
            res.pb({1, 2, 0});
        }
        else{
            res.pb({3, 4, 1});
        }
        return;
    }
    if (color==1){
        res.pb({3, 1, color});
        hanoi(4, 1, 3, x-2, color, res);
        res.pb({3, 4, color});
        hanoi(1, 4, 3, x-1, color, res);
    }
    else{
        res.pb({4, 2, color});
        hanoi(2, 3, 1, x-2, color, res);
        res.pb({1, 2, color});
        hanoi(3, 2, 1, x-1, color, res);
    }
}
void solve() {
    // vector<int> dp(26);
    // dp[0] = 1;
    // for (int i=1; i<=25; i++){
    //     dp[i] = dp[i-1] + (1ll<<i) + (1ll<<(i-1));
    // }
    // for (int i=0; i<=24; i++){
    //     cout << 2*dp[i]+1 << ' ';
    // }

    vector<vector<array<int, 3>>> res(26);
    for (int i=1; i<=25; i++){
        for (int j=1; j<=i; j++){
            // res[i].pb({1, 2, 3});
            move(j, (j%2)^1, res[i]);
        }
        if ((i%2)^1){
            res[i].pb({1, 3, 0});
        }
        else{
            res[i].pb({3, 1, 1});
        }

    }
    auto swap13 = [&](int x){
        if (x==1) return 3;
        if (x==3) return 1;
        return x;
    };
    // for (int i=0; i<=25; i++) cout << i << ' ' << res[i].size() << "\n";
    int T; cin >> T;
    for (int t=0; t<T; t++){
        int X; cin >> X; 
        int N, S; cin >> N >> S; S--;
        int res1, res2, color;
        if (S>=res[N].size()){
            S = (res[N].size()-1) - (S-(res[N].size()-1));
            res1 = swap13(res[N][S][1]);
            res2 = swap13(res[N][S][0]);
            color = res[N][S][2]^1;
        }
        else{
            res1 = res[N][S][0]; res2 = res[N][S][1]; color = res[N][S][2];
        }
        // char* s;
        if (color==0){
            printf("%d %d MOVE white FLOOR FROM LOT %d to LOT %d\n", 
                X, res[N].size()*2-1, res[N][S][0], res[N][S][1]);            
        }
        else{
            printf("%d %d MOVE black FLOOR FROM LOT %d to LOT %d\n", 
                X, res[N].size()*2-1, res[N][S][0], res[N][S][1]);                    
        }
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