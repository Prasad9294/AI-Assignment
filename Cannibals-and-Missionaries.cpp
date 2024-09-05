#include <iostream>
using namespace std;

class MissionaryCannibal {
private:
    int left[3];   // [missionaries, cannibals, boat]
    int right[3];  // [missionaries, cannibals, boat]

public:
    MissionaryCannibal() {
        left[0] = 3;  // 3 missionaries on the left
        left[1] = 3;  // 3 cannibals on the left
        left[2] = 1;  // boat on the left side
        right[0] = 0; // 0 missionaries on the right
        right[1] = 0; // 0 cannibals on the right
        right[2] = 0; // no boat on the right side
    }

    void displayState() {
        cout << "Left side: " << left[0] << " Missionaries, " << left[1] << " Cannibals, Boat: " 
             << (left[2] == 1 ? "Yes" : "No") << endl;
        cout << "Right side: " << right[0] << " Missionaries, " << right[1] << " Cannibals, Boat: " 
             << (right[2] == 1 ? "Yes" : "No") << endl;
    }

    bool move(int missionaries, int cannibals, bool toRight) {
        if (missionaries + cannibals > 2 || missionaries < 0 || cannibals < 0 || (missionaries == 0 && cannibals == 0)) {
            return false;
        }

        if (toRight) {
            if (left[0] >= missionaries && left[1] >= cannibals && left[2] == 1) {
                left[0] -= missionaries;
                left[1] -= cannibals;
                right[0] += missionaries;
                right[1] += cannibals;
                left[2] = 0;
                right[2] = 1;
                return true;
            }
        } else {
            if (right[0] >= missionaries && right[1] >= cannibals && right[2] == 1) {
                right[0] -= missionaries;
                right[1] -= cannibals;
                left[0] += missionaries;
                left[1] += cannibals;
                right[2] = 0;
                left[2] = 1;
                return true;
            }
        }

        return false;
    }

    bool checkLose() {
        if ((left[0] > 0 && left[1] > left[0]) || (right[0] > 0 && right[1] > right[0])) {
            return true;
        }
        return false;
    }

    bool win() {
        if (right[0] == 3 && right[1] == 3) {
            return true;
        }
        return false;
    }

    bool isBoatOnLeft() {  // Getter function to check if the boat is on the left side
        return left[2] == 1;
    }
};

int main() {
    MissionaryCannibal game;
    while (true) {
        game.displayState();

        if (game.win()) {
            cout << "Congratulations! All missionaries and cannibals have successfully crossed the river." << endl;
            break;
        }

        if (game.checkLose()) {
            cout << "You lose. Cannibals outnumber missionaries on one side." << endl;
            break;
        }

        int missionaries, cannibals;
        cout << "Enter number of missionaries to move: ";
        cin >> missionaries;
        cout << "Enter number of cannibals to move: ";
        cin >> cannibals;

        bool toRight = game.isBoatOnLeft();  // Using the getter function to check the boat's position

        if (!game.move(missionaries, cannibals, toRight)) {
            cout << "Invalid move. Try again." << endl;
        }
    }

    return 0;
}
