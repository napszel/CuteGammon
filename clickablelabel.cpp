#include "clickablelabel.h"
#include <QMouseEvent>
#include <QLabel>

ClickableLabel::ClickableLabel(QWidget * parent):
  QLabel(parent)
{
}

void ClickableLabel::setPicture(QString picturefile)
{
  setPixmap(QPixmap(picturefile));
}

void ClickableLabel::mousePressEvent(QMouseEvent * /*event*/)
{
  emit clicked();
}

