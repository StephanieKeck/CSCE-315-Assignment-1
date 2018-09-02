#ifndef PLAYERS_H
#define PLAYERS_H

class Players
{
public:
	Players();
	void addPlayer(int, string);
	Player playerByID(int);
	vector<Player> players();
private:
	map<int, Player> _players;
};

#endif