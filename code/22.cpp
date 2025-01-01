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

vector<ll> get_input(string file_path) {
    string line;
    vector<ll>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) {
        arr.push_back(stoll(line));
    }
    file.close();

    return arr;
}

void print(vector<ll>&arr) {
    cout<<"\n";
    for(ll x: arr) cout<<x<<"\n";
    cout<<"\n";
}

const int MOD = 1<<24;

void next_secret(ll &a) {
    a ^= a*64;
    a %= MOD;
    a ^= a/32;
    a %= MOD;
    a ^= a*2048LL;
    a %= MOD;
}

void part1(vector<ll>arr) {
    ll res = 0;
    for(ll x: arr) {
        for(int i=0;i<2000;i++) next_secret(x);
        res+=x;
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<ll>arr) {
    cout<<"PART2: "<<arr.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "22");
    vector<ll>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 14691757043
    part2(arr); // 
}
