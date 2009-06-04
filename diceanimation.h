#ifndef ANIMATION_H
#define ANIMATION_H
#include <QList>
#include <QTimer>
#include <QObject>
#include "dice.h"

class DiceAnimation : public QObject
{
  Q_OBJECT;

private slots:
  void oneStepOfAnimation();
public slots:
  void startDiceAnimation();
public:
  DiceAnimation(QWidget * parent = 0);
  void addDice(Dice * dice);
private:
  QList<Dice*> dices;
  QTimer * timer;
  int count;
};

#endif
