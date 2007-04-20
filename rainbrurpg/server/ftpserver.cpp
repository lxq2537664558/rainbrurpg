#include "ftpserver.h"

/** The constructor
  *
  * \param port The port used to connect to the Protocol Interpreter
  *
  */
FtpServer::FtpServer(quint16 port)
  : QWidget(){

  setWindowTitle("RainbruRPG FTP server");
  setMinimumWidth(600);

  QVBoxLayout *mainLayout = new QVBoxLayout;

  // Control widgets
  QLabel* lab1=new QLabel(tr("Control :"), this);
  mainLayout->addWidget(lab1);
  textEdit=new QTextEdit(this);
  mainLayout->addWidget(textEdit);
  setLayout(mainLayout);

  // Transfert widgets
  QLabel* lab2=new QLabel(tr("Transfert :"), this);
  mainLayout->addWidget(lab2);
  tree=new QTreeWidget(this);
  QStringList sl;
  sl << "Ip" << "Filename" << "In/Out" << "Rate" << "Progress";
  tree->setHeaderLabels( sl );
  mainLayout->addWidget(tree);


  control=new FtpControl(50002);
  connect(control, SIGNAL(log(const QString&)), this, 
	  SLOT(log(const QString&)));
  control->run();

  transfer=new FtpTransfer(50001);
  connect(transfer, SIGNAL(log(const QString&)), this, 
	  SLOT(log(const QString&)));
  transfer->run();

  TransferVisual* tv=new TransferVisual();
  tv->setIp("123.23.12.123");
  tv->setFilename("essai.txt", "home/aze");
  addTransfer(tv);
}

/** The destructor
  *
  */
FtpServer::~FtpServer(){
  control->quit();
  delete control;
  transfer->quit();
  delete transfer;
  delete tree;
}

/** Log a message in the textEdit
  *
  * \param s The string to append
  *
  */
void FtpServer::log(const QString&s){
  textEdit->append(s);
}

void FtpServer::addTransfer(TransferVisual* tv){
  QTreeWidgetItem *wi=new QTreeWidgetItem();
  wi->setText(0,tv->getIp());
  wi->setText(1,tv->getFilename());
  tree->addTopLevelItem(wi);
}
