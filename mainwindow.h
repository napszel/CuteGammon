#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "board.h"

class QAction;
class QMenu;
class QMenuBar;

class MainWindow : public QMainWindow
{
  Q_OBJECT;

public:
  static const QString autosaveFilename;
  static const unsigned int width, height;
  MainWindow();
  char style;

private slots:
  void about();
  void newGame();
  void loadGame();
  void exit();
  void saveGame();
  void changeStyle();
  void changeBackStyle();
  void autoSaveGame();

private:
  void setBoard(Board * newBoard);

  QMenuBar * menuBar;
  QToolBar * toolBar;
  QStatusBar * statusBar;

  QMenu * fileMenu;
  QMenu * optionsMenu;
  QMenu * helpMenu;

  QAction * exitAction;
  QAction * aboutAction;
  QAction * newgame;
  QAction * savegame;
  QAction * loadgame;
  QAction * changeStyleAction;
  QAction * changeStyleAction2;

  QAction * newgamebar;
  QAction * savegamebar;
  QAction * loadgamebar;

  QTimer * autosaveTimer;
  Board * board;
};

#endif
