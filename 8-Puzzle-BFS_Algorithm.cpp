#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

const int SIZE = 9;

// Function to find the location of the blank tile (0)
int BlankTileLocation(const vector<int>& N) {
    for (int i = 0; i < SIZE; i++) {
        if (N[i] == 0) return i;
    }
    return -1;
}

// Move blank tile up
vector<int> ActionMoveUp(int b, vector<int> N) {
    if (b > 2) {
        swap(N[b], N[b - 3]);
    }
    return N;
}

// Move blank tile down
vector<int> ActionMoveDown(int b, vector<int> N) {
    if (b < 6) {
        swap(N[b], N[b + 3]);
    }
    return N;
}

// Move blank tile left
vector<int> ActionMoveLeft(int b, vector<int> N) {
    if (b != 0 && b != 3 && b != 6) {
        swap(N[b], N[b - 1]);
    }
    return N;
}

// Move blank tile right
vector<int> ActionMoveRight(int b, vector<int> N) {
    if (b != 2 && b != 5 && b != 8) {
        swap(N[b], N[b + 1]);
    }
    return N;
}

// Convert the state to a string for easier comparison and storage
string vecToString(const vector<int>& N) {
    string result;
    for (int i = 0; i < SIZE; i++) {
        result += to_string(N[i]) + " ";
    }
    return result;
}

// Breadth-First Search (BFS) to solve the 8-puzzle
bool BFS(vector<int> start) {
    // The goal state of the 8-puzzle
    vector<int> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    queue<vector<int>> frontier;  // Queue for BFS
    map<string, string> parent;   // Map to store parent states
    map<string, char> moveMade;   // Map to store the move made to reach the state
    parent[vecToString(start)] = "";
    frontier.push(start);

    // To write explored nodes to file
    ofstream exploredFile("Nodes.txt");
    
    while (!frontier.empty()) {
        vector<int> current = frontier.front();
        frontier.pop();

        if (current == goal) {  // Goal found
            exploredFile << vecToString(current) << '\n';
            exploredFile.close();
            return true;
        }

        int blankPos = BlankTileLocation(current);
        vector<int> up = ActionMoveUp(blankPos, current);
        vector<int> down = ActionMoveDown(blankPos, current);
        vector<int> left = ActionMoveLeft(blankPos, current);
        vector<int> right = ActionMoveRight(blankPos, current);

        string currentState = vecToString(current);
        if (up != current && parent.find(vecToString(up)) == parent.end()) {
            parent[vecToString(up)] = currentState;
            moveMade[vecToString(up)] = 'U';
            frontier.push(up);
        }
        if (down != current && parent.find(vecToString(down)) == parent.end()) {
            parent[vecToString(down)] = currentState;
            moveMade[vecToString(down)] = 'D';
            frontier.push(down);
        }
        if (left != current && parent.find(vecToString(left)) == parent.end()) {
            parent[vecToString(left)] = currentState;
            moveMade[vecToString(left)] = 'L';
            frontier.push(left);
        }
        if (right != current && parent.find(vecToString(right)) == parent.end()) {
            parent[vecToString(right)] = currentState;
            moveMade[vecToString(right)] = 'R';
            frontier.push(right);
        }

        exploredFile << vecToString(current) << '\n';  // Write explored nodes to file
    }

    exploredFile.close();
    return false;
}

int main() {
    vector<int> start(SIZE);

    cout << "Enter the start state row-wise (e.g. 1 2 3 0 4 5 8 6 7): ";
    for (int i = 0; i < SIZE; i++) {
        cin >> start[i];
    }

    if (BFS(start)) {
        cout << "Solution found!" << endl;
    } else {
        cout << "No solution exists for this initial state." << endl;
    }

    return 0;
}
