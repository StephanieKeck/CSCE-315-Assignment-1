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


bool not_space(char c) {
	return !isspace(c);
}


bool space(char c) {
	return isspace(c);
}


// Comparison Methods:


bool comparePlayersByGamerscore(const Player& player1, const Player& player2) {
	return player1.gamerscore() > player2.gamerscore();
}

bool compareGamePlayRecordsByGamerscore(const GamePlayRecord& record1, const GamePlayRecord& record2) {
	return record1.gamerscore() > record2.gamerscore();
}


// String Generation Methods:


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
	return to_string(record.victories().size());
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


int tableWidth(vector<int> column_widths) {
	int total_width = 0;

	for (vector<int>::const_iterator it = column_widths.begin();
		it != column_widths.end(); ++it) {
		int column_width = *it;
		total_width += column_width;
	}

	return total_width;
}

int generateColumnWidth(vector<string> column) {
	int padding = 3;

	int longest_string_length = 0;

	for (vector<string>::const_iterator it = column.begin();
		it != column.end(); ++it) {
		string current_string = *it;
		int current_string_length = current_string.size();

		if (current_string_length > longest_string_length) {
			longest_string_length = current_string_length;
		}
	}

	return longest_string_length + padding;
}


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


string::const_iterator getCommand(string::const_iterator begin, string::const_iterator end, 
	string& dest) {
	typedef string::const_iterator iter;

	iter i = find_if(begin, end, not_space);

	iter j = find_if(i, end, space);

	if (i != end)
		dest = string(i, j);

	return j;
}

string::const_iterator getInt(string::const_iterator begin, string::const_iterator end, 
	int& dest) {
	typedef string::const_iterator iter;

	iter i = find_if(begin, end, not_space);

	iter j = find_if(i, end, space);

	if (i != end)
		dest = stoi(string(i, j));

	return j;
}

string::const_iterator getQuoteDelimitedString(string::const_iterator begin, 
	string::const_iterator end, string& dest) {
	typedef string::const_iterator iter;

	iter i = find(begin, end, '"');
	++i;

	iter j = find(i, end, '"');

	if (i != end)
		dest = string(i, j);

	return j;
}


// Output Utilities:


void outputPlayerComparisonForGame(ostream& os, vector<Player> players, const Game& game, int game_id) {
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	vector<string> player_name_column_strings;
	vector<string> player_victories_column_strings;
	vector<string> gamerscore_column_strings;
	vector<string> total_gamerscore_column_strings;
	vector<string> player_ign_column_strings;

	vector<GamePlayRecord> records = extractGamePlayRecordsForGameID(players, game_id);

	transform(players.begin(), players.end(), back_inserter(player_name_column_strings), generatePlayerNameString);
	transform(records.begin(), records.end(), back_inserter(player_victories_column_strings), generateGamePlayRecordVictoryCountString);
	transform(records.begin(), records.end(), back_inserter(gamerscore_column_strings), generateGamePlayRecordGamerscoreString);
	transform(players.begin(), players.end(), back_inserter(total_gamerscore_column_strings), generatePlayerGamerscoreString);
	transform(records.begin(), records.end(), back_inserter(player_ign_column_strings), generateGamePlayRecordIGNString);

	player_name_column_strings.insert(player_name_column_strings.begin(), "Player");
	player_victories_column_strings.insert(player_victories_column_strings.begin(), "Victories");
	gamerscore_column_strings.insert(gamerscore_column_strings.begin(), "Gamerscore (" + game.name() + ")");
	total_gamerscore_column_strings.insert(total_gamerscore_column_strings.begin(), "Gamerscore (Total)");
	player_ign_column_strings.insert(player_ign_column_strings.begin(), "IGN");

	vector< vector<string> > table;
	table.push_back(player_name_column_strings);
	table.push_back(player_victories_column_strings);
	table.push_back(gamerscore_column_strings);
	table.push_back(total_gamerscore_column_strings);
	table.push_back(player_ign_column_strings);

	outputTable(os, table);
}

void outputPlayerComparisonForGame(ostream& os, const Player& player1, const Player& player2, const Game& game, int game_id) {
	vector<Player> players;
	players.push_back(player1);
	players.push_back(player2);

	outputPlayerComparisonForGame(os, players, game, game_id);
}

