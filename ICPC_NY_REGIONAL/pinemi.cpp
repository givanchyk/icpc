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
vector<array<int, 2>> d = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
int inside(int x, int y){
    return 0<=x && x<10 && y>=0 && y<10;
}
vector<vector<int>> v;
vector<vector<int>> req;
vector<int> touched;
vector<int> order;
int rem;
int call;
int check(int row, int col){
    int tsum = 0; int left = 0;
    for (auto [dx, dy]: d){
        if (inside(row+dx, col+dy) && !req[row+dx][col+dy]){
            // cout << row+dx << ' ' << col+dy << "\n";
            if (!v[row+dx][col+dy]){
                left++; tsum++;
            }
            tsum += v[row+dx][col+dy];
        }
    }
    if (!left && tsum!=req[row][col]) return 0;
    if (tsum > req[row][col]) return 0;
    return 1;


}
int solve(int index){
    if (index>=rem) return 1;
    int x = order[index];
    int row = x/10; int col = x%10;
    // cout << x << "\n";
    // if (req[row][col] || v[row][col]) cout << "here\n";
    // if (v[row][col]) return solve(index+1);
    for (int i=1; i<=3; i++){
        v[row][col] = i;
        int ok = 1;
        int rowsum = 0; int rowleft = 0;
        int colsum = 0; int colleft = 0;
        for (int j=0; j<10; j++){
            rowsum += v[row][j];
            if (!req[row][j] && !v[row][j]){
                rowsum++;
                rowleft++;
            } 
            colsum += v[j][col];
            if (!req[j][col] && !v[j][col]){
                colsum++;
                colleft++;
            }
        }
        // cout << rowsum << ' ' << colsum << "\n";
        if (rowsum>10 || colsum>10) continue;
        if (rowsum!=10 && !rowleft) continue;
        if (colsum!=10 && !colleft) continue;
        for (auto [dx, dy]: d){
            if (inside(row+dx, col+dy) && req[row+dx][col+dy]){
                if (!check(row+dx, col+dy)){
                    ok = 0;
                    break;
                }
            }
        }
        if (!ok) continue;
        if (solve(index+1)) return 1;  

    }
    v[row][col] = 0;
    return 0;
}
int recalc(){
    int bestval = -INF;
    int best = -1;
    for (int x=0; x<100; x++){
        int row = x/10; int col = x%10;
        if (touched[x]) continue;
        int s1 = 0; int s2 = 0; int s3 = 0;
        for (int i=0; i<10; i++){
            if (touched[x-x%10+i]) s1++;
            if (touched[x%10+10*i]) s2++;
        }
        for (auto [dx, dy]: d){
            if (inside(row+dx, col+dy) && req[row+dx][col+dy]) s3++;
        }
        int res = max(s1, s2)*max(s1, s2) + min(s1, s2)*min(s1, s2) + s3*3;
        if (res>bestval){
            bestval = res;
            best = x;
        }
    }
    return best;
}
void solve() {
    int K; cin >> K;
    rem = 100; call = 0;
    v = vector<vector<int>>(10, vector<int>(10, 0));
    req = vector<vector<int>>(10, vector<int>(10, 0));
    touched = vector<int>(100, 0);
    order = vector<int>(100, 0);
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            cin >> v[i][j];
            if (v[i][j]!=-1){
                req[i][j] = v[i][j];
                touched[10*i+j] = 1; 
                rem--;
            }
            v[i][j] = 0;
        }
    }
    // cout << rem << "\n";

    for (int i=0; i<rem; i++){
        order[i] = recalc();
        touched[order[i]] = 1;
    }
    cout << solve(0) << "\n";
    // cout << call << "\n";
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            if (req[i][j]) v[i][j] = req[i][j];
        }
    }
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
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