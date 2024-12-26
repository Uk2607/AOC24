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

vector<pair<string, string>> get_input(string file_path) {
    string line;
    vector<pair<string, string>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line))
        arr.push_back({line.substr(0, 2), line.substr(3)});
    file.close();

    return arr;
}

void print(vector<pair<string, string>>&arr) {
    cout<<"\n";
    for(auto [a, b]: arr) cout<<a<<"-"<<b<<"\n";
    cout<<"\n";
}

void part1(vector<pair<string, string>>arr) {
    map<string, set<string>>mp;
    for(auto [a, b]: arr) {
        mp[a].insert(b);
        mp[b].insert(a);
    }
    
    int res = 0;
    for(auto [a, va]: mp)
        for(string b: va)
            if(a!=b)
                for(string c: mp[b])
                    if( a<b && b<c && mp[c].find(a) != mp[c].end())
                        if(a[0]=='t' || b[0]=='t' || c[0]=='t') ++res;
    
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<pair<string, string>>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "23");
    vector<pair<string, string>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 1337
    part2(arr); // 
}
