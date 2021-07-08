#ifndef projet_h
#define projet_h


typedef struct 
{
	char nom[256];
	char acronyme[4];
}Compagnie;
typedef struct 
{
	char Identifiant[7];
	int carburant;
	int consommation;
	char heure_decollage[9];
	Compagnie compagnie;
}Avion;
typedef struct el
{
	Avion cle;
	struct el *suivant;
}Cellule;

void Creation_menu(GtkWidget *);
GtkWidget * window_init();
GtkWidget *pass_window_init();
GtkWidget * window_init_creation();
void pass_page(GtkWidget *);
void Creer_liste();
void Create_first_Menu(GtkWidget *);
void ajout_menu(GtkWidget *);
void supp_menu();
void mod_menu_main(GtkWidget *);
void mod_menu_pop(GtkWidget *);
void affichage_main(GtkWidget *);
void rech_id_main(GtkWidget *);
void rech_id_pop(GtkWidget *);
void rech_heur_main(GtkWidget *);
void rech_com_main(GtkWidget *);
void rech_heur_pop(GtkWidget *);
void rech_com_pop(GtkWidget *);
#endif