#include "doubledice.h"
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

DoubleDice::DoubleDice(QWidget * parent):
  ClickableLabel(parent)
{
  changeStyle('a');
  number = 4;
  move(453, 220);
  connect(this, SIGNAL(clicked()), this, SLOT(numberDouble()));
}

void DoubleDice::setNumber(const int num) {
  setPixmap(QString(":/images/d") + QString::number(num) + style + QString(".png"));
  number = num;
}

int DoubleDice::getNumber() const {
  return number;
}

void DoubleDice::numberDouble() {
  if (number < 64)
    number *= 2;
  else
    number = 2;
  setNumber(number);
}

void DoubleDice::changeStyle(const char codeletter) {
  style = codeletter;
  setNumber(getNumber());
}
