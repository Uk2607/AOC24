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

vector<pair<int, int>> get_input(string file_path) {
    string line;
    vector<pair<int, int>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    int idx = 0;
    while(getline(file, line)) {
        if(line.length()==0) {
            idx = 0;
            continue;
        }
        stringstream ss(line);
        string s, x, y;
        if(idx != 2) ss>>s>>s;
        else ss>>s;
        ss>>x>>y;
        arr.push_back({stoi(x.substr(2, x.length()-3)), stoi(y.substr(2))});
        idx++;
    }
    file.close();

    return arr;
}

void print(vector<pair<int, int>>&arr) {
    cout<<"\n";
    for(pair<int, int>p: arr) cout<<p.first<<" "<<p.second<<"\n";
    cout<<"\n";
}

void part1(vector<pair<int, int>>arr) {
    int n = arr.size(), res = 0;
    for(int i=0;i<n; i+=3) {
        int x = 0, y = 0;
        pair<int,int>button_a = arr[i];
        pair<int,int>button_b = arr[i+1];
        pair<int,int>prize = arr[i+2];
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<pair<int, int>>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "13");
    vector<pair<int, int>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