void outputPlayerComparisonForGame(ostream& os, const Player& player, vector<Player> players, const Game& game, int game_id) {
	players.insert(players.begin(), player);

	outputPlayerComparisonForGame(os, players, game, game_id);
}

void outputPlayerSummary(ostream& os, Player player) {
	vector<GamePlayRecord> records = player.gamePlayRecords();

	sort(records.begin(), records.end(), compareGamePlayRecordsByGamerscore);

	vector<string> game_name_column_strings;
	vector<string> player_victories_column_strings;
	vector<string> gamerscore_column_strings;
	vector<string> player_ign_column_strings;

	transform(records.begin(), records.end(), back_inserter(game_name_column_strings), generateGameNameString);
	transform(records.begin(), records.end(), back_inserter(player_victories_column_strings), generateGamePlayRecordVictoryCountString);
	transform(records.begin(), records.end(), back_inserter(gamerscore_column_strings), generateGamePlayRecordGamerscoreString);
	transform(records.begin(), records.end(), back_inserter(player_ign_column_strings), generateGamePlayRecordIGNString);

	game_name_column_strings.insert(game_name_column_strings.begin(), "Game");
	player_victories_column_strings.insert(player_victories_column_strings.begin(), "Victories");
	gamerscore_column_strings.insert(gamerscore_column_strings.begin(), "Gamerscore");
	player_ign_column_strings.insert(player_ign_column_strings.begin(), "IGN");

	vector< vector<string> > player_stats_table;
	player_stats_table.push_back(game_name_column_strings);
	player_stats_table.push_back(player_victories_column_strings);
	player_stats_table.push_back(gamerscore_column_strings);
	player_stats_table.push_back(player_ign_column_strings);

	outputTable(os, player_stats_table);
	os << endl;

	vector<string> friend_name_column_strings;
	vector<string> friend_gamerscore_column_strings;

	vector<Player> friends = player.friends();

	transform(friends.begin(), friends.end(), back_inserter(friend_name_column_strings), generatePlayerNameString);
	transform(friends.begin(), friends.end(), back_inserter(friend_gamerscore_column_strings), generatePlayerGamerscoreString);

	friend_name_column_strings.insert(friend_name_column_strings.begin(), "Friend");
	friend_gamerscore_column_strings.insert(friend_gamerscore_column_strings.begin(), "IGN");

	vector< vector<string> > friends_stats_table;
	friends_stats_table.push_back(friend_name_column_strings);
	friends_stats_table.push_back(friend_gamerscore_column_strings);

	outputTable(os, friends_stats_table);
}

void outputGameSummary(ostream& os, Game game, int game_id, vector<Player> players) {
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	vector<GamePlayRecord> records = extractGamePlayRecordsForGameID(players, game_id);

	vector<string> player_name_column_strings;
	vector<string> player_victories_column_strings;
	vector<string> gamerscore_column_strings;
	vector<string> total_gamerscore_column_strings;
	vector<string> player_ign_column_strings;

	transform(players.begin(), players.end(), back_inserter(player_name_column_strings), generatePlayerNameString);
	transform(records.begin(), records.end(), back_inserter(player_victories_column_strings), generateGamePlayRecordVictoryCountString);
	transform(records.begin(), records.end(), back_inserter(gamerscore_column_strings), generateGamePlayRecordGamerscoreString);
	transform(players.begin(), players.end(), back_inserter(total_gamerscore_column_strings), generatePlayerGamerscoreString);
	transform(records.begin(), records.end(), back_inserter(player_ign_column_strings), generateGamePlayRecordIGNString);

	player_name_column_strings.insert(player_name_column_strings.begin(), "Player");
	player_victories_column_strings.insert(player_victories_column_strings.begin(), "Victories");
	gamerscore_column_strings.insert(gamerscore_column_strings.begin(), "Gamerscore (" + game.name() + ")");
	total_gamerscore_column_strings.insert(total_gamerscore_column_strings.begin(), "Gamerscore (Total)");
	player_ign_column_strings.insert(player_ign_column_strings.begin(), "IGN");

	vector< vector<string> > player_stats_table;
	player_stats_table.push_back(player_name_column_strings);
	player_stats_table.push_back(player_victories_column_strings);
	player_stats_table.push_back(gamerscore_column_strings);
	player_stats_table.push_back(total_gamerscore_column_strings);
	player_stats_table.push_back(player_ign_column_strings);

	outputTable(os, player_stats_table);
	os << endl;

	vector<string> victory_name_column_strings;
	vector<string> victory_win_count_column_strings;

	vector<Victory> victories = game.victories();

	vector<int> victory_ids = game.victoryIDs();
	vector<int> victory_counts = countGamePlayRecordsWithVictoryIDs(records, victory_ids);

	transform(victories.begin(), victories.end(), back_inserter(victory_name_column_strings), generateVictoryNameString);
	transform(victory_counts.begin(), victory_counts.end(), back_inserter(victory_win_count_column_strings), generateVictoryWinCountString);

	victory_name_column_strings.insert(victory_name_column_strings.begin(), "Victory");
	victory_win_count_column_strings.insert(victory_win_count_column_strings.begin(), "Achieved");

	vector< vector<string> > victory_stats_table;
	victory_stats_table.push_back(victory_name_column_strings);
	victory_stats_table.push_back(victory_win_count_column_strings);

	outputTable(os, victory_stats_table);
}

