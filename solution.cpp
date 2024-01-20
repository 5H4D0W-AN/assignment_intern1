#include<bits/stdc++.h>
using namespace std;

int find_time(string& s){
	int h = 10*(s[11]-'0') + s[12]-'0'; // hour of day
	int min = 10*(s[14]-'0') + s[15]-'0'; // minutes
	if(s[17] == 'P') h+=12; // AM or PM
	return h*60+min;
}
int find_time2(string& s){
	int l = s.size();
	if(l <= 4) return 0;
	if(s[1] <= '3') return 0; // of type 10, 11, 12, 13:XX so less than 14 hours
	return 14; // >=14
}



void individual(vector<bool>& a, vector<bool>&b, vector<bool>&c,
	vector<pair<string, string>>& ids){
	int n = a.size();
	ofstream fa("IA.txt");
	if(!fa.is_open()){
		cerr << "Error while opening file!\n";
		return;
	}
	fa <<"Name----------------------------------------Position"<<endl<<endl;
	for(int i=0; i<n; i++){
		if(a[i]){
			string s = "";
			for(int j=0; j<44-ids[i].second.size(); j++) s+='-';
			fa<< ids[i].second << s<<  ids[i].first << endl;
		}
	}
	fa.close();

	ofstream fb("IB.txt");
	if(!fb.is_open()){
		cerr << "Error while opening file!\n";
		return;
	}
	fb << "Name----------------------------------------Position"<<endl<<endl;
	for(int i=0; i<n; i++){
		if(b[i]){
			string s = "";
			for(int j=0; j<44-ids[i].second.size(); j++) s+='-';
			fb << ids[i].second << s<<  ids[i].first << endl;
		}
	}
	fb.close();

	ofstream fc("IC.txt");
	if(!fc.is_open()){
		cerr << "Error while opening file!\n";
		return;
	}
	fc << "Name----------------------------------------Position"<<endl<<endl;
	for(int i=0; i<n; i++){
		if(c[i]){
			string s = "";
			for(int j=0; j<44-ids[i].second.size(); j++) s+='-';
			fc << ids[i].second << s<<  ids[i].first << endl;
		}
	}
	fc.close();
}


void or_logic(vector<bool>& a, vector<bool>&b, vector<bool>&c,
	vector<pair<string, string>>& ids){
	int n = a.size();
	ofstream o("O.txt");
	if(!o.is_open()){
		cerr << "Error while opening file!\n";
		return;
	}
	o << "Name----------------------------------------Position"<<endl<<endl;
	for(int i=0; i<n; i++){
		if(a[i] || b[i] || c[i]){
			string s = "";
			for(int j=0; j<44-ids[i].second.size(); j++) s+='-';
			o << ids[i].second << s<<  ids[i].first << endl;
		}
	}
	o.close();
}

void and_logic(vector<bool>& a, vector<bool>&b, vector<bool>&c,
	vector<pair<string, string>>& ids){
	int n = a.size();
	ofstream aa("A.txt");
	if(!aa.is_open()){
		cerr << "Error while opening file!\n";
		return;
	}
	aa << "Name----------------------------------------Position"<<endl<<endl;
	for(int i=0; i<n; i++){
		if(a[i] & b[i] & c[i]){
			string s = "";
			for(int j=0; j<44-ids[i].second.size(); j++) s+='-';
			aa<< ids[i].second << s<<  ids[i].first << endl;
		}
	}
	aa.close();
}


