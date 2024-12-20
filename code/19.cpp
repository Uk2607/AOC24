#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>

#define ll long long int
#define ull unsigned long long int
using namespace std;

pair<vector<string>, vector<string>> get_input(string file_path) {
    string line;
    pair<vector<string>, vector<string>>p;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return p;
    }

    bool designStart = false;
    while(getline(file, line)) {
        if(line.length()==0) {designStart = true; continue;}
        if(!designStart) {
            line += ',';
            stringstream ss(line);
            string pattern;
            while(getline(ss, pattern, ' ')) {
                pattern.pop_back();
                p.first.push_back(pattern);
            }
        } else p.second.push_back(line);
    }
    file.close();

    return p;
}

void print(vector<string>&pattern, vector<string>&design) {
    cout<<"\n";
    for(string s: pattern) cout<<s<<" ";
    cout<<"\n";
    for(string s: design) cout<<s<<"\n";
    cout<<"\n";
}

void part1(vector<string>pattern, vector<string>design) {
    cout<<"PART1: "<<""<<"\n";
}

void part2(vector<string>pattern, vector<string>design) {
    cout<<"PART2: "<<""<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "19");
    pair<vector<string>, vector<string>>p  = get_input("input/"+file_name+".in");
    part1(p.first, p.second); // 
    part2(p.first, p.second); // 
}