void outputVictorySummary(ostream& os, Victory victory, int victory_id, Game game, int game_id, vector<Player> players) {
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	vector<GamePlayRecord> records = extractGamePlayRecordsForGameID(players, game_id);

	vector<Player> players_with_victory = extractPlayersWithVictoryID(players, victory_id, game_id);
	int player_count = players.size();

	vector<string> player_name_column_strings;
	vector<string> player_victories_column_strings;
	vector<string> gamerscore_column_strings;
	vector<string> total_gamerscore_column_strings;
	vector<string> player_ign_column_strings;

	transform(players.begin(), players.end(), back_inserter(player_name_column_strings), generatePlayerNameString);
	transform(records.begin(), records.end(), back_inserter(player_victories_column_strings), generateGamePlayRecordVictoryCountString);
	transform(records.begin(), records.end(), back_inserter(gamerscore_column_strings), generateGamePlayRecordGamerscoreString);
	transform(players.begin(), players.end(), back_inserter(total_gamerscore_column_strings), generatePlayerGamerscoreString);
	transform(records.begin(), records.end(), back_inserter(player_ign_column_strings), generateGamePlayRecordIGNString);

	player_name_column_strings.insert(player_name_column_strings.begin(), "Player");
	player_victories_column_strings.insert(player_victories_column_strings.begin(), "Victories");
	gamerscore_column_strings.insert(gamerscore_column_strings.begin(), "Gamerscore (" + game.name() + ")");
	total_gamerscore_column_strings.insert(total_gamerscore_column_strings.begin(), "Gamerscore (Total)");
	player_ign_column_strings.insert(player_ign_column_strings.begin(), "IGN");

	vector< vector<string> > player_stats_table;
	player_stats_table.push_back(player_name_column_strings);
	player_stats_table.push_back(player_victories_column_strings);
	player_stats_table.push_back(gamerscore_column_strings);
	player_stats_table.push_back(total_gamerscore_column_strings);
	player_stats_table.push_back(player_ign_column_strings);

	outputTable(os, player_stats_table);
}

void outputPlayerComparison(ostream& os, vector<Player> players) {
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	vector<string> player_name_column_strings;
	vector<string> gamerscore_column_strings;

	transform(players.begin(), players.end(), back_inserter(player_name_column_strings), generatePlayerNameString);
	transform(players.begin(), players.end(), back_inserter(gamerscore_column_strings), generatePlayerGamerscoreString);

	player_name_column_strings.insert(player_name_column_strings.begin(), "Player");
	gamerscore_column_strings.insert(gamerscore_column_strings.begin(), "Gamerscore");

	vector< vector<string> > table;
	table.push_back(player_name_column_strings);
	table.push_back(gamerscore_column_strings);

	outputTable(os, table);
}