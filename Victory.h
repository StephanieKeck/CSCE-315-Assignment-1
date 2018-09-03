#ifndef VICTORY_H
#define VICTORY_H

class Victory
{
public:
	Victory(std::string, int);
	std::string name() { return _name; }
	int points() { return _points; }
private:
	std::string _name;
	int _points;
};

#endif