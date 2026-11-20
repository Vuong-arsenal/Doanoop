#include "Airline.h"
#include "Utils.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

Airline::Airline(const std::string& ten) : tenHang{ten} {
    docFileChuyenBay();
    docFileHanhKhach();
    docFileVe();
}

Airline::~Airline() {
    try {
        ghiFile();
    } catch (const std::exception& e) {
        std::cerr << "Loi ghi file: " << e.what() << "\n";
    }
}

Flight* Airline::timChuyenBay(const std::string& maCB) const {
    for (const auto& f : dsChuyenBay) {
        if (f->getMaCB() == maCB) return f.get();
    }
    return nullptr;
}

Passenger* Airline::timHanhKhach(const std::string& maHK) const {
    for (const auto& p : dsHanhKhach) {
        if (p->getMaHK() == maHK) return p.get();
    }
    return nullptr;
}

Ticket* Airline::timVe(const std::string& maVe) const {
    for (const auto& t : dsVe) {
        if (t->getMaVe() == maVe) return t.get();
    }
    return nullptr;
}

void Airline::docFileChuyenBay() {
    std::ifstream ifs("chuyenbay.txt");
    if (!ifs.is_open()) return;

    std::string line, currentType;
    while (std::getline(ifs, line)) {
        line = trim(line);
        if (line.empty()) continue;

        if (line == "[DOMESTIC]" || line == "[INTERNATIONAL]") {
            currentType = line;
            continue;
        }
        if (line.find("Ma CB") == 0) continue;

        auto f = FlightFactory::tao(currentType);
        if (f != nullptr) {
            std::stringstream ss(line);
            if (f->docFile(ss) && timChuyenBay(f->getMaCB()) == nullptr) {
                dsChuyenBay.push_back(std::move(f));
            }
        }
    }
}

void Airline::docFileHanhKhach() {
    std::ifstream ifs("hanhkhach.txt");
    if (!ifs.is_open()) return;

    std::string line;
    while (std::getline(ifs, line)) {
        line = trim(line);
        if (line.empty() || line.find("Ma HK") == 0) continue;

        std::stringstream ss(line);
        auto p = std::make_unique<Passenger>();
        ss >> *p;
        if (!p->getMaHK().empty() && timHanhKhach(p->getMaHK()) == nullptr) {
            dsHanhKhach.push_back(std::move(p));
        }
    }
}

void Airline::docFileVe() {
    std::ifstream ifs("ve.txt");
    if (!ifs.is_open()) return;

    std::string line;
    while (std::getline(ifs, line)) {
        line = trim(line);
        if (line.empty() || line.find("Ma ve") == 0) continue;

        std::stringstream ss(line);
        std::string maVe, maCB, maHK, ngayDat;
        if (!std::getline(ss, maVe, '|')) continue;
        if (!std::getline(ss, maCB, '|')) continue;
        if (!std::getline(ss, maHK, '|')) continue;
        if (!std::getline(ss, ngayDat, '|')) continue;

        maVe = trim(maVe);
        maCB = trim(maCB);
        maHK = trim(maHK);
        ngayDat = trim(ngayDat);

        if (maVe.empty() || timVe(maVe) != nullptr) continue;

        Flight* fPtr = timChuyenBay(maCB);
        Passenger* pPtr = timHanhKhach(maHK);
        dsVe.push_back(std::make_unique<Ticket>(maVe, fPtr, pPtr, ngayDat));
    }
}

void Airline::xuatChuyenBay(std::ostream& os) const {
    os << "[DOMESTIC]\n";
    DomesticFlight::inTieuDe(os);
    os << "\n";
    for (const auto& f : dsChuyenBay) {
        if (f->getLoai() == 1) {
            f->xuat(os);
            os << "\n";
        }
    }

    os << "[INTERNATIONAL]\n";
    InternationalFlight::inTieuDe(os);
    os << "\n";
    for (const auto& f : dsChuyenBay) {
        if (f->getLoai() == 2) {
            f->xuat(os);
            os << "\n";
        }
    }
}

void Airline::xuatHanhKhach(std::ostream& os) const {
    Passenger::inTieuDe(os);
    os << "\n";
    for (const auto& p : dsHanhKhach) {
        os << *p << "\n";
    }
}

void Airline::xuatVe(std::ostream& os) const {
    Ticket::inTieuDe(os);
    os << "\n";
    for (const auto& t : dsVe) {
        os << *t << "\n";
    }
}

