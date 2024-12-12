#include "file_name.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

vector<string> get_input(string file_path) {
    string line;
    vector<string>arr;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return arr;
    }

    while(getline(file, line)) arr.push_back(line+"###############################");  // added #'s to prevent string overflow
    file.close();

    return arr;
}

int get_num(string &s, int &i) {
    int x = 0;
    while(x<1000 && isdigit(s[i]))
        x = x*10+(s[i++]-'0');
    if(1<=x && x<=999) return x;
    return -1;
}

void solve(vector<string>arr, bool part2 = false) {
    int res=0;
    bool enable = true;
    for(string s: arr) {
        int n = s.length();
        for(int i=0;i<n;i++) {
            if(part2 && s.substr(i, 4) == "do()") enable = true;
            else if(part2 && s.substr(i, 7) == "don\'t()") enable = false;
            if(enable && s.substr(i, 4)=="mul(") {
                i+=4;
                int x = get_num(s, i);
                if(s[i]==',') {
                    i+=1;
                    int y = get_num(s, i);
                    if(s[i]==')')
                        if(x!=-1 && y!=-1) res+=(x*y);
                }
            }
        }
    }
    cout<<"PART"<<(part2?2:1)<<": "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "03");
    vector<string>arr  = get_input("input/"+file_name+".in");
    solve(arr); // 184576302
    solve(arr, true); // 118173507
}
