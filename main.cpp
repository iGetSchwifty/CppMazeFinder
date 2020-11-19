#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator ==(const Point& obj) {
        return x == obj.x && y == obj.y;
    }
};

ostream& operator <<(ostream& out, const Point& obj) {
    out << "X: " << obj.x << " Y: " << obj.y << '\n';
    return out;
}

bool isValidPosition(vector<vector<int>>& maze,
                     vector<Point>& solution,
                     Point& pos) {
    // assuming M x N and not some weird sized maze
    if((pos.x >= 0 && pos.x < maze[0].size())
        && (pos.y >= 0 && pos.y < maze.size())
        && maze[pos.y][pos.x] == 0
        && find(solution.begin(), solution.end(), pos) == solution.end()) {
        return true;
    }
    return false;
}

bool DFS_Util(vector<vector<int>>& maze,
              vector<Point>& solution,
              Point source,
              const Point& target) {

    if(source == target) {
        solution.push_back(source);
        return true;
    }

    if(isValidPosition(maze, solution, source)) {
        solution.push_back(source);

        if(DFS_Util(maze, solution, Point(source.x, source.y - 1), target)) { // UP
            return true;
        }

        if(DFS_Util(maze, solution, Point(source.x + 1, source.y), target)) { // RIGHT
            return true;
        }

        if(DFS_Util(maze, solution, Point(source.x, source.y + 1), target)) { // DOWN
            return true;
        }

        if(DFS_Util(maze, solution, Point(source.x - 1, source.y), target)) { // LEFT
            return true;
        }

        solution.pop_back();
    }
    return false;
}

bool isEscapePossible(vector<vector<int>>& maze,
                      vector<Point>& solution,
                      Point source,
                      const Point& target) {
    return DFS_Util(maze, solution, source, target);
}

int main() {
    vector<vector<int>> maze = { 
        { 0, 0, 1, 0 },
        { 1, 0, 0, 1 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 }
    };

    vector<Point> solution;
    Point start = { 0, 0 };
    Point end = { 3, 3 };

    cout << "Attempt to solve the maze...\n";

    if(isEscapePossible(maze, solution, start, end)) {
         cout << "Found steps...\n";
        for(auto step : solution) {
            cout << step;
        }
    } else {
        cout << "Couldnt find a path to exit\n";
    }

    return 0;
}