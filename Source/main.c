/* --------------------------------------- Besm Allah rahman rahim   ----------------------------------------------------
 *
 * Copyright (C) 2011 AllahSoft Std.
 *
 * Bijan Binaee   <bijanbina@gmail.com>             
 * Reza Faramarzi <faramarzi.reza14@gmail.com>
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <clutter/clutter.h>
#include <ijadi-gui.h>
#include <ijadi-application.h>

void start (int argc, char *argv[])
{
	//init require implimention
	gtk_init(&argc, &argv);
	
	//gtk_window_set_default_icon_name ("eog");
	g_application_run (G_APPLICATION (IJADI_APP), argc, argv); 
}

int
main (int argc, char *argv[])
{
  start(argc, argv);

  gtk_main();
  return 0;
}






     
