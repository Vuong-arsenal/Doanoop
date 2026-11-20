#include "Ticket.h"

#include <iomanip>

Ticket::Ticket(const std::string& mv, Flight* f, Passenger* p, const std::string& nd)
    : maVe{mv}, flightPtr{f}, passengerPtr{p}, ngayDat{nd} {}

std::string Ticket::getMaVe() const { return maVe; }
Flight* Ticket::getFlightPtr() const { return flightPtr; }
Passenger* Ticket::getPassengerPtr() const { return passengerPtr; }
std::string Ticket::getNgayDat() const { return ngayDat; }

void Ticket::setFlight(Flight* f) { flightPtr = f; }
void Ticket::setPassenger(Passenger* p) { passengerPtr = p; }
void Ticket::setNgayDat(const std::string& nd) { ngayDat = nd; }

double Ticket::tinhTongTien() const {
    if (flightPtr != nullptr) {
        return flightPtr->tinhGiaVe();
    }
    return 0.0;
}

void Ticket::inTieuDe(std::ostream& os) {
    os << std::left
       << std::setw(8) << "Ma ve" << " | "
       << std::setw(14) << "Ma chuyen bay" << " | "
       << std::setw(14) << "Ma hanh khach" << " | "
       << std::setw(12) << "Ngay dat" << " | "
       << "Tong tien";
}

bool Ticket::operator>(const Ticket& other) const {
    return this->tinhTongTien() > other.tinhTongTien();
}

std::ostream& operator<<(std::ostream& os, const Ticket& t) {
    os << std::left
       << std::setw(8) << t.maVe << " | "
       << std::setw(14) << (t.flightPtr ? t.flightPtr->getMaCB() : "N/A") << " | "
       << std::setw(14) << (t.passengerPtr ? t.passengerPtr->getMaHK() : "N/A") << " | "
       << std::setw(12) << t.ngayDat << " | "
       << std::fixed << std::setprecision(0) << t.tinhTongTien();
    return os;
}
