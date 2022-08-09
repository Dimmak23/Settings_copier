#ifndef DESTINATOR_H
#define DESTINATOR_H

#include <string>

class Destinator
{
	private:
		std::string origin = "";
		std::string destination = "";

	public:

		bool ready = false;

		bool cmaker = false;

		std::string getOrigin();
		std::string getDestination();
		void setOrigin(std::string input);
		void setDestination(std::string input);

};

struct testing
{
		int unit;
};

#endif // DESTINATOR_H
