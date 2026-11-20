#ifndef AIRLINE_H
#define AIRLINE_H

#include "Flight.h"
#include "Passenger.h"
#include "Ticket.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 7. Lớp quản lý chính: Airline (RAII với unique_ptr - Bài 3)
class Airline {
private:
    std::string tenHang;
    std::vector<std::unique_ptr<Flight>> dsChuyenBay;
    std::vector<std::unique_ptr<Passenger>> dsHanhKhach;
    std::vector<std::unique_ptr<Ticket>> dsVe;

    Flight* timChuyenBay(const std::string& maCB) const;
    Passenger* timHanhKhach(const std::string& maHK) const;
    Ticket* timVe(const std::string& maVe) const;

    void docFileChuyenBay();
    void docFileHanhKhach();
    void docFileVe();

    void xuatChuyenBay(std::ostream& os) const;
    void xuatHanhKhach(std::ostream& os) const;
    void xuatVe(std::ostream& os) const;
    void ghiFile() const;

public:
    explicit Airline(const std::string& ten);
    ~Airline();

    void xemDanhSach() const;

    void themChuyenBay();
    void suaChuyenBay();
    void xoaChuyenBay();

    void themVe();
    void suaVe();
    void xoaVe();

    void suaHanhKhach();
    void chinhSuaDanhSach();

    void timKiem() const;
    void locChuyenBay() const;
    void thongke() const;
};

#endif
