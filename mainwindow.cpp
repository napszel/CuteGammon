#include <QtGui>
#include "board.h"
#include "mainwindow.h"
#include <stdio.h>
#include <QDebug>
#include <QToolBar>
#include <QMenu>
#include <QStatusBar>
#include <QPalette>
#include <QIcon>
#include <QString>
#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>
#include <QMenuBar>
#include <clickablelabel.h>
#include "lineedit.h"
#include <sstream>
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

const QString MainWindow::autosaveFilename("/Users/napszel/.autosave.bgm");

const unsigned int MainWindow::width = 1050;
const unsigned int MainWindow::height = 715;

const QColor lightGreen = QColor(170,230,170);
const QColor lightGrey = QColor(170,196,170);

MainWindow::MainWindow() : board(0), style('a') {
  setFixedSize(width, height);

/* MENU + TOOLBAR */
  QMenuBar *menuBar = new QMenuBar(this);
  QToolBar *toolBar = new QToolBar(this);
  toolBar->setMovable(false);

  QMenu *fileMenu = new QMenu("&File", this); {
    QAction *newGameAction = fileMenu->addAction(QIcon(":/images/new.png"), "&New", this, SLOT(newGame()));
    toolBar->addAction(newGameAction);

    QAction *loadGameAction = fileMenu->addAction(QIcon(":/images/open.png"), "&Open", this, SLOT(loadGame()));
    toolBar->addAction(loadGameAction);

    saveGameAction = fileMenu->addAction(QIcon(":/images/save.png"), "&Save"); /* connection set in setBoard()*/
    toolBar->addAction(saveGameAction);

    fileMenu->addAction(QIcon(":/images/exit.png"), "E&xit", this, SLOT(close()));
  }

  QMenu *optionsMenu = new QMenu("&Options", this); {
    optionsMenu->addAction(QIcon(":/images/funny.png"), "change style", this, SLOT(changeStyle()));
  }

  QMenu *helpMenu = new QMenu("&Help", this); {
    helpMenu->addAction(QIcon(":/images/about.png"), "About", this, SLOT(about()));
  }

  menuBar->addMenu(fileMenu);
  menuBar->addMenu(optionsMenu);
  menuBar->addMenu(helpMenu);

  setMenuBar(menuBar);
  addToolBar(toolBar);
/* MENU END */

/* STATUS BAR */
  QStatusBar *statusBar = new QStatusBar(this);
  setStatusBar(statusBar);
  statusBar->setSizeGripEnabled(false);
  statusBar->showMessage("Ready",60000);
/* STATUS BAR END */

/* PLAYER'S NAMES */

  playerOneName = new LineEdit("Player one",this);
  playerOneName -> move(901,120);
  playerOneName -> changeColor(lightGrey);

  playerTwoName = new LineEdit("Player two",this);
  playerTwoName -> move(901,640);
  playerTwoName -> changeColor(lightGrey);

/* PLAYER'S NAMES END */

/*Message*/
  message = new QLabel(this);
  message -> move(905, 385);
  message -> setText("Click dice for \ninicial roll.");
  message -> show();

  setWindowTitle(tr("Backgammon by Napszel"));
  Board * loadBoard;
  if (Board::loadFromFile(MainWindow::autosaveFilename, loadBoard)) {
    setBoard(loadBoard);
    readMessagesFromFile(autosaveFilename);
  } else
    newGame();
  board->changeStyle(style);

  autosaveTimer = new QTimer(this);
  connect(autosaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveGame()));
  autosaveTimer->start(60000);   //auto save every 1 minute
}

void MainWindow::setBoard(Board * newBoard) {
  delete board;
  board = newBoard;
  setCentralWidget(board);
  board->setParent(this);
  connect(saveGameAction, SIGNAL(triggered()), this, SLOT(saveGame()));
  board->changeStyle(style);
}

void MainWindow::newGame() {
  setBoard(new Board(this));
}

void MainWindow::loadGame() {
  QString fileName = QFileDialog::getOpenFileName(this, "Load game",
						  "/Users/napszel/mybackgammongame.bgm",
						  "Backgammon games (*.bgm);;All files (*)");
  if (!fileName.isEmpty()) {
    Board * loadedBoard = 0;
    if (Board::loadFromFile(fileName, loadedBoard)) {
      setBoard(loadedBoard);
      readMessagesFromFile(fileName);
    }
    else QMessageBox::warning(this, "Bad file", "Can't open this file.");
  }
}

void MainWindow::saveGame() {
  QString fileName = QFileDialog::getSaveFileName(this, "Save game",
						  "/Users/napszel/mybackgammongame.bgm",
						  "Backgammon games (*.bgm);;All files (*)");
  if (!fileName.isEmpty()) {
    if (!fileName.endsWith(".bgm"))
      fileName += ".bgm";
    board->saveToFile(fileName);
    saveMessagesToFile(fileName);
  }
};

void MainWindow::about() {
  QMessageBox::information(this, "About", "Made by Szadeczky-Karodoss Eva with help from Risko Gergely \n2009");
}

void MainWindow::changeStyle() {
  if (style == 'g') {
    board->changeStyle('a');
    style = 'a';
  } else {
    board->changeStyle('g');
    style = 'g';
  }
}

void MainWindow::autoSaveGame() {
  qDebug() << "Autosave: " << autosaveFilename;
  board->saveToFile(autosaveFilename);
  saveMessagesToFile(autosaveFilename);
}

void MainWindow::saveMessagesToFile(QString filename) {
  std::ofstream savedfile;
  savedfile.open(filename.toUtf8().constData(), std::ios::out | std::ios::app);
  savedfile << (message -> text()).toUtf8().constData();
  savedfile.close();
}

void MainWindow::readMessagesFromFile(QString /*filename*/) {
//   std::ifstream savedfile;
//   std::string messageline;
//   savedfile.open(filename.toUtf8().constData());
//   savedfile.seekg(30);
//   getline(savedfile, messageline);
//   message -> setText(messageline.c_str());
//   savedfile.close();
}