void Airline::ghiFile() const {
    std::ofstream ofsCB("chuyenbay.txt");
    if (!ofsCB.is_open()) throw std::runtime_error("Khong mo duoc file chuyenbay.txt!");
    xuatChuyenBay(ofsCB);

    std::ofstream ofsHK("hanhkhach.txt");
    if (!ofsHK.is_open()) throw std::runtime_error("Khong mo duoc file hanhkhach.txt!");
    xuatHanhKhach(ofsHK);

    std::ofstream ofsVe("ve.txt");
    if (!ofsVe.is_open()) throw std::runtime_error("Khong mo duoc file ve.txt!");
    xuatVe(ofsVe);
}

// --- 1. XEM DANH SÁCH ---
void Airline::xemDanhSach() const {
    int chon{0};
    do {
        std::cout << "\n--- XEM DANH SÁCH ---\n";
        std::cout << "[1] Xem danh sách Chuyến bay (Nội địa & Quốc tế - Đa hình)\n";
        std::cout << "[2] Xem danh sách Hành khách\n";
        std::cout << "[3] Xem danh sách Vé máy bay (Kèm tổng tiền)\n";
        std::cout << "[0] Quay lại menu chính\n";
        std::cout << "=> Nhập lựa chọn: ";
        std::cin >> chon;

        switch (chon) {
        case 1:
            std::cout << "\n=== DANH SÁCH CHUYẾN BAY ===\n";
            xuatChuyenBay(std::cout);
            break;
        case 2:
            std::cout << "\n=== DANH SÁCH HÀNH KHÁCH ===\n";
            xuatHanhKhach(std::cout);
            break;
        case 3:
            std::cout << "\n=== DANH SÁCH VÉ MÁY BAY ===\n";
            xuatVe(std::cout);
            break;
        case 0:
            break;
        default:
            std::cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (chon != 0);
}

// --- 2. QUẢN LÝ NGHIỆP VỤ (THÊM, SỬA, XÓA) ---
void Airline::themChuyenBay() {
    int loai{0};
    std::cout << "Chọn loại chuyến bay (1. Nội địa, 2. Quốc tế): ";
    std::cin >> loai;
    if (loai != 1 && loai != 2) {
        throw std::invalid_argument("Loai chuyen bay khong hop le!");
    }

    std::string maCB, di, den;
    double gia{0.0};
    std::cout << "Nhập mã chuyến bay: ";
    std::cin >> maCB;
    if (timChuyenBay(maCB) != nullptr) {
        throw std::invalid_argument("Ma chuyen bay da ton tai!");
    }

    std::cin.ignore();
    std::cout << "Nhập điểm đi: ";
    std::getline(std::cin, di);
    std::cout << "Nhập điểm đến: ";
    std::getline(std::cin, den);
    std::cout << "Nhập giá cơ bản: ";
    std::cin >> gia;
    if (gia < 0) {
        throw std::invalid_argument("Gia co ban khong duoc am!");
    }

    if (loai == 1) {
        double phuThu{0.0};
        std::cout << "Nhập phụ thu nội địa: ";
        std::cin >> phuThu;
        dsChuyenBay.push_back(std::make_unique<DomesticFlight>(maCB, di, den, gia, phuThu));
    } else {
        double phiQT{0.0}, thue{0.0};
        std::cout << "Nhập phí quốc tế: ";
        std::cin >> phiQT;
        std::cout << "Nhập thuế VAT: ";
        std::cin >> thue;
        dsChuyenBay.push_back(std::make_unique<InternationalFlight>(maCB, di, den, gia, phiQT, thue));
    }
    std::cout << "Thêm chuyến bay thành công!\n";
}

void Airline::suaChuyenBay() {
    std::string ma;
    std::cout << "Nhập mã chuyến bay cần sửa: ";
    std::cin >> ma;

    Flight* f = timChuyenBay(ma);
    if (f == nullptr) {
        throw NotFoundException("Khong tim thay ma chuyen bay: " + ma);
    }

    std::cout << "Thông tin chuyến bay hiện tại:\n";
    if (f->getLoai() == 1) DomesticFlight::inTieuDe(std::cout);
    else InternationalFlight::inTieuDe(std::cout);
    std::cout << "\n";
    f->xuat(std::cout);
    std::cout << "\n";

    f->suaThongTin();
    std::cout << "Cập nhật thông tin chuyến bay thành công!\n";
}

void Airline::xoaChuyenBay() {
    std::string ma;
    std::cout << "Nhập mã chuyến bay cần xóa: ";
    std::cin >> ma;

    for (auto it = dsChuyenBay.begin(); it != dsChuyenBay.end(); ++it) {
        if ((*it)->getMaCB() == ma) {
            Flight* target = it->get();
            for (auto veIt = dsVe.begin(); veIt != dsVe.end();) {
                if ((*veIt)->getFlightPtr() == target) {
                    veIt = dsVe.erase(veIt);
                } else {
                    ++veIt;
                }
            }
            dsChuyenBay.erase(it);
            std::cout << "Xóa chuyến bay (và các vé liên quan nếu có) thành công!\n";
            return;
        }
    }
    throw NotFoundException("Khong tim thay ma chuyen bay: " + ma);
}

void Airline::themVe() {
    std::string maVe, maCB, maHK, ngay;
    std::cout << "Nhập mã vé mới: ";
    std::cin >> maVe;
    if (timVe(maVe) != nullptr) {
        throw std::invalid_argument("Ma ve da ton tai!");
    }

    std::cout << "Nhập mã chuyến bay: ";
    std::cin >> maCB;
    Flight* fPtr = timChuyenBay(maCB);
    if (fPtr == nullptr) {
        throw NotFoundException("Khong tim thay ma chuyen bay: " + maCB);
    }

    std::cout << "Nhập mã hành khách: ";
    std::cin >> maHK;
    Passenger* pPtr = timHanhKhach(maHK);
    if (pPtr == nullptr) {
        std::cout << "Chưa có hành khách " << maHK << ". Nhập thông tin mới:\n";
        auto pMoi = std::make_unique<Passenger>();
        pMoi->nhap(maHK);
        pPtr = pMoi.get();
        dsHanhKhach.push_back(std::move(pMoi));
    }

    std::cout << "Nhập ngày đặt (dd/mm/yyyy): ";
    std::cin >> ngay;

    dsVe.push_back(std::make_unique<Ticket>(maVe, fPtr, pPtr, ngay));
    std::cout << "Đặt vé thành công!\n";
}

void Airline::suaVe() {
    std::string maVe;
    std::cout << "Nhập mã vé cần sửa: ";
    std::cin >> maVe;

    Ticket* t = timVe(maVe);
    if (t == nullptr) {
        throw NotFoundException("Khong tim thay ma ve: " + maVe);
    }

    std::cout << "Thông tin vé hiện tại:\n";
    Ticket::inTieuDe(std::cout);
    std::cout << "\n" << *t << "\n";

    std::string maCB, maHK, ngay;
    std::cout << "Nhập mã chuyến bay mới: ";
    std::cin >> maCB;
    Flight* fPtr = timChuyenBay(maCB);
    if (fPtr == nullptr) {
        throw NotFoundException("Khong tim thay ma chuyen bay: " + maCB);
    }

    std::cout << "Nhập mã hành khách mới: ";
    std::cin >> maHK;
    Passenger* pPtr = timHanhKhach(maHK);
    if (pPtr == nullptr) {
        throw NotFoundException("Khong tim thay ma hanh khach: " + maHK);
    }

    std::cout << "Nhập ngày đặt mới (dd/mm/yyyy): ";
    std::cin >> ngay;

    t->setFlight(fPtr);
    t->setPassenger(pPtr);
    t->setNgayDat(ngay);
    std::cout << "Cập nhật thông tin vé thành công!\n";
}

void Airline::xoaVe() {
    std::string maVe;
    std::cout << "Nhập mã vé cần hủy: ";
    std::cin >> maVe;

    for (auto it = dsVe.begin(); it != dsVe.end(); ++it) {
        if ((*it)->getMaVe() == maVe) {
            dsVe.erase(it);
            std::cout << "Hủy vé thành công!\n";
            return;
        }
    }
    throw NotFoundException("Khong tim thay ma ve: " + maVe);
}

void Airline::suaHanhKhach() {
    std::string maHK;
    std::cout << "Nhập mã hành khách cần sửa: ";
    std::cin >> maHK;

    Passenger* p = timHanhKhach(maHK);
    if (p == nullptr) {
        throw NotFoundException("Khong tim thay ma hanh khach: " + maHK);
    }

    std::cout << "Thông tin hành khách hiện tại:\n";
    Passenger::inTieuDe(std::cout);
    std::cout << "\n" << *p << "\n";

    std::string hoten, cccd, sdt;
    std::cin.ignore();
    std::cout << "Nhập họ tên mới: ";
    std::getline(std::cin, hoten);
    std::cout << "Nhập CCCD mới: ";
    std::cin >> cccd;
    std::cout << "Nhập SĐT mới: ";
    std::cin >> sdt;
    p->setThongTin(hoten, cccd, sdt);
    std::cout << "Cập nhật thông tin hành khách thành công!\n";
}

void Airline::chinhSuaDanhSach() {
    int chon{0};
    do {
        std::cout << "\n--- CHỈNH SỬA DANH SÁCH ---\n";
        std::cout << "[1] Quản lý Chuyến bay (Thêm, Sửa, Xóa)\n";
        std::cout << "[2] Quản lý Vé (Đặt vé mới, Sửa vé, Hủy vé)\n";
        std::cout << "[3] Sửa thông tin Hành khách\n";
        std::cout << "[0] Quay lại menu chính\n";
        std::cout << "=> Nhập lựa chọn: ";
        std::cin >> chon;

        try {
            switch (chon) {
            case 1: {
                int subChoice{0};
                std::cout << "1. Thêm chuyến bay\n2. Sửa chuyến bay\n3. Xóa chuyến bay\nChọn: ";
                std::cin >> subChoice;
                if (subChoice == 1) themChuyenBay();
                else if (subChoice == 2) suaChuyenBay();
                else if (subChoice == 3) xoaChuyenBay();
                break;
            }
            case 2: {
                int subChoice{0};
                std::cout << "1. Đặt vé mới\n2. Sửa thông tin vé\n3. Hủy vé\nChọn: ";
                std::cin >> subChoice;
                if (subChoice == 1) themVe();
                else if (subChoice == 2) suaVe();
                else if (subChoice == 3) xoaVe();
                break;
            }
            case 3:
                suaHanhKhach();
                break;
            case 0:
                break;
            default:
                std::cout << "Lựa chọn không hợp lệ!\n";
            }
        } catch (const NotFoundException& e) {
            std::cout << "[Khong tim thay] " << e.what() << "\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "[Du lieu sai] " << e.what() << "\n";
        }
    } while (chon != 0);
}

// --- 3. TÌM KIẾM ĐỐI TƯỢNG ---
void Airline::timKiem() const {
    int chon{0};
    do {
        std::cout << "\n--- TÌM KIẾM ĐỐI TƯỢNG ---\n";
        std::cout << "[1] Tìm Chuyến bay theo mã\n";
        std::cout << "[2] Tìm Hành khách theo mã hoặc họ tên\n";
        std::cout << "[3] Tìm Vé theo mã vé\n";
        std::cout << "[0] Quay lại menu chính\n";
        std::cout << "=> Nhập lựa chọn: ";
        std::cin >> chon;

        try {
            switch (chon) {
            case 1: {
                std::string ma;
                std::cout << "Nhập mã chuyến bay cần tìm: ";
                std::cin >> ma;
                Flight* f = timChuyenBay(ma);
                if (f == nullptr) {
                    throw NotFoundException("Khong tim thay ma chuyen bay: " + ma);
                }
                if (f->getLoai() == 1) DomesticFlight::inTieuDe(std::cout);
                else InternationalFlight::inTieuDe(std::cout);
                std::cout << "\n";
                f->xuat(std::cout);
                std::cout << "\n";
                break;
            }
            case 2: {
                std::string tuKhoa;
                std::cin.ignore();
                std::cout << "Nhập mã hành khách hoặc họ tên cần tìm: ";
                std::getline(std::cin, tuKhoa);
                bool timThay{false};
                for (const auto& p : dsHanhKhach) {
                    if (p->getMaHK() == tuKhoa || p->getHoTen().find(tuKhoa) != std::string::npos) {
                        if (!timThay) {
                            Passenger::inTieuDe(std::cout);
                            std::cout << "\n";
                            timThay = true;
                        }
                        std::cout << *p << "\n";
                    }
                }
                if (!timThay) {
                    throw NotFoundException("Khong tim thay hanh khach: " + tuKhoa);
                }
                break;
            }
            case 3: {
                std::string ma;
                std::cout << "Nhập mã vé cần tìm: ";
                std::cin >> ma;
                Ticket* t = timVe(ma);
                if (t == nullptr) {
                    throw NotFoundException("Khong tim thay ma ve: " + ma);
                }
                Ticket::inTieuDe(std::cout);
                std::cout << "\n" << *t << "\n";
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Lựa chọn không hợp lệ!\n";
            }
        } catch (const NotFoundException& e) {
            std::cout << "[Khong tim thay] " << e.what() << "\n";
        }
    } while (chon != 0);
}

// --- 4. THỐNG KÊ, LỌC & SẮP XẾP ---
void Airline::locChuyenBay() const {
    int chon{0};
    std::cout << "\n--- LỌC CHUYẾN BAY ---\n";
    std::cout << "1. Lọc theo loại (Nội địa / Quốc tế)\n";
    std::cout << "2. Lọc theo điểm đi và điểm đến\n";
    std::cout << "Chọn: ";
    std::cin >> chon;

    if (chon == 1) {
        int loai{0};
        std::cout << "Chọn loại cần lọc (1. Nội địa, 2. Quốc tế): ";
        std::cin >> loai;
        if (loai != 1 && loai != 2) {
            std::cout << "Loại không hợp lệ!\n";
            return;
        }

        if (loai == 1) DomesticFlight::inTieuDe(std::cout);
        else InternationalFlight::inTieuDe(std::cout);
        std::cout << "\n";

        bool coKetQua{false};
        for (const auto& f : dsChuyenBay) {
            if (f->getLoai() == loai) {
                f->xuat(std::cout);
                std::cout << "\n";
                coKetQua = true;
            }
        }
        if (!coKetQua) std::cout << "(Không có chuyến bay nào thuộc loại này)\n";
    } else if (chon == 2) {
        std::string di, den;
        std::cin.ignore();
        std::cout << "Nhập điểm đi: ";
        std::getline(std::cin, di);
        std::cout << "Nhập điểm đến: ";
        std::getline(std::cin, den);

        bool coKetQua{false};
        for (const auto& f : dsChuyenBay) {
            if (f->getDiemDi() == di && f->getDiemDen() == den) {
                f->xuat(std::cout);
                std::cout << "\n";
                coKetQua = true;
            }
        }
        if (!coKetQua) std::cout << "(Không tìm thấy chuyến bay nào khớp tuyến này)\n";
    } else {
        std::cout << "Lựa chọn không hợp lệ!\n";
    }
}

void Airline::thongke() const {
    int chon{0};
    do {
        std::cout << "\n--- THỐNG KÊ, LỌC & SẮP XẾP ---\n";
        std::cout << "[1] Thống kê tổng doanh thu của hãng\n";
        std::cout << "[2] Sắp xếp danh sách chuyến bay theo giá tiền\n";
        std::cout << "[3] Thống kê số lượng vé theo từng chuyến bay\n";
        std::cout << "[4] Lọc chuyến bay (theo loại hoặc điểm đi - đến)\n";
        std::cout << "[0] Quay lại menu chính\n";
        std::cout << "=> Nhập lựa chọn: ";
        std::cin >> chon;

        switch (chon) {
        case 1: {
            double tongDoanhThu{0.0};
            for (const auto& t : dsVe) {
                tongDoanhThu += t->tinhTongTien();
            }
            std::cout << "\n=> Tổng doanh thu hiện tại của hãng: "
                      << std::fixed << std::setprecision(0) << tongDoanhThu << " VNĐ\n";
            break;
        }
        case 2: {
            std::vector<Flight*> temp;
            for (const auto& f : dsChuyenBay) {
                temp.push_back(f.get());
            }
            std::sort(temp.begin(), temp.end(), [](const Flight* a, const Flight* b) {
                return a->tinhGiaVe() < b->tinhGiaVe();
            });

            std::cout << "\n=== DANH SÁCH CHUYẾN BAY SẮP XẾP THEO GIÁ VÉ TĂNG DẦN ===\n";
            for (const Flight* f : temp) {
                f->xuat(std::cout);
                std::cout << "\n";
            }
            break;
        }
        case 3: {
            std::cout << "\n=== THỐNG KÊ SỐ LƯỢNG VÉ THEO CHUYẾN BAY ===\n";
            for (const auto& f : dsChuyenBay) {
                int count{0};
                for (const auto& t : dsVe) {
                    if (t->getFlightPtr() == f.get()) {
                        ++count;
                    }
                }
                std::cout << "Chuyến bay: " << std::left << std::setw(10) << f->getMaCB()
                          << " | Số lượng vé đã đặt: " << count << "\n";
            }
            break;
        }
        case 4:
            locChuyenBay();
            break;
        case 0:
            break;
        default:
            std::cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (chon != 0);
}
