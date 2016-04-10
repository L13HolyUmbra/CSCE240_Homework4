#include "Domino.h"

/******************************************************************************
 * 3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Domino' for a single domino. 
 * This class holds a constructor, accessors and mutators, a ToString and
 * other general functions for a Domino object. 
 *
 * Author/Copyright: Dion de Jong
 * Date last modified: 7 October 2014
**/

/******************************************************************************
 * Constructor
**/
Domino::Domino()
{
}

/******************************************************************************
 * Constructor with data supplied
**/
Domino::Domino(int left, int right)
{
}

/******************************************************************************
 * Destructor
**/
Domino::~Domino()
{
}

/******************************************************************************
 * Accessors and Mutators
 * 
**/

/****************************************************************
* Setter functions
*
* These will assign a chosen side of a Domino a chosen value
*
* Parameters:
* value- The value to be given to the chosen side of the Domino
*
* Output: None
*
* Returns: None
**/

void Domino::setLeft(int value)
{
  this->left = value; 
}

void Domino::setRight(int value)
{
  this->right = value; 
}

/****************************************************************
* Getter functions
*
* These will return a chosen side of a Domino's value
* 
* Parameters: None
*
* Output: None
*
* Returns: the value of a domino's chosen side
**/
int Domino::getLeft() const
{
  return this->left;
}

int Domino::getRight() const
{
  return this->right; 
}

/******************************************************************************
 * General functions.
**/

/****************************************************************
* Set functions
*
* These assign the dealt or Played value to a domino and assign
* a value for if the Domino has been given to the user or played
* in the game yet
* 
* Parameters:
* value - The boolean value for a domino was played or dealt
*
* Output: None
*
* Returns: None
**/

void Domino::setDealt(bool value)
{
  dealt = value; 
}

void Domino::setPlayed(bool value)
{
  played = value;
}

/****************************************************************
* Hasbeen/was functions
*
* These return the boolean value for if the Domino was dealt or
* Played tell us/the program if the Domino has been given to the 
* user or played in the game yet.
* 
* Parameters: none
*
* Output: None
*
* Returns: The boolean value for if a Domino was dealt or played.
**/


bool Domino::wasDealt() const
{
  return this->dealt; 
}

bool Domino::hasBeenPlayed() const
{
  return this->played; 
}

/****************************************************************
* flipEnds function
*
* This function flips the values of a dominos left and right 
* side. 
* 
* Parameters: none
*
* Output: None
*
* Returns: None
**/

void Domino::flipEnds() 
{
  int temp = this->right;
  this->right = this->left; 
  this->left = temp;
}
/******************************************************************************
 * Function 'toString'.
 * This returns the 'played' as well as the left and right numbers.
 * 
 * Parameters: none
 *  
 * Output: none
 *
 * Returns: The important values of the domino in String form. 
**/
string Domino::toString() const
{
  string s = "[ ";
  
  if (played)
  {
    s += " T ";
  }
 
  else
  {
    s += " F ";
  }

  s += Utils::Format(this->left, 3);
  s += Utils::Format(this->right, 3);

  s += " ]";

  return s;
}
