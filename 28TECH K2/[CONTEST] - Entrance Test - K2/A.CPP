/* RemyVN */
#include <bits/stdc++.h>
#define ll long long 
#define int long long
#define endl '\n'
#define TASK ""
#define ull unsigned long long  
using namespace std;

constexpr int MOD = 1e9 + 7;
constexpr int SIZE = 1e6 + 10;

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen(TASK".INP", "r")) {
        freopen(TASK".INP", "r", stdin);
        freopen(TASK".OUT", "w", stdout);
        freopen(TASK".ERR", "w", stderr);
    }
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    string ans = "YES";
    for(int i = 0; i < n; i++) {
        if(a[i] > a[i + 1] && a[i + 1] <= 1) {
            ans = "NO";
            break;
        }
    }
    cerr << endl << "Running time: " << (1.0 * clock()) / CLOCKS_PER_SEC << endl;
    return (0 ^ 0);
}

/* Chờ em tới khi nào ??? */
