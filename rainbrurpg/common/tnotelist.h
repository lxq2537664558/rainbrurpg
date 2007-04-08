#ifndef T_NOTE_LIST_H
#define T_NOTE_LIST_H

#include <list>

using namespace std;

namespace RainbruRPG{
    namespace Gui{

      /** It is a player's notepad object
       *
       */
      struct tNoteListItem{
	const char* title; //!< The title of the note
	const char* text;  //!< The text of the note
      };

      /** A STL list of notepad item
        *
	*/
      typedef std::list<tNoteListItem*> tNoteList;

    }
}
#endif // T_NOTE_LIST_H
