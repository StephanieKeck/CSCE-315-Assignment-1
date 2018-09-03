#ifndef GAME_H
#define GAME_H

class Game
{
public:
	Game(std::string);
	std::string name() { return _name; }
	
	void addVictory(int, Victory);

	Victory victoryWithID(int);
	vector<Victory> victories();
	vector<int> victoryIDs();
private:
	std::string _name;
	std::map<int, Victory> _victories;
};

#endif