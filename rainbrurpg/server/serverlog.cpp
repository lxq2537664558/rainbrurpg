/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

#include "serverlog.h"
#include "logexportdialog.h"

#include <QDateTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>

#include <logger.h>

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Server::ServerLog::ServerLog(QWidget* parent)
  :QWidget(parent)
{
  setWindowTitle(tr("Server log"));

  // The main layout
  QVBoxLayout* vb1=new QVBoxLayout();
  this->setLayout(vb1);

  // The tree
  tree=new QTreeWidget();

  QStringList header;
  header << tr("Time") << tr("Level") << tr("Message");
  tree->setColumnCount(3);
  tree->setHeaderLabels(header);
  vb1->addWidget(tree);

  // The buttons layout
  QHBoxLayout* hb1=new QHBoxLayout();
  hb1->addStretch(1);
  vb1->addLayout(hb1);

  // The clear button
  QPushButton* btnClear=new QPushButton(tr("Clear"), this);
  hb1->addWidget(btnClear);

  // The export button
  QPushButton* btnExport=new QPushButton(tr("Export"), this);
  hb1->addWidget(btnExport);

  // Treewidget sorting preferences
  tree->setSortingEnabled(true);
  tree->sortItems ( 0, Qt::AscendingOrder );


  // Connections
  connect( btnClear, SIGNAL(clicked()), SLOT(clearLog()) );
  connect( btnExport, SIGNAL(clicked()), SLOT(exportLog()) );
}

/** The destructor
  *
  */
RainbruRPG::Server::ServerLog::~ServerLog(){
  delete tree;
  tree=NULL;
}

/** Adds a log message
  *
  * \sa tServerLogLevel
  *
  * \param lvl The message log level
  * \param msg The text of the message
  *
  */
void RainbruRPG::Server::ServerLog::
addMessage(tServerLogLevel lvl, const QString& msg){
  QString l;
  QColor r=Qt::red;
  QColor c;

  QTime time=QTime::currentTime();
  QString t=time.toString("hh:mm:ss");

  switch (lvl){
  case SLL_INFORMATIVE:
    l=tr("Information");
    c=Qt::black;
    break;
  case SLL_WARNING:
    l=tr("Warning");
    c=r.light(150);
    break;
  case SLL_ERROR:
    l=tr("Error");
    c=Qt::red;
    break;

  }

  QTreeWidgetItem *item=new QTreeWidgetItem(tree);
  item->setText(0, t);
  item->setText(1, l);
  item->setText(2, msg);
  item->setTextColor(0, c);
  item->setTextColor(1, c);
  item->setTextColor(2, c);
  tree->addTopLevelItem( item );
}

/** Clears the content of the log
  *
  * It simply calls \c tree->clear() but it is a convenience
  * to add a dialog in the future, for example to keep only error
  * message or so on.
  *
  */
void RainbruRPG::Server::ServerLog::clearLog(){
  tree->clear();
}

/** Export the content in a text file
  *
  *
  */
void RainbruRPG::Server::ServerLog::exportLog(){
  // Export dialog
  LogExportDialog led(this);
  led.exec();

  QString fn=led.getFilename();

  LOGI("Exporting log :");
  LOGCATS("Log file name :");
  LOGCATS(fn.toLatin1());
  LOGCAT();

  // Header
  QFile file(fn);
  file.open(QIODevice::WriteOnly|QIODevice::Text);
  QTextStream out(&file);

  out << "RainbruRPG-Server user log" <<endl;
  out << "Exported ";

  // Date and time
  QDateTime dt=QDateTime::currentDateTime();
  QString s=dt.toString("dd MMMM yyyy");
  QString s2=dt.toString("hh::mm");
  out << s << " at " << s2 << endl<< endl;

  // Tree srialization
  serializeTree(&out);
  file.close();
}

/** Serialize the whole treeWidget
  *
  * \param ts The QTextStream we serialize the teree in
  *
  */
void RainbruRPG::Server::ServerLog::serializeTree(QTextStream* ts){
  for (int i=0; i<tree->topLevelItemCount(); i++){
    serializeTreeItem(ts, tree->topLevelItem(i));
  }
}

/** Serialize a single tree item
  *
  * \param ts The QTextStream we serialize the teree in
  * \param it The item to serialize
  *
  */
void RainbruRPG::Server::ServerLog::
serializeTreeItem(QTextStream* ts, QTreeWidgetItem* it){
  LOGI("Item serialize");

  // First column
  ts->device()->write(it->text(0).toLatin1());
  ts->device()->write(" ");

  // Second column
  ts->device()->write(it->text(1).toLatin1(), 1);
  ts->device()->write(it->text(1).toLatin1(), 1);
  ts->device()->write(" ");

  // Last column
  ts->device()->write(it->text(2).toLatin1());
  ts->device()->write("\n");

}
