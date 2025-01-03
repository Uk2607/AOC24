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

pair<vector<pair<string, bool>>, vector<vector<string>>> get_input(string file_path) {
    string line;
    vector<pair<string, bool>>vars;
    vector<vector<string>>ops;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return {vars, ops};
    }

    bool flag = false;
    while(getline(file, line)) {
        if(line.length()==0) {
            flag = true;
            continue;
        }
        stringstream ss(line);
        if(!flag) {
            string s;
            int x;
            ss>>s>>x;
            s.pop_back();
            vars.push_back({s, x});
        } else {
            string a, op, b, r, t;
            ss>>a>>op>>b>>t>>r;
            ops.push_back({a, op, b, r});
        }
    }
    file.close();

    return {vars, ops};
}

void print(vector<pair<string,int>>&var, vector<vector<string>>&ops) {
    cout<<"\n";
    for(pair<string, int>p: var) cout<<p.first<<":="<<p.second<<"\n";
    cout<<"\n";
    for(vector<string>op: ops) {
        for(string s: op) cout<<s<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

ll solve(vector<pair<string,bool>>var, vector<vector<string>>ops) {
    map<string, bool>bit_val;
    for(auto [k, v]: var) bit_val[k] = v;
    queue<vector<string>>q;
    for(vector<string>v: ops) q.push(v);
    while(!q.empty()) {
        vector<string>ins = q.front();
        q.pop();
        string a = ins[0], op = ins[1], b = ins[2], t = ins[3];
        if(bit_val.find(a)==bit_val.end() || bit_val.find(b)==bit_val.end()) {
            q.push(ins);
            continue;
        }
        if(op=="AND") bit_val[t] = bit_val[a]&bit_val[b];
        else if(op=="OR") bit_val[t] = bit_val[a]|bit_val[b];
        else bit_val[t] = bit_val[a]^bit_val[b];
    }
    ll res = 0;
    int idx = 0;
    for(auto it: bit_val)
        if(it.first[0]=='z') {
            res += ((ll)it.second)<<idx;
            idx++;
        }
    return res;
}

void part1(vector<pair<string,bool>>var, vector<vector<string>>ops) {
    ll Z = solve(var, ops);
    cout<<"PART1: "<<Z<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "24");
    pair<vector<pair<string, bool>>, vector<vector<string>>>arr = get_input("input/"+file_name+".in");
    part1(arr.first, arr.second); // 57632654722854
}
