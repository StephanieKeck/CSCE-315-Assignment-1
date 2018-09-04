// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

#include <string>
#include <ostream>
#include <vector>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "ioutil.h"
#include "Player.h"
#include "Game.h"
#include "Victory.h"
#include "GamePlayRecord.h"

using namespace std;


// ----------------
// Private Methods:
// ----------------


// Predicate Methods:


/*  not_space function
 *  ----------------------------------------
 *  Returns whether character is not whitespace. For use in find
 *  operations and string parsing.
 */
bool not_space(char c) {
	return !isspace(c);
}


/*  space function
 *  ----------------------------------------
 *  Returns whether character is whitespace. For use in find
 *  operations and string parsing.
 */
bool space(char c) {
	return isspace(c);
}


// Comparison Methods:


/*  comparePlayersByGamerscore function
 *  ----------------------------------------
 *  Compares players by gamerscore, sort descending. For use in sorting
 *  methods.
 */
bool comparePlayersByGamerscore(const Player& player1, const Player& player2) {
	return player1.gamerscore() > player2.gamerscore();
}


/*  compareGamePlayRecordsByGamerscore function
 *  ----------------------------------------
 *  Compares gameplay records by gamerscore, sort descending. For use in
 *  sorting methods.
 */

bool compareGamePlayRecordsByGamerscore(const GamePlayRecord& record1, const GamePlayRecord& record2) {
	return record1.gamerscore() > record2.gamerscore();
}


/*  String Generation Methods:
 *  --------------------------------------
 *  Given various relevant data, these functions format that data
 *  for display in a table.
 */


string generatePlayerNameString(const Player& player) {
	return player.name();
}

string generatePlayerGamerscoreString(const Player& player) {
	return to_string(player.gamerscore());
}

string generateGameNameString(const GamePlayRecord& record) {
	return record.game().name();
}

string generateGamePlayRecordVictoryCountString(const GamePlayRecord& record) {
	return to_string(record.victories().size()) + "/" + 
		to_string(record.game().victories().size());
}

string generateGamePlayRecordGamerscoreString(const GamePlayRecord& record) {
	return to_string(record.gamerscore());
}

string generateGamePlayRecordIGNString(const GamePlayRecord& record) {
	return record.ign();
}

string generateVictoryNameString(const Victory& victory) {
	return victory.name();
}

string generateVictoryWinCountString(int count) {
	return to_string(count);
}


// Data Manipulation Methods:


/*  extractGamePlayRecordsForGameID function
 *  ----------------------------------------
 *  Given a vector of players, a victory id, extracts and returns their
 *  gameplay records in a new vector.
 */
vector<GamePlayRecord> extractGamePlayRecordsForGameID(vector<Player> players, int game_id) {
	vector<GamePlayRecord> records;

	for (vector<Player>::const_iterator it = players.begin();
		it != players.end(); ++it) {
		Player player = *it;
		if (player.plays(game_id))
			records.push_back(player.gamePlayRecordWithID(game_id));
	}

	return records;
}


/*  extractPlayersWithVictoryID function
 *  ------------------------------------
 *  Given a vector of players, a victory id, and a game id. extracts
 *  only those players who have achieved the associated victory.
 */
vector<Player> extractPlayersWithVictoryID(vector<Player> players, int victory_id, int game_id) {
	vector<Player> players_with_id;

	for (vector<Player>::const_iterator it = players.begin();
		it != players.end(); ++it) {
		Player player = *it;
		if (player.hasVictory(game_id, victory_id))
			players_with_id.push_back(player);
	}

	return players_with_id;
}


/*  countGamePlayRecordsWithVictoryIDs function
 *  -------------------------------------------
 *  Given a vector of gameplay records and vector of victory ids, returns
 *  a vector in which each entry corresponds to a victory id and represents
 *  the number of gameplay records which include that victory.
 */
