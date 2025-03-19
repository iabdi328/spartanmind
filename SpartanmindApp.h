/**
* @file SpartanmindApp.h
 * @author Raj Ambekar, Ismail Abdi
 *
 *
 */

#ifndef PROJECT1__SPARTANMINDAPP_H
#define PROJECT1__SPARTANMINDAPP_H

class SpartanmindApp : public wxApp
{
private:

public:
	bool OnInit() override;
	int OnExit() override;

};

#endif //PROJECT1__SPARTANMINDAPP_H