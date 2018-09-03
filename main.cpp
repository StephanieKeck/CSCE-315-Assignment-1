
int main() {
	Players players;
	Games games;

	string lineOfInput;
	while (getline(cin), lineOfInput) {
		typedef string::const_iterator iter;

		string command;
		iter i = lineOfInput.begin();
		i = getCommand(lineOfInput, command);

		if (i != lineOfInput.end()) {
			string addPlayerCommand = "AddPlayer";
			string addGameCommand = "AddGame";
			string addVictoryCommand = "AddVictory";
			string playsCommand = "Plays";
			string addFriendsCommand = "AddFriends";
			string winVictoryCommand = "WinVictory";
			string friendsWhoPlayCommand = "FriendsWhoPlay";
			string comparePlayersCommand = "ComparePlayers";
			string summarizePlayerCommand = "SummarizePlayer";
			string summarizeGameCommand = "SummarizeGame";
			string summarizeVictoryCommand = "SummarizeVictory";
			string victoryRankingCommand = "VictoryRanking";

			if (command == addPlayerCommand) {
				int player_id;
				string name;

				i = getID(i, lineOfInput.end(), player_id);
				i = getQuoteDelimitedString(i, lineOfInput.end(), name);

				Player newPlayer = Player(name);
				players.addPlayer(player_id, newPlayer);
			} else if (command == addGameCommand) {
				int game_id;
				string name;

				i = getID(i, lineOfInput.end(), game_id);
				i = getQuoteDelimitedString(i, lineOfInput.end(), name);

				Game newGame = Game(name);
				games.addGame(game_id, newGame);
			} else if (command == addVictoryCommand) {
				int game_id;
				int victory_id;
				string victory_name;
				int victory_points;

				i = getID(i, lineOfInput.end(), game_id);
				i = getID(i, lineOfInput.end(), victory_id);
				i = getQuoteDelimitedString(i, lineOfInput.end(), victory_name);
				i = getInt(i, lineOfInput.end(), victory_points);

				Game game = games.gameWithID(game_id);

				Victory newVictory = Victory(victory_name, victory_points);
				game.addVictory(victory_id, newVictory);
			} else if (command == playsCommand) {
				int player_id;
				int game_id;
				string player_ign;

				i = getID(i, lineOfInput.end(), player_id);
				i = getID(i, lineOfInput.end(), game_id);
				i = getQuoteDelimitedString(i, lineOfInput.end(), player_ign);

				Player player = players.playerWithID(player_id);
				Game game = games.gameWithID(game_id);

				GamePlayRecord record = GamePlayRecord(game, player_ign);
				player.addGamePlayRecord(record);
			} else if (command == addFriendsCommand) {
				int player_id1;
				int player_id2;

				i = getID(i, lineOfInput.end(), player_id1);
				i = getID(i, lineOfInput.end(), player_id2);

				Player player1 = players.playerWithID(player_id1);
				Player player2 = players.playerWithID(player_id2);

				player1.addFriend(player2);
				player2.addFriend(player1);
			} else if (command == winVictoryCommand) {
				int player_id;
				int game_id;
				int victory_id;

				i = getID(i, lineOfInput.end(), player_id);
				i = getID(i, lineOfInput.end(), game_id);
				i = getID(i, lineOfInput.end(), victory_id);

				Player player = players.playerWithID(player_id);
				GamePlayRecord record = player.gamePlayRecordWithID(game_id);

				record.addVictory(victory_id);
			} else if (command == friendsWhoPlayCommand) {
				int player_id;
				int game_id;

				i = getID(i, lineOfInput.end(), player_id);
				i = getID(i, lineOfInput.end(), game_id);

				Player player = players.playerWithID(player_id);
				Game game = games.gameWithID(game_id);

				cout << "Player: " << player.name() << endl
				     << "Game: " << game.name()<< endl
				     << endl;

				vector<Player> friends_who_play = player.friendsWhoPlay(game_id);
				outputPlayerComparisonForGame(cout, player, friends_who_play, game);
			} else if (command == comparePlayersCommand) {
				int player_id1;
				int player_id2;
				int game_id;

				i = getID(i, lineOfInput.end(), player_id1);
				i = getID(i, lineOfInput.end(), player_id2);
				i = getID(i, lineOfInput.end(), game_id);

				Player player1 = players.playerWithID(player_id1);
				Player player2 = players.playerWithID(player_id2);

				Game game = games.gameWithID(game_id);

				cout << "Player 1: " << player1.name() << endl
				     << "Player 2: " << player2.name() << endl
				     << "Game: " << game.name() << endl
				     << endl;

				outputPlayerComparisonForGame(cout, player1, player2, game);
			} else if (command == summarizePlayerCommand) {
				int player_id;

				i = getID(i, lineOfInput.end(), player_id);

				Player player = players.playerWithID(player_id);

				cout << "Player: " << player.name() << endl
				     << "Total Gamerscore: " << player.gamerscore() << endl
				     << endl;

				outputPlayerSummary(cout, player);
			} else if (command == summarizeGameCommand) {
				int game_id;

				i = getID(i, lineOfInput.end(), game_id);

				Game game = games.gameWithID(game_id);

				vector<Player> players_who_play = players,playersWhoPlay(game_id);

				cout << "Game: " << game.name() << endl
					 << "Players: " << (int) players_who_play.size() << endl
				     << endl;

				outputGameSummary(cout, game, game_id, players_who_play);
			} else if (command == summarizeVictoryCommand) {
				int game_id;
				int victory_id;

				i = getID(i, lineOfInput.end(), game_id);
				i = getID(i, lineOfInput.end(), victory_id);

				Game game = games.gameWithID(game_id);
				Victory victory = game.victoryWithID(victory_id);

				vector<Player> players_who_play = players.playersWhoPlay(game_id);
				vector<Player> players_with_victory = players.playersWithVictory(game_id, victory_id);

				double victory_achieved_percentage = (double) players_with_victory.size() / players_who_play.size();

				cout << "Game: " << game.name() << endl
				     << "Players: " << (int) players_who_play.size() << endl
				     << "Victory Name: " << victory.name() << endl
				     << "Victory Points: " << victory.points() << endl
				     << "Acheived By: " << (int) players_with_victory.size() << " Players" << endl
				     << "Achieved Percentage: " << victory_achieved_percentage << "%" << endl
				     << endl;

				outputVictorySummary(cout, victory, victory_id, game, game_id, players_who_play);
			} else if (command == victoryRankingCommand) {
				vector<Player> allPlayers = players.players();

				outputPlayerComparison(cout, allPlayers);
			}
		}
	}
}