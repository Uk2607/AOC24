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

vector<vector<string>> get_input(string file_path) {
    string line;
    vector<vector<string>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }
    vector<string>grid;
    while(getline(file, line)) {
        if(line.length()==0) {
            arr.push_back(grid);
            grid.clear();
            continue;
        }
        grid.push_back(line);
    }
    arr.push_back(grid);

    file.close();

    return arr;
}

void print(vector<vector<string>>&arr) {
    cout<<"\n";
    for(vector<string> v: arr) {
        for(string s: v) cout<<s<<"\n";
        cout<<"\n";
    }
    cout<<"\n";
}

void part1(vector<vector<string>>patterns) {
    vector<vector<int>>locks, keys;
    for(vector<string>grid: patterns) {
        vector<int>arr(5, 0);
        for(int j=0;j<5;j++)
            for(int i=1;i<6;i++)
                if(grid[i][j] == '#')
                    arr[j]++;
        if(grid[0]=="#####") locks.push_back(arr);
        else keys.push_back(arr);
    }
    // cout<<"Locks:\n";
    // for(vector<int>_lock: locks) {
    //     for(int l: _lock) cout<<l<<" ";
    //     cout<<"\n";
    // }
    // cout<<"Keys:\n";
    // for(vector<int>_key: keys) {
    //     for(int k: _key) cout<<k<<" ";
    //     cout<<"\n";
    // }
    int res = 0;
    for(vector<int>_lock: locks) {
        for(vector<int>_key: keys) {
            bool flag = true;
            for(int i=0;i<5;i++) {
                if(_lock[i]+_key[i] > 5) {flag = false; break;}
            }
            if(flag) ++res;
        }
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<vector<string>>patterns) {
    cout<<"PART2: "<<patterns.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "25");
    vector<vector<string>>patterns  = get_input("input/"+file_name+".in");
    part1(patterns); // 2950
    part2(patterns); // 
}
