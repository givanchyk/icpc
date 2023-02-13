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
int N;
vector<array<int, 2>> d = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
int inside(int x, int y){
    return 0<=x && x<9 && y<=0 && y<9;
}
vector<vector<int>> v;
vector<vector<array<int, 2>>> adj;
vector<vector<int>> rowcnt;
vector<vector<int>> colcnt;
vector<vector<vector<int>>> sqcnt(3, vector<vector<int>>(3, vector<int>(10, 0)));
vector<int> touched;
vector<int> order;
int Left;
int call = 0;
int solve(int index){
    call++;
    if (index>=Left) return 1;
    int x = order[index];
    // cout << x << "\n";
    int row = x/N; int col = x%N;
    if (v[row][col]) return solve(index+1);
    // int target = x+1;
    // vector<int> oki(10, 1);
    // for (int i=1; i<=9; i++){
    //     for (auto [y, w]: adj[x]){
    //         int wrow = y/9; int wcol = y%9; 
    //         if (v[wrow][wcol]==0) {target = continue;}
    //         if (max(i, v[wrow][wcol]) % min(i, v[wrow][wcol]) != w) ok[i] = 0;
    //     }
    // }
    for (int i=1; i<=N; i++){
        int ok = 1;
        if (rowcnt[row][i]) continue;
        if (colcnt[col][i]) continue;
        for (auto [y, w]: adj[x]){
            int wrow = y/N; int wcol = y%N; 
            if (v[wrow][wcol]==0) continue;
            if (w==0 && abs(i-v[wrow][wcol])==1) ok = 0;
            else if (w==1 && abs(i-v[wrow][wcol])!=1) ok = 0;
        }
        if (!ok) continue;
        v[row][col] = i;
        rowcnt[row][i]++;
        colcnt[col][i]++;
        if (solve(index+1)) return 1;  
        rowcnt[row][i]--;
        colcnt[col][i]--;
    }
    v[row][col] = 0;
    return 0;
}
int recalc(){
    int bestval = -INF;
    int best = -1;
    for (int x=0; x<N*N; x++){
        if (touched[x]) continue;
        int s1 = 0; int s2 = 0; int s3 = 0; int s4 = 0; int s5 = 0; int s6 = 0;
        for (int i=0; i<N; i++){
            if (touched[x-x%N+i]) s1++;
            if (touched[x%N+N*i]) s2++;
        }
        for (auto [y, w]: adj[x]){
            if (w==1 && touched[y]) s3++;
            else if (w==0 && touched[y])s4++;
            else if (w==1 && !touched[y]) s5++;
            else s6++;
        }
        int res = max(s1, s2)*max(s1, s2) + min(s1, s2)*min(s1, s2) + s3*20 + s4*4 + s5*6 + s6;
        if (res>bestval){
            bestval = res;
            best = x;
        }
    }
    return best;
}
void solve() {
    int K; cin >> N >> K;
    v = vector<vector<int>>(N, vector<int>(N, 0));
    rowcnt = vector<vector<int>>(N, vector<int>(N+1, 0));
    colcnt = vector<vector<int>>(N, vector<int>(N+1, 0));
    adj = vector<vector<array<int, 2>>>(N*N);
    touched = vector<int>(N*N);
    order = vector<int>(N*N);
    for (int i=0; i<2*N-1; i++){
        string s; cin >> s;
        if (i%2==0){
            int row = i/2;
            for (int col=0; col<N-1; col++){
                int w = s[col] - '0';
                adj[row*N+col].pb({row*N+col+1, w});
                adj[row*N+col+1].pb({row*N+col, w});
            }
        }
        else{
            int row = i/2;
            for (int col=0; col<N; col++){
                int w = s[col] - '0';
                adj[row*N+col].pb({row*N+col+N, w});
                adj[row*N+col+N].pb({row*N+col, w});
            }
        }
    }
    Left = N*N;
    for (int i=0;i<K; i++){
        int r, c, x; cin >> r >> c >> x; r--;c--;
        rowcnt[r][x]++;
        colcnt[c][x]++;
        v[r][c] = x;
        touched[r*N+c] = 1; Left--;
    }
    for (int i=0; i<Left; i++){
        order[i] = recalc();
        touched[order[i]] = 1;
    }
    // for (int i=0; i<N; i++){
    //     for (int j=0; j<N; j++){
    //         for (auto [x, y]: adj[i*N+j]){
    //             cout << i << ' ' << j << ' ' << (x/N) << ' ' << x%N << ' ' << y << "\n";
    //         }
    //     }
    // }
    cout << solve(0) << "\n";
    cout << call << "\n";

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
    // int tt; cin >> tt;
    // for (int xx=1; xx<=tt; xx++)
    solve();
    
}