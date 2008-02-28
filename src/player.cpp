#include "player.h"
#include "itemtypes.h"

Player::Player(QGraphicsItem *parent) 
	: QGraphicsEllipseItem(parent)
{
  setRect(0, 0, 45, 45);
  setBrush(QBrush(Qt::red));
  xspeed = 0;
  yspeed = 0;

  up_key = Qt::Key_unknown;
  down_key = Qt::Key_unknown;
  right_key = Qt::Key_unknown;
  left_key = Qt::Key_unknown;
  
  up_pressed = false;
  down_pressed = false;
  left_pressed = false;
  right_pressed = false;
}

int Player::type() const
{
  return PlayerType;
}
