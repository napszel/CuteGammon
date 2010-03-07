#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QTimer>
#include "checker.h"
#include "point.h"
#include "dice.h"
#include "diceanimation.h"
#include "doubledice.h"

class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QMenu;
class QMenuBar;
class QPushButton;
class QDragEnterEvent;
class QDropEvent;

class Board : public QWidget
{
  Q_OBJECT;

public:
  static const unsigned int noOfPoints, noOfFinishPlaces, noOfCheckers;
  static const unsigned int width, height;  //table's
  Board(QWidget *parent = 0);

  static bool loadFromFile(const QString filename, Board* &retBoard);
  void saveToFile(QString filename) const;

  void changeStyle(const char codeletter);

public slots:
  void placeKilledChecker(Checker * checkerHit);

private:
  void resetCheckers();
  void deleteCheckers(unsigned int num);
  void createCheckers();
  void clearPoints();

  static bool validDoublediceNum(const int num);

  QMenuBar * menuBar;

  Point * points[28];
  Checker * checkers[30];
  Dice * dice1;
  Dice * dice2;
  DoubleDice * doubledice;
  DiceAnimation * diceanimation;

  QGroupBox * gridGroupBox;
  QDialogButtonBox * buttonBox;

  QMenu * fileMenu;
  QMenu * optionsMenu;
  QMenu * helpMenu;

  QAction * exitAction;
  QAction * aboutAction;
  QAction * newgame;
  QAction * savegame;
  QAction * loadgame;

  char stylecode;
};

#endif
