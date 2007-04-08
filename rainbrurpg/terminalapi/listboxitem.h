
#ifndef LISTBOX_ITEM_H
#define LISTBOX_ITEM_H

#include "widget.h"
#include "listboxitem.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{


    /** The base class of all ListBoxItem
      *
      * An item of a ListBox. 
      *
      *
      */
    class ListBoxItem{
    public:
      ListBoxItem();
      ListBoxItem(const char*);
      ~ListBoxItem();

      bool isChecked();
      void setChecked(bool);
      const char* getCaption();
      void setCaption(const char*);

      void toggle();


    private:
      /** Is the item checked */
      bool checked;
      /** The caption of the item */
      const char* caption;


    };

  }
}

#endif // LISTBOX_ITEM_H