vector<int> countGamePlayRecordsWithVictoryIDs(vector<GamePlayRecord> records, 
	vector<int> victory_ids) {
	vector<int> id_counts;

	for (vector<int>::const_iterator victory_ids_index = victory_ids.begin();
		victory_ids_index != victory_ids.end(); ++victory_ids_index) {
		int id = *victory_ids_index;

		int id_count = 0;

		for (vector<GamePlayRecord>::const_iterator records_index = records.begin();
			records_index != records.end(); ++records_index) {
			GamePlayRecord record = *records_index;

			if (record.hasVictory(id))
				++id_count;
		}

		id_counts.push_back(id_count);
	}

	return id_counts;
}


// Output Utilities:


/*  tableWidth function
 *  -------------------
 *  Given a vector of ints representing the widths of the columns
 *  of a table, returns the width of the entire table.
 */
int tableWidth(vector<int> column_widths) {
	int total_width = 0;

	for (vector<int>::const_iterator it = column_widths.begin();
		it != column_widths.end(); ++it) {
		int column_width = *it;
		total_width += column_width;
	}

	return total_width;
}


/*  generateColumnWidth function
 *  ----------------------------
 *  Given a vector of strings representing a column with rows, returns
 *  the width of that column, which is equal to the length of the longest
 *  string plus padding.
 */
int generateColumnWidth(vector<string> column) {
	// set padding amount
	int padding = 3;

	// find longest string
	int longest_string_length = 0;
	for (vector<string>::const_iterator it = column.begin();
		it != column.end(); ++it) {
		string current_string = *it;
		int current_string_length = current_string.size();

		if (current_string_length > longest_string_length) {
			longest_string_length = current_string_length;
		}
	}

	// return longest string length + padding
	return longest_string_length + padding;
}


/*  outputTable function
 *  --------------------
 *  Takes a vector of vector of strings representing a table, where the
 *  vectors represent each table columns and their strings represent the
 *  rows of those columns. Outputs a formatted table to the command line.
 *  Assumes the first entry in each column represents a column header.
 */
void outputTable(ostream& os, vector< vector<string> > columns) {
	// generate widths for each column
	vector<int> column_widths;
	transform(columns.begin(), columns.end(), back_inserter(column_widths), generateColumnWidth);

	// generate horizontal rule for under headings
	int table_width = tableWidth(column_widths);
	string rule(table_width, '-');

	// print headings first
	int row_index = 0;

	for (vector< vector<string> >::size_type column_index = 0;
		column_index != columns.size(); ++column_index) {

		// extract column
		vector<string> column = columns[column_index];

		// extract column width
		int column_width = column_widths[(vector<int>::size_type) column_index];

		// output row of column with appropriate width
		os << setw(column_width) << column[row_index];
	}

	// output rule
	os << endl << rule << endl;

	// start at next row
	++row_index;

	// determine row count from any column
	int any_column_index = 0;
	int row_count = columns[any_column_index].size();

	// output rows
	while (row_index < row_count) {

		// output each column for this row
		for (vector< vector<string> >::size_type column_index = 0;
			column_index != columns.size(); ++column_index) {
			// extract column
			vector<string> column = columns[column_index];

			// extract column width
			int column_width = column_widths[(vector<int>::size_type) column_index];

			// output row of column with appropriate width
			os << setw(column_width) << column[row_index];
		}

		// next row
		os << endl;
		++row_index;
	}
}


// ---------------
// Public Methods:
// ---------------


// Input Utilities:


/*  getCommand function
 *  -------------------
 *  Extracts a single word from the string, returning an iterator 
 *  to the position in the string after the word.
 */
string::const_iterator getCommand(string::const_iterator begin, string::const_iterator end, 
	string& dest) {
	typedef string::const_iterator iter;

	// find first nonspace character
	iter i = find_if(begin, end, not_space);

	// find position after next nonspace character
	iter j = find_if(i, end, space);

	// extract and pass to dest
	if (i != end)
		dest = string(i, j);

	// return new iterator position
	return j;
}


/*  getInt function
 *  ---------------
 *  Extracts an integer from a string, returning an iterator to
 *  the position in the string after the integer.
 */
