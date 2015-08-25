#include "dice.h"
#include "diceanimation.h"
#include "spot.h"
#include <QDebug>
#include <QMouseEvent>
#include <QLabel>
#include <QTimer>

Dice::Dice(int num, Where where, QWidget * parent):
  ClickableLabel(parent),
  number(num)
{
  setPixmap(QPixmap(":/images/dicea.png"));
  if (where == TOP) move(453,281);
  else move(453,331);

  for (int i=0; i<8; ++i){
    spots[i] = new Spot(i+1, this);
  }

  setNumber(number);
}

void Dice::setNumber(const int number) const {
  for (int i=0; i<8; ++i)
    spots[i]->hide();

  QList<int> showThese;
  switch (number){
  case 1:
    showThese << 0;
    break;
  case 2:
    showThese << 3 << 4;
    break;
  case 3:
    showThese << 0 << 3 << 4;
    break;
  case 4:
    showThese << 1 << 3 << 4 << 6;
    break;
  case 5:
    showThese << 0 << 1 << 3 << 4 << 6;
    break;
  case 6:
    showThese << 1 << 2 << 3 << 4 << 5 << 6;
    break;
  }
  foreach (int showThis, showThese)
    spots[showThis]->show();
}

void Dice::roll() const {
  setNumber(((int)(drand48()*6))+1);
}

void Dice::changeStyle(const char codeletter) {
  setPixmap(QString(":/images/dice") + codeletter + QString(".png"));
  for (int i=0; i<8; ++i){
    spots[i]->changeStyle(codeletter);
  }
}

