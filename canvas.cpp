#include "canvas.hpp"

Canvas::Canvas(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::Rgba));
    // nao desenha nada
	
	this->createActions();
	this->createMenus();
	
    this->desenha = false;
    // nenhuma figura selecionada para desenhar
    this->estadoatual = -1;
    // botao esquerdo nao ta pressionado
    this->botEsqPress = false;  
	
	this->botEsqPressEdit = false;
    // escolhe a cor de pre desenho
    this->corPreDesenho = Qt::blue;
    // seta a cor de desenho
    this->corDesenho = Qt:: black;
    // sem figura na tela
    this->totalFiguras = 0;
    // a autorização do construtor das figuras de buffer
    this->construtor = false;
    
	// valores defaults das figuras
    this->numLadosPoligono = 3;
    this->anguloArco = 360;
    
    this->figSelect = NULL;
    //this->pntSelect = NULL;
    this->posPntSelect = -1;
    
    //colocando o tracking como true, ou seja, não é necessário pressionar o botão para
    //o mouseMoveEvent ocorrer! (Penamos : ) )
    setMouseTracking( true );
}

void Canvas::initializeGL()
{
    qglClearColor(Qt::white);
    gluOrtho2D(0,this->width(),0,this->height());
}

void Canvas::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
    gluOrtho2D(0,this->width(),0,this->height());
    
    glFlush();
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw(GL_RENDER);
}

void Canvas::draw(GLenum mode)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // esse metodo redesenha as figuras que ja estao armazenadas
    this->desenhaArrayFiguras(mode);
    this->desenhaBuffer();
   
}

/*
 * A ideia e' a seguinte:
 * se o estado atual for de desenhar alguma figura e o botao esquerdo foi pressionado...
 * nao se desenha nada novo enquato nao soltar o botao do mouse (desenha = false)
 * um flag e' usado pra marcar que o usuario pressionou o botao esquerdo
 * depois disso o evento mouseReleaseEvent verifique se o botao esquerdo foi pressionado
 * e soltado se sim, a nova figura pode ser desenhada (desenho = true)
 * depois e' guardada a posicao inicial do mouse no momento que o botao do mouse e' solto
 * e se for a primeira vez que e' feito isso (ou seja o primeiro momento que sera' desenhado
 * a figura (construtor = true) uma nova figura temporaria sera criada senao apenas as posicoes
 * dela serao atualizadas
 * agora se o botao direito do mouse estiver pressionado a nova figura e' armazenada na lista
 * 
 */
void Canvas::mousePressEvent(QMouseEvent *event)
{
  this->insereFiguraDoBufferParaLista(event);
  if ((event->buttons() & Qt::LeftButton) && this->estadoatual == semfigura){
    
    this->menuPopUp->setVisible(false); 
    
    if(this->posPntSelect == -1)
    	this->figSelect = pick(event->pos());
    	pickV(event->pos());
    }
    
	this->botEsqPressEdit = true;
    
  if((event->buttons() & Qt::RightButton) && this->figSelect != NULL)
  { 
    this->menuPopUp->popup(mapToGlobal(event->pos()));
    this->menuPopUp->setVisible(true);

  }
  updateGL(); 
}

// se pressionou o botao do mouse, quando solta esse evento e' chamado
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{

	if ((event->buttons() & Qt::LeftButton) && this->estadoatual == semfigura){
		this->posPntSelect = -1;
		this->botEsqPressEdit = false;
	}
	
	this->atualizaFiguraDoBuffer(event);
	updateGL();
	
}


//evento quando o mouse se move
void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    // atualizar a posicao atual do mouse
    this->posAtu = event->pos();
	
    if((event->buttons() & Qt::LeftButton) && this->estadoatual == semfigura){
	
	  // a figura ta selecionada
	  if(figSelect != NULL && this->botEsqPressEdit)
	  {

  	   if ( posPntSelect != -1 ){
  	       
    	   this->posAtu.setX(event->pos().x());
    	   this->posAtu.setY( this->height() - event->pos().y());
  		   
  		   figSelect->moveV(posPntSelect,posAtu);
	      
	      }
	   
  	  }

    }
    // atualiza o canvas
    updateGL();
}


// informa que tipo de figura o usuario quer desenhar
void Canvas::setEstado(int estado)
{
  this->estadoatual = estado;
  //cout << "\n\tMudando estado: " << estado << endl;
  this->construtor = true;
 
}

