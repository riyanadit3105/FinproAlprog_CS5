#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype> 

using namespace std;


//	ADD_LOG <RFID> <IN/OUT> (TIMESTAMP) 
//   	SEARCH_LOG <ID/RFID/NAME>
//   	GET_SHORTING_LOGS <LOCAL/GLOBAL> (id)
//  	EXPORT_JSON <LOCAL/GLOBAL> (id)
//   	EXPORT_BINER <LOCAL/GLOBAL> (id)
//   	SHUTDOWN
   		
class Log{
	private:
		string RFID;
		string action;
		string code;
		string time;
		
	public:
		Log(string param){
			
 			stringstream ss(param);
 			getline(ss, RFID,' ');
 			getline(ss, action,' ');
 			getline(ss, code,' ');
 			getline(ss, time,' ');
		}
		
		string getRFID() const { return RFID; }
    	string getAction() const { return action; }
    	string getCode() const { return code; }
    	string getTime() const { return time; }
    	
    	string toString() const {
        return "RFID: " + RFID + ", Action: " + action + ", Code: "+ code +", Time: " + time;
    	}
};

//class User{
//	private:
//		string name;
//		string ID;
//		string RFID;
//		
//	public:
//		User(string n,string m, string o){
//			name = n;
//			ID = m;
//			RFID = o;
//		}
//		
//		string getName() const{ return name; }
//		string getRFID() const{ return RFID; }
//		string getID() const{ return ID; }
//};

vector<Log> logs;
//vector<User> datas;


void insertionSort(std::vector<Log>& listLog) {
    int n = listLog.size();
    for (int i = 1; i < n; i++) {
        Log key = listLog[i];
        int j = i - 1;
        while (j >= 0 && listLog[j].getTime() > key.getTime()) {
            listLog[j + 1] = listLog[j];
            j--;
        }
        listLog[j + 1] = key;
    }
}

string getCurrentTime() {
    time_t now = time(0); // ambil waktu sekarang dalam format epoch (detik)
    tm* localTime = localtime(&now); // ubah jadi struct waktu lokal
    
    stringstream ss;
    ss << put_time(localTime, "%Y-%m-%d->%H:%M:%S"); // format waktu jadi string
    return ss.str();
    
}


string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

string addLog(string param){
	string message;
	
	Log newLog(param);
	logs.push_back(newLog);
	
	message = "Add log berhasil -> " + newLog.toString() +"\n";
 	return message;
}

string listLogs(string param){
	string type,code,message = "";
 	stringstream ss(param);
 	getline(ss, type,' ');
 	getline(ss, code,' ');
 	
 	vector<Log> temp = logs;
 	
 	insertionSort(temp);
 	
 	
 	if(type == "LOCAL"){
// 		message += "Logs local dengan Code(" + .getCode() + "):\n";
 		for(const auto& log:temp){
 			if(log.getCode() == code){
 				message += log.getRFID() + " " + log.getAction() + " " + log.getTime() + "\n";
		 	}
		}
	}else if(type == "GLOBAL"){
		message += "Logs global:\n";
		for(const auto& log:temp){
			message += log.getRFID() + " " + log.getAction() + " " + log.getCode() + " " + log.getTime() + "\n";
		}
	}else{
		message = "Paramater hanya LOCAL/GLOBAL\n";
	}
	
	if (message.empty()) {
        message = "Tidak ada log.\n";
    }
 	
 	return message;
}

string searchLogs(string param){
	string key, message;
	
	stringstream ss(param);
	getline(ss,key,' ');
	
	message = "List Log dengan RFID: "+key+"\n";
	
	for(const auto& log:logs){
		if(log.getRFID() == key){
			message += log.getAction() + " " + log.getCode() + " " + log.getTime() + "\n";
		}
	}
	
	if(message == ("List Log dengan RFID: "+key+"\n")){
		message = "Tidak Ada Log.\n";
	}
	return message;
}

string exportJSON(string param){
	string type,message;
 	stringstream ss(param);
	getline(ss, type,' ');
	
	return message;
}

string exportBiner(string param){
	string type,message;
 	stringstream ss(param);
	getline(ss, type,' ');
	
	return message;
}

string help() {
    string message;
	message = "List Request:\n\n"
			"- ADD_LOG <RFID> <IN/OUT> (TIMESTAMP)      -> menambah log baru\n"
			"- SEARCH_LOG <ID/RFID/NAME>                -> menampilkan list log berdasarkan ID/RFID/Name\n"
			"- LIST_LOGS <LOCAL/GLOBAL> (id)            -> menampilkan list log Lokal/Global berdasarkan waktu\n"
			"- EXPORT_JSON <LOCAL/GLOBAL> (id)          -> menyimpan data log Lokal/Global ke file JSON\n"
    		"- EXPORT_BINER <LOCAL/GLOBAL> (id)         -> menyimpan data log Lokal/Global ke file Biner\n"
    		"- HELP                                     -> menampilkan list Request\n"
    		"- SHUTDOWN                                 -> mengakhiri program\n";

    return message;
}



string processRequest(string recvMessage){
	string request, param,sendMessage;
	
	stringstream ss(recvMessage);
    getline(ss,request,' ');
    getline(ss,param);
    
    if(request == "ADD_LOG"){
    	sendMessage = addLog(param);
	}else if(request == "LIST_LOGS"){
		sendMessage = listLogs(param);
	}else if(request == "SEARCH_LOG"){
		sendMessage = searchLogs(param);
	}else if(request == "EXPORT_JSON"){
		sendMessage = exportJSON(param);
	}else if(request == "EXPORT_BINER"){
		sendMessage = exportBiner(param);
	}else if(request == "HELP"){
		sendMessage = help();
	}else if(request == "SHUTDOWN"){
		sendMessage = "Terimkaish program telah selesai";
	}else{
		sendMessage = "Request tidak terdaftar\n";
	}
    
    return sendMessage;
}
	
int main() {
    string messageSend, code = "K309";
    
    while(1){
    	cout << "\nRequest: ";
   		getline(cin, messageSend);
   		
   		messageSend = toUpper(messageSend);
   		
   		string temp;
   		
   		stringstream ss(messageSend);
   		getline(ss,temp,' ');
   		
   		if(temp == "ADD_LOG"){
   			messageSend += " " + code + " " + getCurrentTime();
		}else if( temp == "GET_SHORTING_LOGS" || temp == "EXPORT_JSON" || temp == "EXPORT_BINER"){
			messageSend += " " + code;
		}
   		
   		//cout<<messageSend<<endl;
   		cout<<endl;
   		
    	if(messageSend == "SHUTDOWN"){
    		break;
		}
    	
    	cout<<processRequest(messageSend);
	}

    return 0;
}
