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
    /*
    19191
    0.........1.........2
    */
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
    cout<<"\nPART2: "<<str.length()<<"\n";
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    string str  = get_input("input/"+file_name+".in");
    part1(str); // 
    part2(str); // 
}
