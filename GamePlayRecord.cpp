// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

#include <string>
#include <vector>
#include <algorithm>
#include "GamePlayRecord.h"
#include "Game.h"
#include "Victory.h"

using namespace std;


// -------------
// Constructors:
// -------------


GamePlayRecord::GamePlayRecord() {
	_ign = "";
}


/*  (game, ign) constructor
 *  -----------------------
 *  'game' is a Game object eferring to a particular game, and 
 *  'ign' is the player's username in that game.
 */
GamePlayRecord::GamePlayRecord(Game game, string ign) {

	// set private fields to parameter values
	_game = game;
	_ign = ign;
}


// -----------------
// Accessor Methods:
// -----------------


/*  victories function
 *  ------------------
 *  Returns a list of Victory objects representing all victories
 *  achieved by the player for this particular game.
 *
 *  Maps internal list of victory ids to Victory objects and
 *  returns the result.
 */
vector<Victory> GamePlayRecord::victories() const {
	// set up empty vector for result
	vector<Victory> all_victories;

	// iterate through the saved victory ids and
	// map them to Victory objects
	for (vector<int>::const_iterator it = _victory_ids.begin();
		it != _victory_ids.end(); ++it) {

		// dereference to get current victory id
		int id = *it;

		// fetch Victory object associated with the id
		// from the private Game object
		Victory victory = _game.victoryWithID(id);

		// add the Victory object to our return vector
		all_victories.push_back(victory);
	}

	// return completed vector of Victory objects
	return all_victories;
}


/*  gamerscore function
 *  -------------------
 *  Returns the player's total score in this particular game.
 *
 *  Adds up points associated with all victories player has
 *  achieved for this game and returns the result.
 */
int GamePlayRecord::gamerscore() const {
	// set up variable to accumulate score
	int score = 0;

	// iterate through victory ids and map each to the amount
	// of points associated with the corresponding Victory object
	for (vector<int>::const_iterator it = _victory_ids.begin();
		it != _victory_ids.end(); ++it) {

		// dereference to get current victory id
		int id = *it;

		// fetch Victory object associated with the id
		// from the private Game object
		Victory victory = _game.victoryWithID(id);

		// add the points of this Victory to the current
		// score count
		score += victory.points();
	}

	// return the total score
	return score;
}


/*  hasVictory function
 *  -------------------
 *  Where 'id' is a valid id for a Victory object associated with 
 *  this game; returns whether the player has achieved this victory.
 *
 *  Searches the internal list of victory ids for a particular id.
 */
bool GamePlayRecord::hasVictory(int victory_id) const {
	bool found = find(_victory_ids.begin(), _victory_ids.end(), victory_id) 
		!= _victory_ids.end();

	return found;
}


// ----------------
// Mutator Methods:
// ----------------


/*  addVictory function
 *  -------------------
 *  Where 'id' is a valid id for a Victory object associated with this 
 *  game; adds this victory to list of those the player has achieved, 
 *  returns nothing.
 */
void GamePlayRecord::addVictory(int victory_id) {
	// only add victory id if it is not
	// already present
	if (!hasVictory(victory_id)) {
		_victory_ids.push_back(victory_id);
	}
}