#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player(std::string);
	std::string name() { return _name; }
	std::vector<Player> friends() { return _friends; }
	GamePlayRecord gamePlayRecordForGameID(int);
	int gamerscore();
	void addFriend(Player);
	void addGamePlayRecord(GamePlayRecord);

private:
	std::string _name;
	std::vector<Player> _friends;
	std::map<int, GamePlayRecord> _gamePlayRecords;
};

#endif