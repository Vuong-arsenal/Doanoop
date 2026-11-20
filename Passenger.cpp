#include "Passenger.h"
#include "Utils.h"

#include <iomanip>
#include <stdexcept>

std::string Passenger::getMaHK() const { return maHK; }
std::string Passenger::getHoTen() const { return hoTen; }
std::string Passenger::getCCCD() const { return cccd; }
std::string Passenger::getSoDT() const { return soDT; }

void Passenger::setThongTin(const std::string& hoten, const std::string& cccdMoi,
                            const std::string& sdt) {
    if (trim(hoten).empty()) {
        throw std::invalid_argument("Ho ten khong duoc de trong!");
    }
    this->hoTen = hoten;
    this->cccd = cccdMoi;
    this->soDT = sdt;
}

void Passenger::inTieuDe(std::ostream& os) {
    os << std::left
       << std::setw(8) << "Ma HK" << " | "
       << std::setw(20) << "Ho ten" << " | "
       << std::setw(14) << "CCCD" << " | "
       << "So dien thoai";
}

void Passenger::nhap(const std::string& maCoSan) {
    if (maCoSan.empty()) {
        std::cout << "Nhập Mã Hành Khách: ";
        std::cin >> maHK;
    } else {
        maHK = maCoSan;
    }
    std::cin.ignore();
    std::cout << "Nhập Họ Tên: ";
    std::getline(std::cin, hoTen);
    if (trim(hoTen).empty()) {
        throw std::invalid_argument("Ho ten khong duoc de trong!");
    }
    std::cout << "Nhập CCCD: ";
    std::cin >> cccd;
    std::cout << "Nhập Số Điện Thoại: ";
    std::cin >> soDT;
}

bool Passenger::operator>(const Passenger& other) const {
    return this->maHK > other.maHK;
}

std::istream& operator>>(std::istream& is, Passenger& p) {
    std::string cot;
    if (!std::getline(is, cot, '|')) return is;
    p.maHK = trim(cot);

    if (!std::getline(is, cot, '|')) return is;
    p.hoTen = trim(cot);

    if (!std::getline(is, cot, '|')) return is;
    p.cccd = trim(cot);

    if (!std::getline(is, cot)) return is;
    p.soDT = trim(cot);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Passenger& p) {
    os << std::left
       << std::setw(8) << p.maHK << " | "
       << std::setw(20) << p.hoTen << " | "
       << std::setw(14) << p.cccd << " | "
       << p.soDT;
    return os;
}
