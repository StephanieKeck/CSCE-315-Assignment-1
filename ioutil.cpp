bool not_space(char c) {

}

bool space(char c) {

}

bool comparePlayersByGamerscore(const Player& player1, const Player& player2) {
	return player1.ganerscore() > player2.gamerscore();
}

string generatePlayerNameString(const Player& player) {
	return player.name();
}

string generatePlayerGamerscoreString(const Player& player) {
	return stoi(player.gamerscore());
}

string generateGameNameString(const Game& game) {
	return game.name();
}

string generateGamePlayRecordVictoryCountString(const GamePlayRecord& record) {
	return stoi(record.victories().size());
}

string generateGamePlayRecordGamerscoreString(const GamePlayRecord& record) {
	return stoi(record.gamerscore());
}

string generateGamePlayRecordIGNString(const GamePlayRecord& record) {
	return record.ign();
}

string generateVictoryNameString(const Victory& victory) {
	return victory.name();
}

string generateVictoryWinCountString(int count) {
	return stoi(count);
}

vector<GamePlayRecord> extractGamePlayRecordsForGameID(vector<Player> players, int game_id) {
	vector<GamePlayRecord> records;

	for (vector<Players>::const_iterator it = players.begin();
		it != players.end(); ++it) {
		Player player = players[it];
		if (player.plays(game_id))
			records.push_back(player.gamePlayRecordWithID(game_id));
	}

	return records;
}

vector<Player> extractPlayersWithVictoryID(vector<Player> players, int victory_id) {
	vector<Players> players_with_id;

	for (vector<Players>::const_iterator it = players.begin();
		it != players.end(); ++it) {
		Player player = players[it];
		if (player.hasVictory(game_id, victory_id))
			players_with_id.push_back(player);
	}

	return players_with_id;
}

vector<int> countGamePlayRecordsWithVictoryIDs(vector<GamePlayRecord> records, vector<int> victory_ids) {
	vector<int> id_counts;

	for (vector<int>::const_iterator victory_ids_index = victory_ids.begin();
		victory_ids_index != victory_ids.end(); ++victory_ids_index) {
		int id = victory_ids[victory_ids_index];
		int id_count = 0;

		for (vector<GamePlayRecord>::const_iterator records_index = records.begin();
			records_index != records.end(); ++records_index;) {
			GamePlayRecord record = records[records_index];

			if (record.hasVictory(id))
				++id_count;
		}

		id_counts.push_back(id_count);
	}

	return id_counts;
}

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

	iter j = find(i, end, space);

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

void outputTable(ostream& os, vector< vector<string> > columns) {
	vector<int> column_widths;

	transform(columns.begin(), columns.end(), generateColumnWidth);

	int table_width = tableWidth(column_widths);
	string rule(table_width, '-');

	int row_index = 0;

	for (vector< vector<string> >::size_type column_index;
		column_index != columns.size(); ++column_index) {
		vector<string> column = columns[column_index];
		int column_width = column_widths[(vector<int>::size_type) column_index];

		os << setw(column_width) << column[row_index];
	}

	os << endl << rule << endl;

	++row_index;

	int row_count = columns[0].size();

	while (row_index < row_count) {
		for (vector< vector<string> >::size_type column_index;
			column_index != columns.size(); ++column_index) {
			vector<string> column = columns[column_index];
			int column_width = column_widths[(vector<int>::size_type) column_index];

			os << setw(column_width) << column[row_index];
		}

		os << endl;
		++row_index;
	}
}

