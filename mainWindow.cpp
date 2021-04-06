#include <QtGui>
#include "mainWindow.hpp"
#include "canvas.hpp"

MainWindow::MainWindow()
{
	//this->cursor;
	this->bitmapCursor;
	
    this->canvas = new Canvas;
    setCentralWidget(this->canvas);
    createActions();
    createMenus();
        
    //Spin Box do numero de lados do polígono    
    this->spinNumLadosPolig = new QSpinBox;
    this->spinNumLadosPolig->setGeometry(10,10,50,10);
    this->spinNumLadosPolig->setMaximum(29);
    this->spinNumLadosPolig->setMinimum(3);
    this->spinNumLadosPolig->setEnabled(true);
    //
    
    //Label que diz Mostra: Lados
    this->numLadosPoligLab = new QLabel(tr("Lados:   "));
    //
    
    // quando muda o valor da spin box muda o valor dos lados no canvas
    connect(spinNumLadosPolig, SIGNAL(valueChanged(int)),this, SLOT(getNumLadosPoligono(int)));
     
    // Spin Box do angulo do arco
    this->spinAnguloArco = new QSpinBox;
    this->spinAnguloArco->setGeometry(10,10,50,10);
    this->spinAnguloArco->setMaximum(360);
    this->spinAnguloArco->setMinimum(1);
    this->spinAnguloArco->setValue(360);
    this->spinAnguloArco->setEnabled(true);
    
    //
    
    //Label do angulo do arco
    this->labelAnguloArco = new QLabel(tr("Angulo:   "));
    //
    
    // quando muda o valor da spin box muda o valor dos lados no canvas
    connect(spinAnguloArco, SIGNAL(valueChanged(int)),this, SLOT(getAnguloArco(int)));
    
    setAttribute(Qt::WA_DeleteOnClose);
    
    //createContextMenu();
    createToolBars();
    //createStatusBar();
    //readSettings();
    setWindowIcon(QIcon(":/imagens/icon.png"));
    setArquivoCorrente("");
}

void MainWindow::createActions()
{  
    /* inicio acoes do menu superior e da toolbar superior */
    this->novoAction = new QAction(tr("&Novo"), this);
    this->novoAction->setIcon(QIcon(":/imagens/new.png"));
    this->novoAction->setShortcut(tr("Ctrl+N"));
    this->novoAction->setStatusTip(tr("Cria um novo arquivo"));
    connect(this->novoAction, SIGNAL(triggered()), this, SLOT(NovoArquivo()));

    this->abrirAction = new QAction(tr("&Abrir"), this);
    this->abrirAction->setIcon(QIcon(":/imagens/open.png"));
    this->abrirAction->setShortcut(tr("Ctrl+A"));
    this->abrirAction->setStatusTip(tr("Abre um arquivo"));
    connect(this->abrirAction, SIGNAL(triggered()), this, SLOT(Abrir()));

    this->salvarAction = new QAction(tr("&Salvar"), this);
    this->salvarAction->setIcon(QIcon(":/imagens/save.png"));
    this->salvarAction->setShortcut(tr("Ctrl+S"));
    this->salvarAction->setStatusTip(tr("Salva um arquivo"));
    connect(this->salvarAction, SIGNAL(triggered()), this, SLOT(Salvar()));

    this->salvarComoAction = new QAction(tr("Salvar &Como"), this);
    this->salvarComoAction->setStatusTip(tr("Salva um arquivo"));
    connect(this->salvarComoAction, SIGNAL(triggered()), this, SLOT(SalvarComo()));

    sairAction = new QAction(tr("&Sair"), this);
    this->sairAction->setShortcut(tr("Ctrl+Q"));
    this->sairAction->setStatusTip(tr("Sair do Jagun"));
    connect(this->sairAction, SIGNAL(triggered()),
            qApp, SLOT(closeAllWindows()));

    this->sobreAction = new QAction(tr("&Sobre"), this);
    this->sobreAction->setStatusTip(tr("Mostra a Caixa de Dialogo Sobre o Jagun"));
    connect(this->sobreAction, SIGNAL(triggered()), qApp, SLOT(Sobre()));
    /* fim acoes do menu e da toolbar superior */

   /* inicio acoes toolbar lateral */
   
    this->padraoAction = new QAction(tr("&Edicao"), this);
    this->padraoAction->setIcon(QIcon(":/imagens/seta.png"));
    this->padraoAction->setShortcut(tr("Ctrl+Shift+M"));
    this->padraoAction->setStatusTip(tr("Edicao de Figuras"));
    connect(this->padraoAction, SIGNAL(triggered()), this, SLOT(setPadrao()));
    
   this->polilinhaAction = new QAction(tr("&Polilinha"), this);
   this->polilinhaAction->setIcon(QIcon(":/imagens/linha.png"));
   this->polilinhaAction->setShortcut(tr("Ctrl+Shift+L"));
   this->polilinhaAction->setStatusTip(tr("Cria uma nova polilinha"));
   connect(this->polilinhaAction, SIGNAL(triggered()), this, SLOT(preDesenhoPolilinha()));
   
   this->poligonoAction = new QAction(tr("&Poligono"), this);
   this->poligonoAction->setIcon(QIcon(":/imagens/poligono.png"));
   this->poligonoAction->setShortcut(tr("Ctrl+Shift+P"));
   this->poligonoAction->setStatusTip(tr("Cria um novo poligono"));
   connect(this->poligonoAction, SIGNAL(triggered()), this, SLOT(preDesenhoPoligono()));
   
   this->arcoAction = new QAction(tr("&Arco e Circulo"), this);
   this->arcoAction->setIcon(QIcon(":/imagens/arco.png"));
   this->arcoAction->setShortcut(tr("Ctrl+Shift+A"));
   this->arcoAction->setStatusTip(tr("Cria um novo arco"));
   connect(this->arcoAction, SIGNAL(triggered()), this, SLOT(preDesenhoArco()));
   
   
   /* fim acoes toolbar lateral */
}

