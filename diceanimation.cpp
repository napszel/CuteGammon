#include <QTimer>
#include <QObject>
#include <QList>
#include <QDebug>
#include "dice.h"
#include "diceanimation.h"

DiceAnimation::DiceAnimation(QWidget * parent):
  QObject(parent),
  count(0)
{
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(oneStepOfAnimation()));
}

void DiceAnimation::startDiceAnimation() {
  timer->start(100);
  count = 0;
}

void DiceAnimation::addDice(Dice * dice) {
  dices.append(dice);
  connect(dice, SIGNAL(clicked()), this, SLOT(startDiceAnimation()));
}

void DiceAnimation::oneStepOfAnimation() {
  ++count;
  foreach (Dice * dice, dices) {
    dice->roll();
  }
  if (count == 15) timer->stop();
}
