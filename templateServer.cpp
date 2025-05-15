#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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

vector<Log> logs;

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

string addLog(string param){
	string message;
	
	Log newLog(param);
	logs.push_back(newLog);
	
	message = "Add log berhasil -> " + newLog.toString();
 	return message;
}

string getLogs(string param){
	string type,code,message = "";
 	stringstream ss(param);
 	getline(ss, type,' ');
 	getline(ss, code,' ');
 	
 	vector<Log> temp = logs;
 	
 	insertionSort(temp);
 	
 	
 	if(type == "LOCAL"){
 		message += "Logs local dengan Code(" + log.getCode() + "):\n";
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


string processRequest(string recvMessage){
	string request, param,sednMessage;
	
	stringstream ss(recvMessage);
    getline(ss,request,' ');
    getline(ss,param);
    
    if(request == "ADD_LOG"){
    	sendMessage = addLogs(param);
	}else if(request == "GET_SHORTING_LOGS"){
		sendMessage = addLogs(param);
	}else if(request == "SEARCH_LOG"){
		sendMessage = addLogs(param);
	}else if(request == "EXPORT_JSON"){
		sendMessage = addLogs(param);
	}else if(request == "EXPORT_BINER"){
		sendMessage = addLogs(param);
	}else if(request == "SHUTDOWN"){
		sendMessage = addLogs(param);
	}else{
		sendMessage = addLogs(param);
	}
    
    return sendMessage;
}

int main() {
    string messageSend;
    
    
    while(1){
    
    	cout << "Pesan dari server: " << messageRecv <<endl;
    
    	string message = processRequest(storage,messageRecv);
    
    	send(client_socket, message.c_str(), message.length(), 0);
    	
    	if(message == "program telah selesai, menutup server....."){
    		break;
		}
	}

    return 0;
}
