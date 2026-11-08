#include <bits/stdc++.h>
using namespace std;
class Passenger {
private:
    string PassengerID;
    string fullName;
    string phone;
    string email;
    string citizenID;
public:
    Passenger (){
        PassengerID = "";
        fullName = "";
        phone = "";
        email = "";
        citizenID = "";
    }
    void displayInfo () const {
        cout << "Ma hanh khach: " << PassengerID << endl;
        cout << "Ho va ten: " << fullName << endl;
        cout << "So dien thoai: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "CCCD: " << citizenID << endl;
    }
    bool operator == (const Passenger &other){
        if (PassengerID == other.PassengerID && fullName == other.fullName && phone == other.phone && email == other.email && citizenID == other.citizenID){
            return 1;
        }
        else return 0;
    }
    string getPassengerID () const {
        return PassengerID;
    }
    Passenger* getPassenger (){
        return passenger;
    }
 };
class PassengerManager {
private:
     vector <Passenger*> Passengers;
public:
    void addPassenger (Passenger *p){
        if ( p == NULL){
            return;
        }
        Passengers.push_back(p);
    }
    bool removePassenger (string id) {
        for (int i = 0; i < Passengers.size(); i++){
            if (id == Passengers[i]->getPassengerID()){
                delete Passengers[i];
                Passengers.erase(Passengers.begin() + i);
                return 1;
            }
        }
        return 0;
    }
    bool updatePassenger (string id){
        for (int i = 0; i < Passengers.size(); i++){
            if (id == Passengers[i]->getPassengerID()){
                Passengers[i]->input() // them phuong thuc input trong lop Passenger
                return 1;
            }
        }
        return 0;
    }
    Passenger* findPassenger (string id){
        for (int i = 0; i < Passengers.size(); i++){
            if (id == Passengers[i]->getPassengerID()){
                return Passengers[i];
            }
        }
        return NULL;
    }
    void displayPassengers () {
        for (int i = 0; i < Passengers.size(); i ++){
            cout << "Thong tin hanh khach thu " << i+1 << " :" << endl;
            Passengers[i]->displayInfo();
        }
    }

 };
 class TicketManager {
 private:
     vector <Ticket*> tickets;
 public:
    void addTicket (Ticket *t){
        if (t == NULL){
            return;
        }
        tickets.push_back(t);
    }
    bool removeTicket (string id){
        for (int i = 0; i < tickets.size(); i++){
            if (id == tickets[i]->getTicketID){
                delete tickets[i];
                tickets.erase(tickets.begin() + i);
                return 1;
            }
        }
        return 0;
    }
    bool updateTicket (string id){
        for (int i = 0; i < tickets.size(); i++){
            if (id == tickets[i]->getTicketID){
                ticket[i]->input(); // them phuong thuc input trong lop ticket
                return 1;
            }
        }
        return 0;
    }
    ticket* findTicket (string id){
        for (int i = 0; i < tickets.size(); i++){
            if (id == tickets[i]->getTicketID){
                return tickets[i];
            }
        }
        return NULL;
    }
    void findByPassenger (string PassengerID){
        vector <Ticket*> results;
        for (int i = 0; i< tickets.size(); i++){
            if (PassengerID == tickets[i]->getPassenger->getPassengerID){
                results.push_back(tickets[i]);
            }
        }
        return results;
    }
    double revenueByArline (){
        double total = 0;
        for (int i = 0; i < tickets.size(); i++){
            total += tickets[i]->getFialPrice();
        }
        return total;
    }


 };
 int main (){
     return 0;

 }
