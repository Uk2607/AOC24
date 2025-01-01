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

vector<pair<string, string>> get_input(string file_path) {
    string line;
    vector<pair<string, string>>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line))
        arr.push_back({line.substr(0, 2), line.substr(3)});
    file.close();

    return arr;
}

void print(vector<pair<string, string>>&arr) {
    cout<<"\n";
    for(auto [a, b]: arr) cout<<a<<"-"<<b<<"\n";
    cout<<"\n";
}

void part1(vector<pair<string, string>>arr) {
    map<string, set<string>>mp;
    for(auto [a, b]: arr) {
        mp[a].insert(b);
        mp[b].insert(a);
    }
    
    int res = 0;
    for(auto [a, va]: mp)
        for(string b: va)
            if(a!=b)
                for(string c: mp[b])
                    if( a<b && b<c && mp[c].find(a) != mp[c].end())
                        if(a[0]=='t' || b[0]=='t' || c[0]=='t') ++res;
    
    cout<<"PART1: "<<res<<"\n";
}

void rec(string a, int i, map<string, vector<string>>&mp, set<pair<string, string>>&pairs, vector<string>clique, vector<string>&biggest_clique) {
    if(i==mp[a].size()) {
        if(clique.size()>biggest_clique.size())
            biggest_clique = clique;
        return;
    }

    rec(a, i+1, mp, pairs, clique, biggest_clique);
    string b = mp[a][i];
    for(string s: clique) if(!pairs.count({b, s})) return;
    clique.push_back(b);
    rec(a, i+1, mp, pairs, clique, biggest_clique);
}

void part2(vector<pair<string, string>>arr) {
    map<string, vector<string>>mp;
    set<pair<string, string>>pairs;
    set<string>vis;
    for(auto [a, b]: arr) {
        mp[a].push_back(b);
        mp[b].push_back(a);
        pairs.insert({a, b});
        pairs.insert({b, a});
    }
    vector<string>biggest_clique;
    for(auto it: mp)
        if(!vis.count(it.first))
            rec(it.first, 0, mp, pairs, {it.first}, biggest_clique);
    
    string res = "";
    sort(biggest_clique.begin(), biggest_clique.end());
    for(string s: biggest_clique) res+=s+',';
    res.pop_back();
    cout<<"PART2: "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "23");
    vector<pair<string, string>>arr  = get_input("input/"+file_name+".in");
    part1(arr); // 1337
    part2(arr); // aw,fk,gv,hi,hp,ip,jy,kc,lk,og,pj,re,sr
}
