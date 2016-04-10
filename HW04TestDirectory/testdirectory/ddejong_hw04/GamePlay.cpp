#include "GamePlay.h"
/******************************************************************************
 * 3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Homework 4 Gameplay class for a Dominos Game.  
 * Author/Copyright: Dion de Jong 
 * Date last modified: 10 October 2014
 * 
 * This program has functions that will create a dominos game. It has an
 * initialize and deal function that assign the user 12 random dominos out of
 * the possible 91 dominos in a domino game. It also has a function that 
 * recursively tests each possible starting value (0-11) and finds the longest 
 * possible chain for each starting value based on the dominos in your hand.
 *
 *
 * Output: An output file for the solved longest chains.  
**/


/******************************************************************************
 * Constructor
**/
GamePlay::GamePlay()
{
}

/******************************************************************************
 * Destructor
**/
GamePlay::~GamePlay()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'dealDominos'.
 * 
 * This function runs through the vector of all possible dominos and uses a 
 * random number generator to randomly select 12 values (or dominos) from that 
 * vector to assign to the users vector (or hand) 
 * 
 * Parameters:
   outStream - the output stream to which to write what happens in the function
 * seed - the value the srand() function will take in to allow the creation of 
          the same random values, so that the code can be tested eas::logStream << ly. 
 * Returns: none
**/

void GamePlay::dealDominos(ofstream& outStream, int seed)
{

  #ifdef EBUG
    Utils::logStream << "enter dealDominos\n";
  #endif
 
  //outstream the random numbers generated for testing purposes
  srand(seed);
  for(int i = 0; i < 10; ++i)
  {
    outStream << "random " << rand() << endl;
  }
  
  //recall the seed to get the same numbers
  srand(seed); 
  int domsDealt = 0;
  int xRan = -1; 
 
  //as long as you haven't assigned 12 dominos add more 
  while(myDominos.size() != 12)
  { 
    //Use %91 to get a random number that is 0-90 (which accesses
    //the 91 random dominos due to the subscript of 0 in the vector)
    xRan = rand()%91; 
     
    //test if you have previously assigned the current random domino
    //(since you can't use the same domino twice) 
    if(allDominos[xRan].wasDealt() == false)
    {
      allDominos[xRan].setDealt(true);
      myDominos.push_back(allDominos[xRan]); 
      domsDealt += 1;  
      //cout << "\n";
      //cout << xRan;
      //cout << "\n";
      //cout << domRan.toString();
    }
  } 
  string label = "";

  //cout << myDominos.size();
  outStream <<  "MY HAND ";
  for(unsigned int i = 0; i < myDominos.size(); ++i)
  { 
    outStream << myDominos[i].toString();  
  }
  outStream <<  "\n";    

  #ifdef EBUG
    Utils::logStream << "leave dealDominos\n"; 
  #endif
}

