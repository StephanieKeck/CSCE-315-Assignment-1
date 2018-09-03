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
 *  * vector<Player> friends() - returns list of the player's
 *    friends.
 *  * vector<Player> friendsWhoPlay(int id) - returns list of
 *    the player's friends who play the game associated with
 *    'id'.
 *  * GamePlayRecord gamePlayRecordWithID(int id) - returns
 *    player's GamePlayRecord object for the game associated
 *    with 'id'.
 *  * vector<GamePlayRecord> gamePlayRecords() - returns list
 *    of all gameplay records.
 *
 *  Mutator Methods:
 *
 *  * void addFrient(Player player) - adds 'player' as a
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
	std::vector<Player> friends() const { return _friends; }
	std::vector<Player> friendsWhoPlay(int) const;
	GamePlayRecord gamePlayRecordWithID(int) const;
	std::vector<GamePlayRecord> gamePlayRecords() const;

	// Mutator Methods:

	void addFriend(Player);
	void addGamePlayRecord(int, GamePlayRecord);
private:
	std::string _name;
	std::vector<Player> _friends;
	std::map<int, GamePlayRecord> _game_play_records;
};

#endif