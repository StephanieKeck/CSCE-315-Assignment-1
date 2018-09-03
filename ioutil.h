#ifndef IOUTIL_H
#define IOUTIL_H

std::string::const_iterator getCommand(std::string::const_iterator, std::string::const_iterator, 
	std::string&);
std::string::const_iterator getInt(std::string::const_iterator, std::string::const_iterator, 
	int&);
std::string::const_iterator getID(std::string::const_iterator beg, std::string::const_iterator end, 
	int& n) { return getInt(beg, end, n); }
std::string::const_iterator getQuoteDelimitedString(std::string::const_iterator, 
	std::string::const_iterator, std::string&);

void outputPlayerComparisonForGame(ostream&, vector<Player>, Game);
void outputPlayerComparisonForGame(ostream&, Player, Player, Game);
void outputPlayerComparisonForGame(ostream&, Player, vector<Player>, Game);
void outputPlayerSummary(ostream&, Player);
void outputGameSummary(ostream&, Game, int, vector<Player>);
void outputVictorySummary(ostream&, Victory, int, Game, int, vector<Player>);
void outputPlayerComparison(ostream&, vector<Player>);

#endif