// metodo que e' usado no metodo draw para desenhar todas as figuras da lista
void Canvas::desenhaArrayFiguras(GLenum mode)
{
	int i = 0;
	for(i = 0 ; i < this->arrayFiguras.size() ;i++)
	{
      if(figSelect == this->arrayFiguras.at(i) ){
      	this->arrayFiguras.at(i)->DesenhaSelecionado(mode);
      }else{
      	this->arrayFiguras.at(i)->Desenha(mode);
      }
	}
}

void Canvas::setBufferConstrutor(bool valorConstrutor)
{
	this->construtor = valorConstrutor;
	this->figSelect = NULL;
	this->posPntSelect = -1;
	updateGL();

}

void Canvas::desenhaBuffer()
{

   GLenum mode = GL_RENDER;
   float xi,yi,xf,yf;
 
   if(this->desenha)
   {
     this->pointIni.setX(posIni.x());
     this->pointIni.setY(this->height() - posIni.y());
     this->pointAtu.setX(posAtu.x());
     this->pointAtu.setY(this->height() - posAtu.y());
     xi = posIni.x(); 
     yi = this->height() - posIni.y(); 
     xf = posAtu.x();
     yf = this->height() - posAtu.y();
        
     if(!this->construtor)
     {
       switch(this->estadoatual)
       {
         case polilinha:

           this->linha = new Polilinha(-1,this->corPreDesenho, pointIni);
           this->linha->adicionaV(pointAtu);
           // linha e' a linha :p que fica mudando dinamicamente quando o mouse
           // se move e que quando o usuario clica com o botao esquerdo do mouse
           // fara' parte da polilinha plinha
           this->linha->Desenha(mode);
           // plinha e' a polilinha que o usuario ja desenhou
           this->plinha->Desenha(mode);
           break;
            
          case poligono:
        	this->poligTemp->setRaio(pointAtu);
        	this->poligTemp->Desenha(mode);
        	break;
          
          case arco:
          	  this->arcTemp->setRaio(pointAtu);
              this->arcTemp->Desenha(mode);
              break;
        	
        	
          case semfigura: break;   
          default: break;
        }
     }
   }
}

void Canvas::insereFiguraDoBufferParaLista(QMouseEvent *event)
{
  if(this->estadoatual > semfigura)
  {
    if (event->buttons() & Qt::LeftButton)
    {
	  // informa que o botao esquerdo foi pressionado
	  this->botEsqPress = true;      
	}
	// se ta desenhando alguma figura, clicou no botao direito parou e tirou a figura do buffer para inserir na lista
	if((event->buttons() & Qt::RightButton) && this->desenha)
	{
	  
    this->desenha = false;
	  this->botEsqPress = false;
	  this->construtor = true;
	  switch(this->estadoatual)
	  {
	    case polilinha:
	      // muda a cor para a definitiva
	      this->plinha->setCor(this->corDesenho);
	      this->arrayFiguras.append(this->plinha);    
	      break;
	      
	    case poligono:
	   	  this->poligTemp->setCor(this->corDesenho);
 		  this->arrayFiguras.append(this->poligTemp);
 		  break;
 		  
	    case arco:
    	  this->arcTemp->setCor(this->corDesenho);
 		  this->arrayFiguras.append(this->arcTemp);
 		  break;
 		  
 		case semfigura: break;
	    default: break;
	  }
	}
  }	
}

void Canvas::atualizaFiguraDoBuffer(QMouseEvent *event)
{
  // se o botao esquerdo foi pressionado antes desse evento
  if (this->botEsqPress )
  {
    this->posIni = event->pos();
    // volta para o estado default
    this->botEsqPress = false;
  
    if(!this->construtor)
    {
      if(this->desenha)
      {
        		
        this->pointAtu.setX(posAtu.x());
        this->pointAtu.setY(this->height() - posAtu.y());
        switch(this->estadoatual)
        {
          case polilinha:
        	
            this->plinha->adicionaV(pointAtu);
            break;
        	    	
          case semfigura: break;
        	    
          default: break;
        	  
        }
      }
        	
    }
    else
    {
      // pode desenhar
      this->desenha = true; //ativando o desenho iterativo, usado em mouseMoveEvent
        	
      this->pointIni.setX(posIni.x());
      this->pointIni.setY(this->height() - posIni.y());
      this->totalFiguras++;
      this->construtor = false;
      switch(this->estadoatual)
      {
        case polilinha:
        	
          this->plinha = new Polilinha(this->totalFiguras,this->corPreDesenho, pointIni);
          break;
        	    
        case poligono:
        		  
          this->poligTemp = new Poligono(this->totalFiguras,this->corPreDesenho,pointIni,pointIni,this->numLadosPoligono);
          break;
          
        case arco:
          this->arcTemp = new Arco(this->totalFiguras,this->corPreDesenho,pointIni,pointIni,this->anguloArco);
          break;
        	    
        case semfigura: break;
        	  
        default: break;
      }
    }
  }     
}