string::const_iterator getInt(string::const_iterator begin, string::const_iterator end, 
	int& dest) {
	typedef string::const_iterator iter;

	// find first nonspace character
	iter i = find_if(begin, end, not_space);

	// find position after next nonspace character
	iter j = find_if(i, end, space);

	// convert to integer and pass to dest
	if (i != end)
		dest = stoi(string(i, j));

	// return new iterator position
	return j;
}


/*  getQuoteDelimitedString function
 *  --------------------------------
 *  Extracts a double-quote-delimited string into dest and returns
 *  an iterator at the position in the string after the second 
 *  double quote.
 */
string::const_iterator getQuoteDelimitedString(string::const_iterator begin, 
	string::const_iterator end, string& dest) {
	typedef string::const_iterator iter;

	// find first quote
	iter i = find(begin, end, '"');
	++i;

	// find end of delimited string
	iter j = find(i, end, '"');

	// if delimited string was found, pass it to dest
	if (i != end)
		dest = string(i, j);

	// return new iterator position
	return j;
}


// Output Utilities:


/*  outputPlayerComparisonForGame function
 *  --------------------------------------
 *  Given a vector of players and a game, outputs a table
 *  comparing player gamerscores (game and total), victories,
 *  and IGNs. Outputs to the given ostream.
 */
void outputPlayerComparisonForGame(ostream& os, vector<Player> players, 
	const Game& game, int game_id) {
	// sort players by gamerscore and then extract their gameplay records
	sort(players.begin(), players.end(), comparePlayersByGamerscore);
	vector<GamePlayRecord> records = extractGamePlayRecordsForGameID(
		players, game_id);


	// only output table if there are players
	if (!players.empty()) {

		// set up the player names column
		vector<string> player_name_column;

		// generate strings of player names from the Player objects
		transform(players.begin(), players.end(), 
			back_inserter(player_name_column), generatePlayerNameString);

		// add column header
		const string player_name_column_header = "Player";
		player_name_column.insert(player_name_column.begin(), 
			player_name_column_header);


		// set up victories won/total column
		vector<string> player_victories_column;

		// generate strings of player victories won/total
		transform(records.begin(), records.end(), back_inserter(
			player_victories_column), generateGamePlayRecordVictoryCountString);

		// add column header
		const string player_victories_column_header = "Victories";
		player_victories_column.insert(player_victories_column.begin(), 
			player_victories_column_header);


		// set up player gamerscore (for game) column
		vector<string> game_gamerscore_column;

		// generate strings of player gamerscores (for game)
		transform(records.begin(), records.end(), back_inserter(game_gamerscore_column), 
			generateGamePlayRecordGamerscoreString);

		// add column header
		const string game_gamerscore_column_header = "Gamerscore (" + game.name() + ")";
		game_gamerscore_column.insert(game_gamerscore_column.begin(), 
			game_gamerscore_column_header);


		// set up player gamerscore column
		vector<string> gamerscore_column;

		// generate strings of player gamerscores
		transform(players.begin(), players.end(), back_inserter(gamerscore_column), 
			generatePlayerGamerscoreString);

		// add column header
		const string gamerscore_column_header = "Gamerscore (Total)";
		gamerscore_column.insert(gamerscore_column.begin(), 
			gamerscore_column_header);


		// set up column of player IGNs
		vector<string> player_ign_column;

		// generate strings of player IGNs
		transform(records.begin(), records.end(), back_inserter(player_ign_column), 
			generateGamePlayRecordIGNString);

		// add column header
		const string player_ign_column_header = "IGN";
		player_ign_column.insert(player_ign_column.begin(), 
			player_ign_column_header);


		// populate table
		vector< vector<string> > table;
		table.push_back(player_name_column);
		table.push_back(player_victories_column);
		table.push_back(game_gamerscore_column);
		table.push_back(gamerscore_column);
		table.push_back(player_ign_column);

		// output table
		outputTable(os, table);
	}
}


/*  outputPlayerComparisonForGame overload function
 *  -----------------------------------------------
 *  Overload of the outputPlayerComparisonForGame function for when
 *  there are only two players.
 */
void outputPlayerComparisonForGame(ostream& os, const Player& player1, 
	const Player& player2, const Game& game, int game_id) {
	vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);

	outputPlayerComparisonForGame(os, players, game, game_id);
}