/******************************************************************************
 * Function 'extendSeq'.
 * This function extends the seq from the start number. It is a recursive function
 * it tests if there is a domino that is not yet played that matches the 
 * right side of the current Domino. If it does, it calls itself and tests that 
 * Domino, only returning out of the recursion if we run through the remaining 
 * domino and none match. When we return, we pop off the last domino, and test 
 * through the remaining dominos in the hand at that level of the recursion.  
 * 
 * Parameters:
 * from - The number to be matched from unplayed Dominos, this is the right side
 *        of the last domino in the sequence.    
 * seq - the current sequence of played dominos (or the remaining unplayed Dominos) 
 * level - the level of recursion on entry to this function
 * outStream - the output stream to which to write
 * 
 * Returns: none
 *
 * Output: Each new maximum sequence found
**/
void GamePlay::extendSeq(int from, const vector<Domino>& seq, int level,
                         ofstream& outStream)
{
  #ifdef EBUG
    Utils::logStream << "enter extendSeq\n";
  #endif
 
  //this is a failsafe test to prevent infinite recursion. 
  //if we have gone through the recursion more than 12 times, we break. 
  //keep in mind that max length was initialized at 12, since that is 
  //the longest possible chain we can make. 
  if(level > maxLength)
  {
    return; 
  }

  //test through all the Dominos in your hand. 
  for (unsigned int i = 0; i < myDominos.size(); i++)
  {
    //if a domino in the hand has a matching value to the right side of the last domino
    //and if it hasn't been played, we have a match and extend the sequence.
    if(myDominos[i].getLeft() == from && myDominos[i].hasBeenPlayed() != true)
    {
      myDominos[i].setPlayed(true);
      mySeq.push_back(myDominos[i]); 
     
      //we should test if the new sequence with the new addition is bigger than the max
      //sequence. If it is, make the current sequence the new max sequence. 
      if (mySeq.size() >= maxSeq.size())
      {
        maxSeq.clear();
        for (unsigned int m = 0; m < mySeq.size(); ++m)
        {
          maxSeq.push_back(mySeq[m]);
        }
        outStream << toStringSeq("NEW MAX", maxSeq);
      }
      
      //increment level to indicate we are about to jump another level in the recursion 
      level++; 
      //now we are ready to jump to the next level of recursion to test on the next 
      //value in the sequence. 
      extendSeq(mySeq.back().getRight(), myDominos, level, outStream); 
      //after returning from that recursive jump, pop off the last domino to continue
      //testing other possible dominos for this chain at this level of recursion. 
      mySeq.pop_back();        
      myDominos[i].setPlayed(false);
    }
    
    //the else if has the same exact rules for matching, except for it tests the left
    //sides of all the dominos in the hand, and flips the domino if that side matches
    //the right side of the last domino in the sequence. 
    else if (myDominos[i].getRight() == from && myDominos[i].hasBeenPlayed() != true) 
    { 
      myDominos[i].flipEnds();
      myDominos[i].setPlayed(true);
      mySeq.push_back(myDominos[i]);
      if (mySeq.size() >= maxSeq.size())
      { 
        maxSeq.clear();
       
        for (unsigned int m = 0; m < mySeq.size(); ++m)
          {
            maxSeq.push_back(mySeq[m]);
          }
      
          outStream << toStringSeq("NEW MAX", maxSeq);
      }
      level++;
       
      extendSeq(mySeq.back().getRight(), myDominos, level, outStream);   
      mySeq.pop_back();
      myDominos[i].setPlayed(false);         
    }
  } 
  //reaching this point indicates no dominos matched the sequence at this
  //level, so we must return to the previous level of recursion and continue
  //testing there. 
  return;
 
  #ifdef EBUG
    Utils::logStream << "leave extendSeq\n";
  #endif
}


/******************************************************************************
 * Function 'findLongestSeq'.
 * 
 * This function runs two for loops. The outer loop runs through each possible
 * starting number (0-11). The inner loop tests if any dominos in the hand
 * match this starting value and if they do, we start the recursive testing 
 * off this domino. 
 * 
 * Parameters:
 * outStream - the output stream to which to write
 *
 * Returns: none
 * 
 * Output: none 
**/
void GamePlay::findLongestSeq(ofstream& outStream)
{
  #ifdef EBUG
    Utils::logStream << "enter findLongestSeq\n";
  #endif
  
  for( int i = 0; i < 13 ; ++i)
  {
    outStream <<  "startNum ";
    outStream <<  i; 
    outStream <<  "\n"; 
    for (unsigned int j = 0; j < myDominos.size(); ++j)
    {
      //if a Domino in the hand matches the starting value
      if (myDominos[j].getLeft() == i)
      { 
        //we know that at this point there should be a clear myseq
        mySeq.clear(); 
        //the domino that matches should be pushed into my seq so that 
        //we can recursively test it. 
        myDominos[j].setPlayed(true);
        mySeq.push_back(myDominos[j]); 
        //for output, add the starting domino to the outstream
        if(maxSeq.size() <= 1)
        {
          outStream << toStringSeq("NEW MAX", mySeq);
        }    
 
        extendSeq(mySeq.back().getRight(), myDominos, 0, outStream); 
        //after returning from the recursion, we want to pop off the first
        //domino in case any other dominos match this loops value. 
        mySeq.pop_back();
        myDominos[j].setPlayed(false);
      }
     
      //the same rules apply to the if else statement, except we need 
      //to test the right side of the remaining dominos and flip them 
      //if they match. 
      else if (myDominos[j].getRight() == i) 
      {
        mySeq.clear();
        myDominos[j].flipEnds();
        myDominos[j].setPlayed(true);
        mySeq.push_back(myDominos[j]);

        if(maxSeq.size() <= 1)
        {
          outStream << toStringSeq("NEW MAX", mySeq);
        }

        extendSeq(mySeq.back().getRight(), myDominos, 0, outStream);
        mySeq.pop_back();
        myDominos[j].setPlayed(false);
      }     
    }
    //we need to clear maxSeq AFTER the inner loop to be able to output
    //max sequences for starting numbers that match multiple dominos. 
    outStream << toStringSeq("MAX SEQ FOR" + Utils::Format(i) , maxSeq);
    outStream << "\n"; 
    maxSeq.clear();   
  } 

  #ifdef EBUG
    Utils::logStream << "leave findLongestSeq\n";
  #endif

}

