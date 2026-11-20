#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <windows.h> // Thư viện hỗ trợ thiết lập bảng mã UTF-8 trên Windows Console

using namespace std;

// Forward declarations
class Passenger;
class Flight;

// ==========================================
// 1. LỚP CƠ SỞ TRỪU TƯỢNG: Flight
// ==========================================
class Flight {
protected:
    string maCB;
    string diemDi;
    string diemDen;
    double giaCoBan;

public:
    virtual ~Flight() = default;

    virtual double tinhGiaVe() const = 0;
    virtual void docFile(istream& is) = 0;
    virtual void xuat(ostream& os) const = 0;
    virtual int getLoai() const = 0; // 1: Nội địa, 2: Quốc tế

    string getMaCB() const { return maCB; }
    string getDiemDi() const { return diemDi; }
    string getDiemDen() const { return diemDen; }
    double getGiaCoBan() const { return giaCoBan; }

    bool operator>(const Flight& other) const {
        return this->tinhGiaVe() > other.tinhGiaVe();
    }
};

// ==========================================
// 2. LỚP CON: DomesticFlight (Chuyến bay nội địa)
// ==========================================
class DomesticFlight : public Flight {
private:
    double phuThuNoiDia;

public:
    double getPhuThu() const { return phuThuNoiDia; }

    double tinhGiaVe() const override {
        return giaCoBan + phuThuNoiDia;
    }

    void docFile(istream& is) override {
        char ch;
        is >> ws >> maCB >> ch >> ws;
        getline(is, diemDi, '|'); while (!diemDi.empty() && diemDi.back() == ' ') diemDi.pop_back();
        getline(is, diemDen, '|'); while (!diemDen.empty() && diemDen.back() == ' ') diemDen.pop_back();
        is >> giaCoBan >> ch >> phuThuNoiDia;
    }

    void xuat(ostream& os) const override {
        os << left << setw(10) << maCB
            << " | Đi: " << setw(12) << diemDi
            << " | Đến: " << setw(12) << diemDen
            << " | Giá cơ bản: " << setw(10) << fixed << setprecision(0) << giaCoBan
            << " | Phụ thu: " << setw(8) << phuThuNoiDia
            << " | Tổng giá: " << tinhGiaVe() << " (Nội địa)";
    }

    int getLoai() const override { return 1; }
};

// ==========================================
// 3. LỚP CON: InternationalFlight (Quốc tế)
// ==========================================
class InternationalFlight : public Flight {
private:
    double phiQuocTe;
    double thueVatKhac;

public:
    double getPhiQuocTe() const { return phiQuocTe; }
    double getThueVatKhac() const { return thueVatKhac; }

    double tinhGiaVe() const override {
        return giaCoBan + phiQuocTe + thueVatKhac;
    }

    void docFile(istream& is) override {
        char ch;
        is >> ws >> maCB >> ch >> ws;
        getline(is, diemDi, '|'); while (!diemDi.empty() && diemDi.back() == ' ') diemDi.pop_back();
        getline(is, diemDen, '|'); while (!diemDen.empty() && diemDen.back() == ' ') diemDen.pop_back();
        is >> giaCoBan >> ch >> phiQuocTe >> ch >> thueVatKhac;
    }

    void xuat(ostream& os) const override {
        os << left << setw(10) << maCB
            << " | Đi: " << setw(12) << diemDi
            << " | Đến: " << setw(12) << diemDen
            << " | Giá cơ bản: " << setw(10) << fixed << setprecision(0) << giaCoBan
            << " | Phí QT: " << setw(8) << phiQuocTe
            << " | Thuế: " << setw(8) << thueVatKhac
            << " | Tổng giá: " << tinhGiaVe() << " (Quốc tế)";
    }

    int getLoai() const override { return 2; }
};

// ==========================================
// 4. LỚP TIỆN ÍCH: FlightFactory
// ==========================================
class FlightFactory {
public:
    static Flight* tao(string loaiStr) {
        if (loaiStr == "[DOMESTIC]") {
            return new DomesticFlight();
        }
        else if (loaiStr == "[INTERNATIONAL]") {
            return new InternationalFlight();
        }
        return nullptr;
    }
};

// ==========================================
// 5. LỚP HÀNH KHÁCH: Passenger
// ==========================================
class Passenger {
private:
    string maHK;
    string hoTen;
    string cccd;
    string soDT;

public:
    string getMaHK() const { return maHK; }
    string getHoTen() const { return hoTen; }
    string getCCCD() const { return cccd; }
    string getSoDT() const { return soDT; }