/*  outputPlayerComparisonForGame overload function
 *  -----------------------------------------------
 *  Overload of the outputPlayerComparisonForGame function for comparing
 *  one player to a vector of players.
 */
void outputPlayerComparisonForGame(ostream& os, const Player& player, 
	vector<Player> players, const Game& game, int game_id) {
	players.insert(players.begin(), player);

	outputPlayerComparisonForGame(os, players, game, game_id);
}


/*  outputPlayerSummary function
 *  ----------------------------
 *  Given a player, outputs a table comparing their gamerscores,
 *  victories, and IGNs accross games and a table comparing the
 *  total gamerscores of their friends. Outputs to the given ostream.
 */
void outputPlayerSummary(ostream& os, Player player, vector<Player> friends) {
	// extract and sort gameplay records by gamerscore
	vector<GamePlayRecord> records = player.gamePlayRecords();
	sort(records.begin(), records.end(), compareGamePlayRecordsByGamerscore);

	// only output table 1 if the player plays at least
	// one game
	if (!records.empty()) {

		// set up game name column
		vector<string> game_name_column;

		// generate game name strings
		transform(records.begin(), records.end(), back_inserter(game_name_column), 
			generateGameNameString);

		// add column header
		const string game_name_column_header = "Game";
		game_name_column.insert(game_name_column.begin(), 
			game_name_column_header);


		// set up player victories won/total column
		vector<string> player_victories_column;

		// generate player victories won/total strings
		transform(records.begin(), records.end(), back_inserter(player_victories_column), 
			generateGamePlayRecordVictoryCountString);

		// add column header
		const string player_victories_column_header = "Victories";
		player_victories_column.insert(player_victories_column.begin(), 
			player_victories_column_header);


		// set up player gamerscore (per game) column
		vector<string> gamerscore_column;

		// generate player gamerscore (per game) strings
		transform(records.begin(), records.end(), back_inserter(gamerscore_column), 
			generateGamePlayRecordGamerscoreString);

		// add column header
		const string gamerscore_column_header = "Gamerscore";
		gamerscore_column.insert(gamerscore_column.begin(), gamerscore_column_header);


		// set up player IGN column
		vector<string> player_ign_column;
		
		// generate player IGN strings
		transform(records.begin(), records.end(), back_inserter(player_ign_column), 
			generateGamePlayRecordIGNString);

		// add column header
		const string player_ign_column_header = "IGN";
		player_ign_column.insert(player_ign_column.begin(), player_ign_column_header);


		// populate table 1
		vector< vector<string> > player_stats_table;
		player_stats_table.push_back(game_name_column);
		player_stats_table.push_back(player_victories_column);
		player_stats_table.push_back(gamerscore_column);
		player_stats_table.push_back(player_ign_column);

		// output table 1
		outputTable(os, player_stats_table);

	}

	// only output table 2 if player has friends
	if (!friends.empty()) {

		// new line to separate from last table
		os << endl;


		// set up friend name column
		vector<string> friend_name_column;

		// generate friend name strings
		transform(friends.begin(), friends.end(), back_inserter(friend_name_column), 
			generatePlayerNameString);

		// add column header
		const string friend_name_column_header = "Friend";
		friend_name_column.insert(friend_name_column.begin(), 
			friend_name_column_header);


		// set up friend gamerscore (total) column
		vector<string> friend_gamerscore_column;

		// generate friend gamerscore (total) strings
		transform(friends.begin(), friends.end(), back_inserter(friend_gamerscore_column), 
			generatePlayerGamerscoreString);

		// add column header
		const string friend_gamerscore_column_header = "Gamerscore";
		friend_gamerscore_column.insert(friend_gamerscore_column.begin(), 
			friend_gamerscore_column_header);


		// populate table 2
		vector< vector<string> > friends_stats_table;
		friends_stats_table.push_back(friend_name_column);
		friends_stats_table.push_back(friend_gamerscore_column);

		// output table 2
		outputTable(os, friends_stats_table);
	}
}