void Canvas::setNumLadosPoligono(int valor)
{
	this->numLadosPoligono = valor;
}

void Canvas::setAnguloArco(int angulo)
{
	this->anguloArco = angulo;
}

Figura* Canvas::pick(QPoint ponto){
	int size = 32;
	int tamanho = 10;
	Figura* figura = NULL;
	GLuint nameBuffer[size];
	GLint hits;
	GLint viewport[4];
	
	glSelectBuffer(size,nameBuffer);		
	glGetIntegerv(GL_VIEWPORT, viewport);
	glRenderMode(GL_SELECT);
		
  glInitNames();
	glPushName(0);
		
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		
		glLoadIdentity();
		
		gluPickMatrix( ponto.x(), viewport[3] - ponto.y() , tamanho, tamanho, viewport);
		
		gluOrtho2D(0,this->width(),0,this->height());
		glMatrixMode(GL_MODELVIEW);
		
		this->draw(GL_SELECT);
		glMatrixMode(GL_PROJECTION);
		
	glPopMatrix();
	glFlush();
		
	hits = glRenderMode(GL_RENDER);
	
	unsigned int j;
	int i, k ;
	GLuint names, *ptr;
	
	ptr = (GLuint *) nameBuffer;
	
	for(i=0; i < hits; i++){
		names = *ptr;
		ptr += 3;
		
		for(j=0; j < names;j++){
			
			for(k = 0 ; k < this->arrayFiguras.size() ; k++)
			{
				if ( this->arrayFiguras.at(k)->getId() == *ptr ){
					figura = this->arrayFiguras.at(k);
					//break;
				}
			}
			
			ptr++;
			
		}
	}
	
	glMatrixMode(GL_MODELVIEW);
	
	return figura;

}

void Canvas::createActions()
{
  this->mudaCorAction = new QAction(tr("&Mudar Cor"), this); 
  this->mudaCorAction->setStatusTip(tr("Muda a cor da figura"));
  connect(this->mudaCorAction, SIGNAL(triggered()), this, SLOT(escolheNovaCor()));
  
  this->deletaFiguraAction = new QAction(tr("&Apagar Figura"),this);
  this->deletaFiguraAction->setStatusTip(tr("Apaga a figura"));
  connect(this->deletaFiguraAction, SIGNAL(triggered()), this, SLOT(deletaFigura()));
  
}

void Canvas::createMenus()
{
  this->menuPopUp = new QMenu(tr("Propriedades"));
  this->menuPopUp->addAction(this->mudaCorAction);
  this->menuPopUp->addAction(this->deletaFiguraAction);
  this->menuPopUp->setVisible(false);
}

void Canvas::escolheNovaCor()
{
        QColor color = QColorDialog::getColor(this->corDesenho, this);
        if (color.isValid()) {
		    if(this->figSelect != NULL)
			{
			  this->figSelect->setCor(color);
              updateGL();
			}
        }


}

void Canvas::deletaFigura()
{
  int pos_remove;
  pos_remove = this->arrayFiguras.indexOf(this->figSelect);
  
  this->arrayFiguras.removeAt(pos_remove);
  this->figSelect = NULL;
  updateGL();
}

bool Canvas :: pontoDentroRetangulo( QPointF ponto , QPointF centro, float largura, float altura) {

  if ( (fabs(ponto.x() - centro.x() ) <= largura/2 ) && (fabs(ponto.y() - centro.y()) <= altura/2)  )
		return true;
	else
		return false;
};

void Canvas::pickV(QPoint pontoMouse) {
	QList<QPointF> pontos;
	int tamanho = 50;
	QPointF centro(pontoMouse.x(),  this->height() - pontoMouse.y() ) ;
	 
	
	if (figSelect){
		pontos = figSelect -> getPontos();
		
		if (this->posPntSelect == -1 || !pontoDentroRetangulo( pontos.at(this->posPntSelect), centro, tamanho, tamanho ) )
		{

			int j = -1;
			for (int i=0; i < pontos.size(); i++ ){
				if ( pontoDentroRetangulo( pontos.at(i), centro, tamanho, tamanho ) ){
					j = i;
					break;
				}	
			}
			this->posPntSelect = j;

    }
	
	}

}


//retornando o array de figuras
QList<Figura*> Canvas::getArrayFiguras()
{
   return( this->arrayFiguras );
}




