// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

/*  Victory Class
 *  -------------
 *  Holds information related to victories associated with particular
 *  games.
 *  
 *  Constructor(s):
 *
 *  * Victory(string name, int points) - 'name' and 'points' are the 
 *    name and points associated with this victory respectively.
 *  
 *  Accessor Methods:
 *  
 *  * string name() - returns the name of this victory.
 *  * int points() - returns the amount of points the victory is
 *    worth.
 */

#ifndef VICTORY_H
#define VICTORY_H

#include <string>

class Victory {
public:

	// Constructors:

	Victory();
	Victory(std::string, int);

	// Accessor Methods:

	std::string name() const { return _name; }
	int points() const { return _points; }
private:
	std::string _name;
	int _points;
};

#endif