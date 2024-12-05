#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<set>

using namespace std;

pair<vector<pair<int,int>>, vector<vector<int>>> get_input(string file_path) {
    string line;
    vector<pair<int,int>>ordering;
    vector<vector<int>>version;

    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << file_path << endl;
        return {ordering, version};
    }
    //Assuming page number will be in two digits only
    bool flag = true;
    while(getline(file, line)) {
        if(line.length()==0) {
            flag = false;
            continue;
        }
        if(flag) {
            ordering.push_back({stoi(line.substr(0, 2)), stoi(line.substr(3, 2))});
        } else {
            vector<int>t;
            for(int i=0;i<line.length(); i+=3) t.push_back(stoi(line.substr(i, 2)));
            version.push_back(t);
        }
    }
    file.close();

    return {ordering, version};
}

void print(vector<pair<int,int>>&page_order, vector<vector<int>>&version) {
    for(auto [l, r]: page_order) cout<<l<<"<->"<<r<<"\n";
    cout<<"\n";
    for(vector<int>v: version) {
        for(int x: v) cout<<x<<" ";
        cout<<"\n";
    }
}

void part1(vector<pair<int,int>>page_order, vector<vector<int>>version) {
    int res=0;
    map<int, set<int>>pages_before;
    for(pair<int,int>p: page_order)
        pages_before[p.second].insert(p.first);
    for(vector<int>v: version) {
        bool flag = true;
        int n = v.size();
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++) {
                if(pages_before.find(v[i])==pages_before.end()) continue;
                if(pages_before[v[i]].find(v[j]) != pages_before[v[i]].end()) {
                    flag = false;
                    break;
                }
            }
        }
        if(flag) res += v[n/2];
    }
    cout<<"PART1: "<<res<<"\n";
}

void part2(vector<pair<int,int>>page_order, vector<vector<int>>version) {
    int res=0;
    map<int, set<int>>pages_after, pages_before;
    for(pair<int,int>p: page_order) {
        pages_after[p.first].insert(p.second);
        pages_before[p.second].insert(p.first);
    }
    for(vector<int>v: version) {
        bool flag = true;
        int n = v.size();
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++) {
                if(pages_before.find(v[i])==pages_before.end()) continue;
                if(pages_before[v[i]].find(v[j]) != pages_before[v[i]].end()) {
                    flag = false;
                }
            }
        }
        if(flag) res += v[n/2];
    }
    cout<<"PART2: "<<res<<"\n";
}

int main() {
    string file_name;
    cout<<"Enter file name: ";
    cin>>file_name;
    pair<vector<pair<int,int>>, vector<vector<int>>>p  = get_input("input/"+file_name+".in");
    part1(p.first, p.second); // 
    part2(p.first, p.second); // 
}
