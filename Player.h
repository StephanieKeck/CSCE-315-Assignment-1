// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

/*  Player Class
 *  ------------
 *  Holds information associated with a particular player.
 *  
 *  Constructor(s):
 *
 *  * Player(string name) - 'name' is the name of this player.
 *  
 *  Accessor Methods:
 *  
 *  * string name() - returns the name of this player.
 *  * int gemerscore() - returns the gamerscore of this
 *    player across all games.
 *  * bool plays(int id) - returns whether the player plays
 *    the game associated with 'id'.
 *  * bool hasVictory(int game_id, int victory_id) - returns 
 *    whether the player has achieved the victory associated
 *    with 'victory_id' in the game associated with 'game_id'.
 *  * vector<int> friendIDs() - returns list of the player's
 *    friends' IDs.
 *  * GamePlayRecord gamePlayRecordWithID(int id) - returns
 *    player's GamePlayRecord object for the game associated
 *    with 'id'.
 *  * vector<GamePlayRecord> gamePlayRecords() - returns list
 *    of all gameplay records.
 *
 *  Mutator Methods:
 *
 *  * void addFriendID(int player_id) - adds 'player_id' as a
 *    friend of this player.
 *  * void addGamePlayRecord(int id, GamePlayRecord record) -
 *    adds GamePlayRecord 'record' for the game associated
 *    with 'id'.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>
#include "GamePlayRecord.h"

class Player {
public:

	// Constructors:

	Player();
	Player(std::string);

	// Accessor Methods:

	std::string name() const { return _name; }
	int gamerscore() const;
	bool plays(int) const;
	bool hasVictory(int, int) const;
	std::vector<int> friendIDs() const { return _friendIDs; }
	GamePlayRecord& gamePlayRecordWithID(int);
	std::vector<GamePlayRecord> gamePlayRecords() const;

	// Mutator Methods:

	void addFriendID(int);
	void addGamePlayRecord(int, GamePlayRecord);
private:
	std::string _name;
	std::vector<int> _friendIDs;
	std::map<int, GamePlayRecord> _game_play_records;
};

#endif