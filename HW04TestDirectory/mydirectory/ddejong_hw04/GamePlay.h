/****************************************************************
 * Header file for the class to find sequences in a domino game.
 *
 * Author/copyright:  Dion de Jong
 * Date: 27 September 2014
 *
**/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
using namespace std;

#include "Domino.h"

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class GamePlay
{
public:
  GamePlay();
  virtual ~GamePlay();

  void dealDominos(ofstream& outStream, int seed);
  void initialize();
  void findLongestSeq(ofstream& outStream);
  string toString() const;
  string toStringSeq(string label, const vector<Domino>& theSeq) const;

private:
  int maxLength;

  vector<Domino> allDominos;
  vector<Domino> myDominos;
  vector<Domino> maxSeq;
  vector<Domino> mySeq;

  void extendSeq(int from, const vector<Domino>& seq,
                 int level, ofstream& outStream);
};

#endif
