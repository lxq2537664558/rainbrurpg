#include "tabenvironment.h"

#include "QVBoxLayout"

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Editor::TabEnvironment::TabEnvironment(QWidget *parent)
               : QWidget(parent){

  QVBoxLayout* layout=new QVBoxLayout(this);
  this->setLayout(layout);

  toolBox=new QToolBox(this);
  QWidget* fogPage=new QWidget(this);
  QWidget* ambientPage=new QWidget(this);
  toolBox->addItem(fogPage, "Fog");
  toolBox->addItem(ambientPage, "Ambient");

  layout->addWidget(toolBox);
}

/** The destructor
  *
  */
RainbruRPG::Editor::TabEnvironment::~TabEnvironment(){

}
