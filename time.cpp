#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

std::string getCurrentTime() {
    time_t now = time(0); // ambil waktu sekarang dalam format epoch (detik)
    tm* localTime = localtime(&now); // ubah jadi struct waktu lokal
    
    cout<<now;

    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S"); // format waktu jadi string
    return ss.str();
}

int main() {
    std::string currentTime = getCurrentTime();
    std::cout << "Waktu sekarang: " << currentTime << std::endl;
}
