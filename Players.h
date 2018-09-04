// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

/*  Players Class
 *  -------------
 *  Database of all players added with the "AddPlayer" command.
 *  
 *  Accessor Methods:
 *  
 *  * Player playerWithID(int id) - returns the Player object
 *    associated with 'id'.
 *  * vector<Player> friendsOfID(int id) - returns list of friends
 *    of player associated with 'id'.
 *  * vector<Player> friendsOfIDwhoPlay(int player_id, int game_id) -
 *    returns list of friends of player associated with 'player_id'
 *    who play game associated with 'game_id'.
 *  * vector<Player> playersWhoPlay(int id) - returns a list
 *    of the players who play the game associated with 'id'.
 *  * vector<Player> playersWithVictory(int game_id, int victory_id) -
 *    returns a list of the players who have achieved the
 *    victory associated with 'victory_id' in the game
 *    associated with 'game_id'.
 *  * vector<Player> players() - returns a list of all players
 *    in this database.
 *
 *  Mutator Methods:
 *
 *  * void addPlayer(int id, Player player) - adds 'player' to
 *    database and associates it with 'id'.
 */


#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>
#include <map>
#include "Player.h"

class Players {
public:

	// Accessor Methods:

	Player& playerWithID(int);
	std::vector<Player> friendsOfID(int) const;
	std::vector<Player> friendsOfIDWhoPlay(int, int) const;
	std::vector<Player> playersWhoPlay(int) const;
	std::vector<Player> playersWithVictory(int, int) const;
	std::vector<Player> players() const;

	// Mutator Methods:

	void addPlayer(int, Player);
	
private:
	std::map<int, Player> _players;
};

#endif