    void setThongTin(string hoten, string cccd, string sdt) {
        this->hoTen = hoten;
        this->cccd = cccd;
        this->soDT = sdt;
    }

    void nhap() {
        cout << "Nhập Mã Hành Khách: "; cin >> maHK;
        cout << "Nhập Họ Tên: "; cin.ignore(); getline(cin, hoTen);
        cout << "Nhập CCCD: "; cin >> cccd;
        cout << "Nhập Số Điện Thoại: "; cin >> soDT;
    }

    void xuat() const {
        cout << left << setw(8) << maHK
            << " | Họ tên: " << setw(20) << hoTen
            << " | CCCD: " << setw(14) << cccd
            << " | SĐT: " << soDT;
    }

    bool operator>(const Passenger& other) const {
        return this->maHK > other.maHK;
    }

    friend istream& operator>>(istream& is, Passenger& p) {
        char ch;
        is >> ws >> p.maHK >> ch >> ws;
        getline(is, p.hoTen, '|'); while (!p.hoTen.empty() && p.hoTen.back() == ' ') p.hoTen.pop_back();
        getline(is, p.cccd, '|'); while (!p.cccd.empty() && p.cccd.back() == ' ') p.cccd.pop_back();
        is >> p.soDT;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Passenger& p) {
        os << p.maHK << " | " << p.hoTen << " | " << p.cccd << " | " << p.soDT;
        return os;
    }
};

// ==========================================
// 6. LỚP VÉ MÁY BAY: Ticket
// ==========================================
class Ticket {
private:
    string maVe;
    Flight* flightPtr;
    Passenger* passengerPtr;
    string ngayDat;

public:
    Ticket() : flightPtr(nullptr), passengerPtr(nullptr) {}
    Ticket(string mv, Flight* f, Passenger* p, string nd)
        : maVe(mv), flightPtr(f), passengerPtr(p), ngayDat(nd) {
    }

    string getMaVe() const { return maVe; }
    Flight* getFlightPtr() const { return flightPtr; }
    Passenger* getPassengerPtr() const { return passengerPtr; }
    string getNgayDat() const { return ngayDat; }

    void setFlight(Flight* f) { flightPtr = f; }
    void setPassenger(Passenger* p) { passengerPtr = p; }
    void setNgayDat(string nd) { ngayDat = nd; }

    double tinhTongTien() const {
        if (flightPtr != nullptr) {
            return flightPtr->tinhGiaVe();
        }
        return 0.0;
    }

    bool operator>(const Ticket& other) const {
        return this->tinhTongTien() > other.tinhTongTien();
    }

    friend ostream& operator<<(ostream& os, const Ticket& t) {
        os << left << setw(8) << t.maVe
            << " | Mã CB: " << setw(10) << (t.flightPtr ? t.flightPtr->getMaCB() : "N/A")
            << " | Mã HK: " << setw(8) << (t.passengerPtr ? t.passengerPtr->getMaHK() : "N/A")
            << " | Ngày đặt: " << setw(12) << t.ngayDat
            << " | Tổng tiền: " << fixed << setprecision(0) << t.tinhTongTien() << " VNĐ";
        return os;
    }
};

// ==========================================
// 7. LỚP QUẢN LÝ CHÍNH: Airline
// ==========================================
class Airline {
private:
    string tenHang;
    vector<Flight*> dsChuyenBay;
    vector<Passenger*> dsHanhKhach;
    vector<Ticket*> dsVe;

    void docFileChuyenBay() {
        ifstream ifs("chuyenbay.txt");
        if (!ifs.is_open()) return;
        string line;
        string currentType = "";
        while (getline(ifs, line)) {
            if (line.empty()) continue;
            if (line.find("[DOMESTIC]") != string::npos) {
                currentType = "[DOMESTIC]";
                continue;
            }
            if (line.find("[INTERNATIONAL]") != string::npos) {
                currentType = "[INTERNATIONAL]";
                continue;
            }
            Flight* f = FlightFactory::tao(currentType);
            if (f) {
                stringstream ss(line);
                f->docFile(ss);
                dsChuyenBay.push_back(f);
            }
        }
        ifs.close();
    }

