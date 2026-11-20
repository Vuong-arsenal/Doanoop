#include "Airline.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h> // Hỗ trợ tiếng Việt UTF-8 trên Windows Console
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    Airline vietnamAirlines{ "Vietnam Airlines" };
    int luaChon{ 0 };

    do {
        std::cout << "\n========================================================\n";
        std::cout << "   PHẦN MỀM QUẢN LÝ VÉ MÁY BAY - AIRLINE SYSTEM\n";
        std::cout << "========================================================\n";
        std::cout << "[1] Xem danh sách (Chuyến bay, Hành khách, Vé)\n";
        std::cout << "[2] Chỉnh sửa danh sách (Thêm, Sửa, Xóa)\n";
        std::cout << "[3] Thống kê, Lọc & Sắp xếp\n";
        std::cout << "[4] Tìm kiếm (Chuyến bay, Hành khách, Vé)\n";
        std::cout << "[0] Thoát chương trình (Tự động lưu dữ liệu vào file)\n";
        std::cout << "========================================================\n";
        std::cout << "=> Nhập lựa chọn của bạn (0-4): ";
        std::cin >> luaChon;

        switch (luaChon) {
        case 1:
            vietnamAirlines.xemDanhSach();
            break;
        case 2:
            vietnamAirlines.chinhSuaDanhSach();
            break;
        case 3:
            vietnamAirlines.thongke();
            break;
        case 4:
            vietnamAirlines.timKiem();
            break;
        case 0:
            std::cout << "\nĐang lưu dữ liệu vào file... Tạm biệt!\n";
            break;
        default:
            std::cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại từ 0 đến 4!\n";
        }
    } while (luaChon != 0);

    return 0;
}
