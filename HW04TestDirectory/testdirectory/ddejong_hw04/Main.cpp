#include "Main.h"

/****************************************************************
 * Main program for Homework 5.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Used by: Dion de Jong
 * Date: 9 September 2014
 *
**/

static const string TAG = "Main: ";

int main(int argc, char *argv[])
{
  int seed;
  string outFileName = "";
  string logFileName = "";
  ofstream outStream;

  GamePlay game;

  Utils::CheckArgs(2, argc, argv, "outfilename logfilename");
  outFileName = static_cast<string>(argv[1]);
  logFileName = static_cast<string>(argv[2]);

  Utils::LogFileOpen(logFileName);
  Utils::FileOpen(outStream, outFileName);

  Utils::logStream << TAG << "Beginning execution\n";
  Utils::logStream.flush();

  Utils::logStream << TAG << "outfile '" << outFileName << "'\n";
  Utils::logStream << TAG << "logfile '" << logFileName << "'\n";

  cin >> seed;
  outStream << TAG << "RN seed is " << seed << endl << endl;

  game.initialize();
  game.dealDominos(outStream, seed);
  game.findLongestSeq(outStream);

  Utils::logStream << TAG << "Ending execution\n";
  Utils::logStream.flush();

  Utils::FileClose(outStream);
  Utils::FileClose(Utils::logStream);

  return 0;
}
