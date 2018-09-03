// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

/*  Game Class
 *  ----------
 *  Holds information associated with a particular game.
 *  
 *  Constructor(s):
 *
 *  * Game(string name) - 'name' is the name of this game.
 *  
 *  Accessor Methods:
 *  
 *  * string name() - returns the name of this game.
 *  * Victory victoryWithID(int id) - where 'id' is a valid id 
 *    for a Victory object associated with this game; returns
 *    the victory object associated with this id.
 *  * vector<Victory> victories() - returns list of all
 *    Victory objects associated with this game.
 *  * vector<int> victoryIDs() - returns list of victory ids
 *    associated with victories of this game.
 *
 *  Mutator Methods:
 *
 *  * void addVictory(int id, Victory victory) - adds new victory
 *    to this game and associates it with the provided id.
 */

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <map>
#include "Victory.h"

class Game {
public:

	// Constructors:

	Game();
	Game(std::string);

	// Accessor Methods:

	std::string name() const { return _name; }
	Victory victoryWithID(int) const;
	std::vector<Victory> victories() const;
	std::vector<int> victoryIDs() const;

	// Mutator Methods
	
	void addVictory(int, Victory);
private:
	std::string _name;
	std::map<int, Victory> _victories;
};

#endif