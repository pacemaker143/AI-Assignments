#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> goal = {{1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 0}};

int moves[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};


string stateToString(const vector<vector<int>>& state) {
    string s = "";
    for (auto &row : state)
        for (int val : row) s += to_string(val);
    return s;
}


pair<int,int> findBlank(const vector<vector<int>>& state) {
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            if (state[i][j] == 0) return {i,j};
    return {-1,-1};
}


bool isGoal(const vector<vector<int>>& state) {
    return state == goal;
}

// Generate neighbors
vector<vector<vector<int>>> getNeighbors(const vector<vector<int>>& state) {
    vector<vector<vector<int>>> neighbors;
    auto [r,c] = findBlank(state);

    for (auto &m : moves) {
        int nr = r + m[0], nc = c + m[1];
        if (nr>=0 && nr<3 && nc>=0 && nc<3) {
            auto newState = state;
            swap(newState[r][c], newState[nr][nc]);
            neighbors.push_back(newState);
        }
    }
    return neighbors;
}

// BFS ----------
vector<vector<vector<int>>> bfs(vector<vector<int>> start) {
    queue<pair<vector<vector<int>>, vector<vector<vector<int>>>>> q;
    set<string> visited;

    q.push({start, {}});
    visited.insert(stateToString(start));

    while (!q.empty()) {
        auto [state, path] = q.front(); q.pop();

        if (isGoal(state)) {
            path.push_back(state);
            return path;
        }

        for (auto &neighbor : getNeighbors(state)) {
            string key = stateToString(neighbor);
            if (!visited.count(key)) {
                auto newPath = path;
                newPath.push_back(state);
                q.push({neighbor, newPath});
                visited.insert(key);
            }
        }
    }
    return {};
}

// DFS ----------
vector<vector<vector<int>>> dfs(vector<vector<int>> start, int depthLimit=30) {
    stack<pair<vector<vector<int>>, vector<vector<vector<int>>>>> st;
    set<string> visited;

    st.push({start, {}});

    while (!st.empty()) {
        auto [state, path] = st.top(); st.pop();

        if (isGoal(state)) {
            path.push_back(state);
            return path;
        }

        if ((int)path.size() >= depthLimit) continue;

        string key = stateToString(state);
        if (visited.count(key)) continue;
        visited.insert(key);

        for (auto &neighbor : getNeighbors(state)) {
            if (!visited.count(stateToString(neighbor))) {
                auto newPath = path;
                newPath.push_back(state);
                st.push({neighbor, newPath});
            }
        }
    }
    return {};
}

// Print State ----------
void printState(const vector<vector<int>>& state) {
    for (auto &row : state) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }
    cout << "------\n";
}

// Main ----------
int main() {
    vector<vector<int>> start = {{1,2,3},
                                 {4,0,6},
                                 {7,5,8}};

    cout << "BFS Solution:\n";
    auto bfsPath = bfs(start);
    if (!bfsPath.empty()) {
        for (auto &step : bfsPath) printState(step);
    } else {
        cout << "No solution found with BFS.\n";
    }

    cout << "\nDFS Solution:\n";
    auto dfsPath = dfs(start, 20);
    if (!dfsPath.empty()) {
        for (auto &step : dfsPath) printState(step);
    } else {
        cout << "No solution found with DFS.\n";
    }
    return 0;
}
