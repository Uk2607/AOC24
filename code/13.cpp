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

vector<pair<ll, ll>> get_input(string file_path) {
    string line;
    vector<pair<ll, ll>>arr;

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
        arr.push_back({stoll(x.substr(2, x.length()-3)), stoll(y.substr(2))});
        idx++;
    }
    file.close();

    return arr;
}

void print(vector<pair<ll, ll>>&arr) {
    cout<<"\n";
    for(pair<ll, ll>p: arr) cout<<p.first<<" "<<p.second<<"\n";
    cout<<"\n";
}

void part1(vector<pair<ll, ll>>arr) {
    int n = arr.size();
    ll res = 0;
    for(int i=0;i<n; i+=3) {
        auto [x1, y1] = arr[i];
        auto [x2, y2] = arr[i+1];
        auto [X, Y] = arr[i+2];
        ll num_a = ((X*y2)-(Y*x2)), den_a = ((x1*y2)-(x2*y1));
        ll num_b = ((X*y1)-(Y*x1)), den_b = ((x2*y1)-(x1*y2));
        if(num_a%den_a == 0 && num_b%den_b == 0)
            res += (3*(num_a/den_a) + (num_b/den_b));
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<pair<ll, ll>>arr) {
    int n = arr.size();
    ll res = 0;
    for(int i=0;i<n; i+=3) {
        auto [x1, y1] = arr[i];
        auto [x2, y2] = arr[i+1];
        auto [X, Y] = arr[i+2];
        X += 10000000000000;
        Y += 10000000000000;
        ll num_a = ((X*y2)-(Y*x2)), den_a = ((x1*y2)-(x2*y1));
        ll num_b = ((X*y1)-(Y*x1)), den_b = ((x2*y1)-(x1*y2));
        if(num_a%den_a == 0 && num_b%den_b == 0)
            res += (3*(num_a/den_a) + (num_b/den_b));
    }
    cout<<"PART2: "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "13");
    vector<pair<ll, ll>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 29201
    part2(arr); // 104140871044942
}
