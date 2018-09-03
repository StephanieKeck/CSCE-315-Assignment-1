#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(std::string);

	void addFriend(Player);
	void addGamePlayRecord(int, GamePlayRecord);

	std::string name() { return _name; }
	int gamerscore();
	bool plays(int);
	bool hasVictory(int, int);

	std::vector<Player> friends() { return _friends; }
	std::vector<Player> friendsWhoPlay(int);
	GamePlayRecord gamePlayRecordWithID(int);

private:
	std::string _name;
	std::vector<Player> _friends;
	std::map<int, GamePlayRecord> _game_play_records;
};

#endif