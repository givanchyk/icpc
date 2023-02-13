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
int N = 6;
vector<vector<array<int, 2>>> v;
vector<int> touched;
vector<int> order;
int rem;
int checkrow(int x){
    int row = x/2/N; int col = (x/2)%N; int ind = x%2;  
    for (int i=0; i<N; i++){
        for (int ind2=0; ind2<=1; ind2++){
            if (i==col && ind==ind2) continue;
            if (v[row][i][ind2]==v[row][col][ind]) return 0;            
        }

    }
    return 1;
}
int checkcol(int x){
    int row = x/2/N; int col = (x/2)%N; int ind = x%2;  
    for (int i=0; i<N; i++){
        for (int ind2=0; ind2<=1; ind2++){
            if (i==row && ind==ind2) continue;
            if (v[i][col][ind2]==v[row][col][ind]) return 0;            
        }

    }
    return 1;
}
int check33(int x){
    int row = x/2/N; int col = (x/2)%N; int ind = x%2;
    for (int i=0; i<2; i++){
        for (int j=0; j<3; j++){
            for (int ind2=0; ind2<=1; ind2++){
                int c1 = 2*(row/2)+i; int c2 = 3*(col/3)+j;
                if (c1==row && c2==col && ind2==ind) continue;
                if (v[c1][c2][ind2]==v[row][col][ind]){
                    return 0;
                }
            }
        }
    }
    return 1;
}
int solve(int index){
    if (index>=rem) return 1;
    int x = order[index];
    int row = x/2/N; int col = (x/2)%N; int ind = x%2;
    // cout << x << "\n";
    // if (req[row][col] || v[row][col]) cout << "here\n";
    // if (v[row][col]) return solve(index+1);
    // cout << x << "\n";
    for (int i=1; i<=9; i++){
        int ok = 1;
        v[row][col][ind] = i;
        ok &= checkrow(x);
        ok &= checkcol(x);
        ok &= check33(x);
        if (!ok) continue;
        // cout << "here\n";
        
        if (solve(index+1)) return 1;  

    }
    v[row][col][ind] = 0;
    return 0;
}
int recalc(){
    int bestval = -INF;
    int best = -1;
    for (int x=0; x<2*N*N; x++){
        int row = (x/2)/N; int col = (x/2)%N; int ind = x%2;
        if (touched[x]) continue;
        // int s1 = 0; int s2 = 0; int s3 = 0;
        // for (int i=0; i<N; i++){
        //     if (touched[x-x%N+i]) s1++;
        //     if (touched[x%N+N*i]) s2++;

        // }
        // for (auto [dx, dy]: d){
        //     // if (inside(row+dx, col+dy) && req[row+dx][col+dy]) s3++;
        // }
        int res = 0;//max(s1, s2)*max(s1, s2) + min(s1, s2)*min(s1, s2) + s3*3;
        if (res>bestval){
            bestval = res;
            best = x;
        }
    }
    return best;
}
array<int, 2> process(string s){
    array<int, 2> res;
    if (s.size()==3){
        if (s[0]=='-') res[0] = 0;
        else res[0] = s[0]-'0';
        if (s[2]=='-') res[1] = 0;
        else res[1] = s[2]-'0';
        return res;
    }
    res[1] = -1;
    if (s[0]=='-') res[0] = 0;
    else res[0] = s[0]-'0';
    return res;

}
void solve() {
    int K; cin >> K;
    v = vector<vector<array<int, 2>>>(6, vector<array<int, 2>>(6));
    touched = vector<int>(6*6*2, 0);
    order = vector<int>(6*6*2, 0);
    rem = 6*6*2;
    for (int i=0; i<6; i++){
        for (int j=0; j<6; j++){
            string s; cin >> s;
            v[i][j] = process(s);
            if (v[i][j][0]){
                rem--;
                touched[i*2*N + j*2] = 1;
            }
            if (v[i][j][1]){
                rem--;
                touched[i*2*N + j*2 + 1] = 1;
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
    for (int i=0; i<6; i++){
        for (int j=0; j<6; j++){
            if (v[i][j][1]==-1) cout << v[i][j][0] << ' ';
            else cout << v[i][j][0] << '/' << v[i][j][1] << ' ';
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