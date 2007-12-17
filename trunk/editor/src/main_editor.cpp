#include <gtkmm/main.h>

#include "editor.h"

int main(int argc, char **argv)
{  
   
   Gtk::Main m(&argc, &argv);

   Glib::RefPtr<Gnome::Glade::Xml> refXml;
   refXml = Gnome::Glade::Xml::create("Archivos_Editor/DisenioEditorMundos/disenioeditormundos.glade");

   Editor E(refXml);

   E.correr();
   return 0;
}
