#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
  bool isWhite;

public:
  Player(bool isWhite);
  bool IsWhite() const;
};

#endif // PLAYER_H
