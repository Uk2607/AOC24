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

using Block = tuple<int, int, int>;  // {id, block_size, pos}

string  get_input(string file_path) {
    string line;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return "";
    }

    getline(file, line);
    file.close();

    return line;
}

void print(string &str) {
    cout<<"\n";
    cout<<str<<"";
    cout<<"\n";
}

void part1(string str) {
    ull res = 0;
    int n = str.length();
    vector<int>disc;
    for(int i=0;i<n;i++) {
        int sz = str[i]-'0', id = (i%2==0)?(i/2):-1;
        while(sz--) disc.push_back(id);
    }
    int l = 0, r = disc.size()-1;
    while(l<r) {
        while (disc[l]!=-1) ++l;
        while (disc[r]==-1) --r;
        if(l>=r) break;
        swap(disc[l], disc[r]);
        ++l;--r;
    }
    for(int i=0;i<disc.size();i++) {
        if(disc[i] == -1) break;
        res += (i*disc[i]);
    }
    cout<<"\nPART1: "<<res<<"\n";
}

void part2(string str) {
    vector<Block>blocks;
    ull res = 0;
    int pos = 0;
    for(int i=0;i<str.length();i++) {
        int sz = str[i]-'0';
        if(i%2==0) blocks.push_back(make_tuple(i/2, sz, pos));
        pos+=sz;
    }
    // Block {id, block_size, pos}
    while(blocks.size()>1) {
        Block last = blocks.back();
        // blocks.pop_back();
        bool inserted = false;
        for(int i=0;i<blocks.size()-1;i++) {
            int A = get<2>(blocks[i])+get<1>(blocks[i]);
            int B = get<2>(blocks[i+1]);
            if(B-A >= get<2>(last)) {
                get<2>(last) = A;
                blocks.pop_back();
                blocks.insert(blocks.begin()+i+1, last);
                inserted = true;
                break;
            }
        }
        if(!inserted) {
            blocks.pop_back();
            // get<2>(last) = get<1>(blocks.back()) + get<2>(blocks.back());
            // blocks.push_back(last);
            for(int j=0;j<(get<1>(last));j++) {
                res += (ull)(get<2>(last)+j)*(ull)get<0>(last);
            }
            // break;
        }
    }
    cout<<"\nPART2: "<<res<<"\n";
}

int main(int argc, char* argv[]) {
    string file_name = get_file_name(argc, argv, "09");
    string str  = get_input("input/"+file_name+".in");
    part1(str); // 6301895872542
    part2(str); // 
}