void MainWindow::createMenus()
{
    this->arquivoMenu = menuBar()->addMenu(tr("&Arquivo"));
    this->arquivoMenu->addAction(this->novoAction);
    this->arquivoMenu->addAction(this->abrirAction);
    this->arquivoMenu->addAction(this->salvarAction);
    this->arquivoMenu->addAction(this->salvarComoAction);
    this->arquivoMenu->addSeparator();
    
    this->arquivoMenu->addAction(this->sairAction);
    
    this->ajudaMenu = menuBar()->addMenu(tr("A&juda"));
    this->ajudaMenu->addAction(sobreAction);
    
}

void MainWindow::createToolBars()
{
    /* toolbar superior */
    this->arquivoToolBar = addToolBar(tr("&Arquivo"));
    this->arquivoToolBar->addAction(novoAction);
    this->arquivoToolBar->addAction(abrirAction);
    this->arquivoToolBar->addAction(salvarAction);
    addToolBar ( Qt::TopToolBarArea, this->arquivoToolBar );

    /*Toolbar de propriedades do poligono*/
    this->propriedadesPoligonoToolBar = addToolBar(tr("&Propriedades do Poligono"));
    
    //label do numero de lados
    this->propriedadesPoligonoToolBar->addWidget(this->numLadosPoligLab);
    //numero de lados do polígono
    this->propriedadesPoligonoToolBar->addWidget(this->spinNumLadosPolig);
    this->propriedadesPoligonoToolBar->setVisible(false);
    
    /*Toolbar de propriedades do arco*/
     this->propriedadesArcoToolBar = addToolBar(tr("&Propriedades do Arco"));
    //label do angulo
    this->propriedadesArcoToolBar->addWidget(this->labelAnguloArco);
    //angulo do arco
    this->propriedadesArcoToolBar->addWidget(this->spinAnguloArco);
    this->propriedadesArcoToolBar->setVisible(false);
    
    
    
    addToolBar ( Qt::TopToolBarArea, this->propriedadesPoligonoToolBar );
    //addToolBar ( Qt::TopToolBarArea, this->propriedadesArcoToolBar );  
    
     /*  toolbar lateral*/
    this->ferramentasToolBar = addToolBar(tr("&Ferramentas"));
    this->ferramentasToolBar->addAction(padraoAction);
    this->ferramentasToolBar->addAction(polilinhaAction);
    this->ferramentasToolBar->addAction(poligonoAction);
    this->ferramentasToolBar->addAction(arcoAction);
    addToolBar ( Qt::LeftToolBarArea, this->ferramentasToolBar );

}

