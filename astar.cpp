#include <algorithm> // std::sort
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <sstream>   // std::istringstream
#include <string>    // std::string
#include <vector>    // std::vector
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

// Defined above, can't define it again else it throws an error
enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kGoal };

std::string CellString(const State &state) {
  switch (state) {
  case State::kEmpty:
    return "0 ";
    break;
  case State::kStart:
    return "🚦 ";
    break;
  case State::kGoal:
    return "🏁";
    break;
  case State::kObstacle:
    return "⛰️ ";
    break;
  case State::kClosed:
    return "x ";
    break;
  case State::kPath:
    return "🚗";
    break;
  default:
    std::cout << "Unknown State\n";
    throw std::runtime_error("Unknown State");
  }
}

void PrintBoard(const std::vector<std::vector<State>> board) {
  for (std::vector<State> row : board) {
    for (State state : row) {
      std::cout << CellString(state) << " ";
    }
    std::cout << "\n";
  }
}

std::vector<State> ParseLine(const std::string &line) {
  std::vector<State> v;
  std::istringstream str_stream(line);

  int num;
  char comma;
  while (str_stream >> num >> comma && comma == ',') {
    v.push_back(State(num));
  }
  return v;
}

// auto refers to std::vector<std::vector<State>>
// have to use auto, else an error is thrown due to xeus-cling
auto ReadBoardFile(const std::string &path) {
  std::ifstream board_file(path);
  std::vector<std::vector<State>> board;
  if (board_file) {
    std::string line;
    while (getline(board_file, line)) {
      board.push_back(ParseLine(line));
    }
    return board;
  } else {
    throw std::runtime_error("File stream failed.");
  }
}

int Heuristic(const int p_x, const int p_y, const int q_x, const int q_y) {
  // Calculate the manhattan distance
  return abs(p_x - q_x) + abs(p_y - q_y);
}

void AddToOpen(int x, int y, int g, int h,
               std::vector<std::vector<int>> &openlist,
               std::vector<std::vector<State>> &board) {
  std::vector<int> node = {x, y, g, h};
  openlist.push_back(node);
  board[x][y] = State::kClosed;
  bool same = board[x][y] != State::kEmpty;
}

// Helper function for CellSort
bool Compare(std::vector<int> node1, std::vector<int> node2) {
  // A node has these values: {x, y, g, h}
  int f1 = node1[2] + node1[3];
  int f2 = node2[2] + node2[3];
  return f1 > f2;
}

void CellSort(std::vector<std::vector<int>> &openlist) {
  std::sort(openlist.begin(), openlist.end(), Compare);
}

bool CheckValidCell(std::vector<std::vector<State>> board, int node[2]) {
  int x = node[0];
  int y = node[1];
  if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size() ||
      board[x][y] != State::kEmpty) {
    return false;
  }
  return true;
}

void ExpandNeighbors(int x, int y, int g, const int goal[2],
                     std::vector<std::vector<int>> &openlist,
                     std::vector<std::vector<State>> &board) {
  g = g + 1;
  int h;

  // Four vectors for getting the nodes that are up, left, right,
  // and below current node
  std::vector<std::vector<int>> delta = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  int node[2];

  for (std::vector<int> d : delta) {
    node[0] = x + d[0];
    node[1] = y + d[1];
    h = Heuristic(node[0], node[1], goal[0], goal[1]);
    if (CheckValidCell(board, node)) {
      AddToOpen(node[0], node[1], g, h, openlist, board);
    }
  }
}

// auto refers to std::vector<std::vector<State>>
// have to use auto, else an error is thrown due to xeus-cling
auto Search(std::vector<std::vector<State>> &board, int start[2], int goal[2]) {
  std::vector<std::vector<int>> openlist{};
  int x = start[0];
  int y = start[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  AddToOpen(x, y, g, h, openlist, board);

  std::vector<int> current_node;
  while (!openlist.empty()) {
    CellSort(openlist);
    current_node = openlist.back();
    openlist.pop_back();

    x = current_node[0];
    y = current_node[1];
    g = current_node[2];
    board[x][y] = State::kPath;

    if (x == goal[0] && y == goal[1]) {
      board[start[0]][start[1]] = State::kStart;
      board[goal[0]][goal[1]] = State::kGoal;
      return board;
    }
    ExpandNeighbors(x, y, g, goal, openlist, board);
  }
  return board;
}

int main() {
  int start[2]{0, 0};
  int goal[2]{4, 5};
  std::vector<std::vector<State>> board = ReadBoardFile("files/1.board");
  std::cout << '\n';
  std::cout << "The original board: \n";
  std::cout << '\n';
  PrintBoard(board);
  std::vector<std::vector<State>> solution = Search(board, start, goal);
  std::cout << '\n';
  std::cout << "With A* performced: \n";
  std::cout << '\n';
  PrintBoard(solution);
  std::cout << '\n';
}
