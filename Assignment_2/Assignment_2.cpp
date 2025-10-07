#include <bits/stdc++.h>
using namespace std;

// Colors
vector<string> colors = {"Red", "Green", "Blue"};

// Graph adjacency (map representation)
map<string, vector<string>> adj = {
    {"WA", {"NT", "SA"}},
    {"NT", {"WA", "SA", "Q"}},
    {"SA", {"WA", "NT", "Q", "NSW", "V"}},
    {"Q",  {"NT", "SA", "NSW"}},
    {"NSW",{"Q", "SA", "V"}},
    {"V",  {"SA", "NSW"}},
    {"T",  {}}  // Tasmania (no neighbors)
};

// Function to check if assignment is valid
bool isValid(string region, string color,
             map<string,string>& assignment) {
    for (auto neighbor : adj[region]) {
        if (assignment.count(neighbor) &&
            assignment[neighbor] == color)
            return false; // neighbor has same color
    }
    return true;
}

// Backtracking CSP solver
bool backtrack(map<string,string>& assignment,
               vector<string>& regions, int idx) {
    if (idx == regions.size()) return true; // all assigned

    string region = regions[idx];
    for (auto color : colors) {
        if (isValid(region, color, assignment)) {
            assignment[region] = color;
            if (backtrack(assignment, regions, idx+1))
                return true;
            assignment.erase(region); // backtrack
        }
    }
    return false;
}

int main() {
    vector<string> regions;
    for (auto &p : adj) regions.push_back(p.first);

    map<string,string> assignment;

    if (backtrack(assignment, regions, 0)) {
        cout << "Map Coloring Solution:\n";
        for (auto &p : assignment) {
            cout << p.first << " -> " << p.second << "\n";
        }
    } else {
        cout << "No solution found.\n";
    }
    return 0;
}
