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

vector<ll> get_input(string file_path) {
    string line;
    vector<ll>arr;

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

ll getCombo(ll x, ll a, ll b, ll c) {
    if(x>=0 && x<=3) return x;
    if(x==4) return a;
    if(x==5) return b;
    if(x==6) return c;
    assert(false);
}

vector<ll> solve(vector<ll>&arr, ll reg_a, ll reg_b, ll reg_c) {
    int n = arr.size(), idx = 0;
    ll cmd;
    vector<ll> res;
    while(true) {
        if(idx>n) break;
        cmd = arr[idx];
        // cout<<"arr["<<idx<<"]="<<arr[idx]<<": "<<reg_a<<", "<<reg_b<<", "<<reg_c<<"\n";
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
            res.push_back(getCombo(arr[idx+1], reg_a, reg_b, reg_c)%8);
            idx+=2;
        } else if(cmd == 6) {
            reg_b = reg_a/pow(2,getCombo(arr[idx+1], reg_a, reg_b, reg_c));
            idx+=2;
        } else if(cmd == 7) {
            reg_c = reg_a/pow(2,getCombo(arr[idx+1], reg_a, reg_b, reg_c));
            idx+=2;
        }
    }
    return res;
}

void part1(vector<ll>&arr) {
    ll reg_a = A, reg_b = B, reg_c = C;
    vector<ll> res = solve(arr, reg_a, reg_b, reg_c);
    cout<<"\nPART1:\n";
    for(ll x: res) cout<<x<<", ";
    cout<<"\n";
}

/*
2,4 -- B=A%8
1,3 -- B^=3
7,5 -- C=A>>B
1,5 -- B^=5
0,3 -- A>>=3
4,_ -- B^=C
5,5 -- out (B%8)
3,0 -- if A==0 then stop, else repeat
*/


void part2(vector<ll>&arr) {
    ll reg_b = B, reg_c = C;
    vector<ll>res;
    vector<ll>cands;
    for(ll i=0;i<1024;i++) cands.push_back(i);
    ll pw = 1024;
    for(int k=0;k<arr.size();k++) {
        vector<ll>new_cands;
        for(ll _A: cands) {
            res.clear();
            res = solve(arr, _A, reg_b, reg_c);
            bool ok = true;
            for(int j=0;j<=k;j++) {
                if(j>=res.size() || res[j]!=arr[j]) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                for(int j=0;j<8;j++) {
                    new_cands.push_back(_A+j*pw);
                }
            }
        }
        cands = new_cands;
        cout<<cands.size()<<"\n";
        pw *= 8;
    }
    for(ll _A: cands) {
        if(solve(arr, _A, reg_b, reg_c).size()==arr.size()) {
            cout<<_A<<"\n";
        }
    }
    // cout<<"\nPART2: "<<reg_a<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "17");
    vector<ll>arr  = get_input("input/"+file_name+".in");
    // part1(arr); // 6,2,7,2,3,1,6,0,5
    part2(arr); // _ > 105970123
}
