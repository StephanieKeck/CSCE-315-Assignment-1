// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

/*  Games Class
 *  -----------
 *  Database of all games added with the "AddGame" command.
 *  
 *  Accessor Methods:
 *  
 *  * Game gameWithID(int id) - returns the Game object
 *    associated with 'id'.
 *
 *  Mutator Methods:
 *
 *  * void addGame(int id, Game game) - adds 'game' to
 *    database and associates it with 'id'.
 */

#ifndef GAMES_H
#define GAMES_H

#include <map>
#include "Game.h"

class Games {
public:

	// Accessor Methods:

	Game gameWithID(int) const;

	// Mutator Methods:

	void addGame(int, Game);

private:
	std::map<int, Game> _games;
};

#endif