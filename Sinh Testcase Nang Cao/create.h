#include<bits/stdc++.h>
using namespace std;

namespace Create
{
    string str (long long a)
    {
        if(a == 0) return "0";
        if(a < 0) return "-" + str(-a);
        string ans = "";
        for(int i = 1; i <= 4; i ++)
        {
            ans = "0" + ans;
            ans[0] = (a % 10) + '0';
            a /= 10;
        }
        return ans;
    }

    void copy_test (string prob_name, string subtask, int iTest)
    {
        cerr << "Dang tao thu muc chua test #" << iTest << ".\n";

        // Sử dụng to_string chuẩn thay vì str để không zero-padding
        stringstream ss;
        ss << setw(4) << setfill('0') << iTest; // Vẫn giữ zero-padding 4 chữ số cho thư mục test con
        string test_folder_index = ss.str();

        string folder_link = prob_name + "\\" + test_folder_index + (subtask.empty() ? "" : ("_" + subtask)); // Thêm subtask nếu có
        string check_cmd = "if exist \"" + folder_link + "\\\" (exit /b 0) else (exit /b 1)"; // Sửa logic: trả về 0 nếu TỒN TẠI

        // Xóa thư mục con nếu nó đã tồn tại để ghi đè
        if (system(check_cmd.c_str()) == 0) {
             cerr << "Thu muc test con da ton tai, xoa bo: " << folder_link << endl;
             system(("rmdir /s /q \"" + folder_link + "\"").c_str());
        }

        system(("mkdir \"" + folder_link + "\"").c_str());

        cerr << "Dang sao chep cac file input va output.\n";

        string inp_file = prob_name + ".inp";
        string out_file = prob_name + ".out";

        string copy_inp_cmd = "copy \"" + inp_file + "\" \"" + folder_link + "\" > nul"; // Ẩn output của copy
        string copy_out_cmd = "copy \"" + out_file + "\" \"" + folder_link + "\" > nul"; // Ẩn output của copy

        if (system(copy_inp_cmd.c_str()) != 0) {
             cerr << "CANH BAO: Khong the sao chep file " << inp_file << endl;
        }
        if (system(copy_out_cmd.c_str()) != 0) {
            cerr << "CANH BAO: Khong the sao chep file " << out_file << endl;
        }


        cerr << "Da sao chep xong.\n";
    }

    void create_root (string prob_name)
    {
        string check_cmd = "if exist \"" + prob_name + "\\\" (exit /b 0) else (exit /b 1)"; // Trả về 0 nếu TỒN TẠI
        bool existed = (system (check_cmd.c_str()) == 0); // Kiểm tra xem thư mục đã tồn tại chưa

        if (existed) // Chỉ xử lý nếu thư mục đã tồn tại
        {
            cerr << "Thu muc \"" << prob_name << "\" da ton tai.\n";
            cerr << "Xoa bo test cu (y) hay luu vao history (n)? [y/n]: ";
            string _ok;
            cin >> _ok;

            while (_ok != "y" && _ok != "n")
            {
                cerr << "Nhap lai (y/n): ";
                cin >> _ok;
            }

            if (_ok == "y") // Người dùng chọn xóa
            {
                cerr << "Dang xoa bo test cu...\n";
                string delete_cmd = "rmdir /s /q \"" + prob_name + "\"";
                if (system(delete_cmd.c_str()) != 0) {
                     cerr << "CANH BAO: Khong the xoa thu muc " << prob_name << endl;
                     // Có thể dừng chương trình ở đây nếu việc xóa là bắt buộc
                } else {
                    cerr << "Da xoa bo test cu.\n";
                }
                existed = false; // Đánh dấu là đã xóa (hoặc không còn tồn tại để move)
            }
            else // Người dùng chọn lưu vào history <<< LOGIC MỚI >>>
            {
                cerr << "Dang di chuyen bo test cu vao history...\n";
                string history_root = prob_name + "_history";

                // 1. Tạo thư mục history gốc nếu chưa có
                string mkdir_history_cmd = "mkdir \"" + history_root + "\" 2> nul"; // 2> nul để ẩn lỗi nếu thư mục đã tồn tại
                system(mkdir_history_cmd.c_str());

                // 2. Tìm chỉ số history tiếp theo
                int history_index = 1;
                string current_history_check_path;
                string check_history_item_cmd;
                do {
                    current_history_check_path = history_root + "\\" + prob_name + "_" + to_string(history_index);
                    check_history_item_cmd = "if exist \"" + current_history_check_path + "\\\" (exit /b 0) else (exit /b 1)";
                    if (system(check_history_item_cmd.c_str()) == 0) { // Nếu thư mục con tồn tại
                        history_index++;
                    } else {
                        break; // Tìm thấy chỉ số trống
                    }
                } while (true); // Lặp cho đến khi tìm thấy chỉ số trống

                string target_history_path = current_history_check_path; // Đường dẫn đích trong history

                // 3. Di chuyển thư mục cũ vào thư mục history
                string move_cmd = "move \"" + prob_name + "\" \"" + target_history_path + "\"";
                cerr << "Thuc thi lenh: " << move_cmd << endl; // In lệnh để debug (tùy chọn)

                if (system(move_cmd.c_str()) != 0) {
                     cerr << "LOI: Khong thể di chuyển \"" << prob_name << "\" vào \"" << target_history_path << "\". Vui lòng kiểm tra lại." << endl;
                     cerr << "Giữ nguyên thư mục cũ và thoát." << endl;
                     exit(1); // Dừng chương trình vì không thể di chuyển
                } else {
                     cerr << "Da di chuyen bo test cu vao: \"" << target_history_path << "\"\n";
                     existed = false; // Đánh dấu là đã di chuyển thành công
                }
            }
        }

        // Tạo thư mục gốc mới nếu nó chưa tồn tại ban đầu hoặc đã được xóa/di chuyển thành công
        if (!existed) {
             string mkdir_cmd = "mkdir \"" + prob_name + "\"";
             if(system(mkdir_cmd.c_str()) != 0) {
                 cerr << "LOI: Khong thể tạo thư mục gốc mới \"" << prob_name << "\". Vui lòng kiểm tra lại." << endl;
                 exit(1); // Dừng chương trình vì không thể tạo thư mục làm việc chính
             }
        }
    }

    void compile_solution ()
    {
        cerr << "Dang bien dich file loi giai (solution.cpp).\n";
        // Nên dùng c++17 trở lên và bật cảnh báo
        int result = system("g++ -std=c++14 -Wall -Wextra -O2 -s -static solution.cpp -o solution.exe");
        if (result != 0) {
            cerr << "LOI: Khong the bien dich solution.cpp. Ma loi: " << result << endl;
            exit(1); // Thoát nếu biên dịch lỗi
        }
        cerr << "Bien dich solution.cpp thanh cong.\n";
    }

    // <<< HÀM MỚI >>>
    void compile_validator ()
    {
        cerr << "Dang bien dich file kiem tra (validator.cpp).\n";
         // Nên dùng c++17 trở lên và bật cảnh báo
        int result = system("g++ -std=c++14 -Wall -Wextra -O2 -s -static validator.cpp -o validator.exe");
        if (result != 0) {
            cerr << "LOI: Khong the bien dich validator.cpp. Ma loi: " << result << endl;
            exit(1); // Thoát nếu biên dịch lỗi
        }
        cerr << "Bien dich validator.cpp thanh cong.\n";
    }
}
