#ifndef PLAYERS_H
#define PLAYERS_H

class Players
{
public:
	void addPlayer(int, Player);
	Player playerWithID(int);
	vector<Player> playersWhoPlay(int);
	vector<Player> playersWithVictory(int, int);
	vector<Player> players();
private:
	map<int, Player> _players;
};

#endif