#ifndef TICKET_H
#define TICKET_H

#include "Flight.h"
#include "Passenger.h"

#include <iostream>
#include <string>

// 6. Lớp vé máy bay: Ticket (Aggregation - Bài 5)
class Ticket {
private:
    std::string maVe;
    Flight* flightPtr{nullptr};       // Tham chiếu quan sát (không sở hữu)
    Passenger* passengerPtr{nullptr}; // Tham chiếu quan sát (không sở hữu)
    std::string ngayDat;

public:
    Ticket() = default;
    Ticket(const std::string& mv, Flight* f, Passenger* p, const std::string& nd);

    std::string getMaVe() const;
    Flight* getFlightPtr() const;
    Passenger* getPassengerPtr() const;
    std::string getNgayDat() const;

    void setFlight(Flight* f);
    void setPassenger(Passenger* p);
    void setNgayDat(const std::string& nd);

    double tinhTongTien() const;
    static void inTieuDe(std::ostream& os);

    bool operator>(const Ticket& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Ticket& t);
};

#endif
