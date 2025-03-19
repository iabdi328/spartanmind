/**
 * @file Declaration.h
 * @author Raj Ambekar
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_DECLARATION_H
#define PROJECT1_SPARTANMINDLIB_DECLARATION_H

#include <wx/string.h>
#include <wx/xml/xml.h>

class LoadLevel;

class Declaration
{
private:
    LoadLevel *mLevel;
protected:
    Declaration(LoadLevel *level);
public:
    virtual ~Declaration() = default;
    Declaration() = delete;
    Declaration(const Declaration &) = delete;

    virtual void XmlLoad(wxXmlNode *node);

};

#endif //PROJECT1_SPARTANMINDLIB_DECLARATION_H