/*criando novo arquivo*/
void MainWindow::NovoArquivo()
{
   /* if (okToContinue()) {
          setArquivoCorrente("");
    } */
}

void MainWindow::Abrir()
{
	//TODO
}

bool MainWindow::Salvar()
{
   if (curFile.isEmpty()) {
        return SalvarComo();
   } 
   else {
        return salvarArquivo(this->curFile);
   }
  
}

bool MainWindow::salvarArquivo(const QString &fileName)
{
    //escrevendo no xml
    if(!EscreverXML(fileName)) {
        //statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }
    //colocando arquivo corrente
    setArquivoCorrente(fileName);
    //statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}


bool MainWindow::okToContinue()
{
     int r = QMessageBox::warning(this, tr("Jagun"),
                        tr("O Documento foi modificado.\n"
                           "Voce deseja salvar suas mudancas?"),
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::No,
                        QMessageBox::Cancel | QMessageBox::Escape);
     if (r == QMessageBox::Yes) {
            return Salvar();
     } else if (r == QMessageBox::Cancel) {
            return false;
       }
    
    return true;
}

/*colocando arquivo corrente*/
void MainWindow::setArquivoCorrente(const QString &fileName)
{
    this->curFile = fileName;
    setWindowModified(false);
    QString shownName = "Novo";
    if (!curFile.isEmpty()) {
        shownName = strippedName(this->curFile);
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName)
                                   .arg(tr("Jagun")));
}

/*nome completo do arquivo*/
QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

//salvar como
bool MainWindow::SalvarComo()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                               tr("Salvar Arquivo Jagun"), ".",
                               tr("Documento XML (*.xml)"));
    if (fileName.isEmpty())
        return false;
    return salvarArquivo(fileName);
}

