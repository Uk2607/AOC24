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
    // size is 21 because maxinmum difference between the numbers will be 20 eg: 9-(-9)
    const int diff = 20;
    // using arrays instead of map<vector<int>, int> because it will be faster about 50x;
    int mp[diff][diff][diff][diff] = {0};
    int vis[diff][diff][diff][diff] = {0};
    int id = 0;
    for(ll x: arr) {
        ++id;
        vector<int>v;
        v.push_back(x%10);
        for(int i=1;i<=2000;i++) {
            next_secret(x);
            v.push_back(x%10);
            if(i>=4) {
                int d[4];
                for(int j=0;j<4;j++) d[j] = v[i-3+j]-v[i-4+j];
                if(vis[d[0]+10][d[1]+10][d[2]+10][d[3]+10]!=id) {
                    vis[d[0]+10][d[1]+10][d[2]+10][d[3]+10] = id;
                    mp[d[0]+10][d[1]+10][d[2]+10][d[3]+10] += x%10;
                }
            }
        }
    }
    int res = 0;
    for(int i=0;i<diff;i++)
        for(int j=0;j<diff;j++)
            for(int k=0;k<diff;k++)
                for(int l=0;l<diff;l++)
                    res = max(res, mp[i][j][k][l]);
    cout<<"PART2: "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "22");
    vector<ll>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 14691757043
    part2(arr); // 1831
}
