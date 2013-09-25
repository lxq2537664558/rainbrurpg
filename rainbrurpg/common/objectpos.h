#ifndef OBJECT_POS_H
#define OBJECT_POS_H

#include <string>

namespace RainbruRPG{
  namespace Core{

    /** An object defining the position of a mesh
      *
      * An ObjectMesh can appears more than one times. The position, rotation
      * and name of all its instance are this class.
      *
      */
    class ObjectPos{
    public:
      ObjectPos();
      ObjectPos(const ObjectPos&);
      ~ObjectPos();

      void setName(std::string);
      std::string getName();

      double getPosX();
      double getPosY();
      double getPosZ();

      double getRotW();
      double getRotX();
      double getRotY();
      double getRotZ();

      void setPosX(double);
      void setPosY(double);
      void setPosZ(double);

      void setRotW(double);
      void setRotX(double);
      void setRotY(double);
      void setRotZ(double);

    private:
      /** The name of this positionning instance */
      std::string name;

      /** The x position of the object */
      double posX;
      /** The y position of the object */
      double posY;
      /** The z position of the object */
      double posZ;
      /** The value of the initial rotation of the object in the X axis */
      double rotX;
      /** The value of the initial rotation of the object in the Y axis */
      double rotY;
      /** The value of the initial rotation of the object in the Z axis */
      double rotZ;
      /** The value of the initial rotation of the object in the W axis */
      double rotW;
    };
  }
}
#endif // OBJECT_POS_H