bool MainWindow::EscreverXML(const QString &arquivoNome)
{
    //cor da figura em QColor
   QColor corFiguraAtual;
   
   int v; //contador

   //cor da figura em RGB real
   qreal r;
   qreal g;
   qreal b;
   
   //tag polilinha
   QDomElement polilinhaD;
    
   //coordenadas dos vértices
   float cordxVerticeFiguraAtual;
   float cordyVerticeFiguraAtual;
   
   //tag poligono
   QDomElement poligonoD;

   //centro do polígono
   float centroXFiguraAtual;
   float centroYFiguraAtual;
   //pRef do polígono 
   float pRefXFiguraAtual;
   float pRefYFiguraAtual;
   
   //tag centro, usada em arco e polígono 
   QDomElement centro;
   //valor do centro, usada em arco e polígono 
   QDomText centroV;
   //tag pRef, usada em arco e círculo 
   QDomElement pontoR;
   //valor do pRef, usada em arco e polígono
   QDomText pontoRV;
   //tag angulo, usada em arco 
   QDomElement angulo;
   //valor de angulo, usada em arco 
   QDomText anguloV;
   //tag lados, usada em polígono 
   QDomElement lados;
   //valor de lados, usada em polígono 
   QDomText ladosV;

   //tag arco
   QDomElement arcoD;
   
   int ladosFiguraAtual;
   float anguloFiguraAtual;

   //identação
   const int Indent = 4;
   
   //arquivo 
   QFile *arquivo = new QFile(arquivoNome);
   
   //retorna false se o arquivo não puder ser aberto
   if(!arquivo->open(QIODevice::WriteOnly))  return(false);
      
   //cria elemento principal 
   QDomDocument doc;
   //cria elemento raiz
   QDomElement root = doc.createElement("jagun");
   //o raiz é filho do principal
   doc.appendChild(root);
   
   //para cada figura na lista de figuras
   for(int i = 0; i < this->canvas->getArrayFiguras().size(); i++ )
   {
     
     //criando tag figura
     QDomElement figura = doc.createElement("figura");
     //configurando o atributo da tag figura como o id da figura
     figura.setAttribute("id",canvas->getArrayFiguras().at(i)->getId());
     
     //colocando figura como filho de root
     root.appendChild(figura);
     
     //pegando a cor de cada figura
     corFiguraAtual = canvas->getArrayFiguras().at(i)->getCor();
     
     //recebendo as cores das figuras
     r = corFiguraAtual.redF();
     g = corFiguraAtual.greenF();
     b = corFiguraAtual.blueF();
   
     //criando tag cor
     QDomElement cor  = doc.createElement("cor");
     //adicionando cor como filha de figura
     figura.appendChild(cor);
     
     //criando tag r
     QDomElement vermelho  = doc.createElement("r");
     //colocando o rgb vermelho para ser o valor da tag r
     QDomText vermelhoValor  = doc.createTextNode(tr("%1").arg(r));
     
     //criando tag g
     QDomElement verde  = doc.createElement("g");
     //colocando o rgb verde para ser o valor da tag g
     QDomText verdeValor  = doc.createTextNode(tr("%1").arg(g));
     
     //criando tag b
     QDomElement azul  = doc.createElement("b");
     //colocando o rgb azul para ser o valor da tag b
     QDomText azulValor  = doc.createTextNode(tr("%1").arg(b));
     
     //adicionando os valores das tags r, g e b 
     cor.appendChild(vermelho);
      vermelho.appendChild(vermelhoValor);
     cor.appendChild(verde);
      verde.appendChild(verdeValor); 
     cor.appendChild(azul);
      azul.appendChild(azulValor);
     
     //armazena cada figura
     Figura *figuraAtual = canvas->getArrayFiguras().at(i);

     //convertendo uma figura para um polígono
     Poligono *poligonoAtual = static_cast<Poligono*>(figuraAtual);
     //convertendo uma figura para um arco
     Arco *arcoAtual = static_cast<Arco*>(figuraAtual);     

     //para cada tipo de figura
     switch(canvas->getArrayFiguras().at(i)->getClasse())
     {
        case polilinha:
         
          //cria tag polilinha
          polilinhaD = doc.createElement("polilinha");
            figura.appendChild(polilinhaD);
          
          //para cada vértice 
          for(v = 0; v < figuraAtual->getPontos().size(); v++ )
          {   
             //pegando as coordenadas dos vértices
             cordxVerticeFiguraAtual = figuraAtual->getPontos().at(v).x();
             cordyVerticeFiguraAtual = figuraAtual->getPontos().at(v).y(); 
             
             //cria uma tag vertice como as coordenadas dos vertices 
             QDomElement vertice = doc.createElement("vertice");
             QDomText coord  = doc.createTextNode(tr("%1;%2").arg(cordxVerticeFiguraAtual).arg(cordyVerticeFiguraAtual));
             //adicionando vértices da polilinha
             polilinhaD.appendChild(vertice);
              vertice.appendChild(coord);
             
          }
          break;
        
        case arco:

           //cria uma tag arco 
           arcoD = doc.createElement("arco");
            figura.appendChild(arcoD);
          
           //pegando o centro do arco
           centroXFiguraAtual = figuraAtual->getPontos().at(0).x();
           centroYFiguraAtual = figuraAtual->getPontos().at(0).y(); 
           
           //pegando o ponto de Referência do arco
           pRefXFiguraAtual = figuraAtual->getPontos().at(1).x();
           pRefYFiguraAtual = figuraAtual->getPontos().at(1).y(); 

           //obtendo o angulo do arco
           anguloFiguraAtual = arcoAtual->getAngulo();      

           //tag centro do arco       
           centro = doc.createElement("centro");
           centroV  = doc.createTextNode(tr("%1;%2").arg(centroXFiguraAtual).arg(centroYFiguraAtual));
           //tag pRef do arco
           pontoR = doc.createElement("pRef");
           pontoRV  = doc.createTextNode(tr("%1;%2").arg(pRefXFiguraAtual).arg(pRefYFiguraAtual));    
           //tag angulo do arco       
           angulo = doc.createElement("angulo");
           anguloV  = doc.createTextNode(tr("%1").arg(anguloFiguraAtual));
      
           //adicionando valores do arco
           arcoD.appendChild(centro);
             centro.appendChild(centroV);
           arcoD.appendChild(pontoR);
             pontoR.appendChild(pontoRV);
           arcoD.appendChild(angulo);
             angulo.appendChild(anguloV);
             
           break;    
       
        case poligono:

           //cria uma tag poligono 
           poligonoD = doc.createElement("poligono");
            figura.appendChild(poligonoD);
          
           //pegando o centro do poligono
           centroXFiguraAtual = figuraAtual->getPontos().at(0).x();
           centroYFiguraAtual = figuraAtual->getPontos().at(0).y(); 
           
           //pegando o ponto de Referência do poligono
           pRefXFiguraAtual = figuraAtual->getPontos().at(1).x();
           pRefYFiguraAtual = figuraAtual->getPontos().at(1).y(); 
       
           //obtendo o angulo do poligono
           ladosFiguraAtual = poligonoAtual->getLados();      

           //tag centro do poligono
           centro = doc.createElement("centro");
           centroV  = doc.createTextNode(tr("%1;%2").arg(centroXFiguraAtual).arg(centroYFiguraAtual));
           //tag pRef do poligono
           pontoR = doc.createElement("pRef");
           pontoRV  = doc.createTextNode(tr("%1;%2").arg(pRefXFiguraAtual).arg(pRefYFiguraAtual));   
            
           //tag angulo do poligono
           lados = doc.createElement("lados");
           ladosV  = doc.createTextNode(tr("%1").arg(ladosFiguraAtual));
 
           //adicionando valores do poligono
           poligonoD.appendChild(centro);
             centro.appendChild(centroV);
           poligonoD.appendChild(pontoR);
             pontoR.appendChild(pontoRV);
           poligonoD.appendChild(lados);
             lados.appendChild(ladosV);
  
           break;
        
        default: break;
                  
     }
   }
   //criando um stream de saída como o arquivo passado para a função
   QTextStream out(arquivo);
   
   //inserindo instrução de processamento
   QDomNode xmlNode = doc.createProcessingInstruction("xml",
                           "version=\"1.0\" encoding=\"UTF-8\"");

   //inserindo comentário
   QDomNode xmlComment = doc.createComment(" Gerado pelo Maravilhoso Jagun! ");
   
   doc.insertBefore(xmlComment, doc.firstChild());  
   doc.insertBefore(xmlNode, doc.firstChild());
      
   //salvando arquivo xml
   doc.save(out, Indent);
  
   //retorna true se deu tudo certo
   return(true);
    
}

