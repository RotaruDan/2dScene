
#include "PV2D.h"
#include <math.h>


//---------------------------------------------------------------------------

PV2D::PV2D(float x1, float y1){
  x=x1;
  y=y1;
}
//---------------------------------------------------------------------------
PV2D::~PV2D(){
}
//---------------------------------------------------------------------------
float PV2D::getX(){
  return x;
}
//---------------------------------------------------------------------------
float PV2D::getY(){
  return y;
}
//---------------------------------------------------------------------------
void PV2D::setX(float x1){
  x=x1;
}
//---------------------------------------------------------------------------
void PV2D::setY(float y1){
  y=y1;
}
//---------------------------------------------------------------------------
void PV2D::trasladar(PV2D* traslacion){
  x= x+ traslacion->getX();
  y= y+ traslacion->getY();
}
//---------------------------------------------------------------------------
float PV2D::dot(PV2D* vector2){
  return x*vector2->getX() + y*vector2->getY();
}
//---------------------------------------------------------------------------
void PV2D::escalar(float factor){
  x= x*factor;
  y= y*factor;
}
//---------------------------------------------------------------------------
void PV2D::normalizar(){
  float norma2= dot(this);
  if(norma2>0){
    x= x/sqrt(norma2);
    y= y/sqrt(norma2);
  }
}
//---------------------------------------------------------------------------
void PV2D::suma(PV2D* vector2){
  x= x+vector2->getX();
  y= y+vector2->getY();
}
//---------------------------------------------------------------------------
PV2D* PV2D::clonar(){
  return new PV2D(x,y);
}
//---------------------------------------------------------------------------
float PV2D::distanciaAPunto(PV2D* p){
  float incX= x-p->getX();
  float incY= y-p->getY();
  return sqrt(incX*incX + incY*incY);
}
//---------------------------------------------------------------------------
PV2D* PV2D::rotaP(PV2D* centroRot, double ang){
   float cx= centroRot->getX();
   float cy= centroRot->getY();
   float dx=(1.0-cos(ang))*cx + sin(ang)*cy;
   float dy=-sin(ang)*cx + (1.0-cos(ang))*cy;
   float x1= x*cos(ang)-y*sin(ang)+dx;
   float y1= x*sin(ang)+y*cos(ang)+dy;
   return new PV2D(x1,y1);
}
//---------------------------------------------------------------------------
PV2D* PV2D::rotaV(double ang){
   float x1= x*cos(ang)-y*sin(ang);
   float y1= x*sin(ang)+y*cos(ang);
   return new PV2D(x1,y1);
}
//---------------------------------------------------------------------------
float PV2D::longitud(){
  return sqrt(x*x+y*y);
}
//---------------------------------------------------------------------------



