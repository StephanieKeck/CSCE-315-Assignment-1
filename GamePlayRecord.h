// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

/*  GamePlayRecord Class
 *  --------------------
 *  Holds information relating a player to a single game, including
 *  username, victories earned, and point totals.
 *  
 *  Constructor(s):
 *
 *  * GamePlayRecord(Game game, string ign) - 'game' is a Game object
 *    referring to a particular game, and 'ign' is the player's
 *    username in that game.
 *  
 *  Accessor Methods:
 *  
 *  * vector<Victory> victories() - returns a list of Victory objects
 *    representing all victories achieved by the player for this
 *    particular game.
 *  * Game game() - returns the Game object associated with this
 *    record.
 *  * string ign() - returns the player's username for this
 *    particular game.
 *  * int gamerscore() - returns the player's total score in this
 *    particular game.
 *  * bool hasVictory(int id) - where 'id' is a valid id for a
 *    Victory object associated with this game; returns whether
 *    the player has achieved this victory.
 *
 *  Mutator Methods:
 *
 *  * void addVictory(int id) - where 'id' is a valid id for a
 *    Victory object associated with this game; adds this victory
 *    to list of those the player has achieved, returns nothing.
 */

#ifndef GAMEPLAYRECORD_H
#define GAMEPLAYRECORD_H

#include <string>
#include <vector>
#include "Game.h"
#include "Victory.h"

class GamePlayRecord {
public:

	// Constructors:

	GamePlayRecord();
	GamePlayRecord(Game, std::string);

	// Accessor Mathods:

	std::vector<Victory> victories() const;
	Game game() const { return _game; }	
	std::string ign() const { return _ign; }
	int gamerscore() const;
	bool hasVictory(int) const;

	// Mutator Methods:

	void addVictory(int);
private:
	Game _game;
	std::string _ign;
	std::vector<int> _victory_ids;
};

#endif