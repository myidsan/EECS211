#include "system.h"
#include "machines.h"

#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

System::System()
        : tick_(0) {}

void System::format(std::ostream& os, const vector<IP_address>& ips0) const
{
    vector<IP_address> ips = ips0;
    if (ips.empty()) {
        for (size_t i = 0; i < network_.size(); ++i)
            if (network_[i] != nullptr)
                ips.push_back(network_[i]->get_ip());
    }
    os << "system {\n  tick = " << tick_ << ",\n";
    for (IP_address& ip : ips) {
        os << "  ";
        os << ip;
        os << " = ";
        int idx = -1;
        for (int i = 0; i < MAX_MACHINES; ++i) {
            if (network_[i]->get_ip() == ip) {
                idx = i;
                break;
            }
        }
        if (idx < 0)
            throw err_code::no_such_machine;
        os << *network_[idx];
        os << '\n';
    }
    os << "}\n";
}


///
/// \param type
/// \param name
/// \param ip
/// \return creates machine node in the system
///
void System::create_machine(const string& type, const string& name, const IP_address& ip)
{
    if (type != "laptop" &&  type != "server" && type != "wan" ) {
        throw err_code::unknown_machine_type;
    }

    if (tick_ >= MAX_MACHINES) {
        throw err_code::network_full;
    } else {
        for (int i = 0; i <= MAX_MACHINES; i++) {
            if (network_[i] == nullptr) {
                network_[i] = make_shared<Node>(name, ip);
                tick_++;
                break;
            }
        }
    }



    cout << "System::create_machine: " << type << ' ' << name << ' ';
    cout << ip;
    cout << '\n';
}

///
/// \param ip
/// \return deletes machine node in the system
///
void System::delete_machine(const IP_address& ip)
{
    bool exists1 =  false;
    shared_ptr<Node> machine1;

    for (int i = 0; i < tick_; i++) {
        if (network_[i] == nullptr) {
            continue;
        } else if (network_[i]->get_ip() == ip) {
            exists1 = true;
            machine1 = (network_[i]);
            break;
        }
    }

    if (!exists1) {
        throw err_code::no_such_machine;
    } else {
        for (int i = 0; i < tick_; i++) {
            network_[i]->disconnect(machine1);
        }
        machine1 = nullptr;
        tick_--;
    }


    cout << "System::delete_machine: ";
    cout << ip;
    cout << '\n';
}

///
/// \param ip1
/// \param ip2
/// \return connects two different machines in the same system
void System::connect_machine(const IP_address& ip1, const IP_address& ip2)
{
    bool exists1 =  false;
    bool exists2 =  false;
    shared_ptr<Node> machine1;
    shared_ptr<Node> machine2;


    for (int i = 0; i < tick_; i++) {
        if (network_[i]->get_ip() == ip1) {
            exists1 = true;
            machine1 = (network_[i]);
            break;
        }
    }

    for (int j = 0; j < tick_; j++) {
        if (network_[j]->get_ip() == ip2) {
            exists2 = true;
            machine2 = (network_[j]);
            break;
        }
    }

    if (!exists1 || !exists2) {
        throw err_code::no_such_machine;
    } else {
        for (int i = 0; i < tick_; i++) {
            machine1->connect(machine2);
            machine2->connect(machine1);
        }
    }

    cout << "System::connect_machine: ";
    cout << ip1;
    cout << ", ";
    cout << ip2;
    cout << '\n';
}

void System::allocate_datagram(const IP_address& ip1, const IP_address& ip2, const string& message)
{
    cout << "System::allocate_datagram: ";
    cout << ip1;
    cout << ", ";
    cout << ip2;
    cout << ", \"" << message << "\"\n";
}

void System::release_datagram(const IP_address& ip)
{
    cout << "System::release_datagram: ";
    cout << ip;
    cout << '\n';
}

void System::time_click()
{
    ++tick_;
    cout << "System::time_click\n";
}

std::ostream& operator<<(std::ostream& os, const System& sys)
{
    sys.format(os, {});
    return os;
}
