void addGame(int game_id, Game game) {
	_games[game_id] = game;
}

Game gameWithID(int) {
	map<int, Game>::const_iterator it = _games.find(game_id);

	if (it != _games.end())
		return *it;
}