#ifndef GS_LOCAL_TEST
#define GS_LOCAL_TEST

#include "gsgamebase.h"

namespace RainbruRPG {
  namespace Core{

    /** A super-class for game gamestate shareable capabilities
      *
      * A game gamestate is based on a map.
      *
      */
    class gsLocalTest : public gsGameBase{
    public:
      /** An empty default destructor needed to avoid compilation warnings */
      virtual ~gsLocalTest(){};

      virtual void init();

    };
  }
}

#endif // GS_LOCAL_TEST
