#include <gtk/gtk.h>
#include "PROJECT.h"
int main(int argc,char *argv[])
{
	gtk_init(&argc,&argv);
	GtkWidget *pass_window=pass_window_init();
	pass_page(pass_window);
	gtk_main();
	return 0;
}
//gcc-7 `pkg-config --cflags gtk+-3.0` -o test PROJECT_INTERFACE.c PROJECT.c `pkg-config --libs gtk+-3.0`
