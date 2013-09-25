#ifndef TAB_ENVIRONMENT_H
#define TAB_ENVIRONMENT_H

#include <QWidget>
#include <QToolBox>

namespace RainbruRPG{
  namespace Editor{
    /** The tab parameters environment
      *
      * This Qt widget is used in the editor. It provides an environment
      * customization.
      *
      */
    class TabEnvironment : public QWidget{
      Q_OBJECT
	
	public:
      TabEnvironment(QWidget *parent = 0);
      ~TabEnvironment();

    private:
      /** A toolbox used to separate different parameter */
      QToolBox* toolBox;
      
    };
    
  }
}

#endif // TAB_ENVIRONMENT_H
