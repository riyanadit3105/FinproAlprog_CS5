#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

string getCurrentTime() {
    time_t now = time(0); // ambil waktu sekarang dalam format epoch (detik)
    tm* localTime = localtime(&now); // ubah jadi struct waktu lokal
    
    stringstream ss;
    ss << put_time(localTime, "%Y-%m-%d->%H:%M:%S"); // format waktu jadi string
    return ss.str();
}

int main() {
    string messageSend,code = K301;
    
    
//  ADD_LOG <RFID> <IN/OUT> <TIMESTAMP>
//  SEARCH_LOG <ID/RFID/NAME>
//  GET_SHORTING_LOGS <LOCAL/GLOBAL>
//  EXPORT_JSON <LOCAL/GLOBAL>
//  EXPORT_BINER <LOCAL/GLOBAL>
//  SHUTDOWN
    
    while(1){
    	cout << "Request: ";
   		getline(cin, messageSend);
   		
   		string temp;
   		
   		stringstream ss(messageSend);
   		getline(ss,temp,' ');
   		
   		if(temp == "ADD_LOG"){
   			messageSend += " " + code + " " + getCurrentTime();
		}else if( temp == "GET_SHORTING_LOGS" || temp == "EXPORT_JSON" || temp == "EXPORT_BINER"){
			messageSend += " " + code;
		}
   		
   		cout<<messageSend<<endl;
   		
    	if(messageSend == "SHUTDOWN"){
    		break;
		}
		
		cout<<"----------------------------------\n"<<endl;
	}

    cout<<"----------------------------------\n"<<endl;
    return 0;
}