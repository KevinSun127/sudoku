#ifndef SUDOKU_H
#define SUDOKU_H


class Board {
public:
  Board();
  Board(std::istream& istr);
  ~Board();
  bool solve(int );
private:
  int** board_;

};

#endif
