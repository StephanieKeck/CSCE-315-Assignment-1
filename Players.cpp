// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

#include <vector>
#include <map>
#include <utility>
#include "Players.h"
#include "Player.h"

using namespace std;


// -----------------
// Accessor Methods:
// -----------------


/*  playerWithID(int id) function
 *  -----------------------------
 *  Returns the Player object associated with 'id'.
 */
Player& Players::playerWithID(int player_id) {
	map<int, Player>::iterator it = _players.find(player_id);

	// dereference and extract player
	Player& player = it->second;

	return player;
}


/*  friendsOfID(int id) function
 *  ----------------------------
 *  Returns list of friends of player associated with 'id'.
 */
vector<Player> Players::friendsOfID(int player_id) const {
	vector<Player> friends;

	// get ids of friend associated with player_id
	map<int, Player>::const_iterator player_iterator = _players.find(player_id);

	Player player = player_iterator->second;

	vector<int> friendIDs = player.friendIDs();

	for (vector<int>::const_iterator it = friendIDs.begin();
		it != friendIDs.end(); ++it) {
		// dereference id and look up friend
		int friend_id = *it;

		player_iterator = _players.find(friend_id);

		Player f = player_iterator->second;

		// add to return vector
		friends.push_back(f);
	}

	return friends;
}


/*  friendsOfIDwhoPlay(int id) function
 *  ----------------------------
 *  Returns list of friends of player associated with 'player_id'
 *  who play game associated with 'game_id'.
 */
vector<Player> Players::friendsOfIDWhoPlay(int player_id, int game_id) const {
	vector<Player> friends;

	// get ids of friend associated with player_id
	map<int, Player>::const_iterator player_iterator = _players.find(player_id);

	Player player = player_iterator->second;

	vector<int> friendIDs = player.friendIDs();

	for (vector<int>::const_iterator it = friendIDs.begin();
		it != friendIDs.end(); ++it) {
		// dereference id and look up friend
		int friend_id = *it;

		player_iterator = _players.find(friend_id);

		Player f = player_iterator->second;

		// add to return vector only if friend plays game_id
		if (f.plays(game_id)) {
			friends.push_back(f);
		}
	}

	return friends;
}


/*  playersWhoPlay(int id) function
 *  -------------------------------
 *  Returns a list of the players who play the game associated 
 *  with 'id'.
 */
vector<Player> Players::playersWhoPlay(int game_id) const {
	vector<Player> players_who_play;

	// iterate over players and extract those who play game
	for (map<int, Player>::const_iterator it = _players.begin();
		it != _players.end(); ++it) {
		// dereference and extract player
		Player player = it->second;

		// if player plays game, add to result
		if (player.plays(game_id))
			players_who_play.push_back(player);
	}

	return players_who_play;
}


/*  playersWithVictory(int game_id, int victory_id) function
 *  --------------------------------------------------------
 *  Returns a list of the players who have achieved the victory 
 *  associated with 'victory_id' in the game associated with 
 *  'game_id'.
 */
vector<Player> Players::playersWithVictory(int game_id, int victory_id) const {
	vector<Player> players_with_victory;

	// iterate over players and extract those with victory
	for (map<int, Player>::const_iterator it = _players.begin();
		it != _players.end(); ++it) {
		// dereference and extract player
		Player player = it->second;

		// if player has victory, add to result
		if (player.hasVictory(game_id, victory_id))
			players_with_victory.push_back(player);
	}

	return players_with_victory;
}


/*  players() function
 *  ------------------
 *  Returns a list of all players in this database.
 */
vector<Player> Players::players() const {
	vector<Player> all_players;

	// iterate through all players and extract into list
	for (map<int, Player>::const_iterator it = _players.begin();
		it != _players.end(); ++it) {
		// dereference and extract player
		Player player = it->second;

		// add to result
		all_players.push_back(player);
	}

	return all_players;
}


// ----------------
// Mutator Methods:
// ----------------


/*  playerWithID(int id) function
 *  ---------------------------
 *  Adds 'player' to database and associates it with 'id'.
 */
void Players::addPlayer(int player_id, Player player) {
	_players[player_id] = player;
}