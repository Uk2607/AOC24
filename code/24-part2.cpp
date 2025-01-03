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

int getNumber(string s) {
    if(isdigit(s.back())) {
        s.erase(s.begin());
        return stoi(s);
    } return -1;
}

vector<pair<string,bool>> getVarValues(ll x, ll y) {
    vector<pair<string,bool>>var;
    for(int i=0;i<45;i++) {
        string s = "x"+(string)(i<10?"0":"")+to_string(i);
        var.push_back({s, bool(x&(1LL<<i))});
    }
    for(int i=0;i<45;i++) {
        string s = "y"+(string)(i<10?"0":"")+to_string(i);
        var.push_back({s, bool(y&(1LL<<i))});
    }
    return var;
}

void part2(vector<pair<string,bool>>var, vector<vector<string>>ops) {
    // ll X, Y, Z;
    // int xidx = 0, yidx = 0;
    // for(pair<string, int> p: var) {
    //     if(p.first[0]=='x') {
    //         X += ((ll)p.second)<<xidx;
    //         xidx++;
    //     }
    //     else if(p.first[0]=='y') {
    //         Y += ((ll)p.second)<<yidx;
    //         yidx++;
    //     }
    // }
    // Z = X+Y;

    map<string, vector<string>>edges;
    set<string>nodes;

    for(vector<string>op: ops) {
        edges[op[0]].push_back(op[3]);
        edges[op[2]].push_back(op[3]);
        nodes.insert(op[0]);
        nodes.insert(op[2]);
        nodes.insert(op[3]);
    }

    // vector<int>bad = {5, 6, 13, 14, 15, 21, 22, 23, 37, 39, 44};
    for(int i=0;i<45;i++) {
        ll NX = (1LL<<i);
        if(solve(getVarValues(2*NX, NX), ops)!=3*NX)
            cout<<i<<" ";
    } cout<<"\n";

    cout<<"PART2: "<<ops.size()<<"\n";
}

int main(int argc, char* argv[]) {
    srand(0);
    string file_name = get_file_name(argc, argv, "24");
    pair<vector<pair<string, bool>>, vector<vector<string>>>arr = get_input("input/"+file_name+".in");
    // part1(arr.first, arr.second); // 57632654722854
    part2(arr.first, arr.second); // 
}
