#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <bits/stdc++.h>

using namespace std;

const int N = 3;

// Define the goal state
vector<vector<int>> goal_state = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// Directions for moving the blank space (0)
map<string, pair<int, int>> directions = {
    {"up", {-1, 0}},
    {"down", {1, 0}},
    {"left", {0, -1}},
    {"right", {0, 1}}
};

// Check if the current state is the goal state
bool is_goal(const vector<vector<int>>& state) {
    return state == goal_state;
}

// Get the position of the blank (0)
pair<int, int> get_blank_position(const vector<vector<int>>& state) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (state[i][j] == 0) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should never happen
}

// Move the blank space in a specified direction
vector<vector<int>> move(const vector<vector<int>>& state, const string& direction) {
    vector<vector<int>> new_state = state;
    pair<int, int> blank_pos = get_blank_position(new_state);
    int i = blank_pos.first, j = blank_pos.second;
    int di = directions[direction].first, dj = directions[direction].second;
    int new_i = i + di, new_j = j + dj;

    // Check if the move is valid
    if (new_i >= 0 && new_i < N && new_j >= 0 && new_j < N) {
        swap(new_state[i][j], new_state[new_i][new_j]);
        return new_state;
    }
    return {};
}

// DFS function to solve the puzzle
vector<vector<vector<int>>> dfs(const vector<vector<int>>& initial_state) {
    stack<vector<vector<int>>> stack;
    set<vector<vector<int>>> visited;
    map<vector<vector<int>>, vector<vector<int>>> parent_map;

    stack.push(initial_state);
    visited.insert(initial_state);
    parent_map[initial_state] = {};

    while (!stack.empty()) {
        vector<vector<int>> current_state = stack.top();
        stack.pop();

        if (is_goal(current_state)) {
            vector<vector<vector<int>>> path;
            vector<vector<int>> state = current_state;
            while (!state.empty()) {
                path.push_back(state);
                state = parent_map[state];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Explore all four possible directions
        for (const auto& dir : directions) {
            vector<vector<int>> new_state = move(current_state, dir.first);
            if (!new_state.empty() && visited.find(new_state) == visited.end()) {
                visited.insert(new_state);
                parent_map[new_state] = current_state;
                stack.push(new_state);
            }
        }
    }

    return {}; // Return an empty vector if no solution is found
}

// Print the path to the solution
void print_path(const vector<vector<vector<int>>>& path) {
    for (const auto& state : path) {
        for (const auto& row : state) {
            for (int tile : row) {
                cout << tile << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main() {
    // Example initial state
    vector<vector<int>> initial_state = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    vector<vector<vector<int>>> path = dfs(initial_state);

    if (!path.empty()) {
        print_path(path);
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