    void docFileHanhKhach() {
        ifstream ifs("hanhkhach.txt");
        if (!ifs.is_open()) return;
        string line;
        while (getline(ifs, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            Passenger* p = new Passenger();
            ss >> *p;
            dsHanhKhach.push_back(p);
        }
        ifs.close();
    }

    void docFileVe() {
        ifstream ifs("ve.txt");
        if (!ifs.is_open()) return;
        string line;
        while (getline(ifs, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string maVe, maCB, maHK, ngayDat;
            char ch;
            ss >> maVe >> ch >> maCB >> ch >> maHK >> ch >> ngayDat;

            Flight* fPtr = nullptr;
            for (auto f : dsChuyenBay) {
                if (f->getMaCB() == maCB) { fPtr = f; break; }
            }

            Passenger* pPtr = nullptr;
            for (auto p : dsHanhKhach) {
                if (p->getMaHK() == maHK) { pPtr = p; break; }
            }

            Ticket* t = new Ticket(maVe, fPtr, pPtr, ngayDat);
            dsVe.push_back(t);
        }
        ifs.close();
    }

    void ghiFile() {
        // Ghi chuyến bay
        ofstream ofsCB("chuyenbay.txt");
        ofsCB << "[DOMESTIC]\n";
        for (auto f : dsChuyenBay) {
            if (f->getLoai() == 1) {
                DomesticFlight* df = dynamic_cast<DomesticFlight*>(f);
                if (df) {
                    ofsCB << df->getMaCB() << " | " << df->getDiemDi() << " | " << df->getDiemDen()
                        << " | " << fixed << setprecision(0) << df->getGiaCoBan() << " | " << df->getPhuThu() << "\n";
                }
            }
        }
        ofsCB << "[INTERNATIONAL]\n";
        for (auto f : dsChuyenBay) {
            if (f->getLoai() == 2) {
                InternationalFlight* inf = dynamic_cast<InternationalFlight*>(f);
                if (inf) {
                    ofsCB << inf->getMaCB() << " | " << inf->getDiemDi() << " | " << inf->getDiemDen()
                        << " | " << fixed << setprecision(0) << inf->getGiaCoBan() << " | " << inf->getPhiQuocTe() << " | " << inf->getThueVatKhac() << "\n";
                }
            }
        }
        ofsCB.close();

        // Ghi hành khách
        ofstream ofsHK("hanhkhach.txt");
        for (auto p : dsHanhKhach) {
            ofsHK << p->getMaHK() << " | " << p->getHoTen() << " | " << p->getCCCD() << " | " << p->getSoDT() << "\n";
        }
        ofsHK.close();

        // Ghi vé
        ofstream ofsVe("ve.txt");
        for (auto t : dsVe) {
            ofsVe << t->getMaVe() << " | "
                << (t->getFlightPtr() ? t->getFlightPtr()->getMaCB() : "") << " | "
                << (t->getPassengerPtr() ? t->getPassengerPtr()->getMaHK() : "") << " | "
                << t->getNgayDat() << "\n";
        }
        ofsVe.close();
    }

public:
    Airline(string ten) : tenHang(ten) {
        docFileChuyenBay();
        docFileHanhKhach();
        docFileVe();
    }

    ~Airline() {
        ghiFile();
        for (auto f : dsChuyenBay) delete f;
        for (auto p : dsHanhKhach) delete p;
        for (auto t : dsVe) delete t;
    }

    // --- XEM DANH SÁCH ---
    void xemDanhSach() const {
        int chon;
        do {
            cout << "\n--- XEM DANH SÁCH ---\n";
            cout << "[1] Xem danh sách Chuyến bay (Nội địa & Quốc tế - Đa hình)\n";
            cout << "[2] Xem danh sách Hành khách\n";
            cout << "[3] Xem danh sách Vé máy bay (Kèm tổng tiền)\n";
            cout << "[0] Quay lại menu chính\n";
            cout << "=> Nhập lựa chọn: ";
            cin >> chon;

            switch (chon) {
            case 1:
                cout << "\n=== DANH SÁCH CHUYẾN BAY ===\n";
                for (size_t i = 0; i < dsChuyenBay.size(); ++i) {
                    cout << i + 1 << ". ";
                    dsChuyenBay[i]->xuat(cout);
                    cout << endl;
                }
                break;
            case 2:
                cout << "\n=== DANH SÁCH HÀNH KHÁCH ===\n";
                for (size_t i = 0; i < dsHanhKhach.size(); ++i) {
                    cout << i + 1 << ". ";
                    dsHanhKhach[i]->xuat();
                    cout << endl;
                }
                break;
            case 3:
                cout << "\n=== DANH SÁCH VÉ MÁY BAY ===\n";
                for (size_t i = 0; i < dsVe.size(); ++i) {
                    cout << i + 1 << ". ";
                    cout << *dsVe[i] << endl;
                }
                break;
            case 0:
                break;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
            }
        } while (chon != 0);
    }

    // --- QUẢN LÝ NGHIỆP VỤ (THÊM, SỬA, XÓA) ---
    void themChuyenBay() {
        int loai;
        cout << "Chọn loại chuyến bay (1. Nội địa, 2. Quốc tế): ";
        cin >> loai;
        Flight* f = nullptr;
        if (loai == 1) {
            f = new DomesticFlight();
            string maCB, di, den;
            double gia, phuThu;
            cout << "Nhập (MaCB DiemDi DiemDen GiaCoBan PhuThu): \n";
            cin >> maCB >> di >> den >> gia >> phuThu;
            stringstream ss;
            ss << maCB << " | " << di << " | " << den << " | " << gia << " | " << phuThu;
            f->docFile(ss);
        }
        else if (loai == 2) {
            f = new InternationalFlight();
            string maCB, di, den;
            double gia, phiQT, thue;
            cout << "Nhập (MaCB DiemDi DiemDen GiaCoBan PhiQT ThueVAT): \n";
            cin >> maCB >> di >> den >> gia >> phiQT >> thue;
            stringstream ss;
            ss << maCB << " | " << di << " | " << den << " | " << gia << " | " << phiQT << " | " << thue;
            f->docFile(ss);
        }
        else {
            cout << "Loại không hợp lệ!\n";
            return;
        }
        dsChuyenBay.push_back(f);
        cout << "Thêm chuyến bay thành công!\n";
    }

    void xoaChuyenBay() {
        string ma;
        cout << "Nhập mã chuyến bay cần xóa: ";
        cin >> ma;
        for (auto it = dsChuyenBay.begin(); it != dsChuyenBay.end(); ++it) {
            if ((*it)->getMaCB() == ma) {
                delete* it;
                dsChuyenBay.erase(it);
                cout << "Xóa chuyến bay thành công!\n";
                return;
            }
        }
        cout << "Không tìm thấy mã chuyến bay!\n";
    }

    void themVe() {
        string maVe, maCB, maHK, ngay;
        cout << "Nhập mã vé mới: "; cin >> maVe;
        cout << "Nhập mã chuyến bay: "; cin >> maCB;
        cout << "Nhập mã hành khách: "; cin >> maHK;
        cout << "Nhập ngày đặt (dd/mm/yyyy): "; cin >> ngay;

        Flight* fPtr = nullptr;
        for (auto f : dsChuyenBay) if (f->getMaCB() == maCB) { fPtr = f; break; }
        if (!fPtr) { cout << "Không tìm thấy chuyến bay!\n"; return; }

        Passenger* pPtr = nullptr;
        for (auto p : dsHanhKhach) if (p->getMaHK() == maHK) { pPtr = p; break; }
        if (!pPtr) {
            cout << "Không tìm thấy hành khách. Vui lòng nhập thông tin hành khách mới:\n";
            pPtr = new Passenger();
            pPtr->nhap();
            dsHanhKhach.push_back(pPtr);
        }

        Ticket* t = new Ticket(maVe, fPtr, pPtr, ngay);
        dsVe.push_back(t);
        cout << "Đặt vé thành công!\n";
    }

    void xoaVe() {
        string maVe;
        cout << "Nhập mã vé cần hủy: ";
        cin >> maVe;
        for (auto it = dsVe.begin(); it != dsVe.end(); ++it) {
            if ((*it)->getMaVe() == maVe) {
                delete* it;
                dsVe.erase(it);
                cout << "Hủy vé thành công!\n";
                return;
            }
        }
        cout << "Không tìm thấy mã vé!\n";
    }

    void suaHanhKhach() {
        string maHK;
        cout << "Nhập mã hành khách cần sửa: ";
        cin >> maHK;
        for (auto p : dsHanhKhach) {
            if (p->getMaHK() == maHK) {
                string hoten, cccd, sdt;
                cout << "Nhập họ tên mới: "; cin.ignore(); getline(cin, hoten);
                cout << "Nhập CCCD mới: "; cin >> cccd;
                cout << "Nhập SĐT mới: "; cin >> sdt;
                p->setThongTin(hoten, cccd, sdt);
                cout << "Cập nhật thông tin hành khách thành công!\n";
                return;
            }
        }
        cout << "Không tìm thấy hành khách!\n";
    }

    void chinhSuaDanhSach() {
        int chon;
        do {
            cout << "\n--- CHỈNH SỬA DANH SÁCH ---\n";
            cout << "[1] Quản lý Chuyến bay (Thêm mới, Xóa)\n";
            cout << "[2] Quản lý Vé (Đặt vé mới, Hủy vé)\n";
            cout << "[3] Cập nhật thông tin Hành khách\n";
            cout << "[0] Quay lại menu chính\n";
            cout << "=> Nhập lựa chọn: ";
            cin >> chon;

            switch (chon) {
            case 1: {
                int subChoice;
                cout << "1. Thêm chuyến bay\n2. Xóa chuyến bay\nChọn: ";
                cin >> subChoice;
                if (subChoice == 1) themChuyenBay();
                else if (subChoice == 2) xoaChuyenBay();
                break;
            }
            case 2: {
                int subChoice;
                cout << "1. Đặt vé mới\n2. Hủy vé\nChọn: ";
                cin >> subChoice;
                if (subChoice == 1) themVe();
                else if (subChoice == 2) xoaVe();
                break;
            }
            case 3:
                suaHanhKhach();
                break;
            case 0:
                break;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
            }
        } while (chon != 0);
    }

    // --- THỐNG KÊ & BÁO CÁO ---
    void thongke() const {
        int chon;
        do {
            cout << "\n--- THỐNG KÊ & BÁO CÁO ---\n";
            cout << "[1] Thống kê tổng doanh thu của hãng\n";
            cout << "[2] Sắp xếp danh sách chuyến bay theo giá tiền\n";
            cout << "[3] Thống kê số lượng vé theo từng chuyến bay\n";
            cout << "[0] Quay lại menu chính\n";
            cout << "=> Nhập lựa chọn: ";
            cin >> chon;

            switch (chon) {
            case 1: {
                double tongDoanhThu = 0;
                for (auto t : dsVe) {
                    tongDoanhThu += t->tinhTongTien();
                }
                cout << "\n=> Tổng doanh thu hiện tại của hãng: " << fixed << setprecision(0) << tongDoanhThu << " VNĐ\n";
                break;
            }
            case 2: {
                vector<Flight*> temp = dsChuyenBay;
                sort(temp.begin(), temp.end(), [](Flight* a, Flight* b) {
                    return a->tinhGiaVe() < b->tinhGiaVe();
                    });
                cout << "\n=== DANH SÁCH CHUYẾN BAY SẮP XẾP THEO GIÁ VÉ TĂNG DẦN ===\n";
                for (auto f : temp) {
                    f->xuat(cout);
                    cout << endl;
                }
                break;
            }
            case 3: {
                cout << "\n=== THỐNG KÊ SỐ LƯỢNG VÉ THEO CHUYẾN BAY ===\n";
                for (auto f : dsChuyenBay) {
                    int count = 0;
                    for (auto t : dsVe) {
                        if (t->getFlightPtr() && t->getFlightPtr()->getMaCB() == f->getMaCB()) {
                            count++;
                        }
                    }
                    cout << "Chuyến bay: " << left << setw(10) << f->getMaCB()
                        << " | Số lượng vé đã đặt: " << count << endl;
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
            }
        } while (chon != 0);
    }
};

// ==========================================
// 8. HÀM MAIN - MÀN HÌNH CHÍNH
// ==========================================
int main() {
    // Thiết lập bảng mã UTF-8 chuẩn (65001) cho cả xuất và nhập trên Windows Console
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Airline vietnamAirlines("Vietnam Airlines");
    int luaChon;

    do {
        cout << "\n========================================================\n";
        cout << "   PHẦN MỀM QUẢN LÝ VÉ MÁY BAY - AIRLINE SYSTEM\n";
        cout << "========================================================\n";
        cout << "[1] Xem danh sách (Chuyến bay, Hành khách, Vé)\n";
        cout << "[2] Chỉnh sửa danh sách (Thêm, Sửa, Xóa)\n";
        cout << "[3] Thống kê (Doanh thu, Sắp xếp, Lọc)\n";
        cout << "[0] Thoát chương trình (Tự động lưu dữ liệu vào file)\n";
        cout << "========================================================\n";
        cout << "=> Nhập lựa chọn của bạn (0-3): ";
        cin >> luaChon;

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
        case 0:
            cout << "\nĐang lưu dữ liệu vào file... Tạm biệt!\n";
            break;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại từ 0 đến 3!\n";
        }
    } while (luaChon != 0);

    return 0;
}