// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

#include <string>
#include <vector>
#include <map>
#include <utility>
#include "Player.h"
#include "GamePlayRecord.h"

using namespace std;


// -------------
// Constructors:
// -------------


Player::Player() {
	_name = "";
}


/*  (name) constructor
 *  -----------------------
 *  'name' is the name of this player.
 */
Player::Player(string name) {
	// set private fields
	_name = name;
}


// -----------------
// Accessor Methods:
// -----------------


/*  gamerscore() function
 *  ---------------------
 *  Returns the gamerscore of this player across all games.
 *
 *  Adds up the gamerscores associated with all gameplay records and
 *  returns the result.
 */
int Player::gamerscore() const {
	// initially set score to zero
	int score = 0;

	// iterate through each gameplay record and extract associated
	// gamerscore
	for (map<int, GamePlayRecord>::const_iterator it = _game_play_records.begin();
		it != _game_play_records.end(); ++it) {
		// dereference and extract ganeplay record
		GamePlayRecord record = it->second;

		// add gameplay record score to total
		score += record.gamerscore();
	}

	return score;
}


/*  plays(int id) function
 *  ----------------------
 *  Returns whether the player plays the game associated with 'id'.
 */
bool Player::plays(int game_id) const {

	bool game_id_found = _game_play_records.find(game_id) != _game_play_records.end();

	return game_id_found;
}


/*  hasVictory(int game_id, int victory_id) function
 *  ------------------------------------------------
 *  Returns whether the player has achieved the victory associated 
 *  with 'victory_id' in the game associated with 'game_id'.
 */
bool Player::hasVictory(int game_id, int victory_id) const {

	map<int, GamePlayRecord>::const_iterator it = _game_play_records.find(game_id);

	bool id_found = it != _game_play_records.end();

	if (id_found) {
		// dereference to get record
		GamePlayRecord record = it->second;

		// determine if record includes particular victory
		bool player_has_victory = record.hasVictory(victory_id);

		return player_has_victory;
	}

	// if reached, player does not play game
	return false;
}


/*  friendsWhoPlay(int game_id) function
 *  ------------------------------------
 *  Returns list of the player's friends who play the game associated 
 *  with 'id'.
 */
vector<Player> Player::friendsWhoPlay(int game_id) const {
	// empty vector to accumulate result
	vector<Player> friends_who_play;

	// iterate over friends to extract those who play game
	for (vector<Player>::const_iterator it = _friends.begin();
		it != _friends.end(); ++it) {
		// dereference to get friend
		Player player = *it;
		// if friend plays game, add to result
		if (player.plays(game_id))
			friends_who_play.push_back(player);
	}

	return friends_who_play;
}


/*  gamePlayRecordWithID(int game_id) function
 *  ------------------------------------------
 *  Returns player's GamePlayRecord object for the game associated
 *  with 'id'.
 */
GamePlayRecord Player::gamePlayRecordWithID(int game_id) const {
	map<int, GamePlayRecord>::const_iterator it = _game_play_records.find(game_id);

	// dereference and extract record
	GamePlayRecord record = it->second;

	return record;
}


/*  gamePlayRecords() function
 *  --------------------------
 *  Returns list of all gameplay records.
 */
vector<GamePlayRecord> Player::gamePlayRecords() const {
	vector<GamePlayRecord> records;

	for (map<int, GamePlayRecord>::const_iterator it = _game_play_records.begin();
		it != _game_play_records.end(); ++it) {
		GamePlayRecord record = it->second;

		records.push_back(record);
	}

	return records;
}


// ----------------
// Mutator Methods:
// ----------------


/*  addFriend(Player player) function
 *  ---------------------------------
 *  Adds 'player' as a friend of this player.
 */
void Player::addFriend(Player player) {
	_friends.push_back(player);
}


/*  addGamePlayRecord(int id, GamePlayRecord record) function
 *  ---------------------------------------------------------
 *  Adds GamePlayRecord 'record' for the game associated
 *  with 'id'.
 */
void Player::addGamePlayRecord(int game_id, GamePlayRecord record) {
	_game_play_records[game_id] = record;
}