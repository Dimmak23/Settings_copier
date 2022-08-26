#ifndef DESTINATOR_H
#define DESTINATOR_H

#include <string>
#include <QString>

class Destinator
{
	private:
		std::string origin {""};
		std::string destination {""};
		std::string project_name {""};

	public:
		//don't need?
		bool ready = false;

		bool cmaker = false;

		bool error_caught = false;

		std::string getOrigin () const;
		std::string getDestination() const;
		std::string getProject() const;
		void setOrigin(const std::string &input);
		void setDestination(const std::string &input);
		void setProjectName(const std::string &input = "Untitled");

};

//don't need?
struct testing
{
		int unit;
};

#endif // DESTINATOR_H