void outputPlayerComparisonForGame(ostream& os, vector<Player> players, const Game& game, int game_id) {
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	vector<string> player_name_column_strings;
	vector<string> player_victories_column_strings;
	vector<string> gamerscore_column_strings;
	vector<string> total_gamerscore_column_strings;
	vector<string> player_ign_column_strings;

	vector<GamePlayRecord> records = extractGamePlayRecordsForGameID(players, game_id);

	transform(players.begin(), players.end(), generatePlayerNameString, back_inserter(player_name_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordVictoryCountString, back_inserter(player_victories_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordGamerscoreString, back_inserter(gamerscore_column_strings));
	transform(players.begin(), players.end(), generatePlayerGamerscoreString, back_inserter(total_gamerscore_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordIGNString, back_inserter(player_ign_column_strings));

	player_name_column_strings.push_front("Player");
	player_victories_column_strings.push_front("Victories");
	gamerscore_column_strings.push_front("Gamerscore (" + game.name() + ")");
	total_gamerscore_column_strings.push_front("Gamerscore (Total)");
	player_ign_column_strings.push_front("IGN");

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
	players.push_front(player);

	outputPlayerComparisonForGame(os, players, game, game_id);
}

void outputPlayerSummary(ostream& os, Player player) {
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	vector<GamePlayRecord> records;
	transform(player.begin(), player.end(), extractGamePlayRecords, back_inserter(records));

	vector<string> game_name_column_strings;
	vector<string> player_victories_column_strings;
	vector<string> gamerscore_column_strings;
	vector<string> player_ign_column_strings;

	transform(records.begin(), records.end(), generateGameNameString, back_inserter(game_name_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordVictoryCountString, back_inserter(player_victories_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordGamerscoreString, back_inserter(gamerscore_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordIGNString, back_inserter(player_ign_column_strings));

	game_name_column_strings.push_front("Game");
	player_victories_column_strings.push_front("Victories");
	gamerscore_column_strings.push_front("Gamerscore");
	player_ign_column_strings.push_front("IGN");

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

	transform(friends.begin(), friends.end(), generatePlayerNameString, back_inserter(friend_name_column_strings));
	transform(friends.begin(), friends.end(), generatePlayerGamerscoreString, back_inserter(friend_gamerscore_column_strings));

	friend_name_column_strings.push_front("Friend");
	friend_gamerscore_column_strings.push_front("IGN");

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

	transform(players.begin(), players.end(), generatePlayerNameString, back_inserter(player_name_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordVictoryCountString, back_inserter(player_victories_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordGamerscoreString, back_inserter(gamerscore_column_strings));
	transform(players.begin(), players.end(), generatePlayerGamerscoreString, back_inserter(total_gamerscore_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordIGNString, back_inserter(player_ign_column_strings));

	player_name_column_strings.push_front("Player");
	player_victories_column_strings.push_front("Victories");
	gamerscore_column_strings.push_front("Gamerscore (" + game.name + ")");
	total_gamerscore_column_strings.push_front("Gamerscore (Total)");
	player_ign_column_strings.push_front("IGN");

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

	transform(victories.begin(), victories.end(), generateVictoryNameString, back_inserter(victory_name_column_strings));
	transform(victory_counts.begin(), victory_counts.end(), generateVictoryWinCountString, back_inserter(victory_win_count_column_strings));

	victory_name_column_strings.push_front("Victory");
	victory_win_count_column_strings.push_front("Achieved");

	vector< vector<string> > victory_stats_table;
	victory_stats_table.push_back(victory_name_column_strings);
	victory_stats_table.push_back(victory_win_count_column_strings);

	outputTable(victory_stats_table);
}

void outputVictorySummary(ostream& os, Victory victory, int victory_id, Game game, int game_id, vector<Player> players) {
	sort(players.begin(), players.end(), comparePlayersByGamerscore);

	vector<GamePlayRecord> records = extractGamePlayRecordsForGameID(players, game_id);

	vector<Player> players_with_victory = extractPlayersWithVictoryID(players, victory_id);
	int player_count = players.size();

	vector<string> player_name_column_strings;
	vector<string> player_victories_column_strings;
	vector<string> gamerscore_column_strings;
	vector<string> total_gamerscore_column_strings;
	vector<string> player_ign_column_strings;

	transform(players.begin(), players.end(), generatePlayerNameString, back_inserter(player_name_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordVictoryCountString, back_inserter(player_victories_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordGamerscoreString, back_inserter(gamerscore_column_strings));
	transform(players.begin(), players.end(), generatePlayerGamerscoreString, back_inserter(total_gamerscore_column_strings));
	transform(records.begin(), records.end(), generateGamePlayRecordIGNString, back_inserter(player_ign_column_strings));

	player_name_column_strings.push_front("Player");
	player_victories_column_strings.push_front("Victories");
	gamerscore_column_strings.push_front("Gamerscore (" + game.name + ")");
	total_gamerscore_column_strings.push_front("Gamerscore (Total)");
	player_ign_column_strings.push_front("IGN");

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

	transform(players.begin(), players.end(), generatePlayerNameString, back_inserter(player_name_column_strings));
	transform(players.begin(), players.end(), generatePlayerGamerscoreString, back_inserter(total_gamerscore_column_strings));

	player_name_column_strings.push_front("Player");
	gamerscore_column_strings.push_front("Gamerscore");

	vector< vector<string> > table;
	table.push_back(player_name_column_strings);
	table.push_back(gamerscore_column_strings);

	outputTable(table);
}