/******************************************************************************
 * Function 'initialize'.
 * This function creates all 91 possible Dominos within a game and pushes
 * them into a vector.  
 * 
 * Parameters: none
 * Returns : None
 * Output: none
**/
void GamePlay::initialize()
{
  #ifdef EBUG
    Utils::logStream << "enter initialize\n";
  #endif
 
  //declare the failsafe int to prevent infinite recursion 
  maxLength = 12; 

  //running two loops to account for all possible values of dominos
  for(int i = 0; i <= 12; ++i)
  {
    //set j = i to prevent duplicate dominos that were created in earlier
    //iterations of the outer loop. 
    for (int j = i; j <= 12; ++j)
    {
      //push each of these created dominos to the allDominos vector.
      Domino tempDomino(i,j);
      tempDomino.setLeft(i); 
      tempDomino.setRight(j);
      tempDomino.setPlayed(false);
      tempDomino.setDealt(false);  
      allDominos.push_back(tempDomino); 
    } 
  } 
// cout << allDominos.size(); 

  #ifdef EBUG
    Utils::logStream << "leave initialize\n";
  #endif
}

/******************************************************************************
 * Function 'toString'.
 * This function dumps the 'vector' of data to a 'string' and returns it.
 *
 * Parameters: none
 * 
 * Returns:
 * the 'toString' of the data in the class
 *
 * Output: Some log data
 *
**/
string GamePlay::toString() const
{
  string s = ""; 
#ifdef EBUG
  Utils::logStream << "enter toString\n";
#endif

#ifdef EBUG
  Utils::logStream << "leave toString\n";
#endif
  return s;
}

/******************************************************************************
 * Function 'toStringSeq'.
 * This function dumps the 'mySeq' data to a 'string' and returns it.
 * 
 * Parameters: 
 * label - the title of the function being sent toString
 * theSeq - the sequence to be converted to String
 * 
 * Returns:
 *   the 'toString' of the 'vector' of dominoes
 * 
 * Output: Some log data. 
**/
string GamePlay::toStringSeq(string label, const vector<Domino>& theSeq) const
{ 
  #ifdef EBUG
    Utils::logStream << "enter toStringSeq\n";
  #endif
  label = Utils::Format(label, 16); 
  string s = "";
  s += label; 
  s += "              :   (  ";
  s += Utils::Format(theSeq.size()); 
  s += ")  :  ";

  for (unsigned int i = 0; i < theSeq.size(); ++i)
  {
    s += theSeq[i].toString(); 
  } 
  s += "\n"; 

  #ifdef EBUG
    Utils::logStream << "leave toStringSeq\n";
  #endif
 
   return s;
}

