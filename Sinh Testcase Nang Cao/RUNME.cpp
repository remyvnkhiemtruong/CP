#include <fstream> // <<< THÊM HEADER NÀY
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip> // Để định dạng số

#define GENERATOR
#include "generator.cpp" // Include generator code
#include "create.h"      // Include helper functions

using namespace std;

// Hàm trợ giúp để chuyển đổi thời gian double thành string
string format_time(double time_ms) {
    stringstream ss;
    ss << fixed << setprecision(2) << time_ms; // Định dạng 2 chữ số thập phân
    return ss.str();
}


int main ()
{
    int testnum;
    cout << "Nhap so luong test: ";
    cin >> testnum;

    string prob_name;
    cout << "Nhap ma bai: ";
    cin >> prob_name;

    using namespace Create;
    create_root (prob_name);
    compile_solution (); // Biên dịch solution (có thể dùng C++14)
    compile_validator (); // Biên dịch validator (có thể dùng C++14)

    // --- Mở file log CSV --- <<< THÊM MỚI >>>
    string log_filename = prob_name + "_log.csv";
    ofstream log_file(log_filename);
    if (!log_file.is_open()) {
        cerr << "LOI: Khong the mo file log " << log_filename << " de ghi." << endl;
        return 1;
    }

    // Ghi header cho file CSV
    log_file << "Test Order,Input Gen Time (ms),Input Valid?,Validator Time (ms),Solution Error?,Solution Time (ms)\n";
    // --- Kết thúc phần mở file log ---

    cerr << "Bat dau sinh test\n----------\n";

    bool generation_ok = true; // Cờ để kiểm tra nếu có lỗi xảy ra

    for (int i = 1; i <= testnum; i ++)
    {
        string input_filename = prob_name + ".inp";
        string output_filename = prob_name + ".out";

        // Biến để lưu kết quả cho log
        string test_order_str = to_string(i);
        string input_gen_time_str = "N/A";
        string input_valid_str = "N/A";
        string validation_time_str = "N/A";
        string solution_error_str = "N/A";
        string solution_time_str = "N/A";

        int validation_result = -1; // Khởi tạo giá trị mặc định
        int solution_result = -1;   // Khởi tạo giá trị mặc định

        // --- Sinh Input ---
        if (!freopen (input_filename.c_str (), "w", stdout)) {
             cerr << "Loi: Khong the mo file input " << input_filename << " de ghi cho Test #" << i << "." << endl;
             generation_ok = false;
             // Ghi log lỗi và dừng lại
             log_file << test_order_str << ",ERROR_OPENING_INP,N/A,N/A,N/A,N/A\n";
             break; // Dừng vòng lặp
        }

        double input_gen_time, solution_exec_time = -1.0, validation_time = -1.0;
        clock_t start_time;

        cerr << "Test #" << i << ":\n";

        start_time = clock ();
        Gen::gen (i); // Sinh input vào file <prob_name>.inp
        input_gen_time = 1000.0 * (clock() - start_time) / CLOCKS_PER_SEC;
        input_gen_time_str = format_time(input_gen_time);
        fclose (stdout); // Đóng file input sau khi ghi xong

        cerr << "Da sinh xong input. Dang kiem tra tinh hop le (validate).\n";

        // --- KIỂM TRA INPUT BẰNG VALIDATOR ---
        start_time = clock();
        string validator_command = "validator.exe < " + input_filename;
        validation_result = system (validator_command.c_str()); // Chạy validator
        validation_time = 1000.0 * (clock() - start_time) / CLOCKS_PER_SEC;
        validation_time_str = format_time(validation_time);

        if (validation_result != 0) {
            input_valid_str = "NO"; // <<< Ghi nhận kết quả Validate
            cerr << "--------------------------------------------------\n";
            cerr << "LOI: Input KHONG HOP LE cho Test #" << i << " (validator tra ve ma loi: " << validation_result << ").\n";
            cerr << "=> Nguyen nhan co the do generator.cpp sinh sai hoac validator.cpp bi loi.\n";
            cerr << "=> Kiem tra thong bao loi (stderr) tu validator de biet chi tiet.\n";
            cerr << "=> Huy bo qua trinh sinh test.\n";
            cerr << "--------------------------------------------------\n";
            generation_ok = false;
            // Ghi dòng log cho test lỗi này và dừng lại
            log_file << test_order_str << "," << input_gen_time_str << "," << input_valid_str << "," << validation_time_str << ",N/A,N/A\n"; // <<< Ghi log khi Validate lỗi
            break; // Dừng vòng lặp
        } else {
            input_valid_str = "YES"; // <<< Ghi nhận kết quả Validate
            cerr << "Input hop le (Thoi gian kiem tra: " << validation_time << " ms).\n";
        }
        // --- KẾT THÚC KIỂM TRA ---

        cerr << "Dang chay file loi giai.\n";

        // --- Chạy Lời giải ---
        string solution_command = "solution.exe < " + input_filename + " > " + output_filename;

        start_time = clock ();
        solution_result = system(solution_command.c_str()); // Chạy solution
        solution_exec_time = 1000.0 * (clock() - start_time) / CLOCKS_PER_SEC;
        solution_time_str = format_time(solution_exec_time);

        if (solution_result != 0) {
             solution_error_str = "YES"; // <<< Ghi nhận Solution có lỗi
             cerr << "CANH BAO: File loi giai (solution.exe) ket thuc voi ma loi khac 0: " << solution_result << " cho Test #" << i << endl;
        } else {
             solution_error_str = "NO"; // <<< Ghi nhận Solution không có lỗi
        }

        cerr << "Da sinh xong output.\n";

        // --- Sao chép Test ---
        copy_test (prob_name, subtask, i); // subtask lấy từ generator thông qua template.h

        // --- Ghi log cho test thành công --- <<< THÊM MỚI >>>
        log_file << test_order_str << ","
                 << input_gen_time_str << ","
                 << input_valid_str << ","
                 << validation_time_str << ","
                 << solution_error_str << ","
                 << solution_time_str << "\n";
        // --- Kết thúc ghi log ---

        cerr << "Ket thuc qua trinh sinh test #" << i << ".\n";
        cerr << "Thoi gian sinh input: " << input_gen_time << " ms.\n";
        cerr << "Thoi gian chay loi giai: " << solution_exec_time << " ms.\n";
        cerr << "-----\n";
    }

    // --- Đóng file log --- <<< THÊM MỚI >>>
    log_file.close();
    cerr << "--------------------\n";
    if (generation_ok) {
        cerr << "Da sinh thanh cong " << testnum << " test.\n";
    } else {
        cerr << "Qua trinh sinh test bi dung do co loi.\n";
    }
    cerr << "Log chi tiet da duoc ghi vao file: " << log_filename << endl;
    cerr << "Ket thuc chuong trinh sinh test.\n";


    return 0;
}
