// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

#include <map>
#include <utility>
#include "Games.h"
#include "Game.h"

using namespace std;


// -----------------
// Accessor Methods:
// -----------------


/*  gameWithID(int id) function
 *  ---------------------------
 *  Returns the Game object associated with 'id'.
 */
Game Games::gameWithID(int game_id) const {
	map<int, Game>::const_iterator it = _games.find(game_id);

	// dereference and extract game
	Game game = it->second;

	return game;}


// ----------------
// Mutator Methods:
// ----------------


/*  gameWithID(int id) function
 *  ---------------------------
 *  Adds 'game' to database and associates it with 'id'.
 */
void Games::addGame(int game_id, Game game) {
	_games[game_id] = game;
}