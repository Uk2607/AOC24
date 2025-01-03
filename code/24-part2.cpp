#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<assert.h>

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

int N = 1;
map<string, int> nameID;
int getID(string s) {
    if(nameID.count(s)) {
        return nameID[s];
    }
    nameID[s] = N++;
    return nameID[s];
}
string getName(int id) {
    for(auto it: nameID)
        if(it.second==id) return it.first;
    assert(false);
}
const int XOR = 0, OR = 1, AND = 2;
int getOP(string s) {
    if(s=="XOR") return XOR;
    if(s=="OR") return OR;
    if(s=="AND") return AND;
    assert(false);
}

struct Operation {
    int a, b, c, op;
};

vector<Operation>ops;
vector<int>xs, ys, zs;

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

ll simulate(ll X, ll Y) {
    vector<int>value(N, -1);
    for(int i=0;i<45;i++) {
        value[xs[i]] = bool(X&(1LL<<i));
        value[ys[i]] = bool(Y&(1LL<<i));
    }

    while(true) {
        bool somthing = false;
        for(Operation op: ops) {
            if(value[op.a]!=-1 && value[op.b]!=-1 && value[op.c]==-1) {
                somthing = true;
                if(op.op==AND) value[op.c] = value[op.a]&value[op.b];
                else if(op.op==OR) value[op.c] = value[op.a]|value[op.b];
                else value[op.c] = value[op.a]^value[op.b];
            }
        }
        if(!somthing) break;
    }
    ll res = 0;
    int idx = 0;
    for(int id: zs) {
        if(value[id]==-1) return 0LL;
        res += ((ll)value[id])<<idx;
        idx++;
    }
    return res;
}

int getNumber(string s) {
    if(isdigit(s.back())) {
        s.erase(s.begin());
        return stoi(s);
    } return -1;
}

void part2(vector<pair<string,bool>>var, vector<vector<string>>operations) {
    for(char c: "xyz") {
        for(int i=0;i<=45;i++)  {
            string s;
            s+=c;
            if(i<10) s+='0';
            s+=to_string(i);
            if(c=='x') xs.push_back(getID(s));
            if(c=='y') ys.push_back(getID(s));
            if(c=='z') zs.push_back(getID(s));
        }
    }

    for(vector<string>op: operations) {
        int A = getID(op[0]);
        int B = getID(op[2]);
        int C = getID(op[3]);
        ops.push_back(Operation{A, B, C, getOP(op[1])});
    }

    // vector<int>bad = {5, 6, 13, 14, 15, 21, 22, 23, 37, 39, 44};

    // [[[ 75, 151 ]]]
    swap(ops[75].c, ops[151].c); // <10 bit
    // [[[ 5, 116 ]]]
    swap(ops[5].c, ops[116].c); // <15 bit
    // [[[ 62, 181 ]]]
    swap(ops[62].c, ops[181].c); // <25 bit
    // [[[ 67, 108 ]]]
    swap(ops[67].c, ops[108].c); // <40 bit

    // for(int i=0;i<ops.size();i++) {
    //     // cout<<i<<" ";
    //     for(int j=i+1;j<ops.size();j++) {
    //         cout<<i<<" "<<j<<"\n";
    //         swap(ops[i].c, ops[j].c);
    //         bool ok = true;
    //         for(int k=0;k<40;k++) { // < bits
    //             ll x = 1LL<<k;
    //             if(simulate(x, x)!=2*x || (x!=0 && simulate(x+1, x-1)!=2*x))
    //                 ok = false;
    //         }
    //         if(ok) {
    //             cout<<"[[[ "<<i<<", "<<j<<" ]]]\n";
    //             return;
    //         }
    //         swap(ops[i].c, ops[j].c);
    //     }
    // }

    for(int t = 0;t<50;t++) {
        ll x = rand();
        x = (x<<15)+x;
        ll y = rand();
        y = (y<<15)+y;
        x %= (1LL << 45);
        y %= (1LL << 45);
        assert(simulate(x, y)==x+y);
    }

    vector<string>res;
    for(int id: {75, 151, 5, 116, 62, 181, 67, 108}) {
        res.push_back(getName(ops[id].c));
    }
    sort(res.begin(), res.end());
    for(string s: res) cout<<s<<",";
    cout<<"\n";

}

int main(int argc, char* argv[]) {
    srand(0);
    string file_name = get_file_name(argc, argv, "24");
    pair<vector<pair<string, bool>>, vector<vector<string>>>arr = get_input("input/"+file_name+".in");
    part2(arr.first, arr.second); // 
}
