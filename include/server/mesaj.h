#ifndef __MESAJ_H
#define __MESAJ_H

#include <string>


class MESAJ {
	public:
		MESAJ ();
		~MESAJ ();
                MESAJ (const MESAJ& mesaj); // copy constructor
                std::string& getName ();
                std::string& getComment ();
	private:
		std::string name;
		std::string comment;
};

#endif
