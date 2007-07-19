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

/** Constructor
  *
  * \param filename The filename with absolute path
  * \param parent The parent widget
  *
  */
RainbruRPG::Gui::FilePreview::
FilePreview(const QString& filename, QWidget* parent)
  :QDialog(parent){

  setWindowTitle("File preview");
  help=NULL;

  QVBoxLayout* layout=new QVBoxLayout(this);
  this->setLayout(layout);

  this->filename=filename;
  std::string strFn(filename.toLatin1());
  strFilename=strFn;

  if (!mimeDispatcher()){
    if(!extDispatcher()){
      showMessage(tr("This file cannot be previewed. Please "
		     "use an external program."));

    }
    else{
      setMinimumSize(400, 300);
    }
  }
  else{
    setMinimumSize(400, 300);
  }
 
  // The dialog's button
  QHBoxLayout *buttonLayout=new QHBoxLayout();
  layout->addLayout(buttonLayout);
  buttonLayout->addStretch(100);
  QPushButton* quit=new QPushButton(tr("Quit"));
  buttonLayout->addWidget(quit);

  connect(quit, SIGNAL(clicked()), this, SLOT(accept()));
}

/** The destructor
  *
  */
RainbruRPG::Gui::FilePreview::~FilePreview(){
  if (help)
    delete help;
}

/** Dispatch the mime-type and show preview for known ones
  *
  * Provides preview for \c image/*, \c text/plain, \c text/html.
  *
  * \return \c true if a preview is launched, \c false otherwise
  *
  */
bool RainbruRPG::Gui::FilePreview::mimeDispatcher(){

  FileTypeGuesser ftg;
  std::string s=ftg.getMimeType(strFilename);
  QString qs(s.c_str());

  if (qs.contains("image/")){
    imagePreview();
    return true;
  }
  else if (qs.contains("text/plain")){
    textPreview();
    return true;
  }
  else if (qs.contains("text/html")){
    htmlPreview();
    return true;
  }
  else{
    return false;
  }
}

/** Dispatch the file extension and show preview for known ones
  *
  * Provides preview for none.
  *
  * \return \c true if a preview is launched, \c false otherwise
  *
  */
bool RainbruRPG::Gui::FilePreview::extDispatcher(){
  return false;
}

/** Shows an image preview
  *
  */
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

/** Shows a plain text preview
  *
  */
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
    showMessage(tr("Cannot read this file"));

  }
}

/** Shows a message instead a preview widget
  *
  */
void RainbruRPG::Gui::FilePreview::showMessage(const QString& msg){
  if (!help){
    help=new QLabel( this);
    help->setWordWrap(true);
    layout()->addWidget(help);
  }

  help->setText(msg);
}

/** Shows a HTML preview
  *
  */
void RainbruRPG::Gui::FilePreview::htmlPreview(){
  setWindowTitle("Html text preview");

  QTextBrowser* text=new QTextBrowser(this);
  text->setSource(QUrl(filename));
  layout()->addWidget(text);  
  setMinimumSize(800, 600);
 
}
