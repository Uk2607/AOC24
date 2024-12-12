#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>

#define ll long long int
#define ull unsigned long long int
using namespace std;

map<ll, vector<ll>> get_input(string file_path) {
    string line;
    map<ll, vector<ll>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) {
        stringstream ss(line);
        ll src;
        string s;
        bool flag = true;
        while(getline(ss, s, ':')) {
            if(flag) {
                src = stoll(s);
                flag = false;
            } else {
                string x;
                stringstream val(s);
                while(val>>x) arr[src].push_back(stoll(x));
            }
        }
    }
    file.close();

    return arr;
}

void print(map<ll, vector<ll>>&arr) {
    cout<<"\n";
    for(auto it: arr) {
        cout<<it.first<<": ";
        for(ll s: it.second) cout<<s<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

void part1(map<ll, vector<ll>>mp) {
    ull res=0;
    for(auto it: mp) {
        ll target = it.first;
        vector<ll>arr = it.second;
        int n = arr.size();
        ll ways = pow(2,n-1), itr=0;
        while(itr<ways) {
            int idx = 0;
            // cout<<arr[idx];
            ull val = arr[idx++];
            while(idx<n) {
                if((1<<(idx-1)&itr) == 0) {
                    // cout<<"+"<<arr[idx];
                    val += arr[idx++];
                } else {
                    // cout<<"*"<<arr[idx];
                    val *= arr[idx++];
                }
                if(val>target) break;
            }
            if(val == target) {
                res+=target;
                // cout<<" = "<<target<<"\n";
                break;
            }
            // else {
            //     cout<<" ≠ "<<target<<"\n";
            // }
            ++itr;
        }
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(map<ll, vector<ll>>mp) {
    ull res=0;
    for(auto it: mp) {
        ll target = it.first;
        vector<ll>arr = it.second;
        int n = arr.size();
        ll ways = pow(3,n-1), itr=0;
        while(itr<ways) {
            int idx = 0;
            // cout<<arr[idx];
            ull val = arr[idx++];
            while(idx<n) {
                int x = (itr / (ull)pow(3, idx - 1)) % 3;
                if(x == 0) {
                    // cout<<"+"<<arr[idx];
                    val += arr[idx++];
                } else if (x == 1) {
                    // cout<<"*"<<arr[idx];
                    val *= arr[idx++];
                } else {
                    // cout<<"||"<<arr[idx];
                    val = stoull(to_string(val)+to_string(arr[idx++]));
                }
                if(val>target) break;
            }
            if(val == target) {
                res+=target;
                // cout<<" = "<<target<<"\n";
                break;
            }
            // else {
            //     cout<<" ≠ "<<target<<"\n";
            // }
            ++itr;
        }
    }
    cout<<"PART2: "<<res<<"\n";
}
int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "11");
    map<ll, vector<ll>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 5702958180383
    part2(arr); // 92612386119138
}
