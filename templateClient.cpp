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

string help(){
	string message =
    	"\nList Request:\n"
    	"- ADD_LOG <RFID> <IN/OUT> (TIMESTAMP) 	-> menambah log baru\n"
    	"- SEARCH_LOG <ID/RFID/NAME>		-> menampilkan list log berdasarkan ID/RFID/Name\n"
    	"- GET_SHORTING_LOGS <LOCAL/GLOBAL> (id) -> menampilkan list log Lokal/Global berdasarkan waktu\n" 
    	"- EXPORT_JSON <LOCAL/GLOBAL> (id) 	-> menyimpan data log Lokal/Global kedalam file JSON\n"
    	"- EXPORT_BINER <LOCAL/GLOBAL> (id)  	-> menyimpan data log Lokal/Global kedalam file Biner\n"
    	"- HELP 					-> menampilkan list Request\n"
    	"- SHUTDOWN				-> mengakhiri program\n\n";
    	
	return message;
}

int main() {
    string messageSend,code = "K301";
    
    
//  ADD_LOG <RFID> <IN/OUT> <TIMESTAMP>
//  SEARCH_LOG <ID/RFID/NAME>
//  GET_SHORTING_LOGS <LOCAL/GLOBAL>
//  EXPORT_JSON <LOCAL/GLOBAL>
//  EXPORT_BINER <LOCAL/GLOBAL>
//  SHUTDOWN

cout<<help();
    
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