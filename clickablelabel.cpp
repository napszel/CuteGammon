#include "clickablelabel.h"
#include <QMouseEvent>
#include <QLabel>

ClickableLabel::ClickableLabel(QWidget * parent):
  QLabel(parent)
{
}

void ClickableLabel::mousePressEvent(QMouseEvent * /*event*/)
{
  emit clicked();
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent * /*event*/)
{
  emit doubleClicked(this);
}

