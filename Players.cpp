void addPlayer(int player_id, Player player) {
	_players[player_id] = player;
}

Player playerWithID(int player_id) {
	map<int, Player>::const_iterator it = _players.find(player_id);

	if (it != _players.end())
		return *it;
}

vector<Player> playersWhoPlay(int game_id) {
	vector<Player> players_who_play;

	for (map<int, Player>::const_iterator it = _players.begin();
		it != _players.end(); ++it;) {
		Player player = it->second;
		if (player.plays(game_id))
			players_who_play.push_back(player);
	}

	return players_who_play;
}

vector<Player> playersWithVictory(int game_id, int victory_id) {
	vector<Player> players_with_victory;

	for (map<int, Player>::const_iterator it = _players.begin();
		it != _players.end(); ++it;) {
		Player player = it->second;
		if (player.hasVictory(game_id, victory_id))
			players_with_victory.push_back(player);
	}

	return players_with_victory;
}

vector<Player> players() {
	vector<Player> all_players;

	for (map<int, Player>::const_iterator it = _players.begin();
		it != _players.end(); ++it;) {
		Player player = it->second;
		all_players.push_back(player);
}