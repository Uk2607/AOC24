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

map<string,ll>mp;

ull match(string s, vector<string>&pattern) {
    if(mp[s]) return mp[s];
    if(s.length()==0) return 1;
    ull flag = 0;
    for(string p: pattern) {
        int x = s.length(), y = p.length();
        if(x>=y && s.substr(0, y) == p) {
            flag += match(s.substr(y), pattern);
        }
    }
    return mp[s] = flag;
}

void solve(vector<string>pattern, vector<string>designs) {
    int res1 = 0;
    ll res2 = 0;
    for(string design: designs) {
        ull x = match(design, pattern);
        if(x!=0LL) ++res1;
        res2 += x;
    }
    cout<<"PART1: "<<res1<<"\n";
    cout<<"PART2: "<<res2<<"\n";
}

// TODO merge two functions
int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "19");
    pair<vector<string>, vector<string>>p  = get_input("input/"+file_name+".in");
    solve(p.first, p.second); // 342 & 891192814474630
}
