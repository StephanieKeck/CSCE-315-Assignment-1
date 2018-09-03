Player::Player(string name) {
	_name = name;
}

void addFriend(Player player) {
	_friends.push_back(player);
}

void addGamePlayRecord(int game_id, GamePlayRecord record) {
	_game_play_records[game_id] = record;
}

int gamerscore() {
	int score = 0;

	for (map<int, GamePlayRecord>::const_iterator it = _game_play_records.begin();
		it != _game_play_records.end(); ++it;) {
		GamePlayRecord record = *it;
		score += record.gamerscore();
	}

	return score;
}

bool plays(int game_id) {
	return _game_play_records.find(game_id) != _game_play_records.end();
}

bool hasVictory(int game_id, int victory_id) {
	map<int, GamePlayRecord>::const_iterator it = _game_play_records.find(game_id);

	return it != _game_play_records.end() && it->hasVictory(victory_id);
}

vector<Player> friendsWhoPlay(int game_id) {
	vector<Player> friends_who_play;

	for (vector<Player>::const_iterator it = _friends.begin();
		it != _friends.end(); ++it;) {
		Player friend = *it;
		if (friend.plays(game_id))
			friends_who_play.push_back(friend);
	}

	return friends_who_play;
}

GamePlayRecord gamePlayRecordWithID(int game_id) {
	map<int, GamePlayRecord>::const_iterator it = _game_play_records.find(game_id);

	if (it != _game_play_records.end())
		return *it;
}