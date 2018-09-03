// Stephanie Keck
// UIN 526009919
// CSCE 315 508
// Project 1

#include <string>
#include "Victory.h"

using namespace std;

// -------------
// Constructors:
// -------------


Victory::Victory() {
	_name = "";
}


/*  (name, points) constructor
 *  --------------------------
 *  'name' and 'points' are the name and points associated with 
 *  this victory respectively.
 */
Victory::Victory(string name, int points) {
	// set private fields to parameter values
	_name = name;
	_points = points;
}