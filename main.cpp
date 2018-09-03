// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

/*  Main Program
 *  ------------
 *  Entrance to Project 1. This program works as follows:
 *
 *  * Players and games are associated with Player and Game objects
 *    respectively. These objects are kept in database classes of
 *    type Players and Games respectively.
 *
 *  * The program reads one line of input at a time. It then extracts
 *    relevant information from each line and generates objects
 *    appropriately.
 *
 *  * When asked to output data, it queries the two databases and
 *    uses utility functions from ioutil.h to format the output.
 */

#include <iostream>
#include <string>
#include <vector>
#include "Players.h"
#include "Games.h"
#include "Player.h"
#include "Game.h"
#include "Victory.h"
#include "GamePlayRecord.h"
#include "ioutil.h"

using namespace std;

int main() {
	// set up the two main databases
	Players players;
	Games games;

	// storage space for reading lines of input into
	string line_of_input;

	// process each line of input
	while (getline(cin, line_of_input)) {
		// storage space for command word
		string command;

		// i represents our current position in the input line
		string::const_iterator i = line_of_input.begin();

		// get command word
		i = getCommand(line_of_input.begin(), line_of_input.end(), command);

		// skip blank lines
		if (i != line_of_input.end()) {

			// predefined command words so they can be
			// changed in one place
			const string add_player_command = "AddPlayer";
			const string add_game_command = "AddGame";
			const string add_victory_command = "AddVictory";
			const string plays_command = "Plays";
			const string add_friends_command = "AddFriends";
			const string win_victory_command = "WinVictory";
			const string friends_who_play_command = "FriendsWhoPlay";
			const string compare_players_command = "ComparePlayers";
			const string summarize_player_command = "SummarizePlayer";
			const string summarize_game_command = "SummarizeGame";
			const string summarize_victory_command = "SummarizeVictory";
			const string victory_ranking_command = "VictoryRanking";

			if (command == add_player_command) {


				// read input
				int player_id;
				i = getID(i, line_of_input.end(), player_id);

				string name;
				getQuoteDelimitedString(i, line_of_input.end(), name);

				// add new player
				players.addPlayer(player_id, Player(name));


			} else if (command == add_game_command) {


				// read input
				int game_id;
				i = getID(i, line_of_input.end(), game_id);

				string name;
				getQuoteDelimitedString(i, line_of_input.end(), name);

				// add new player
				games.addGame(game_id, Game(name));


			} else if (command == add_victory_command) {


				// read input
				int game_id;
				i = getID(i, line_of_input.end(), game_id);

				int victory_id;
				i = getID(i, line_of_input.end(), victory_id);

				string victory_name;
				i = getQuoteDelimitedString(i, line_of_input.end(), victory_name);

				int victory_points;
				getInt(i, line_of_input.end(), victory_points);

				// get Game object to add victory to
				Game game = games.gameWithID(game_id);

				// add victory to game
				game.addVictory(victory_id, Victory(victory_name, victory_points));


			} else if (command == plays_command) {


				// read input
				int player_id;
				i = getID(i, line_of_input.end(), player_id);

				int game_id;
				i = getID(i, line_of_input.end(), game_id);

				string player_ign;
				getQuoteDelimitedString(i, line_of_input.end(), player_ign);

				// get player to add gameplay record to
				Player player = players.playerWithID(player_id);

				// get game to add to ganeplay record
				Game game = games.gameWithID(game_id);

				// add gameplay record to player
				player.addGamePlayRecord(game_id, GamePlayRecord(game, player_ign));


			} else if (command == add_friends_command) {


				// read input
				int player_id1;
				i = getID(i, line_of_input.end(), player_id1);

				int player_id2;
				getID(i, line_of_input.end(), player_id2);

				// get players to make friends
				Player player1 = players.playerWithID(player_id1);
				Player player2 = players.playerWithID(player_id2);

				// set friend relationships
				player1.addFriend(player2);
				player2.addFriend(player1);


			} else if (command == win_victory_command) {


				// read input
				int player_id;
				i = getID(i, line_of_input.end(), player_id);

				int game_id;
				i = getID(i, line_of_input.end(), game_id);

				int victory_id;
				getID(i, line_of_input.end(), victory_id);

				// get player to get gameplay record from
				Player player = players.playerWithID(player_id);

				// get ganeplay record to add victory to
				GamePlayRecord record = player.gamePlayRecordWithID(game_id);

				// add victory
				record.addVictory(victory_id);


			} else if (command == friends_who_play_command) {


				// read input
				int player_id;
				i = getID(i, line_of_input.end(), player_id);

				int game_id;
				getID(i, line_of_input.end(), game_id);

				// get player and game
				Player player = players.playerWithID(player_id);
				Game game = games.gameWithID(game_id);

				// initial output
				cout << "Player: " << player.name() << endl
				     << "Game: " << game.name()<< endl
				     << endl;

				// get friends who play game
				vector<Player> friends_who_play = player.friendsWhoPlay(game_id);

				// generate output table
				outputPlayerComparisonForGame(cout, player, friends_who_play, game, game_id);


			} else if (command == compare_players_command) {


				// read input
				int player_id1;
				i = getID(i, line_of_input.end(), player_id1);

				int player_id2;
				i = getID(i, line_of_input.end(), player_id2);

				int game_id;
				getID(i, line_of_input.end(), game_id);

				// get players to compare
				Player player1 = players.playerWithID(player_id1);
				Player player2 = players.playerWithID(player_id2);

				// get game
				Game game = games.gameWithID(game_id);

				// initial output
				cout << "Player 1: " << player1.name() << endl
				     << "Player 2: " << player2.name() << endl
				     << "Game: " << game.name() << endl
				     << endl;

				// generate output table
				outputPlayerComparisonForGame(cout, player1, player2, game, game_id);


			} else if (command == summarize_player_command) {


				// read input
				int player_id;
				getID(i, line_of_input.end(), player_id);

				// look up player
				Player player = players.playerWithID(player_id);

				// initial output
				cout << "Player: " << player.name() << endl
				     << "Total Gamerscore: " << player.gamerscore() << endl
				     << endl;

				// generate output table
				outputPlayerSummary(cout, player);


			} else if (command == summarize_game_command) {


				// read input
				int game_id;
				getID(i, line_of_input.end(), game_id);

				// look up game
				Game game = games.gameWithID(game_id);

				// look up players who play game
				vector<Player> players_who_play = players.playersWhoPlay(game_id);

				// initial output
				cout << "Game: " << game.name() << endl
					 << "Players: " << (int) players_who_play.size() << endl
				     << endl;

				// generate output table
				outputGameSummary(cout, game, game_id, players_who_play);


			} else if (command == summarize_victory_command) {


				// read input
				int game_id;
				i = getID(i, line_of_input.end(), game_id);

				int victory_id;
				getID(i, line_of_input.end(), victory_id);

				// look up game and victory
				Game game = games.gameWithID(game_id);
				Victory victory = game.victoryWithID(victory_id);

				// get players who play game and have victory
				vector<Player> players_who_play = players.playersWhoPlay(game_id);
				vector<Player> players_with_victory = players.playersWithVictory(game_id, 
					victory_id);

				// calculate percentage of players who have victory
				double victory_achieved_percentage = (double) players_with_victory.size() 
					/ players_who_play.size();

				// initial output
				cout << "Game: " << game.name() << endl
				     << "Players: " << (int) players_who_play.size() << endl
				     << "Victory Name: " << victory.name() << endl
				     << "Victory Points: " << victory.points() << endl
				     << "Acheived By: " << (int) players_with_victory.size() << " Players" << endl
				     << "Achieved Percentage: " << victory_achieved_percentage << "%" << endl
				     << endl;

				// generate output table
				outputVictorySummary(cout, victory, victory_id, game, game_id, players_who_play);


			} else if (command == victory_ranking_command) {


				// no input to read

				// get all players
				vector<Player> allPlayers = players.players();

				// generate output table
				outputPlayerComparison(cout, allPlayers);


			}
		}
	}

	return 0;
}