void MainWindow::AtualizarStatusBar()
{
	//TODO
}

void MainWindow::Sobre()
{
	//TODO
}

void MainWindow::setPadrao()
{
	this->canvas->setCursor(QCursor(Qt::ArrowCursor));
	this->canvas->setEstado(semfigura);
	this->canvas->setBufferConstrutor(false);
	this->propriedadesPoligonoToolBar->setVisible(false);
	this->propriedadesArcoToolBar->setVisible(false);
	
}

void MainWindow::preDesenhoPolilinha()
{
	this->propriedadesPoligonoToolBar->setVisible(false);
	this->propriedadesArcoToolBar->setVisible(false);
	
	// limpa todas as acoes se estao ocorrendo
	this->canvas->setBufferConstrutor(false);
	this->canvas->setEstado(semfigura);
	
	
	this->canvas->setCursor(QCursor(QPixmap(":/imagens/linhaC.png")));
	this->canvas->setEstado(polilinha);
	this->canvas->setBufferConstrutor(true);
	
	      
}

void MainWindow::preDesenhoPoligono()
{

	this->propriedadesPoligonoToolBar->setVisible(true);
	this->propriedadesArcoToolBar->setVisible(false);
	
	// limpa todas as acoes se estao ocorrendo
    this->canvas->setBufferConstrutor(false);
	this->canvas->setEstado(semfigura);
	
	this->canvas->setCursor(QCursor(QPixmap(":/imagens/poligonoC.png")));
	
	this->canvas->setEstado(poligono);
	this->canvas->setBufferConstrutor(true);
	this->propriedadesArcoToolBar->setVisible(false);
	      
}

void MainWindow::preDesenhoArco()
{
	this->propriedadesPoligonoToolBar->setVisible(false);
    this->propriedadesArcoToolBar->setVisible(true);
	// limpa todas as acoes se estao ocorrendo
    this->canvas->setBufferConstrutor(false);
	this->canvas->setEstado(semfigura);
	
	this->canvas->setCursor(QCursor(QPixmap(":/imagens/arcoC.png")));
	this->canvas->setEstado(arco);
	this->canvas->setBufferConstrutor(true);
	
}

void MainWindow::getNumLadosPoligono(int numlados)
{
        this->canvas->setNumLadosPoligono(numlados);
}

void MainWindow::getAnguloArco(int angulo)
{
	this->canvas->setAnguloArco(angulo);
}


