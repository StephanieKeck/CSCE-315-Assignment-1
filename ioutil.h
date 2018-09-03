// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

/*  IOUTIL Utilities
 *  ----------------
 *  Various utility functions to assist with reading input and
 *  writing output.
 *  
 *  Input Utilities:
 *  
 *  * getCommand(begin, end, string& dest) - given string iterators denoting
 *    a range in a string, extracts a command word into dest.
 *  * getInt(begin, end, int& dest) - given string iterators denoting
 *    a range in a string, extracts an integer into dest.
 *  * getID(begin, end, int& dest) - given string iterators denoting
 *    a range in a string, extracts a valid id into dest.
 *  * getQuoteDelimitedString(begin, end, string& dest) - given string 
 *    iterators denoting a range in a string, extracts a quote
 *    delimited string into dest.
 *
 *  Output Utilities:
 *
 *  * void outputPlayerComparisonForGame - generates an output table comparing
 *    the stats of two or more players in a particular game; this function is
 *    overloaded.
 *  * void outputPlayerSummary - generates an output table of stats for one
 *    player.
 *  * void outputGameSummary - generates an output table of stats for one
 *    game.
 *  * void outputVictorySummary - generates an output table of stats for one
 *    victory.
 *  * outputPlayerComparison - generates output table comparing all players.
 */

#ifndef IOUTIL_H
#define IOUTIL_H

#include <string>
#include <ostream>
#include <vector>
#include "Player.h"
#include "Game.h"
#include "Victory.h"

// Input Utilities:

std::string::const_iterator getCommand(std::string::const_iterator, 
	std::string::const_iterator, std::string&);
std::string::const_iterator getInt(std::string::const_iterator, 
	std::string::const_iterator, int&);
inline std::string::const_iterator getID(std::string::const_iterator beg, 
	std::string::const_iterator end, int& n) { return getInt(beg, end, n); }
std::string::const_iterator getQuoteDelimitedString(std::string::const_iterator, 
	std::string::const_iterator, std::string&);

// Output Utilities:

void outputPlayerComparisonForGame(std::ostream& os, std::vector<Player> players, const Game& game, int game_id);
void outputPlayerComparisonForGame(std::ostream&, const Player&, const Player&, const Game&, int);
void outputPlayerComparisonForGame(std::ostream&, const Player&, std::vector<Player>, const Game&, int);
void outputPlayerSummary(std::ostream&, Player);
void outputGameSummary(std::ostream&, Game, int, std::vector<Player>);
void outputVictorySummary(std::ostream&, Victory, int, Game, int, std::vector<Player>);
void outputPlayerComparison(std::ostream&, std::vector<Player>);

#endif