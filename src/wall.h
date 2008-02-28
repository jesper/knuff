#ifndef WALL_H
#define WALL_H

#include <QGraphicsPathItem>
#include "itemtypes.h"

class Wall : public QGraphicsPathItem
{
public:
  Wall(QGraphicsItem *parent=0);
  int type() const;
};
#endif
