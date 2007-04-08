#ifndef LIST_VIEW_COLUMN_H
#define LIST_VIEW_COLUMN_H


namespace RainbruRPG{
  namespace Terminal{

    /** Defines a column of a ListView
      *
      * A column has a width and a caption.
      *
      */
    class ListViewColumn{
    public:
      ListViewColumn();
      ListViewColumn(const char*);
      ListViewColumn(const char*, unsigned int);

      ~ListViewColumn();

      void setCaption(const char*);
      const char* getCaption();
      void setWidth(unsigned int);
      unsigned int getWidth();

    private:
      /** The width of the column innumber of visible characters */
      unsigned int width;
      /** The cation of the column */
      const char* caption;

    };

  }
}

#endif // LIST_VIEW_COLUMN_H
