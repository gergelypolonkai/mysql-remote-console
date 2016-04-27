#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <gdk/gdkkeysyms.h>

static char * mysql_console_16_xpm[] = {
"16 16 4 1",
" 	c None",
".	c #000000",
"+	c #FFFFFF",
"@	c #808080",
"                ",
"                ",
" .............. ",
".++++++++++++++.",
".++++++++++++++.",
".+@@@++@@+++@++.",
".+@+++@++@++@++.",
".+@@++@++@++@++.",
".+++@+@++@++@++.",
".+++@+@++@++@++.",
".+@@@++@@+++@@+.",
".++++++++@@++++.",
".++++++++++++++.",
" .............. ",
"                ",
"                "};

GtkWidget *window,
		  *ssh_user_field,
		  *ssh_host_field,
		  *mysql_user_field,
		  *mysql_db_field,
		  *mysql_pass_field,
		  *ok_gomb;

void
destroy_window(GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

void
ok_clicked(GtkWidget *gomb, gpointer data)
{
	gchar *cmd;
	gint len;

	if ((strlen(gtk_entry_get_text(GTK_ENTRY(ssh_host_field))) > 0) && (strlen(gtk_entry_get_text(GTK_ENTRY(mysql_user_field))) > 0) && (strlen(gtk_entry_get_text(GTK_ENTRY(mysql_db_field))) > 0))
	{
		len = 87 +
			(strlen(gtk_entry_get_text(GTK_ENTRY(ssh_user_field))) * 2) +
			((strlen(gtk_entry_get_text(GTK_ENTRY(ssh_user_field))) > 0) ? 1 : 0) +
			(strlen(gtk_entry_get_text(GTK_ENTRY(ssh_host_field))) * 2) +
			(strlen(gtk_entry_get_text(GTK_ENTRY(mysql_user_field))) * 2) +
			strlen(gtk_entry_get_text(GTK_ENTRY(mysql_pass_field))) +
			(strlen(gtk_entry_get_text(GTK_ENTRY(mysql_db_field))) * 2);
		cmd = g_malloc(len);
		memset(cmd, 0, len);

#ifdef DEBUG
		printf("%d\n", strlen("gnome-terminal -t \"MySQL console - %s%s%s - %s@%s\" -x ssh -t %s%s%s mysql -u %s -p%s %s"));
#endif /* DEBUG */
		sprintf(
				cmd,
				"gnome-terminal -t \"MySQL console - %s%s%s - %s@%s\" -x ssh -t %s%s%s mysql -u %s -p%s %s",
				gtk_entry_get_text(GTK_ENTRY(ssh_user_field)),
				(strlen(gtk_entry_get_text(GTK_ENTRY(ssh_user_field))) > 0) ? "@" : "",
				gtk_entry_get_text(GTK_ENTRY(ssh_host_field)),
				gtk_entry_get_text(GTK_ENTRY(mysql_user_field)),
				gtk_entry_get_text(GTK_ENTRY(mysql_db_field)),
				gtk_entry_get_text(GTK_ENTRY(ssh_user_field)),
				(strlen(gtk_entry_get_text(GTK_ENTRY(ssh_user_field))) > 0) ? "@" : "",
				gtk_entry_get_text(GTK_ENTRY(ssh_host_field)),
				gtk_entry_get_text(GTK_ENTRY(mysql_user_field)),
				gtk_entry_get_text(GTK_ENTRY(mysql_pass_field)),
				gtk_entry_get_text(GTK_ENTRY(mysql_db_field))
				);
		
		gtk_widget_hide(window);
		system(cmd);
		gtk_widget_destroy(window);
	}
	else
	{
		GtkWidget *dialog;

		dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Kötelező kitölteni az SSH host, MySQL felhasználónév és MySQL adatbázis mezőket!");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_hide(dialog);
	}
}

void
cancel_clicked(GtkWidget *gomb, gpointer data)
{
	gtk_widget_destroy(window);
}

void
entry_activate(GtkWidget *entry, gpointer data)
{
	gtk_button_clicked(GTK_BUTTON(ok_gomb));
}

gboolean
window_keypress(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if (event->keyval == GDK_Escape)
	{
		gtk_widget_destroy(window);
		return TRUE;
	}
	return FALSE;
}

int
main(int argc, char **argv)
{
	GtkWidget *ssh_user_label,
			  *ssh_host_label,
			  *mysql_user_label,
			  *mysql_db_label,
			  *mysql_pass_label,
			  *megsem_gomb,
			  *tabla;

	GdkPixbuf *window_icon;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	ssh_user_label = gtk_label_new("SSH felhasználónév:");
	ssh_user_field = gtk_entry_new();

	ssh_host_label = gtk_label_new("SSH host:");
	ssh_host_field = gtk_entry_new();

	mysql_user_label = gtk_label_new("MySQL user:");
	mysql_user_field = gtk_entry_new();

	mysql_db_label = gtk_label_new("MySQL adatbázis:");
	mysql_db_field = gtk_entry_new();

	mysql_pass_label = gtk_label_new("MySQL jelszó:");
	mysql_pass_field = gtk_entry_new();

	ok_gomb = gtk_button_new_from_stock(GTK_STOCK_OK);
	megsem_gomb = gtk_button_new_from_stock(GTK_STOCK_CANCEL);

	tabla = gtk_table_new(6, 2, FALSE);

	gtk_table_attach_defaults(GTK_TABLE(tabla), ssh_host_label, 0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tabla), ssh_host_field, 1, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tabla), ssh_user_label, 0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(tabla), ssh_user_field, 1, 2, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(tabla), mysql_user_label, 0, 1, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(tabla), mysql_user_field, 1, 2, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(tabla), mysql_pass_label, 0, 1, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(tabla), mysql_pass_field, 1, 2, 3, 4);
	gtk_table_attach_defaults(GTK_TABLE(tabla), mysql_db_label, 0, 1, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(tabla), mysql_db_field, 1, 2, 4, 5);
	gtk_table_attach_defaults(GTK_TABLE(tabla), ok_gomb, 0, 1, 5, 6);
	gtk_table_attach_defaults(GTK_TABLE(tabla), megsem_gomb, 1, 2, 5, 6);

	gtk_container_add(GTK_CONTAINER(window), tabla);

	gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(destroy_window), NULL);
	gtk_signal_connect(GTK_OBJECT(ok_gomb), "clicked", GTK_SIGNAL_FUNC(ok_clicked), NULL);
	gtk_signal_connect(GTK_OBJECT(megsem_gomb), "clicked", GTK_SIGNAL_FUNC(cancel_clicked), NULL);
	gtk_signal_connect(GTK_OBJECT(ssh_host_field), "activate", GTK_SIGNAL_FUNC(entry_activate), NULL);
	gtk_signal_connect(GTK_OBJECT(ssh_user_field), "activate", GTK_SIGNAL_FUNC(entry_activate), NULL);
	gtk_signal_connect(GTK_OBJECT(mysql_user_field), "activate", GTK_SIGNAL_FUNC(entry_activate), NULL);
	gtk_signal_connect(GTK_OBJECT(mysql_pass_field), "activate", GTK_SIGNAL_FUNC(entry_activate), NULL);
	gtk_signal_connect(GTK_OBJECT(mysql_db_field), "activate", GTK_SIGNAL_FUNC(entry_activate), NULL);
	gtk_signal_connect(GTK_OBJECT(window), "key-press-event", GTK_SIGNAL_FUNC(window_keypress), NULL);

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_title(GTK_WINDOW(window), "MySQL console");
	window_icon = gdk_pixbuf_new_from_xpm_data((const char **)mysql_console_16_xpm);
	gtk_window_set_default_icon(window_icon);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

