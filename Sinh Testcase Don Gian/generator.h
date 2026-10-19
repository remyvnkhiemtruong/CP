#include <bits/stdc++.h>
#include "template.h"
using namespace std;

void gen(int iTest, int testnum, string target_file)
{
    ofstream cout(target_file);
    
    // Khởi tạo T tùy theo độ lớn của iTest
    int T = (iTest <= 10) ? Rand(1, 10) : Rand(10, 100);
    cout << T << '\n';
    
    // Đảm bảo tổng n <= 10^6
    int max_sum_n = 1000000;
    
    // Nếu là các test cuối (test lớn), ép tổng n xấp xỉ 10^6
    if (iTest >= 40) max_sum_n = 1000000; 
    else max_sum_n = Rand(1000, 100000); 

    for(int t = 1; t <= T; t++) {
        // Phân bổ n cho từng test case
        int n;
        if (t == T) n = max_sum_n;
        else {
            n = Rand(1, max_sum_n - (T - t)); 
            max_sum_n -= n;
        }
        
        cout << n << '\n';
        for(int i = 1; i <= n; i++) {
            long long val;
            int type = Rand(1, 100);
            
            // Tạo bẫy: Các test case có a_i = 0 hoặc 1 (rất dễ sai)
            if (type <= 10) val = 0;
            else if (type <= 20) val = 1;
            else val = Rand(0, 1000000000); // 0 <= a_i <= 10^9
            
            cout << val << (i == n ? "" : " ");
        }
        cout << '\n';
    }
}