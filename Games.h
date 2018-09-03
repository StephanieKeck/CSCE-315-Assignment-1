#ifndef GAMES_H
#define GAMES_H

class Games
{
public:
	void addGame(int, Game);
	Game gameWithID(int);
private:
	map<int, Game> _games;
};

#endif