#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<assert.h>

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

int getCombo(int x, int a, int b, int c) {
    if(x>=0 && x<=3) return x;
    if(x==4) return a;
    if(x==5) return b;
    if(x==6) return c;
    assert(false);
}

string solve(vector<int>&arr, ll reg_a, ll reg_b, ll reg_c) {
    int n = arr.size(), idx = 0, cmd;
    string res;
    while(true) {
        if(idx>n) break;
        cmd = arr[idx];
        if(cmd == 0) {
            reg_a = reg_a/pow(2,getCombo(arr[idx+1], reg_a, reg_b, reg_c));
            idx+=2;
        } else if(cmd == 1) {
            reg_b = reg_b ^ arr[idx+1];
            idx+=2;
        } else if(cmd == 2) {
            reg_b = getCombo(arr[idx+1], reg_a, reg_b, reg_c)%8;
            idx+=2;
        } else if(cmd == 3) {
            if(reg_a == 0) idx+=2;
            else idx = arr[idx+1];
        } else if(cmd == 4) {
            reg_b = reg_b ^ reg_c;
            idx+=2;
        } else if(cmd == 5) {
            res+=to_string(getCombo(arr[idx+1], reg_a, reg_b, reg_c)%8)+',';
            idx+=2;
        } else if(cmd == 6) {
            reg_b = reg_a/pow(2,getCombo(arr[idx+1], reg_a, reg_b, reg_c));
            idx+=2;
        } else if(cmd == 7) {
            reg_c = reg_a/pow(2,getCombo(arr[idx+1], reg_a, reg_b, reg_c));
            idx+=2;
        }
    }
    if(res.size()!=0) res.pop_back();
    return res;
}

void part1(vector<int>&arr) {
    ll reg_a = A, reg_b = B, reg_c = C;
    string res = solve(arr, reg_a, reg_b, reg_c);
    cout<<"\nPART1: "<<res<<"\n";
}

void part2(vector<int>&arr) {
    ll reg_a = A, reg_b = B, reg_c = C;
    string target = "", res = "";
    for(int x: arr) target += to_string(x);
    do {
        ++reg_a;
        res = solve(arr, reg_a, reg_b, reg_c);
        cout<<reg_a<<"\n";
    } while (target!=res);
    cout<<"\nPART2: "<<reg_a<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "17");
    vector<int>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 6,2,7,2,3,1,6,0,5
    part2(arr); // _ > 105970123
}