int main(){
	ios::sync_with_stdio(0); // for faster input and output
	cin.tie(0); 
	cout.tie(0);

	// storing every file in vector of strings
	vector<string> Names, In_Time, Out_Time, Shift_Time, Position;


	//FILE : names
	//open file 
	ifstream fn("names.txt");
	if(!fn.is_open()){
		cerr << "Error while opening file names.txt\n";
		return 1;
	}
	// take input line by line in string s
	string s;
	while(getline(fn, s)){
		Names.push_back(s);// push string in vector
	}
	fn.close();

	//FILE : in_time
	ifstream fi("in_time.txt");
	if(!fi.is_open()){
		cerr << "Error while opening file in_time.txt\n";
		return 1;
	}
	while(getline(fi, s)){
		In_Time.push_back(s);
	}
	fi.close();

	//FILE : out_time
	ifstream fo("out_time.txt");
	if(!fo.is_open()){
		cerr << "Error while opening file out_time.txt\n";
		return 1;
	}
	while(getline(fo, s)){
		Out_Time.push_back(s);
	}
	fo.close();

	//FILE : shift_time
	ifstream fs("shift_time.txt");
	if(!fs.is_open()){
		cerr << "Error while opening file shift_time.txt\n";
		return 1;
	}
	while(getline(fs, s)){
		Shift_Time.push_back(s);
	}
	fs.close();

	//FILE : position
	ifstream file("position.txt");
	if(!file.is_open()){
		cerr << "Error while opening file position.txt\n";
		return 1;
	}
	while(getline(file, s)){
		Position.push_back(s);
	}
	file.close();

	// storing for every employee in map
	map<string, vector<vector<string>>> mp;
	for(int i=0; i<Names.size(); i++){
		if(Shift_Time[i] == "nan" || Shift_Time[i] == "0:00") {
			continue;											// skip if no work done
		}
		vector<string> v = {In_Time[i], Out_Time[i], Shift_Time[i], Names[i]};
		mp[Position[i]].push_back(v);
	}

	int n = mp.size(); // number of employees

	// flags for all 3 conditions
	vector<bool> a_flag(n, false), b_flag(n, false), c_flag(n, false);
	vector<pair<string, string>> ids; // storing all employee names and positions as per their index


	// for a_flag
	int i = 0;
	for(auto& x: mp){
		auto& v = x.second;
		ids.push_back({x.first, v[0][3]});
		int l = v.size();// total shifts of an employee
		set<int> dates;
		for(int j=0; j<l;j++){
			// inserting both in_date and out_date in set
			s = v[j][0];
			int d = 10*(s[3]-'0') + s[4]-'0';
			dates.insert(d);
			s = v[j][1];
			d = 10*(s[3]-'0') + s[4]-'0';
			dates.insert(d);
		}
		bool pos = false; // for keeping track of consecutive days
		int next_day = *dates.begin()+1;
		int len = 1;
		for(auto d: dates){
			if(d > next_day){
				len = 1;
				next_day = d+1;
			}else if(d == next_day){
				len++;
				next_day++;
			}
			if(len>=7) pos = true; // found a 7 day streak
		}
		if(pos == true) a_flag[i] = true;
		i++;
	}


	// for b_flag
	i=0;
	for(auto&x : mp){
		auto& v = x.second;
		int l = v.size();
		s = v[0][1];
		// we will be taking time of day as minutes i.e. out of 1440 minutes of day
		int curr_time = find_time(s);
		bool pos = false;
		for(int j = 1; j<l; j++){
			s = v[j][0];
			int next_time = find_time(s);
			if(next_time < curr_time){ //meaning next day so add 24 hours
				next_time += 1440;
			}
			int diff = next_time - curr_time;
			int mins = diff%60;
			int hours = diff/60;
			if(hours >=1 && hours < 10) pos = true;
			if(hours == 10 && mins == 0) pos = true;
		}
		if(pos == true) b_flag[i] = true;
		i++;
	}


	//for c_flag
	i=0;
	for(auto&x: mp){
		auto& v = x.second;
		int l = v.size();
		bool pos = false;
		for(int j=0; j<l; j++){
			s = v[j][2];
			int t = find_time2(s);
			if(t>=14) pos = true;
		}
		if(pos) c_flag[i] = true;
		i++;
	}

	// for individual answers to a, b, c
	individual(a_flag, b_flag, c_flag, ids);
	// using OR logic b/w a, b, c
	or_logic(a_flag, b_flag, c_flag, ids);

	// using AND login
	and_logic(a_flag, b_flag, c_flag, ids);

	return 0;
}