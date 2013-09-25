#include "loglistener.h"

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
myLogListener::myLogListener(QWidget* parent) 
  : LogListener(), QWidget(parent){

}

/** The default destructor
  *
  */
myLogListener::~myLogListener(){
}

/** Write a new log message
  *
  * \param name An unused parameter
  * \param msg The log message
  * \param lvl An unused parameter
  * \param maskDebug An unused parameter
  *
  */
void myLogListener::write(const Ogre::String& name, const Ogre::String& msg, Ogre::LogMessageLevel lvl, bool maskDebug)
{
	Q_UNUSED(name);
	Q_UNUSED(lvl);
	Q_UNUSED(maskDebug);
	logMsg = msg.c_str();
}

/** Gets the logged message
  *
  * \return The logged message
  *
  */
QString myLogListener::getMsg()
{
	return logMsg;
}
