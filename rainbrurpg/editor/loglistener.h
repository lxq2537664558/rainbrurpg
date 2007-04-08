#ifndef MY_LOG_LISTENER
#define MY_LOG_LISTENER

#include <OGRE/Ogre.h>
#include <QWidget>


/** A subclass of Ogre::LogListener showing messages in a QWidget
  *
  */
class myLogListener : public Ogre::LogListener, QWidget
{
public:
	myLogListener(QWidget* parent = 0);
	~myLogListener();

	void write(const Ogre::String &name, const Ogre::String &message,
			   Ogre::LogMessageLevel lml=Ogre::LML_CRITICAL, bool maskDebug=true);
	QString getMsg();

private:
	/** The log message */
	QString logMsg;
};

#endif // MY_LOG_LISTENER
