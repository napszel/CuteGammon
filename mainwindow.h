#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "board.h"
#include "clickablelabel.h"
#include "lineedit.h"

class QAction;

class MainWindow : public QMainWindow
{
  Q_OBJECT;

public:
  MainWindow();

private slots:
  void about();
  void newGame();
  void loadGame();
  void saveGame();
  void changeStyle();
  void autoSaveGame();

private:
  void setBoard(Board * newBoard);

  static const QString autosaveFilename;
  static const unsigned int width, height;

  LineEdit * playerOneName;
  LineEdit * playerTwoName;
  QAction * saveGameAction;
  QTimer * autosaveTimer;
  Board * board;
  char style;
};

#endif
