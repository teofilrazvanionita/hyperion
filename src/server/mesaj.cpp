#include "mesaj.h"

MESAJ::MESAJ()
{

}

MESAJ::~MESAJ()
{

}

//copy constructor
MESAJ::MESAJ(const MESAJ& mesaj)
{
    name = ((MESAJ &)mesaj).getName();
    comment = ((MESAJ &)mesaj).getComment();
}

std::string& MESAJ::getName()
{
    return name;
}

std::string& MESAJ::getComment()
{
    return comment;
}