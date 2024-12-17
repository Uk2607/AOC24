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

ll A, B, C;
vector<int>program;

vector<int> get_input(string file_path) {
    string line;
    vector<int>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    bool flag = false;
    int idx = 0;
    while(getline(file, line)) {
        if(line.length()==0) {
            flag = true;
            continue;
        }
        if(!flag) {
            string s;
            ll x;
            stringstream ss(line);
            ss>>s>>s>>x;
            if(idx == 0) A = x;
            if(idx == 1) B = x;
            if(idx == 2) C = x;
            idx++;
        } else {
            string lst;
            stringstream ss(line);
            ss>>lst>>lst;
            for(int i=0;i<lst.length();i+=2)
                arr.push_back(lst[i]-'0');
        }
    }
    file.close();

    return arr;
}

void print(vector<int>&arr) {
    cout<<"\n";
    cout<<"A: "<<A<<"\n"<<"B: "<<B<<"\n"<<"C: "<<C<<"\n";
    for(int x: arr) cout<<x<<" "; cout<<"\n";
    cout<<"\n";
}

void part1(vector<int>arr) {
    ll reg_a = A, reg_b = B, reg_c = C;
    cout<<"PART1: "<<arr.size()<<"\n";
}

void part2(vector<int>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "17");
    vector<int>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 
    part2(arr); // 
}
