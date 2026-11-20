#ifndef UTILS_H
#define UTILS_H

#include <stdexcept>
#include <string>

// Ngoại lệ tự định nghĩa khi không tìm thấy đối tượng (Bài 7)
class NotFoundException : public std::runtime_error {
public:
    explicit NotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

// Hàm phụ cắt khoảng trắng thừa ở đầu và cuối chuỗi
std::string trim(std::string s);

#endif
