#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

map<char, string> cafe;
map<char, vector<pair<char, int>>> adj;

void graf(){
    cafe['A'] = "Warung Kopi Pak Harry";
    cafe['B'] = "Kedai Coding IKLC";
    cafe['C'] = "Catfe Alya";
    cafe['D'] = "Studio Fasilkom, TI gak diajak";
    cafe['E'] = "Wifi Gratis Sejagat";

    adj['A'].push_back({'B', 4});
    adj['A'].push_back({'C', 2});
    
    adj['B'].push_back({'A', 4});
    adj['B'].push_back({'D', 3});

    adj['C'].push_back({'A', 2});
    adj['C'].push_back({'D', 1});

    adj['D'].push_back({'B', 3});
    adj['D'].push_back({'C', 1});
    adj['D'].push_back({'E', 5});

    adj['E'].push_back({'D', 5});
}

void dfs(char start, map<char, bool> &visited){
    visited[start] = true;
    cout << cafe[start] << endl;

    for(auto edge : adj[start]){
        char next = edge.first;
        if(!visited[next]){
            dfs(next, visited);
        }
    }
}

void bfs(char start_node, char end_node) {
    queue<char> q;
    map<char, bool> visited_bfs;
    map<char, char> parent; 
    map<char, int> edge_weight; 

    q.push(start_node);
    visited_bfs[start_node] = true;
    parent[start_node] = '\0'; 
    edge_weight[start_node] = 0;

    while (!q.empty()) {
        char current = q.front();
        q.pop();

        if (current == end_node) {
            break;
        }

        for (auto edge : adj[current]) {
            char neighbor = edge.first;
            int weight = edge.second;

            if (!visited_bfs[neighbor]) {
                visited_bfs[neighbor] = true;
                parent[neighbor] = current; 
                edge_weight[neighbor] = weight; 
                q.push(neighbor);
            }
        }
    }

    vector<char> path;
    char current = end_node;
    int total_distance = 0;

    while (current != '\0') {
        path.push_back(current);
        total_distance += edge_weight[current]; 
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    int total_steps = path.size() - 1; 

    for (int i = 0; i < path.size(); i++) {
        char node = path[i];
        cout << cafe[node] << " (" << node << ")" << endl;
        
        if (i < path.size() - 1) {
            cout << edge_weight[path[i+1]] << "m" << endl;
        }
    }

    cout << endl; 

    cout << "Jalur terpendek: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    cout << "Total langkah: " << total_steps << " edge" << endl;
    cout << "Total jarak: " << total_distance << " meter" << endl;
}

int main(){
    cout << "Penjelajahan Cafe (DFS dari A)" << endl;
    graf();
    map<char, bool> visited;
    dfs('A', visited);

    cout << endl;
    cout << "JALUR TERCEPAT PARUL (BFS):" << endl;
    bfs('A', 'E');
}
