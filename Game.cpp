Game::Game(string name) {
	_name = name;
}

void addVictory(int victory_id, Victory victory) {
	_victories[victory_id] = victory;
}

Victory victoryWithID(int victory_id) {
	map<int, Victory>::const_iterator it = _victories.find(game_id);

	if (it != _victories.end())
		return *it;
}

vector<Victory> victories() {
	vector<Victory> all_victories;

	for (map<int, Victory>::const_iterator it = _victories.begin();
		it != _victories.end(); ++it;) {
		Victory victory = it->second;
		all_victories.push_back(victory);
	}

	return victories;
}

vector<int> victoryIDs() {
	vector<int> all_victory_ids;

	for (map<int, Victory>::const_iterator it = _victories.begin();
		it != _victories.end(); ++it;) {
		int id = it->first;
		all_victory_ids.push_back(id);
	}

	return all_victory_ids;
}