/**
 * @file Given.h
 * @author Daniel Conti
 *
 *
 */
 
#ifndef GIVEN_H
#define GIVEN_H
#include "Letter.h"


class Given : public Letter {
private:
public:
    Given(Spartanmind* spartanmind, const std::wstring& filename, const wxString& id, wxString width, wxString height,
          const wxString& image, wxString value, wxString col, wxString row);
};



#endif //GIVEN_H
