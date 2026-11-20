#include "Flight.h"
#include "Utils.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

// ==========================================
// Flight
// ==========================================
Flight::Flight(const std::string& ma, const std::string& di, const std::string& den, double gia)
    : maCB{ma}, diemDi{di}, diemDen{den}, giaCoBan{gia} {
    if (gia < 0) {
        throw std::invalid_argument("Gia co ban khong duoc am!");
    }
}

void Flight::suaThongTinChung() {
    std::string diMoi, denMoi;
    double giaMoi{0.0};
    std::cin.ignore();
    std::cout << "Nhập điểm đi mới: ";
    std::getline(std::cin, diMoi);
    std::cout << "Nhập điểm đến mới: ";
    std::getline(std::cin, denMoi);
    std::cout << "Nhập giá cơ bản mới: ";
    std::cin >> giaMoi;
    if (giaMoi < 0) {
        throw std::invalid_argument("Gia co ban khong duoc am!");
    }
    diemDi = diMoi;
    diemDen = denMoi;
    giaCoBan = giaMoi;
}

std::string Flight::getMaCB() const { return maCB; }
std::string Flight::getDiemDi() const { return diemDi; }
std::string Flight::getDiemDen() const { return diemDen; }
double Flight::getGiaCoBan() const { return giaCoBan; }

bool Flight::operator>(const Flight& other) const {
    return this->maCB > other.maCB;
}

// ==========================================
// DomesticFlight
// ==========================================
DomesticFlight::DomesticFlight(const std::string& ma, const std::string& di, const std::string& den,
                               double gia, double phuThu)
    : Flight{ma, di, den, gia}, phuThuNoiDia{phuThu} {
    if (phuThu < 0) {
        throw std::invalid_argument("Phu thu noi dia khong duoc am!");
    }
}

double DomesticFlight::getPhuThu() const { return phuThuNoiDia; }

double DomesticFlight::tinhGiaVe() const {
    return giaCoBan + phuThuNoiDia;
}

void DomesticFlight::inTieuDe(std::ostream& os) {
    os << std::left
       << std::setw(10) << "Ma CB" << " | "
       << std::setw(14) << "Diem di" << " | "
       << std::setw(14) << "Diem den" << " | "
       << std::setw(12) << "Gia co ban" << " | "
       << std::setw(10) << "Phu thu" << " | "
       << "Tong gia";
}

bool DomesticFlight::docFile(std::istream& is) {
    std::string cot;
    if (!std::getline(is, cot, '|')) return false;
    maCB = trim(cot);

    if (!std::getline(is, cot, '|')) return false;
    diemDi = trim(cot);

    if (!std::getline(is, cot, '|')) return false;
    diemDen = trim(cot);

    if (!std::getline(is, cot, '|')) return false;
    std::stringstream ssGia(trim(cot));
    if (!(ssGia >> giaCoBan) || giaCoBan < 0) return false;

    if (!std::getline(is, cot, '|')) return false;
    std::stringstream ssPhuThu(trim(cot));
    if (!(ssPhuThu >> phuThuNoiDia) || phuThuNoiDia < 0) return false;

    return !maCB.empty();
}

void DomesticFlight::xuat(std::ostream& os) const {
    os << std::left
       << std::setw(10) << maCB << " | "
       << std::setw(14) << diemDi << " | "
       << std::setw(14) << diemDen << " | "
       << std::setw(12) << std::fixed << std::setprecision(0) << giaCoBan << " | "
       << std::setw(10) << phuThuNoiDia << " | "
       << tinhGiaVe();
}

void DomesticFlight::suaThongTin() {
    suaThongTinChung();
    double phuThuMoi{0.0};
    std::cout << "Nhập phụ thu nội địa mới: ";
    std::cin >> phuThuMoi;
    if (phuThuMoi < 0) {
        throw std::invalid_argument("Phu thu noi dia khong duoc am!");
    }
    phuThuNoiDia = phuThuMoi;
}

int DomesticFlight::getLoai() const { return 1; }

// ==========================================
// InternationalFlight
// ==========================================
InternationalFlight::InternationalFlight(const std::string& ma, const std::string& di,
                                         const std::string& den, double gia, double phiQT,
                                         double thue)
    : Flight{ma, di, den, gia}, phiQuocTe{phiQT}, thueVatKhac{thue} {
    if (phiQT < 0 || thue < 0) {
        throw std::invalid_argument("Phi quoc te va thue VAT khong duoc am!");
    }
}

double InternationalFlight::getPhiQuocTe() const { return phiQuocTe; }
double InternationalFlight::getThueVatKhac() const { return thueVatKhac; }

double InternationalFlight::tinhGiaVe() const {
    return giaCoBan + phiQuocTe + thueVatKhac;
}

void InternationalFlight::inTieuDe(std::ostream& os) {
    os << std::left
       << std::setw(10) << "Ma CB" << " | "
       << std::setw(14) << "Diem di" << " | "
       << std::setw(14) << "Diem den" << " | "
       << std::setw(12) << "Gia co ban" << " | "
       << std::setw(10) << "Phi QT" << " | "
       << std::setw(10) << "Thue VAT" << " | "
       << "Tong gia";
}

bool InternationalFlight::docFile(std::istream& is) {
    std::string cot;
    if (!std::getline(is, cot, '|')) return false;
    maCB = trim(cot);

    if (!std::getline(is, cot, '|')) return false;
    diemDi = trim(cot);

    if (!std::getline(is, cot, '|')) return false;
    diemDen = trim(cot);

    if (!std::getline(is, cot, '|')) return false;
    std::stringstream ssGia(trim(cot));
    if (!(ssGia >> giaCoBan) || giaCoBan < 0) return false;

    if (!std::getline(is, cot, '|')) return false;
    std::stringstream ssPhi(trim(cot));
    if (!(ssPhi >> phiQuocTe) || phiQuocTe < 0) return false;

    if (!std::getline(is, cot, '|')) return false;
    std::stringstream ssThue(trim(cot));
    if (!(ssThue >> thueVatKhac) || thueVatKhac < 0) return false;

    return !maCB.empty();
}

void InternationalFlight::xuat(std::ostream& os) const {
    os << std::left
       << std::setw(10) << maCB << " | "
       << std::setw(14) << diemDi << " | "
       << std::setw(14) << diemDen << " | "
       << std::setw(12) << std::fixed << std::setprecision(0) << giaCoBan << " | "
       << std::setw(10) << phiQuocTe << " | "
       << std::setw(10) << thueVatKhac << " | "
       << tinhGiaVe();
}

void InternationalFlight::suaThongTin() {
    suaThongTinChung();
    double phiMoi{0.0}, thueMoi{0.0};
    std::cout << "Nhập phí quốc tế mới: ";
    std::cin >> phiMoi;
    std::cout << "Nhập thuế VAT mới: ";
    std::cin >> thueMoi;
    if (phiMoi < 0 || thueMoi < 0) {
        throw std::invalid_argument("Phi quoc te va thue VAT khong duoc am!");
    }
    phiQuocTe = phiMoi;
    thueVatKhac = thueMoi;
}

int InternationalFlight::getLoai() const { return 2; }

// ==========================================
// FlightFactory
// ==========================================
std::unique_ptr<Flight> FlightFactory::tao(const std::string& loaiStr) {
    if (loaiStr == "[DOMESTIC]") {
        return std::make_unique<DomesticFlight>();
    } else if (loaiStr == "[INTERNATIONAL]") {
        return std::make_unique<InternationalFlight>();
    }
    return nullptr;
}
