/* RemyVN */
#include <bits/stdc++.h>
#define ll long long 
#define int long long
#define endl '\n'
#define TASK ""
using namespace std;

constexpr int MOD = 1e9 + 7;
constexpr int SIZE = 1e6 + 10;

void solve() {
    int n;
    cin >> n;
    // Dùng vector thay cho mảng VLA để an toàn bộ nhớ
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    string ans = "YES";
    // Sửa điều kiện lặp thành i < n - 1 để tránh lỗi a[i + 1] bị tràn
    for(int i = 0; i < n - 1; i++) {
        if(a[i] > a[i + 1] && a[i + 1] <= 1) {
            ans = "NO";
            break;
        }
    }
    
    // THÊM LỆNH IN KẾT QUẢ
    cout << ans << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    if(fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        freopen(TASK".ERR", "w", stderr);
    }
    
    // THÊM VÒNG LẶP T ĐỂ XỬ LÝ ĐÚNG INPUT
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    
    cerr << endl << "Running time: " << (1.0 * clock()) / CLOCKS_PER_SEC << endl;
    return (0 ^ 0);
}