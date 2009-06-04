#include "board.h"
#include "point.h"
#include "dice.h"
#include "spot.h"
#include "diceanimation.h"
#include "doubledice.h"
#include <QtGui>
#include <QString>
#include <sstream>
#include <iostream>
#include <fstream>
#include <QIODevice>
#include <QDataStream>
#include <QLabel>
#include <QPalette>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QFileDialog>
#include <QFSFileEngine>
#include <QDir>


const unsigned int Board::noOfPoints = 24;
const unsigned int Board::noOfCheckers = 30;
const unsigned int Board::width = 900;
const unsigned int Board::height = 626;


Board::Board(QWidget * parent) : QWidget(parent) {
  setFixedSize(width, height);

  QPalette myPalette = palette();
  myPalette.setBrush(QPalette::Window, QBrush(QPixmap(":/images/backgrounda.png")));
  setPalette(myPalette);
  setAutoFillBackground(true);

/* POINTS */
  for (unsigned int i=0, line = 0; i<noOfPoints/2; ++i) {
    if ((i%2)!=0) {
      points[i] = new Point(Point::WHITE,Point::DOWN,this);
    } else 
      points[i] = new Point(Point::BLACK,Point::DOWN,this);
    if (i == noOfPoints*1/4) line = 70;
    points[i]->move(i*points[i]->scalex + line + 100, height/2 + 26);
  }

  for (unsigned int i=noOfPoints/2, j = 0, line = 0; i<noOfPoints; ++i, ++j) {
    if ((i%2)==0) {
      points[i] = new Point(Point::WHITE, Point::UP,this);
    } else points[i] = new Point(Point::BLACK, Point::UP,this);
    if (i == noOfPoints*3/4) line = 70;
    points[i]->move((j*points[i]->scalex) + line + 100, 57);
  }

  /* FINISH PLACE */
  points[24] = new Point(Point::BLACK, Point::END,this);
  points[24]->move(5, 54);
  points[25] = new Point(Point::WHITE, Point::END,this);
  points[25]->move(5, 335);
  points[26] = new Point(Point::WHITE, Point::END,this);
  points[26]->move(845, 54);
  points[27] = new Point(Point::BLACK, Point::END,this);
  points[27]->move(845, 335);
  /* FINISH PLACE END*/
/* POINTS END */

  createCheckers();

/* DICE */
  dice1 = new Dice(6, Dice::TOP, this);
  dice2 = new Dice(6, Dice::BOTTOM, this);
  diceanimation = new DiceAnimation(this);
  diceanimation->addDice(dice1);
  diceanimation->addDice(dice2);

  doubledice = new DoubleDice(this);
  doubledice->setNumber(64);
/* DICE */

  resetCheckers();

  stylecode = 'a';

  changeStyle(stylecode);
}

void Board::createCheckers() {
  for (unsigned int i=0; i<Board::noOfCheckers; ++i){
    if (i<=Board::noOfCheckers/2-1) 
      checkers[i] = new Checker(Checker::WHITE, this);
    else 
      checkers[i] = new Checker(Checker::BLACK, this);
  }
}

void Board::deleteCheckers(unsigned int num) {
  for (unsigned int i=0; i<num; ++i) {
    delete checkers[i];
  }
}

void Board::resetCheckers() {
/* CHECKERS */
  for (int i=0; i<5; ++i) points[0]->addChecker(checkers[i]);
  for (int i=5; i<7; ++i) points[11]->addChecker(checkers[i]);
  for (int i=7; i<10; ++i) points[16]->addChecker(checkers[i]);
  for (int i=10; i<15; ++i) points[18]->addChecker(checkers[i]);
  for (int i=15; i<18; ++i) points[4]->addChecker(checkers[i]);
  for (int i=18; i<23; ++i) points[6]->addChecker(checkers[i]);
  for (int i=23; i<28; ++i) points[12]->addChecker(checkers[i]);
  for (int i=28; i<30; ++i) points[23]->addChecker(checkers[i]);
/* CHECKERS END */
}

