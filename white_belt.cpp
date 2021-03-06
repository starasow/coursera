#include <iostream>
#include <iomanip>
#include <cassert>
#include <map>
#include <string>
#include <set>
#include <cmath>
#include <vector>
#include <stdexcept>

using namespace std;

// g++ -O2 white_belt.cpp -o white_belt
// g++ -std=c++17 -O2 white_belt.cpp -o white_belt
vector<string> split_date(const string& i_str, const string& i_delim){
    vector<string> result;
    
    size_t found = i_str.find(i_delim);
    size_t startIndex = 0;

    while(found != string::npos){
		if(string(i_str.begin() + startIndex, i_str.begin()+found).size() < sizeof(char)){
			found += 2;
		}		
		result.push_back(string(i_str.begin()+startIndex, i_str.begin()+found));
		startIndex = found + i_delim.size();
		found = i_str.find(i_delim, startIndex);
    }
    if(startIndex != i_str.size())
        result.push_back(string(i_str.begin()+startIndex, i_str.end()));
    return result;      
}

vector<string> split(const string& i_str, const string& i_delim){
    vector<string> result;
    
    size_t found = i_str.find(i_delim);
    size_t startIndex = 0;

    while(found != string::npos){
        result.push_back(string(i_str.begin()+startIndex, i_str.begin()+found));
        startIndex = found + i_delim.size();
        found = i_str.find(i_delim, startIndex);
    }
    if(startIndex != i_str.size())
        result.push_back(string(i_str.begin()+startIndex, i_str.end()));
    return result;      
}

void PrintSet(const set<string>& v){
    for (const auto& s : v){cout << s << endl;}
    return;
}

void PrintVector(const vector<string>& v){
    for (const auto& s : v){cout << s << endl;}
    return;
}


class Date {
public:
    Date() {Year = 0; Month = 0; Day = 0;}
	explicit Date (string Y, string M, string D) {
		Year = stoi(Y); Month = stoi(M); Day = stoi(D);
		if (Month > 12 || Month < 1) {throw "Month value is invalid: " + to_string(Month);}
		else if (Day > 31 || Day < 1) {throw "Day value is invalid: " + to_string(Day);}
	}
    int GetYear() const { return Year; };
    int GetMonth() const { return Month; };
    int GetDay() const { return Day; };
private:
	int Year;
	int Month;
	int Day;
};

bool operator<(const Date& lhs, const Date& rhs){
	if (lhs.GetYear() != rhs.GetYear()) { return lhs.GetYear() < rhs.GetYear(); }
	else if (lhs.GetMonth() != rhs.GetMonth()) { return lhs.GetMonth() < rhs.GetMonth(); }
	else { return lhs.GetDay() < rhs.GetDay(); }
}

bool operator<=(const Date& lhs, const Date& rhs){
	if (lhs.GetYear() != rhs.GetYear()) { return lhs.GetYear() < rhs.GetYear(); }
	else if (lhs.GetMonth() != rhs.GetMonth()) { return lhs.GetMonth() < rhs.GetMonth(); }
	else { return lhs.GetDay() <= rhs.GetDay(); }
}

class Database {
public:
    Database() { map <class Date, set<string>> date_to_events; }	
    
	void AddEvent(const Date& date, const string& event) {
		date_to_events[date].insert(event);
	}
	
    bool DeleteEvent(const Date& date, const string& event) {
		if (date_to_events.count(date) > 0 && date_to_events.at(date).count(event) > 0) {
			date_to_events.at(date).erase(event); 
			cout << "Deleted successfully" << endl;
			return true;
		}
		cout <<"Event not found"<< endl;
		return false;
    }
	
    int DeleteDate(const Date& date){
		int init_size = date_to_events.count(date);
		date_to_events.at(date).clear();
		return init_size;
	}

    void Find(const Date& date) const {
		PrintSet(date_to_events.at(date));
	}
  
    void Print() const {
		cout << setfill('0');		
		for (auto const& x : date_to_events) {
		    if (x.second.size() > 0){
				cout <<setw(4)<< x.first.GetYear() << '-' <<setw(2)<< x.first.GetMonth() << '-' <<setw(2)<< x.first.GetDay()<<' ';
				PrintSet(x.second);
			}
		}
	}
	
private:
	map <class Date, set<string>> date_to_events;
};

int main() {
  Database db;
  vector<string> parsed_command;
  vector<string> parsed_date;
  string command;
  
  while (getline(cin, command, '\n')) {
	  //if (command == to_string('\n')) {continue;}
	  if (command.size() == 0){              /* if .size() == 0, empty line */
	      continue; 
	  }   
	  parsed_command = split(command, " ");
	  /*
	  parsed_command is a vector of {"command", "Date", "event"} 
	  */
	  //PrintVector(parsed_command);
	  if (parsed_command[0] == "Print"){
		   db.Print();
	  } else if (parsed_command[0] == "Add" || parsed_command[0] == "Del" || parsed_command[0] == "Find"){
		try {
			parsed_date = split_date(parsed_command[1], "-");
			cout << "****" << parsed_date.size() << endl;
			PrintVector(parsed_date);
			cout << "****" << parsed_date.size() << endl;
			Date date = Date (parsed_date[0], parsed_date[1], parsed_date[2]);
			if (parsed_command[0] == "Add") {db.AddEvent(date, parsed_command[2]);} 
			else if (parsed_command[0] == "Del" && parsed_command.size() > 2) {
			//cout << "Deleting particular event:" << parsed_command[2] << " <-- this is the event" << endl;
			db.DeleteEvent(date, parsed_command[2]);
			} else if (parsed_command[0] == "Del" && parsed_command.size() == 2) {
		    //cout << "Deleting whole date" << endl;
		    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
	        } else if (parsed_command[0] == "Find") {db.Find(date);}
		} catch (const string &str) {
			cout << str;
		} catch (...) {
			cout << "Wrong date format: " << parsed_command[1];
		}	
	  } else {cout << "Unknown command: " << parsed_command[0];} 
  }	
  // ???????????????? ?????????????? ?? ???????????? ?????????? ?? ?????????????????????? ????????????
  return 0;
}