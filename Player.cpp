Player::Player(string name) {
	_name = name;
}

GamePlayRecord gamePlayRecordForGameID(int id) {
	typedef map<int, GamePlayRecord>::const_iterator MAP_ITERATOR;
	try {
		MAP_ITERATOR it = _gamePlayRecords.find(id);
		if (it != _gamePlayRecords.end())
			return *it;
		else
			throw domain_error("invalid Game ID in GamePlayRecord lookup");
	} catch domain_error(e) {
		cout << e.what();
	}
}

int gamerscore() {
	typedef map<int, GamePlayRecord>::const_iterator MAP_ITERATOR;

	int sumOfScores = 0;

	for (MAP_ITERATOR it = _gamePlayRecords.begin();
		it != _gamePlayRecords.end(); ++it;) {
		GamePlayRecord record = it->second;
		sumOfScores += record.gamerscore();
	}

	return sumOfScores;
}

void addFriend(Player friend) {
	_friends.push_back(friend);
}

void addGamePlayRecord(int id, Game game, string ign) {
	typedef map<int, GamePlayRecord>::const_iterator MAP_ITERATOR;

	MAP_ITERATOR it = _gamePlayRecords.find(id);
	if (it == _gamePlayRecords.end())
		_gamePlayRecords[id] = GamePlayRecord(game, ign);
}