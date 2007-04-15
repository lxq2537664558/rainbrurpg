#include "objectpos.h"

/** The default constructor 
  *
  */
RainbruRPG::Core::ObjectPos::ObjectPos(){
  this->name="";
  this->posX=0;
  this->posY=0;
  this->posZ=0;
  this->rotW=0;
  this->rotX=0;
  this->rotY=0;
  this->rotZ=0;
}

/** The copy constructor
  *
  */
RainbruRPG::Core::ObjectPos::ObjectPos(const ObjectPos& p){
  this->name=p.name;
  this->posX=p.posX;
  this->posY=p.posY;
  this->posZ=p.posZ;
  this->rotW=p.rotX;
  this->rotX=p.rotX;
  this->rotY=p.rotY;
  this->rotZ=p.rotZ;
}

/** The default destructor
  *
  */
RainbruRPG::Core::ObjectPos::~ObjectPos(){

}

/** Sets the name of this positionning instance
  *
  * This name must be unique.
  *
  * \param n The new name
  *
  */
void RainbruRPG::Core::ObjectPos::setName(std::string n){
  name=n;
}

/** Get the name of this object
  *
  * \return the name
  *
  */
std::string RainbruRPG::Core::ObjectPos::getName(){
  return name;
}

/** Gets the X position value
  *
  * \return The X position value
  *
  */
double RainbruRPG::Core::ObjectPos::getPosX(){
  return posX;
}

/** Gets the Y position value
  *
  * \return The Y position value
  *
  */
double RainbruRPG::Core::ObjectPos::getPosY(){
  return posY;
}

/** Gets the Z position value
  *
  * \return The Z position value
  *
  */
double RainbruRPG::Core::ObjectPos::getPosZ(){
  return posZ;
}

/** Gets the W rotation value
  *
  * \return The W rotation value
  *
  */
double RainbruRPG::Core::ObjectPos::getRotW(){
  return rotX;
}

/** Gets the X rotation value
  *
  * \return The X rotation value
  *
  */
double RainbruRPG::Core::ObjectPos::getRotX(){
  return rotX;
}

/** Gets the Y rotation value
  *
  * \return The Y rotation value
  *
  */
double RainbruRPG::Core::ObjectPos::getRotY(){
  return rotY;
}

/** Gets the Z rotation value
  *
  * \return The Z rotation value
  *
  */
double RainbruRPG::Core::ObjectPos::getRotZ(){
  return rotZ;
}

/** Sets the X position value
  *
  * \param d The X position value
  *
  */
void RainbruRPG::Core::ObjectPos::setPosX(double d){
  posX=d;
}

/** Sets the Y position value
  *
  * \param d The Y position value
  *
  */
void RainbruRPG::Core::ObjectPos::setPosY(double d){
  posY=d;
}

/** Sets the Z position value
  *
  * \param d The Z position value
  *
  */
void RainbruRPG::Core::ObjectPos::setPosZ(double d){
  posZ=d;
}

/** Sets the W rotation value
  *
  * \param d The W rotation value
  *
  */
void RainbruRPG::Core::ObjectPos::setRotW(double d){
  rotW=d;
}

/** Sets the X rotation value
  *
  * \param d The X rotation value
  *
  */
void RainbruRPG::Core::ObjectPos::setRotX(double d){
  rotX=d;
}

/** Sets the Y rotation value
  *
  * \param d The Y rotation value
  *
  */
void RainbruRPG::Core::ObjectPos::setRotY(double d){
  rotY=d;
}

/** Sets the Z rotation value
  *
  * \param d The Z rotation value
  *
  */
void RainbruRPG::Core::ObjectPos::setRotZ(double d){
  rotZ=d;
}

/** The assignment operator
  *
  * \param p The object to assign
  *
  * \return The assigned object
  *
  */
RainbruRPG::Core::ObjectPos& 
RainbruRPG::Core::ObjectPos::operator=(const RainbruRPG::Core::ObjectPos& p){

  if (this == &p) return *this;

  this->name=p.name;
  this->posX=p.posX;
  this->posY=p.posY;
  this->posZ=p.posZ;
  this->rotW=p.rotX;
  this->rotX=p.rotX;
  this->rotY=p.rotY;
  this->rotZ=p.rotZ;

}
