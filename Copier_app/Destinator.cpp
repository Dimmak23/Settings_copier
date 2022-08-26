#include "Destinator.h"
#include <string>

std::string Destinator::getOrigin() const
{
	return origin;
}
std::string Destinator::getDestination() const
{
	return destination;
}
std::string Destinator::getProject() const
{
	return project_name;
}
void Destinator::setOrigin(const std::string &input)
{
	origin = input;
}
void Destinator::setDestination(const std::string &input)
{
	destination = input;
}
void Destinator::setProjectName(const std::string &input)
{
	if (input == "Untitled")
	{
		const auto position = destination.find_last_of('\\');
		project_name = destination.substr(position);
	}
	else
	{
		project_name = input;
	}
}
