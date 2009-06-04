#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QObject>
#include <QLabel>
#include <QString>

class ClickableLabel : public QLabel
{
  Q_OBJECT

public:
  ClickableLabel(QWidget * parent = 0);
  void mousePressEvent(QMouseEvent * event);
  void setPicture(QString picturefile);
signals:
  void clicked();
};
#endif
