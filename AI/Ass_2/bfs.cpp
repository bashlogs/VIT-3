#include <iostream> 
#include <set> 
#include <vector> 
using namespace std; 
 
struct State { 
    vector<vector<int>> board; 
    int rows, cols; 
    static const vector<vector<int>> goal; 
 
    State(vector<vector<int>>& b, int zRow, int zCol) : board(b), rows(zRow), cols(zCol) 
{} 
 
    bool isGoal() const { 
        return board == goal; 
    } 
 
    // Function to generate successor states 
    vector<State> successors() const { 
        static const int dr[] = {-1, 1, 0, 0}; // Up, Down, Left, Right 
        static const int dc[] = {0, 0, -1, 1}; 
        vector<State> succ; 
        for (int d = 0; d < 4; ++d) { 
            int newRow = rows + dr[d]; 
            int newCol = cols + dc[d]; 
            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) { 
                vector<vector<int>> newBoard = board; 
                swap(newBoard[rows][cols], newBoard[newRow][newCol]); 
                succ.emplace_back(newBoard, newRow, newCol); 
            } 
        } 
        return succ; 
    } 
}; 
 
const vector<vector<int>> State::goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}; 
 
bool dfs(State currentState, set<vector<vector<int>>>& visited, int depth) { 
    if (currentState.isGoal()) { 
        cout << "Goal state reached!" << endl; 
        return true; 
    } 
 
    visited.insert(currentState.board); 
 
    for (const State& nextState : currentState.successors()) { 
        if (visited.find(nextState.board) == visited.end()) { 
            cout << "Depth Level: " << depth << endl; 
            cout << "Next state:" << endl; 
            for (const auto& row : nextState.board) { 
                for (int val : row) { 
                    cout << val << " "; 
                } 
                cout << endl; 
            } 
            cout << "-----------------" << endl; 
            if (dfs(nextState, visited, depth + 1)) 
                return true; 
        } 
    } 
 
    return false; 
} 
 
int main() { 
    vector<vector<int>> board = {{1, 2, 3}, {4, 0, 6}, {7, 5, 8}};  
    int rows = 1, cols = 1;  
    State initialState(board, rows, cols); 
    cout << "Initial state:" << endl; 
    for (const auto& row : board) { 
        for (int val : row) { 
            cout << val << " "; 
        } 
        cout << endl; 
    } 
    cout << "-----------------" << endl; 
 
    cout << "Goal state:" << endl; 
    for (const auto& row : State::goal) { 
        for (int val : row) { 
            cout << val << " "; 
        } 
        cout << endl; 
    } 
    cout << "\n------Start------\n" << endl; 
 
    set<vector<vector<int>>> visited; 
    if (!dfs(initialState, visited, 1)) 
        cout << "No solution found!" << endl; 
 
    return 0; 
} 