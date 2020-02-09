#include "graphstat2d.h"
#include "ui_graphstat2d.h"

GraphStat2D::GraphStat2D(const EtudeStat2D* E1,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphStat2D)
{
   ui->setupUi(this);
   Pt = true;
   TracerLigne = false;
   EtudeLocal = (EtudeStat2D*)E1;
   cout << "dans GraphStat2D" << endl;
   this->p = dynamic_cast<DataSourceSerie2D*>((E1->getE())->getSource());
   cout << "suite" << endl;
	L = new Liste<Data2D>(*(p->getL()));
	int i = 1;
	MinX = this->L->getElement(0).getVal1();
	MinY = this->L->getElement(0).getVal2();
	MaxX = this->L->getElement(0).getVal1();
	MaxY = this->L->getElement(0).getVal2();
	while (i < L->Size())
	{ 
 	 if (MinX > this->L->getElement(i).getVal1())  MinX = this->L->getElement(i).getVal1();
 	 if (MinY > this->L->getElement(i).getVal2())  MinY = this->L->getElement(i).getVal2();
	 if (MaxX < this->L->getElement(i).getVal1())  MaxX = this->L->getElement(i).getVal1();
 	 if (MaxY < this->L->getElement(i).getVal2())  MaxY = this->L->getElement(i).getVal2();
	 i++;
	}
}

GraphStat2D::~GraphStat2D()
{
    delete ui;
}

void GraphStat2D::on_ButtonTracer_clicked()
{
    printf("on_ButtonTracer_clicked\n");fflush(stdout);
    
    p->setL(L);          // 1111111111111111111&&
    EtudeLocal->setCoeffA();
    EtudeLocal->setCoeffB();
    char	Buff[80];
    if (EtudeLocal->getCoeffB() > 0)
       sprintf(Buff,"%8.2f x + %8.2f",EtudeLocal->getCoeffA(),EtudeLocal->getCoeffB());
    else sprintf(Buff,"%8.2f x - %8.2f",EtudeLocal->getCoeffA(),-EtudeLocal->getCoeffB());
    ui->lineEquation->setText(Buff);
    TracerLigne = true;
    this->update();
}

void GraphStat2D::on_ButtonSelectionner_clicked()
{
	printf("on_ButtonSelectionner_clicked\n");fflush(stdout);
	float X,Y;
	if (PointDepart.x() < PointArrivee.x()) X = PointDepart.x();
     else X = PointArrivee.x();
 
	if (PointDepart.y() > PointArrivee.y()) Y = PointDepart.y();
     else Y = PointArrivee.y();
	float XX = (X-80)*(MaxX-MinX)/340 + MinX;
	float YY = MinY -(Y - 320)*(MaxY-MinY)/280  ;
     
	Data2D	D(XX,YY);
	if (PointDepart.x() > PointArrivee.x()) X = PointDepart.x();
     else X = PointArrivee.x();
	if (PointDepart.y() < PointArrivee.y()) Y = PointDepart.y();
     else Y = PointArrivee.y();
	XX = (X-80)*(MaxX-MinX)/340 + MinX;
	YY = MinY - (Y - 320)*(MaxY-MinY)/280  ;
	Data2D	DBis(XX,YY);
 
	int i = 0;
	while (i < L->Size())
		{ Data2D DInter(L->getElement(i)); 
		cout << DInter.getVal1() << " - " << D.getVal1() << endl;
		cout << DInter.getVal2() << " - " << D.getVal2() << endl;
			if (D < DInter) if (DInter < DBis)
			{ 
				L->retireElement(i);
				i = 0;
				LUndo.insere(DInter);
				continue;
			}
      	i++;
		}	
	PointDepart = PointArrivee;
	TracerLigne = false;
	ui->lineEquation->clear();
	this->update();
// cout << "dans ButtonSelectionner " << L->Size() << endl;
     p->setL(L);                  //insereer par la suite
    
}

void GraphStat2D::on_ButtonAnnuler_clicked()
{
     printf("on_ButtonAnnuler_clicked\n");fflush(stdout);
     
     int 	Indice = LUndo.Size() - 1;
     if (Indice < 0) return;
     L->insere(LUndo.getElement(Indice));
     LUndo.retireElement(Indice);
     TracerLigne = false;
     ui->lineEquation->clear();
     this->update();
    
}

void GraphStat2D::paintEvent(QPaintEvent *)
{
QPainter painter(this);
    painter.drawLine(50, 20, 50, 360);
    painter.drawLine(50, 360, 460, 360);
    
    char 	Buff[10];
	sprintf(Buff,"%-8.2f",MinY);
	painter.drawText(10 ,324,Buff);	//320 + 3
	sprintf(Buff,"%-8.2f",MaxY);
	painter.drawText(10 ,45,Buff);	//40 + 3
	sprintf(Buff,"%-8.2f",MinX);
	painter.drawText(63 ,380,Buff);	//320 + 3
	sprintf(Buff,"%-8.2f",MaxX);
	painter.drawText(394 ,380,Buff);	//40 + 3
	
	int i = 0;
	while (i < L->Size())
	{ 
		painter.drawText(80 + (this->L->getElement(i).getVal1() - MinX) * 340 / (MaxX - MinX)  - 3,
	     320 - (this->L->getElement(i).getVal2() - MinY) * 280 / (MaxY - MinY) +3,"x");
	   i++;
	}
	     
    if (Pt)
       painter.drawText(PointDepart.x()-3,PointDepart.y()+3,"x");
    painter.drawRect(PointDepart.x(),PointDepart.y(),PointArrivee.x()-PointDepart.x(),PointArrivee.y()-PointDepart.y());
	if (TracerLigne)
		{
		float X1=MinX,Y1,X2=MaxX,Y2;
		Y1 = X1 * EtudeLocal->getCoeffA() + EtudeLocal->getCoeffB();
		Y2 = X2 * EtudeLocal->getCoeffA() + EtudeLocal->getCoeffB();
		painter.drawLine(80   - 3,320 - (Y1 - MinY) * 280 / (MaxY - MinY) +3,
	    80 +  340 - 3, 320 - (Y2 - MinY) * 280 / (MaxY - MinY) +3);
		}

}

void GraphStat2D::mouseReleaseEvent(QMouseEvent * e)
{
   PointArrivee = e->pos();
   Pt =false ;
   this->update();
}

void GraphStat2D::mousePressEvent(QMouseEvent * e)
{
	PointDepart = e->pos();
	PointArrivee = e->pos();
   Pt =  true;
  	this->update();
}

