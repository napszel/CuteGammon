#ifndef DOUBLEDICE_H
#define DOUBLEDICE_H
#include <QObject>
#include "clickablelabel.h"

class DoubleDice : public ClickableLabel
{
  Q_OBJECT

public:
  DoubleDice(QWidget * parent = 0);
  void setNumber(const int num);
  int getNumber() const;
  void changeStyle(const char codeletter);
private slots:
  void numberDouble();
private:
  int number;
  char style;
};

#endif
