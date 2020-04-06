#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

void printBoard(int**& board, int&n)
{

  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < n; ++j)
    {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

bool isValid(int**& board, int& n, int& r,  int& c)
{
  int num = board[r][c];
  if(!(num > 0 && num < 10))
  {
    return false;
  }
  for(int i = 0; i < n; ++i)
  {
    if(i != r)
    {
      if(num == board[i][c])
      {
        return false;
      }
    }
  }
  for(int j = 0; j < n; ++j)
  {
    if(j != c)
    {
      if(num == board[r][j])
      {
        return false;
      }
    }
  }
  for(int i = r - r%3; i < r - r%3 + 3; ++i)
  {
    for(int j = c - c%3; j < c - c%3 + 3; ++j)
    {
      if(i != r && j != c && board[i][j] == num)
      {
        return false;
      }
    }
  }
  return true;
}


bool checkCompleted(int** board, int& n)
{
  for(int i = 0; i < n; ++i)
  {
    for(int j = 0; j < n; ++j)
    {
      if(!isValid(board, n, i, j))
      {
        return false;
      }
    }
  }
  return true;
}


bool solver(int** board, int& n, int r, int c)
{
  //if you find the solution, print
  if(r >= n)
  {
    if(checkCompleted(board, n))
    {
      printBoard(board, n);
      return true;
    }
    return false;
  }

  if(board[r][c] != -1)
  {
    bool status;
    if(c < n - 1)
    {
      status = solver(board, n, r, c+1);
    }
    else
    {
      status = solver(board, n, r + 1, 0);
    }
    if(status)
    {
      return true;
    }
    return false;
  }

  for(int i = 1; i < 10; ++i)
  {
    // place every single possible value in this
    board[r][c] = i;

    if(isValid(board, n, r, c))
    {
      bool status;
      if(c < n - 1)
      {
        status = solver(board, n, r, c+1);
      }
      else
      {
        status = solver(board, n, r + 1, 0);
      }
      if(status)
      {
        return true;
      }
    }
    board[r][c] = -1;
    // try next row and column
  }
  return false;
}


int main(int argc, char** argv)
{
  if(argc < 3)
  {
    cout << "Need input and output file." << endl;
    return 1;
  }

  ifstream ifile(argv[1]);
  int n;
  ifile >> n;

  int** board = new int*[n];
  for(int i = 0; i < n; ++i)
  {
    board[i] = new int[n];
    for(int j = 0; j < n; ++j)
    {
      char c;
      ifile >> c;
      if(c == '*')
      {
        board[i][j] = -1;
      }
      else
      {
        board[i][j] = c - 48;
      }
    }
  }

  if(!solver(board, n, 0, 0))
  {
    cout << "No Solution!" << endl;
  }
  else
  {
    ofstream ofile(argv[2]);
    for(int i = 0; i < n; ++i)
    {
      for(int j = 0; j < n; ++j)
      {
        ofile << board[i][j] << " ";
      }
      ofile << endl;
    }
  }

  for(int i = 0; i < n; ++i)
  {
    delete[] board[i];
  }
  delete[] board;

  return 0;
}
