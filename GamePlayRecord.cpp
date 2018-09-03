GamePlayRecord::GamePlayRecord(Game game, string ign) {
	_game = game;
	_ign = ign;
}

int gamerscore() {
	int score = 0;

	for (vector<int>::const_iterator it = _victory_ids.begin();
		it != _victory_ids.end(); ++it;) {
		int id = *it;
		Victory victory = _game.victoryWithID(id);
		score += victory.points();
	}

	return score;
}

bool hasVictory(int victory_id) {
	return find(_victory_ids.begin(), _victory_ids.end(), victory_id) != _victory_ids.end();
}

void addVictory(int victory_id) {
	if (!hasVictory(victory_id))
		_victory_ids.push_back(victory_id);
}

vector<Victory> victories() {
	vector<Victory> all_victories;

	for (vector<int>::const_iterator it = _victory_ids.begin();
		it != _victory_ids.end(); ++it;) {
		int id = *it;
		Victory victory = _game.victoryWithID(id);
		all_victories.push_back(victory);
	}

	return all_victories;
}