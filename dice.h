#ifndef DICE_H
#define DICE_H
#include <QObject>
#include "spot.h"
#include "clickablelabel.h"

class Dice : public ClickableLabel
{
  Q_OBJECT

public:
  enum Where{TOP,BOTTOM};
  Dice(int num, Where where, QWidget * parent = 0);
  void changeStyle(const char codeletter);
protected:
  unsigned int number;
  Spot *spots[8];
public slots:
  void roll() const;
  void setNumber(const int number) const;
};
#endif
