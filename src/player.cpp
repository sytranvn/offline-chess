#include "player.h"

Player::Player(bool isWhite) : isWhite(isWhite){};
bool Player::IsWhite() const { return isWhite; }
