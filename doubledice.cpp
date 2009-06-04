#include "doubledice.h"
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

DoubleDice::DoubleDice(QWidget * parent):
  ClickableLabel(parent)
{
  style = 'a';
  changeStyle('a');
  number = 64;
  move(435, 220);
  connect(this, SIGNAL(clicked()), this, SLOT(numberDouble()));
}

void DoubleDice::setNumber(const int num){
  setPicture(QString(":/images/d") + QString::number(num) + style + QString(".png"));
  number = num;
}

int DoubleDice::getNumber() const {
  return number;
}

void DoubleDice::numberDouble() {
  if (number < 64)
    number += number;
  else
    number = 2;
  setNumber(number);
}


void DoubleDice::changeStyle(const char codeletter)
{
  style = codeletter;
  setNumber(getNumber());
}
