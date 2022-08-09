#include "Destinator.h"
#include <string>

std::string Destinator::getOrigin()
{
	return origin;
}
std::string Destinator::getDestination()
{
	return destination;
}
void Destinator::setOrigin(std::string input)
{
	origin = input;
}
void Destinator::setDestination(std::string input)
{
	destination = input;
}
