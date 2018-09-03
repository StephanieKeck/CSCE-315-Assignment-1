#ifndef GAMEPLAYRECORD_H
#define GAMEPLAYRECORD_H value

class GamePlayRecord
{
public:
	GamePlayRecord(Game, std::string);

	std::string ign() { return _ign; }
	int gamerscore();
	bool hasVictory(int);

	void addVictory(int);

	std::vector<Victory> victories();	
private:
	Game _game;
	std::string _ign;
	std::vector<int> _victory_ids;
};

#endif