/*
 *  Copyright 2006-2007 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "filepreview.h"

RainbruRPG::Gui::FilePreview::
FilePreview(const QString& filename, QWidget* parent)
  :QDialog(parent){

  setWindowTitle("File preview");
  setMinimumSize(400, 300);

  QVBoxLayout* layout=new QVBoxLayout(this);
  this->setLayout(layout);

  help=new QLabel(this);
  help->setWordWrap(true);
  layout->addWidget(help);

  this->filename=filename;
  std::string strFn(filename.toLatin1());
  strFilename=strFn;
  /*
  if (!mimeDispatcher()){
    if(!extDispatcher()){
      showMessage(tr("This file cannot be previewed. Please "
		     "use an external program."));

    }
  }
  */

  // The dialog's button
  QHBoxLayout *buttonLayout=new QHBoxLayout();
  layout->addLayout(buttonLayout);
  buttonLayout->addStretch(100);
  QPushButton* quit=new QPushButton(tr("Quit"));
  buttonLayout->addWidget(quit);

  connect(quit, SIGNAL(clicked()), this, SLOT(accept()));
}

RainbruRPG::Gui::FilePreview::~FilePreview(){
  delete help;
}


bool RainbruRPG::Gui::FilePreview::mimeDispatcher(){

  FileTypeGuesser ftg;
  std::string s=ftg.getMimeType(strFilename);
  QString qs(s.c_str());

  if (s=="image/png"){
    imagePreview();
    return true;
  }
  else if (qs.contains("text/plain")){
      textPreview();
    return true;
  }
}

bool RainbruRPG::Gui::FilePreview::extDispatcher(){
  return false;
}

void RainbruRPG::Gui::FilePreview::imagePreview(){
  setWindowTitle("Image preview");

  QImage image(filename);
  if (image.isNull()) {
    showMessage(tr("Cannot load image file"));
  }
  else{
    QLabel * imageLabel=new QLabel();
    layout()->addWidget(imageLabel);  
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(QPixmap::fromImage(image));
  }
}

void RainbruRPG::Gui::FilePreview::textPreview(){
  setWindowTitle("Plain text preview");

  QFile file(filename);
  if(file.open(QIODevice::ReadOnly)){
    QTextEdit* textEdit=new QTextEdit(this);
    textEdit->setCurrentFont(QFont("Courrier", 8));
    textEdit->setPlainText(file.readAll());
    layout()->addWidget(textEdit);  
    file.close();
  }
  else{

  }
}

void RainbruRPG::Gui::FilePreview::showMessage(const QString& msg){
  help->setText(msg);
}