void Board::clearPoints() {
  for (unsigned int i=0; i<noOfPoints+4; ++i) {
    points[i]->clearCheckers();
  }
}

bool Board::validDoublediceNum(const int num) {
  return (num == 2 || num == 4 || num == 8 || num == 16 || num == 32 || num == 64);
}

bool Board::loadFromFile(const QString filename, Board* &retBoard) {
  bool error = false;
  retBoard = new Board;
  std::ifstream openedfile;
  openedfile.open(filename.toUtf8().constData());
  if (openedfile.is_open()) {
    std::string doubledicestr;
    int doubledicenum;
    bool ok;
    openedfile >> doubledicestr;
    doubledicenum = QString(doubledicestr.c_str()).toInt(&ok);
    int checker_count = 0;
    if ((ok) && (validDoublediceNum(doubledicenum))) {
      retBoard->doubledice->setNumber(doubledicenum);
      int nextChecker = 0;
      retBoard->clearPoints();
      retBoard->deleteCheckers(noOfCheckers);
      int error_at = 0;
      std::string nextPointstr;
      openedfile >> nextPointstr;
      while ((!openedfile.eof()) && (!error)) {
	error_at += 1;
	unsigned int nextPoint;
	unsigned int nextColor;
	unsigned int nextCount;
	std::string nextColorstr;
	std::string nextCountstr;

	nextPoint = QString(nextPointstr.c_str()).toInt(&ok);
	if ((ok) && (nextPoint<=noOfPoints+4)){

	  openedfile >> nextColorstr;
	  nextColor = QString(nextColorstr.c_str()).toInt(&ok);
	  if ((ok) && (nextColor<3)){

	    openedfile >> nextCountstr;
	    nextCount = QString(nextCountstr.c_str()).toInt(&ok);
	    if ((ok) && (nextCount<noOfCheckers)){

	      for (unsigned int j=0; j < nextCount; j++) {
		retBoard->checkers[nextChecker] = new Checker(nextColor, retBoard);
		checker_count+=1;
		retBoard->points[nextPoint]->addChecker(retBoard->checkers[nextChecker]);
		++nextChecker;
	      }
	    } else error = true;
	  } else error = true;
	} else error = true;
	openedfile >> nextPointstr;
      }
      openedfile.close();
      //        if (error) {
      //          QMessageBox::warning(this, "Error", "There is an error in the file at line " + QString::number(error_at));
      //          clearPoints();
      //          deleteCheckers(checker_count);
      //          createCheckers();
      //          resetCheckers();
      //        }
    } else error = true;// QMessageBox::warning(this, "Error", "The first line is wrong in the file.");
    openedfile.close();
  } else error = true;// QMessageBox::warning(this, "File not found", "Can't find this file.");
  return !error;
}

void Board::saveToFile(QString filename) const {
  std::ofstream savedfile;
  savedfile.open(filename.toUtf8().constData());
  savedfile << doubledice->getNumber() << "\n";
  for (unsigned int i=0; i<noOfPoints+4; ++i) {
    savedfile << i << " " << points[i]->checkersColor() << " " << points[i]->getCheckersNo() << "\n";
  }
  savedfile.close();
}

void Board::changeStyle(const char codeletter) {
  stylecode = codeletter;

  QPalette myPalette = palette();
  myPalette.setBrush(QPalette::Window, 
		     QBrush(QPixmap(QString(":/images/background") 
				    + codeletter 
				    + QString(".png"))));
  setPalette(myPalette);
  setAutoFillBackground(true);

  for (unsigned int i=0; i<noOfPoints+4; ++i) {
    points[i]->changeStyle(codeletter);
  }

  dice1->changeStyle(codeletter);
  dice2->changeStyle(codeletter);

  doubledice->changeStyle(codeletter);

  for (unsigned int i=0; i<Board::noOfCheckers; ++i) {
    checkers[i]->changeStyle(codeletter);
  }
}


