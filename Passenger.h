#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>

// 5. Lớp hành khách: Passenger (Bài 3 & 4)
class Passenger {
private:
    std::string maHK;
    std::string hoTen;
    std::string cccd;
    std::string soDT;

public:
    std::string getMaHK() const;
    std::string getHoTen() const;
    std::string getCCCD() const;
    std::string getSoDT() const;

    void setThongTin(const std::string& hoten, const std::string& cccdMoi, const std::string& sdt);
    static void inTieuDe(std::ostream& os);
    void nhap(const std::string& maCoSan = "");

    bool operator>(const Passenger& other) const;

    friend std::istream& operator>>(std::istream& is, Passenger& p);
    friend std::ostream& operator<<(std::ostream& os, const Passenger& p);
};

#endif
