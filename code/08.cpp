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

vector<string> get_input(string file_path) {
    string line;
    vector<string>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) arr.push_back(line);
    file.close();

    return arr;
}

void print(vector<string>&arr) {
    cout<<"\n";
    for(string s: arr) {
        for(char c: s)
            cout<<c<<"";
        cout<<"\n";
    }
    cout<<"\n";
}

void part1(vector<string>arr) {
    int r = arr.size(), c = arr[0].length();
    map<char, vector<pair<int,int>>>mp;
    // set<pair<int,int>>st;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            if(arr[i][j]!='.') {
                mp[arr[i][j]].push_back({i, j});
                // st.insert({i, j});
            }
    set<pair<int,int>>ants;
    for(auto it: mp) {
        vector<pair<int,int>>v = it.second;
        int n = v.size();
        for(int i=0;i<n;i++) {
            int x1 = v[i].first, y1 = v[i].second;
            for(int j=i+1;j<n;j++) {
                int x2 = v[j].first, y2 = v[j].second;
                pair<int,int>c3 = {2*x1-x2, 2*y1-y2}, c4 = {2*x2-x1, 2*y2-y1};
                if(c3.first>=0 && c3.first<r && c3.second>=0 && c3.second<c) ants.insert(c3);
                if(c4.first>=0 && c4.first<r && c4.second>=0 && c4.second<c) ants.insert(c4);
            }
        }
    }
    cout<<"PART1: "<<ants.size()<<"\n";
}

void part2(vector<string>arr) {
    int r = arr.size(), c = arr[0].length();
    map<char, vector<pair<int,int>>>mp;
    // set<pair<int,int>>st;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            if(arr[i][j]!='.') {
                mp[arr[i][j]].push_back({i, j});
                // st.insert({i, j});
            }
    set<pair<int,int>>ants;
    for(auto it: mp) {
        vector<pair<int,int>>v = it.second;
        int n = v.size();
        for(int i=0;i<n;i++) {
            int x1 = v[i].first, y1 = v[i].second;
            for(int j=i+1;j<n;j++) {
                int x2 = v[j].first, y2 = v[j].second;
                pair<int,int>c3 = {2*x1-x2, 2*y1-y2}, c4 = {2*x2-x1, 2*y2-y1};
                if(c3.first>=0 && c3.first<r && c3.second>=0 && c3.second<c) ants.insert(c3);
                if(c4.first>=0 && c4.first<r && c4.second>=0 && c4.second<c) ants.insert(c4);
            }
        }
    }
    // TODO:
    cout<<"PART2: "<<ants.size()<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "11");
    vector<string>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 271
    part2(arr); // 
}