/*  outputGameSummary function
 *  --------------------------
 *  Given a game and a vector of players who play that game,
 *  generates a table comparing players by gamerscore (total
 *  and game), victories achieved, and IGN. Outputs to the 
 *  given ostream.
 */
void outputGameSummary(ostream& os, Game game, int game_id, vector<Player> players) {
	// sort players by gamerscore and extract gameplay records
	sort(players.begin(), players.end(), comparePlayersByGamerscore);
	vector<GamePlayRecord> records = extractGamePlayRecordsForGameID(players, game_id);
	
	// only output table 1 if there are players who play
	// this game
	if (!players.empty()) {

		// set up player name column
		vector<string> player_name_column;

		// generate player name strings
		transform(players.begin(), players.end(), back_inserter(player_name_column), 
			generatePlayerNameString);

		// add column header
		const string player_name_column_header = "Player";
		player_name_column.insert(player_name_column.begin(), 
			player_name_column_header);


		// set up player victories won/total column
		vector<string> player_victories_column;

		// generate player victories won/total strings
		transform(records.begin(), records.end(), back_inserter(player_victories_column), 
			generateGamePlayRecordVictoryCountString);

		// add column header
		const string player_victories_column_header = "Victories";
		player_victories_column.insert(player_victories_column.begin(), 
			player_victories_column_header);


		// set up player gamerscore (for game) column
		vector<string> game_gamerscore_column;

		// generate player gamerscore (for game) strings
		transform(records.begin(), records.end(), back_inserter(game_gamerscore_column), 
			generateGamePlayRecordGamerscoreString);

		// add column header
		const string game_gamerscore_column_header = "Gamerscore (" + game.name() + ")";
		game_gamerscore_column.insert(game_gamerscore_column.begin(), 
			game_gamerscore_column_header);


		// set up player gamerscore (total) column
		vector<string> gamerscore_column;

		// generate player gamerscore (total) strings
		transform(players.begin(), players.end(), back_inserter(gamerscore_column), 
			generatePlayerGamerscoreString);

		// add column header
		const string gamerscore_column_header = "Gamerscore (Total)";
		gamerscore_column.insert(gamerscore_column.begin(), gamerscore_column_header);


		// sey up player IGN column
		vector<string> player_ign_column;

		// generate player ign strings
		transform(records.begin(), records.end(), back_inserter(player_ign_column), 
			generateGamePlayRecordIGNString);

		// add column header
		const string player_ign_column_header = "IGN";
		player_ign_column.insert(player_ign_column.begin(), 
			player_ign_column_header);


		// populate table 1
		vector< vector<string> > player_stats_table;
		player_stats_table.push_back(player_name_column);
		player_stats_table.push_back(player_victories_column);
		player_stats_table.push_back(game_gamerscore_column);
		player_stats_table.push_back(gamerscore_column);
		player_stats_table.push_back(player_ign_column);

		// output table 1
		outputTable(os, player_stats_table);

	}


	// extract victories for this game
	vector<Victory> victories = game.victories();

	// only output table 2 if game has victories
	if (!victories.empty()) {

		// new line to separate from last table
		os << endl;


		// set up victory name column
		vector<string> victory_name_column;

		// generate victory name strings
		transform(victories.begin(), victories.end(), 
			back_inserter(victory_name_column), generateVictoryNameString);

		// add column header
		const string victory_name_column_header = "Victory";
		victory_name_column.insert(victory_name_column.begin(), 
			victory_name_column_header);


		// extract victory ids for game
		vector<int> victory_ids = game.victoryIDs();

		// for each victory id, determine how many times it has been achieved
		vector<int> times_achieved_counts = countGamePlayRecordsWithVictoryIDs(
			records, victory_ids);


		// set up times achieved column
		vector<string> times_achieved_column;

		// generate times achieved strings for victories
		transform(times_achieved_counts.begin(), times_achieved_counts.end(), 
			back_inserter(times_achieved_column), generateVictoryWinCountString);

		// add column header
		const string times_achieved_column_header = "Times Achieved";
		times_achieved_column.insert(times_achieved_column.begin(), 
			times_achieved_column_header);


		// populate table 2
		vector< vector<string> > victory_stats_table;
		victory_stats_table.push_back(victory_name_column);
		victory_stats_table.push_back(times_achieved_column);

		// output table 2
		outputTable(os, victory_stats_table);
	}
}


