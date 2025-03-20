/**
* @file SpartanmindApp.h
 * @author Raj Ambekar, Ismail Abdi
 *
 * The General Game App
 */

#ifndef PROJECT1__SPARTANMINDAPP_H
#define PROJECT1__SPARTANMINDAPP_H

/**
 * The General Game App
 */
class SpartanmindApp : public wxApp
{
private:

public:
	bool OnInit() override;
	int OnExit() override;

};

#endif //PROJECT1__SPARTANMINDAPP_H