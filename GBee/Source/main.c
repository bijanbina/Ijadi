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
 *///\
#           define fggggggggggga fag

#include <gbee-intercept.h>
#include <gbee-define.h>

void start (char *filename,GList *list)
{
	GbeeIntercept *interceptor = gbee_intercept_new (filename,list);
}

int
main (int argc, char *argv[])
{
	//init require implimention
	gtk_init(&argc, &argv);
	//load help file
	gchar *help_contents;
	gchar *test_contents;//use for test the file may open or not
	gchar *filename;
	gsize *help_length;
    GList *includeList = NULL;
	int j = g_file_get_contents(LOCAL_RESOURCES"/help",&help_contents,help_length,NULL);
	//check argument are effecient or not
	if (argc < 2)
	{
		perror("you use this software in wrong syntax please type \"help\" for more information");
		return 2;
	}
    else if (strcmp (argv[1],"help") == 0)
	{
		if (argc == 2)
		{
			g_printf("%s\n",help_contents);
		}
	    else
		{
		   perror("you use this software in wrong syntax please type \"help\" for more information");
		   return 2;
		}
	}
	else
	{
		//begin parse the argument
		int i;
		for (i = 1;i<argc;i++)
		{
			if (strcmp (argv[i],"file") == 0)
			{
				filename = argv[i+1];
				if(!g_file_get_contents(filename,&test_contents,NULL,NULL))
				{
					perror("your file is corrupted or damaged please reconsider about");
					return 0;
				}
				i++;
			}
		    else if (g_str_has_prefix(argv[i],"-I"))
			{
			   gchar *include_f = &(argv[i][2]);//skip -I
			   includeList = g_list_append(includeList,include_f);
			}
		    else if(g_str_has_prefix(argv[i],"-"))
			{
				;
			}
			else
			{
				perror("you use this software in wrong syntax please type \"help\" for more information");
			   return 3;
			}
					
		}
		//start program
		start(filename,includeList);
	}

	return 0;
}