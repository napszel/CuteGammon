#ifndef SPOT_H
#define SPOT_H
#include <QObject>
#include <QLabel>

class Spot : public QLabel
{
  Q_OBJECT

public:
  explicit Spot(int num, QWidget * parent = 0);
  void changeStyle(const char codeletter);
};

#endif
