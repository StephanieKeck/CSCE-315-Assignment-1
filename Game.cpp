// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

#include <string>
#include <map>
#include <utility>
#include "Game.h"
#include "Victory.h"

using namespace std;


// -------------
// Constructors:
// -------------


Game::Game() {
	_name = "";
}


/*  (name) constructor
 *  -----------------------
 *  'name' is the name of this game.
 */
Game::Game(string name) {
	_name = name;
}


// -----------------
// Accessor Methods:
// -----------------


/*  victoryWithID(int id) function
 *  ------------------------------
 *  Where 'id' is a valid id for a Victory object associated with this 
 *  game; returns the victory object associated with this id.
 */
Victory Game::victoryWithID(int victory_id) const {
	// fetch Victory object associated with this id
	map<int, Victory>::const_iterator it = _victories.find(victory_id);

	// dereference and extract Victory object
	Victory victory = it->second;

	// return Victory object
	return victory;
}


/*  victories() function
 *  --------------------
 *  Returns list of all Victory objects associated with this game.
 *
 *  Iterates through the map of <victory id, Victory object> pairs
 *  and extracts the objects; returns the result in a list.
 */
vector<Victory> Game::victories() const {
	// set up vector to hold Victory objects
	vector<Victory> all_victories;

	// iterate through <victory id, Victory object> pairs
	// and extract Victory objects
	for (map<int, Victory>::const_iterator it = _victories.begin();
		it != _victories.end(); ++it) {
		// dereference and extract Victory value
		Victory victory = it->second;

		// add Victory object to return list
		all_victories.push_back(victory);
	}

	return all_victories;
}


/*  victoryIDs() function
 *  ---------------------
 *  Returns list of victory ids associated with victories of 
 *  this game.
 *
 *  Iterates through the map of <victory id, Victory object> pairs
 *  and extracts the ids; returns the result in a list.
 */
vector<int> Game::victoryIDs() const {
	// set up vector to hold ids
	vector<int> all_victory_ids;

	// iterate through <victory id, Victory object> pairs
	// and extract victory ids
	for (map<int, Victory>::const_iterator it = _victories.begin();
		it != _victories.end(); ++it) {
		// dereference and extract id key
		int id = it->first;

		// add id to return list
		all_victory_ids.push_back(id);
	}

	return all_victory_ids;
}


// ----------------
// Mutator Methods:
// ----------------


/*  addVictory(int id, Victory victory) function
 *  --------------------------------------------
 *  Adds new victory to this game and associates it with the 
 *  provided id.
 */
void Game::addVictory(int victory_id, Victory victory) {
	_victories[victory_id] = victory;
}