/*  outputVictorySummary function
 *  -----------------------------
 *  Given a victory, a game, and a vector of players who play that
 *  game, generates a table of players who have that victory, 
 *  comparing them by gamerscore (total and game) and displaying IGNs.
 *  Outputs to the given ostream.
 */
void outputVictorySummary(ostream& os, Victory victory, int victory_id, Game game, 
	int game_id, vector<Player> players) {

	// sort player by gamerscore and extract gameplay records
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	// extract players who have this victory and their gameplay records
	vector<Player> players_with_victory = extractPlayersWithVictoryID(
		players, victory_id, game_id);
	vector<GamePlayRecord> records = extractGamePlayRecordsForGameID(
		players_with_victory, game_id);


	// only output table if there are players with victory
	if (!players_with_victory.empty()) {

		// set up player name column
		vector<string> player_name_column;

		// generate player name strings
		transform(players_with_victory.begin(), players_with_victory.end(), 
			back_inserter(player_name_column), generatePlayerNameString);

		// add column header
		const string player_name_column_header = "Player";
		player_name_column.insert(player_name_column.begin(), 
			player_name_column_header);


		// set up player gamerscore (for game) column
		vector<string> game_gamerscore_column;

		// generate player gamerscore (for game) strings
		transform(records.begin(), records.end(), back_inserter(game_gamerscore_column), 
			generateGamePlayRecordGamerscoreString);

		// add column header
		const string game_gamerscore_column_header = "Gamerscore (" + game.name() + ")";
		game_gamerscore_column.insert(game_gamerscore_column.begin(), 
			game_gamerscore_column_header);


		// set up player gamerscore (total) column
		vector<string> total_gamerscore_column;

		// generate player gamerscore (total) strings
		transform(players_with_victory.begin(), players_with_victory.end(), 
			back_inserter(total_gamerscore_column), generatePlayerGamerscoreString);

		// add column header
		const string total_gamerscore_column_header = "Gamerscore (Total)";
		total_gamerscore_column.insert(total_gamerscore_column.begin(), 
			total_gamerscore_column_header);


		// set up player IGN column
		vector<string> player_ign_column;

		// generate player IGN strings
		transform(records.begin(), records.end(), back_inserter(player_ign_column), 
			generateGamePlayRecordIGNString);

		// add column header
		const string player_ign_column_header = "IGN";
		player_ign_column.insert(player_ign_column.begin(), 
			player_ign_column_header);

		// populate table
		vector< vector<string> > player_stats_table;
		player_stats_table.push_back(player_name_column);
		player_stats_table.push_back(game_gamerscore_column);
		player_stats_table.push_back(total_gamerscore_column);
		player_stats_table.push_back(player_ign_column);

		// output table
		outputTable(os, player_stats_table);

	}
}


/*  outputPlayerComparison function
 *  -------------------------------
 *  Given a vector of players, generates a table comparing players by
 *  gamerscore. Outputs to the given ostream.
 */
void outputPlayerComparison(ostream& os, vector<Player> players) {
	// sort players by gamerscore
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	// set up player name column
	vector<string> player_name_column;

	// generate player name strings
	transform(players.begin(), players.end(), back_inserter(player_name_column), 
		generatePlayerNameString);

	// add column header
	const string player_name_column_header = "Player";
	player_name_column.insert(player_name_column.begin(), 
		player_name_column_header);


	// set up player gamerscore column
	vector<string> gamerscore_column;

	// generate player gamerscore strings
	transform(players.begin(), players.end(), back_inserter(gamerscore_column), 
		generatePlayerGamerscoreString);

	// add column header
	const string gamerscore_column_header = "Gamerscore";
	gamerscore_column.insert(gamerscore_column.begin(), gamerscore_column_header);


	// populate table
	vector< vector<string> > table;
	table.push_back(player_name_column);
	table.push_back(gamerscore_column);

	// output table
	outputTable(os, table);
}