//---------------------------------------------------------------------------

#ifndef PV2D_H
#define PV2D_H
//---------------------------------------------------------------------------
class PV2D{
private:
   float x;
   float y;

public:
   PV2D();
   PV2D(float x1, float y1);
   ~PV2D();
   void trasladar(PV2D* traslacion); //modifica this
   void escalar(float factor); //modifica this
   void normalizar(); //modifica this
   float dot(PV2D* vector2);
   void suma(PV2D* vector2); //modifica this
   PV2D* clonar();
   float distanciaAPunto(PV2D* p);
   float getX();
   float getY();
   void setX(float x1);
   void setY(float y1);
   float longitud(); //longitud del vector
   PV2D* normalIzquierda();

   PV2D* rotaP(PV2D* centroRot, double ang);
  //se construye un nuevo punto a partir del receptor girando el ángulo ang
  //sobre el centro de rotación centroRot

   PV2D* rotaV(double ang);
  //se construye un nuevo vector a partir del receptor girando el ángulo ang
  //sobre el origen de coordenadas

};
#endif
