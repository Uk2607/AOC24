#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

pair<vector<int>,vector<int>> get_input(string file_path) {
    string line;
    vector<int>l, r;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return {l, r};
    }

    while(getline(file, line)) {
        int a, b;
        stringstream ss(line);
        ss>>a>>b;
        l.push_back(a);
        r.push_back(b);
    }
    file.close();

    return {l, r};
}

void part1(vector<int>a, vector<int>b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int x=0, n = a.size();
    for(int i=0;i<n;i++) x += abs(a[i]-b[i]);
    cout<<"PART1: "<<x<<"\n";
}

void part2(vector<int>&a, vector<int>&b) {
    long long int score = 0;
    map<int,int>mp;
    for(int x: b) ++mp[x];
    for(int x: a) if(mp.find(x)!=mp.end()) score+=(x*mp[x]);
    cout<<"PART2: "<<score<<"\n";
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    pair<vector<int>, vector<int>>v  = get_input(file_name);
    part1(v.first, v.second);
    part2(v.first, v.second);
}
