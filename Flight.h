#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <memory>
#include <string>

// 1. Lớp cơ sở trừu tượng: Flight (Bài 6)
class Flight {
protected:
    std::string maCB;
    std::string diemDi;
    std::string diemDen;
    double giaCoBan{0.0};

    void suaThongTinChung();

public:
    Flight() = default;
    Flight(const std::string& ma, const std::string& di, const std::string& den, double gia);
    virtual ~Flight() = default; // Hàm hủy ảo (Bài 6)

    virtual double tinhGiaVe() const = 0;
    virtual bool docFile(std::istream& is) = 0;
    virtual void xuat(std::ostream& os) const = 0;
    virtual void suaThongTin() = 0;
    virtual int getLoai() const = 0; // 1: Nội địa, 2: Quốc tế

    std::string getMaCB() const;
    std::string getDiemDi() const;
    std::string getDiemDen() const;
    double getGiaCoBan() const;

    bool operator>(const Flight& other) const;
};

// 2. Lớp con: DomesticFlight (Bài 5 & 6)
class DomesticFlight : public Flight {
private:
    double phuThuNoiDia{0.0};

public:
    DomesticFlight() = default;
    DomesticFlight(const std::string& ma, const std::string& di, const std::string& den,
                   double gia, double phuThu);

    double getPhuThu() const;
    double tinhGiaVe() const override;
    static void inTieuDe(std::ostream& os);

    bool docFile(std::istream& is) override;
    void xuat(std::ostream& os) const override;
    void suaThongTin() override;
    int getLoai() const override;
};

// 3. Lớp con: InternationalFlight (Bài 5 & 6)
class InternationalFlight : public Flight {
private:
    double phiQuocTe{0.0};
    double thueVatKhac{0.0};

public:
    InternationalFlight() = default;
    InternationalFlight(const std::string& ma, const std::string& di, const std::string& den,
                        double gia, double phiQT, double thue);

    double getPhiQuocTe() const;
    double getThueVatKhac() const;
    double tinhGiaVe() const override;
    static void inTieuDe(std::ostream& os);

    bool docFile(std::istream& is) override;
    void xuat(std::ostream& os) const override;
    void suaThongTin() override;
    int getLoai() const override;
};

// 4. Lớp tiện ích: FlightFactory (Dùng unique_ptr - Bài 3)
class FlightFactory {
public:
    static std::unique_ptr<Flight> tao(const std::string& loaiStr);
};

#endif
