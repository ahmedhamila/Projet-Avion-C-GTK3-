#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include "PROJECT.h"
#include <math.h>
/*variables globales*/
GtkWidget *user_entry;
GtkWidget *Pass_entry;
GtkWidget *button;
GtkWidget *button2;
GtkWidget *identifiant_frame;
GtkWidget *carburant_frame;
GtkWidget *consommation_frame;
GtkWidget *heure_frame;
GtkWidget *comp_nom_frame;
GtkWidget *comp_acro_frame;
GtkWidget *title;
GtkWidget *entry_ident;
GtkWidget *entry_carb;
GtkWidget *entry_consom;
GtkWidget *entry_heure;
GtkWidget *entry_comp_nom;
GtkWidget *entry_comp_acro;
GtkWidget *fixed;
GtkWidget *fixed_p;
GtkWidget *dialog_ident;
GtkWidget *position;
GtkWidget *entry_pos;
GtkWidget *box;
GtkWidget *mbar;
GtkWidget *Creation_du_repertoire;
GtkWidget *Mise_a_jour;
GtkWidget *Recherche;
GtkWidget *enregistrement;
GtkWidget *QUIT;
GtkWidget *about;
GtkWidget *MAJ_ajouter;
GtkWidget *MAJ_Supprimer;
GtkWidget *MAJ_modifier;
GtkWidget *MAJ_ajouter_text;
GtkWidget *MAJ_Supprimer_text;
GtkWidget *MAJ_modifier_text;
GtkWidget *Rech_cont_text;
GtkWidget *Rech_ident_text;
GtkWidget *Rech_comp_text;
GtkWidget *Rech_heure_text;
GtkWidget *Rech_Tri_text;
GtkWidget *Rech_cont_text;
GtkWidget *MAJ;
GtkWidget *Rech;
GtkWidget *Enr;
GtkWidget *Enr_enreg_text;
GtkWidget *Enr_charg_text;
GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *entry3;
GtkWidget *frame1;
GtkWidget *frame_pop;
GtkWidget *button_pop;
GtkWidget *entry_pop;
GtkTextBuffer *buffer;
GtkTextIter start, end;
GtkTextIter iter_title;
GtkTextIter iter_aff;
GtkTextIter iter_tail;
GtkWidget *view;
GtkWidget *scrolled_window;
GtkWidget *window_SUP;
static char nom_avion[10];
static char comp_nom[256];
static char heur_d[8];
static Avion info;
static int posi;
static int ok=0;

/**************/

typedef struct 
{
	Cellule *premier;
	Cellule *dernier;
}liste;

static liste L;

/*Fonctions de verification*/
unsigned verif_identifiant(char *id,char *acro)
{
	for(int i =0;i<3;i++)
		if(id[i]!=acro[i])
			return 0;
	for(int i=3;i<6;i++)
		if(!isdigit(id[i]))
			return 0;
	return 1;
}
int verif_nom(char *ch)
{
	if(!strlen(ch))
		return -1;
	if(isspace(ch[0]) || isspace(ch[strlen(ch)-1]))
		return -2;
	for(int i=0;i<strlen(ch);i++)
	{
		if(!isalpha(ch[i]) && !isspace(ch[i]) || (isspace(ch[i]) && isspace(ch[i+1])) )
			return -2;
	}	
	return 1;
}
unsigned verif_heure(char *ch)
{
	if(strlen(ch)!=8)
		return 0;
	for(int i=0;i<strlen(ch);i++)
		if(!isdigit(ch[i]) && ch[i]!=':')
			return 0;
	char hh[3];
	hh[0]=ch[0];
	hh[1]=ch[1];
	hh[2]='\0';
	char mm[3];
	mm[0]=ch[3];
	mm[1]=ch[4];
	mm[2]='\0';
	char ss[3];
	ss[0]=ch[6];
	ss[1]=ch[7];
	ss[2]='\0';

	int heure=atoi(hh);
	int minute=atoi(mm);
	int seconde=atoi(ss);
	return ((seconde>=0 && seconde<=59)&& (minute>=0 && minute<=59)&&(heure>=0 && heure<=23));
}
unsigned chaine_num(char *ch)
{
	for(int i=0;ch[i];i++)
	{
		if(!isdigit(ch[i]))
			return 0;
	}
	return 1;

}
/**************************************************************************************************************************************************************/

/*Fonctions de la liste*/
void Creer_liste()
{
	L.premier=NULL;
	L.dernier=NULL;
}



unsigned Vide()
{
	return(!L.premier && !L.dernier);
}

unsigned existe_pas(char *ident)
{
	Cellule *aux=L.premier;
	while(aux)
	{
		if(strcmp((aux->cle).Identifiant,ident)==0)
			return 0;
		aux=aux->suivant;
	}
	return 1;
}
unsigned existe_pas_comp_nom(char *comp)
{
	Cellule *aux=L.premier;
	while(aux)
	{
		if(strcmp((aux->cle).compagnie.nom,comp)==0)
			return 0;
		aux=aux->suivant;
	}
	return 1;
}
unsigned existe_pas_hure(char *heure)
{
	Cellule *aux=L.premier;
	while(aux)
	{
		if(strcmp((aux->cle).heure_decollage,heure)==0)
			return 0;
		aux=aux->suivant;
	}
	return 1;
}
Cellule *rech_ident(char *ident)
{

	Cellule *aux=L.premier;
	while(aux)
	{
		if(strcmp((aux->cle).Identifiant,ident)==0)
			return aux;
		aux=aux->suivant;
	}
	return NULL;
}
unsigned taille_liste()
{
	unsigned taille=0;
	Cellule *aux=L.premier;
	while(aux)
	{
		taille++;
		aux=aux->suivant;
	}
	return taille;
}
int max_length_name()
{
	Cellule *aux=L.premier;
	int max=strlen(aux->cle.compagnie.nom);
	while(aux)
	{
		if(strlen(aux->cle.compagnie.nom)>max)
			max=strlen(aux->cle.compagnie.nom);
		aux=aux->suivant;
	}
	return max;
}

int max_length_name_id(char *id)
{
	Cellule *aux=L.premier;
	int max=strlen(aux->cle.compagnie.nom);
	while(aux)
	{
		if(strcmp(aux->cle.Identifiant,id)==0&&strlen(aux->cle.compagnie.nom)>max)
			max=strlen(aux->cle.compagnie.nom);
		aux=aux->suivant;
	}
	return max;
}

int max_length_name_heur(char *heur)
{
	Cellule *aux=L.premier;
	int max=strlen(aux->cle.compagnie.nom);
	while(aux)
	{
		if(strcmp(aux->cle.heure_decollage,heur)==0&&strlen(aux->cle.compagnie.nom)>max)
			max=strlen(aux->cle.compagnie.nom);
		aux=aux->suivant;
	}
	return max;
}

int length_car(int x)
{
	int s=1;
	int a=x/10;
	while(a)
	{
		s++;
		a=a/10;
	}
	return s;
}
int max_length_car()
{
	Cellule *aux=L.premier;
	int max=length_car(aux->cle.carburant);
	while(aux)
	{
		if(length_car(aux->cle.carburant)>max)
			max=length_car(aux->cle.carburant);
		aux=aux->suivant;
	}
	return max;
}

int max_length_car_nom(char *nom)
{
	Cellule *aux=L.premier;
	int max=length_car(aux->cle.carburant);
	while(aux)
	{
		if(strcmp(aux->cle.compagnie.nom,nom)==0&&length_car(aux->cle.carburant)>max)
			max=length_car(aux->cle.carburant);
		aux=aux->suivant;
	}
	return max;
}

int max_length_car_heur(char *heur)
{
	Cellule *aux=L.premier;
	int max=length_car(aux->cle.carburant);
	while(aux)
	{
		if(strcmp(aux->cle.heure_decollage,heur)==0&&length_car(aux->cle.carburant)>max)
			max=length_car(aux->cle.carburant);
		aux=aux->suivant;
	}
	return max;
}

int max_length_car_id(char *id)
{
	Cellule *aux=L.premier;
	int max=length_car(aux->cle.carburant);
	while(aux)
	{
		if(strcmp(aux->cle.Identifiant,id)==0&&length_car(aux->cle.carburant)>max)
			max=length_car(aux->cle.carburant);
		aux=aux->suivant;
	}
	return max;
}

void inserer_tete(Avion info)
{
	Cellule *new=(Cellule *)malloc(sizeof(Cellule));
	new->cle=info;
	new->suivant=L.premier;
	if(Vide())
		L.dernier=new;
	L.premier=new;
}
void inserer_queue(Avion info)
{
	Cellule *new=(Cellule *)malloc(sizeof(Cellule));
	new->cle=info;
	new->suivant=NULL;
	if(Vide())
		L.premier=new;
	else
		(L.dernier)->suivant=new;
	L.dernier=new;
}
void ajouter_apres(Cellule *q,Avion info)
{
	if(q==L.dernier)
		inserer_queue(info);
	else
	{
		Cellule *new=(Cellule *)malloc(sizeof(Cellule));
		new->cle=info;
		new->suivant=q->suivant;
		q->suivant=new;
	}
}
void inserer_position(Avion info,int pos)
{
	int position =pos;

	if(position==0)
		inserer_tete(info);
	else if(position==taille_liste())
		inserer_queue(info);
	else
	{
		Cellule *aux=L.premier;
		position =pos-1;
		while(position)
		{
			position--;
			aux=aux->suivant;
		}
		ajouter_apres(aux,info);
	}
}

void affiche_liste()
{
	Cellule *aux=L.premier;
	while(aux)
	{

		aux=aux->suivant;
	}
}

void Supprimer_tete()
{
	assert(!Vide());
	Cellule *aux=L.premier;
	L.premier=aux->suivant;
	if(!L.premier)
		L.dernier=NULL;
	free(aux);
}
void Supprimer_queue()
{
	assert(!Vide());
	if(L.premier==L.dernier)
	{
		free(L.premier);
		L.premier=NULL;
		L.dernier=NULL;
	}
	else
	{
		Cellule *aux=L.premier;
		while(aux->suivant!=L.dernier)
		{
			aux=aux->suivant;
		}
		free(L.dernier);
		L.dernier=aux;
		aux->suivant=NULL;
	}
	
}    	
void Supprimer_pos(int position)
{
	assert(!Vide());
	if(position==0)
	{
		Cellule *aux=L.premier;
		Cellule *a;
		while(aux)
		{
			a=aux->suivant;
			free(aux);
			aux=a;
		}
		Creer_liste();
	}
	else
	{
		Cellule *aux=L.premier;
		while(position)
		{
			position--;
			aux=aux->suivant;
		}
		Cellule *s=L.premier;
		while(s->suivant!=aux)
		{
			s=s->suivant;
		}
		s->suivant=NULL;
		L.dernier=s;
		Cellule *a;
		while(aux)
		{
			a=aux->suivant;
			free(aux);
			aux=a;
		}
		
	}
	

}
void supprimer_noeud(Cellule *q)
{
	assert(!Vide());
	if(q==L.premier)
		Supprimer_tete();
	else if(q==L.dernier)
		Supprimer_queue();
	else
	{
		Cellule *aux=L.premier;
		Cellule *aux2;
		while(aux!=q)
		{
			aux2=aux;
			aux=aux->suivant;
		}	
		aux2->suivant=aux->suivant;
		free(aux);
	}
}
void Supprimer_avion(char *nom)
{
	assert(!Vide());
	Cellule *aux=L.premier;
	while(aux&&strcmp((aux->cle).Identifiant,nom)!=0)
		aux=aux->suivant;
	supprimer_noeud(aux);
}
void Supprimer_comp(char *com)
{
	Cellule *aux=L.premier;
	Cellule *aux2;
	while(aux)
	{
		aux2=aux->suivant;
		if(strcmp(aux->cle.compagnie.nom,com)==0)
			Supprimer_avion(aux->cle.Identifiant);
		aux=aux2;
	}
}

Cellule* rech_id(char *id,int *i)
{
	int a=1;
	Cellule *aux=L.premier;
	while(aux&&strcmp(id,aux->cle.Identifiant)!=0)
	{	
		aux=aux->suivant;
		a++;
	}
	*i=a;
	return aux;
}
Cellule *rech_com(char *nom,int *i)
{
	int a=1;
	Cellule *aux=L.premier;
	while(aux&&strcmp(nom,aux->cle.compagnie.nom)!=0)
	{	
		aux=aux->suivant;
		a++;
	}
	*i=a;
	return aux;
}
Cellule *rech_heur(char *heur,int *i)
{
	int a=1;
	Cellule *aux=L.premier;
	while(aux&&strcmp(heur,aux->cle.heure_decollage)!=0)
	{	
		aux=aux->suivant;
		a++;
	}
	*i=a;
	return aux;
}
void Tri_liste()
{
	Avion perm;
	Cellule * con_max;
	for(Cellule *aux=L.premier;aux->suivant;aux=aux->suivant)
	{
		con_max=aux;
		for(Cellule *aux2=aux->suivant;aux2;aux2=aux2->suivant)
			if(aux2->cle.consommation>con_max->cle.consommation)
				con_max=aux2;
		if(con_max!=aux)
		{
			perm=con_max->cle;
			con_max->cle=aux->cle;
			aux->cle=perm;
		}
		
	}
}
void Enregistrement()
{
	FILE *F=fopen("PROJECT.txt","w+");
	Cellule *aux=L.premier;
	while(aux)
	{
		fprintf(F,"%s/%d/%d/%s/%s/%s/\n",aux->cle.Identifiant,aux->cle.carburant,aux->cle.consommation,aux->cle.heure_decollage,aux->cle.compagnie.nom,aux->cle.compagnie.acronyme);
		aux=aux->suivant;
	}
	fclose(F);
}

char *ret(char *main,char sep,unsigned *pos)
{
	char *ch=(char *)malloc(1000*sizeof(char));
	int k=0,i;
	for( i=*pos;main[i]!=sep;i++,k++)
	{
		ch[k]=main[i];
	}
	ch[k]='\0';
	*pos=i+1;
	return ch;
}

void Chargement()
{
	Avion av;
	char line[1000];
	unsigned pos;

	FILE *F=fopen("PROJECT.txt","r");
	//av.Identifiant,&av.carburant,&av.consommation,av.heure_decollage,av.compagnie.nom,av.compagnie.acronyme
	while(fgets(line,1000,F)!=NULL)
	{
		pos=0;
		strcpy(av.Identifiant,ret(line,'/',&pos));
		av.carburant=atoi(ret(line,'/',&pos));
		av.consommation=atoi(ret(line,'/',&pos));
		strcpy(av.heure_decollage,ret(line,'/',&pos));
		av.heure_decollage[8]='\0';
		strcpy(av.compagnie.nom,ret(line,'/',&pos));
		strcpy(av.compagnie.acronyme,ret(line,'/',&pos));		
		inserer_queue(av);
	}
	fclose(F);
}
/************************************************************************************************************************************************************/
/*fontions des appels(signal-connect)*/
void on_response(GtkDialog *dialog,gint response_id,gpointer   user_data)
{
  
  gtk_widget_destroy (GTK_WIDGET (dialog));

}
void end_program(GtkWidget *wid,gpointer ptr)
{
	gtk_main_quit();
}
void destroy_window(GtkWidget *window,gpointer data)
{
	gtk_widget_destroy (window);
}
void reset_entry()
{

	gtk_entry_set_text(GTK_ENTRY(entry_ident),"");
	gtk_entry_set_text(GTK_ENTRY(entry_carb),"");
	gtk_entry_set_text(GTK_ENTRY(entry_consom),"");
	gtk_entry_set_text(GTK_ENTRY(entry_heure),"");
	gtk_entry_set_text(GTK_ENTRY(entry_comp_nom),"");
	gtk_entry_set_text(GTK_ENTRY(entry_comp_acro),"");
	gtk_entry_set_text(GTK_ENTRY(entry_pos),"0");
	char pos[100];
    snprintf(pos,sizeof(pos),"Position de saisir : (entre 0 (en tete) et %u (en queue) ",taille_liste());
	gtk_frame_set_label(GTK_FRAME(position),pos);

}

void response_ajouter(GtkDialog *dialog,gint response_id,GtkWidget *window)
{

  inserer_position(info,posi);
  if (response_id == GTK_RESPONSE_YES) 
  {
  	reset_entry();//to reset the entry boxes
  	
  }
  else if(response_id==GTK_RESPONSE_NO)
  	gtk_widget_destroy(GTK_WIDGET(window));

  gtk_widget_destroy (GTK_WIDGET (dialog));
  

}
void destroy_wind(GtkWidget *widget,gpointer window)
{
	gtk_widget_destroy(window);
}
void saisie(GtkWidget *widget,GtkWidget *window)
{
	
	
	Compagnie com;
	char ch1[100];
	char ch2[100];
	char ch3[100];

	strcpy(info.Identifiant,(char *)gtk_entry_get_text(GTK_ENTRY(entry_ident)));
	strcpy(ch1,(char *)gtk_entry_get_text(GTK_ENTRY(entry_carb)));
	strcpy(ch2,(char *)gtk_entry_get_text(GTK_ENTRY(entry_consom)));
	strcpy(info.heure_decollage,(char *)gtk_entry_get_text(GTK_ENTRY(entry_heure)));
	strcpy(com.nom,(char *)gtk_entry_get_text(GTK_ENTRY(entry_comp_nom)));
	strcpy(com.acronyme,(char *)gtk_entry_get_text(GTK_ENTRY(entry_comp_acro)));
	strcpy(ch3,(char *)gtk_entry_get_text(GTK_ENTRY(entry_pos)));
	posi=atoi(ch3);

	info.compagnie=com;
	

	if(!verif_identifiant(info.Identifiant,info.compagnie.acronyme))//checks if the name is valid
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nL'identifiant est incorrecte!</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		
	}
	else if(!existe_pas(info.Identifiant))//checks if the name exists already or not 
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nL'identifiant du compagnie existe deja !</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		
	}
	else if(!chaine_num(ch1) || strlen(ch1)>=9)
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nLe niveau du carburant est Invalide!</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	else if(!chaine_num(ch2)||strlen(ch2)>=9)
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nLa consommation est Invalide !</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	else if(!verif_heure(info.heure_decollage))//checks if the hour is valid
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nL'heure de decollage est Invalide!</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		
	}
	else if(verif_nom((info.compagnie).nom)!=1)//checks if the name is valid
	{
		if(verif_nom((info.compagnie).nom)==-1)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le nom du compagnie est incorrecte!\nIl doit avoir au moins 1 caractére</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else if(verif_nom((info.compagnie).nom)==-2)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le nom du compagnie est incorrecte!\nIl doit étre alphabétique et contient un seul espace</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		
	}
	
	else if(posi>taille_liste() || posi<0 || !chaine_num(ch3) )
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nPosition Invalide !</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	else
	{
		info.carburant=atoi(ch1);
		info.consommation=atoi(ch2);
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"<span size=\"x-large\"foreground=\"#1D1D2C\">Le repertoire a été ajouter avec succés\nVoulez-vous ajouter un autre ?</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(response_ajouter),window);
		
	}
		
		
}
void exit_sup(GtkDialog *dialog,GtkWidget *window)
{
	gtk_widget_destroy(GTK_WIDGET(dialog));
	gtk_widget_destroy(window_SUP);

}
void response_modifier(GtkWidget *widget,GtkWidget *window)
{
	gtk_widget_destroy(widget);
}
void retour(GtkWidget *widget,GtkWidget *window)
{
	gtk_widget_destroy(window);
}

void Supression_call(GtkWidget *pBtn, gpointer data)
{
	char posii[100];
	if(!Vide())
		snprintf(posii,sizeof(posii),"Position de suppression : (entre 0(en tete) et %u(en queue) ",taille_liste()-1>=0?taille_liste()-1:0);
	else
		snprintf(posii,sizeof(posii),"La liste est vide!");
	gtk_frame_set_label(GTK_FRAME(frame1),posii);

    GtkWidget *pInfo;
    GtkWidget *pWindow;
    GSList *pList;
    const gchar *sLabel;
 
    /* Récupération de la liste des boutons */
    pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(data));
 	pWindow = gtk_widget_get_toplevel(GTK_WIDGET(data));
    /* Parcours de la liste */
    while(pList)
    {
        /* Le bouton est-il sélectionné */
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data)))
        {
            /* OUI -> on copie le label du bouton */
            sLabel = gtk_button_get_label(GTK_BUTTON(pList->data));
            /* On met la liste a NULL pour sortir de la boucle */
            pList = NULL;
        }
        else
        {
            /* NON -> on passe au bouton suivant */
            pList = g_slist_next(pList);
        }
    }
    if(Vide())
    {		
    	dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<b><span foreground=\"#501015\"> <span size=\"large\"> La liste est vide !</span></span></b>");
    	gtk_widget_show_all(dialog_ident);
    	g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
    	return;
    }
 
    else if(strcmp(sLabel,"Supression en tete ")==0)
    {
    		Supprimer_tete();
    		pWindow = gtk_widget_get_toplevel(GTK_WIDGET(data));
    		pInfo = gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nSuppression effectuée avec succèes</span>");
				gtk_dialog_run(GTK_DIALOG(pInfo)); 
    		gtk_widget_destroy(pInfo);
    }
    else if(strcmp(sLabel,"Supression en queue")==0)
    {
   			Supprimer_queue();
        pWindow = gtk_widget_get_toplevel(GTK_WIDGET(data)); 
        pInfo = gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nSuppression effectuée avec succèes</span>"); 
        gtk_dialog_run(GTK_DIALOG(pInfo)); 
        gtk_widget_destroy(pInfo);
	}
    else if(strcmp(sLabel,"Supression à partir d'une position")==0)
    {
    	char ch[256];
    	strcpy(ch,(char *)gtk_entry_get_text(GTK_ENTRY(entry1)));
		int position=atoi(ch);
		if(position>taille_liste()-1 || position <0 || !chaine_num(ch))
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nPosition Invalide !</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{	
					Supprimer_pos(position);
					gtk_entry_set_text(GTK_ENTRY(entry1),"");
					pWindow = gtk_widget_get_toplevel(GTK_WIDGET(data));
		 
		    		pInfo = gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nSuppression effectuée avec succèes</span>");
		 
		    		gtk_dialog_run(GTK_DIALOG(pInfo));
		 
		    		gtk_widget_destroy(pInfo);
		 }
    }
    else if(strcmp(sLabel,"Supression d'un avion donné ")==0)
    {
    	char nom[256];
    	strcpy(nom,(char *)gtk_entry_get_text(GTK_ENTRY(entry2)));
    	if(existe_pas(nom))
    	{
    		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nL'identifiant n'existe pas!</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
    	}
    	else
    	{
    		Supprimer_avion(nom);
    		pWindow = gtk_widget_get_toplevel(GTK_WIDGET(data));
 
    		pInfo = gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nSuppression effectuée avec succèes</span>");
 
    		gtk_dialog_run(GTK_DIALOG(pInfo));
 
    		gtk_widget_destroy(pInfo);
    	}
    	gtk_entry_set_text(GTK_ENTRY(entry2),"");
    }
    else if(strcmp(sLabel,"Supression des avions d'une compagnie ")==0)
    {
    	char nom[256];
    	strcpy(nom,(char *)gtk_entry_get_text(GTK_ENTRY(entry3)));
    	if(!existe_pas_comp_nom(nom))
    	{
    		Supprimer_comp(nom);
    		gtk_entry_set_text(GTK_ENTRY(entry3),"");
    		pWindow = gtk_widget_get_toplevel(GTK_WIDGET(data));
 
    		pInfo = gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nSuppression effectuée avec succèes</span>");
 
    		gtk_dialog_run(GTK_DIALOG(pInfo));
 
    		gtk_widget_destroy(pInfo);
    	}
    	else
    	{
    		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(pWindow),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nLe nom du compagnie n'existe pas!</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
    	}
    	
    }
    
    

	if(!Vide())
		snprintf(posii,sizeof(posii),"Position de suppression : (entre 0(en tete) et %u(en queue) ",taille_liste()-1>=0?taille_liste()-1:0);
	else
		snprintf(posii,sizeof(posii),"La liste est vide!");
	gtk_frame_set_label(GTK_FRAME(frame1),posii);

    
}

void modifie(GtkWidget *widget,GtkWidget *window)
{

	Cellule *av=rech_ident(nom_avion);
	Avion inf;
	Compagnie com;
	char ch1[100];
	char ch2[100];
	strcpy(inf.Identifiant,(char *)gtk_entry_get_text(GTK_ENTRY(entry_ident)));
	strcpy(ch1,(char *)gtk_entry_get_text(GTK_ENTRY(entry_carb)));
	strcpy(ch2,(char *)gtk_entry_get_text(GTK_ENTRY(entry_consom)));
	strcpy(inf.heure_decollage,(char *)gtk_entry_get_text(GTK_ENTRY(entry_heure)));
	strcpy(com.nom,(char *)gtk_entry_get_text(GTK_ENTRY(entry_comp_nom)));
	strcpy(com.acronyme,(char *)gtk_entry_get_text(GTK_ENTRY(entry_comp_acro)));
	strcpy(inf.compagnie.nom,com.nom);
	strcpy(inf.compagnie.acronyme,com.acronyme);

	if(!verif_identifiant(inf.Identifiant,inf.compagnie.acronyme))//checks if the name is valid
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \n l'identifiant est incorrecte! </span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	else if(!chaine_num(ch1)||strlen(ch1)>=9)
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nLe niveau du carburant est Invalide!</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	else if(!chaine_num(ch2)||strlen(ch2)>=9)
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nLa consommation est Invalide !</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	else if(!verif_heure(inf.heure_decollage))//checks if the hour is valid
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nL'heure de decollage est Invalide!</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		
	}
	else if(verif_nom(inf.compagnie.nom)!=1)//checks if the name is valid
	{

		if(verif_nom((inf.compagnie).nom)==-1)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le nom du compagnie est incorrecte!\nIl doit avoir au moins 1 caractére</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else if(verif_nom((inf.compagnie).nom)==-2)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le nom du compagnie est incorrecte!\nIl doit étre alphabétique et contient un seul espace </span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		
	}
	else if(!existe_pas(inf.Identifiant))//checks if the name exists already or not 
	{
		if(strcmp(nom_avion,inf.Identifiant)==0)
		{
			inf.carburant=atoi(ch1);
			inf.consommation=atoi(ch2);
			av->cle=inf;
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nLe repertoire a été modifier avec succée</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(response_modifier),window);
			
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \nL'identifiant du compagnie existe deja !</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		
		
	}
	else
	{
		inf.carburant=atoi(ch1);
		inf.consommation=atoi(ch2);
		av->cle=inf;
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nLe repertoire a été modifier avec succée</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(response_modifier),window);
		
	}
}
void about_fun(GtkWidget *widget,GtkWidget *window)
{
	
	
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("airplane.png", NULL);
  	GtkWidget *about_dialog = gtk_about_dialog_new();
  	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "Repertoire d'avion");
  	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog), "5.0.5"); 
  	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),"© 2020-2021 H.Ahmed ");
  	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),"Mini projet par Ahmed Hamila.\ncsahmed17@gmail.com");
  	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog),"https://www.facebook.com/ahmed.hamila66");
  	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_dialog), pixbuf);
  	g_object_unref(pixbuf), pixbuf = NULL;
  	gtk_dialog_run(GTK_DIALOG (about_dialog));
  	gtk_widget_destroy(about_dialog);

		

	

}

void contenu_fichier(GtkWidget *widget,gpointer data)
{
	system("gedit PROJECT.txt");
}
void question_rep(GtkWidget *widget,gint response_id,GtkWidget *window)
{
	if (response_id == GTK_RESPONSE_YES) 
  	{
  		Enregistrement();
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nEnregistrement éffectuée avec succèes</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
			gtk_widget_destroy(widget);
  	}
  else if(response_id==GTK_RESPONSE_NO)
  {
  	gtk_widget_destroy(widget);
  }
}
void affiche_enonce(GtkWidget *widget,gpointer data)
{
	system("xdg-open projet.pdf ");
}

void question_reponse(GtkWidget *widget,gint response_id,GtkWidget *window)
{
	if (response_id == GTK_RESPONSE_YES) 
  	{
  		Enregistrement();
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nEnregistrement éffectuée avec succèes</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		gtk_main_quit();
  	}
  else if(response_id==GTK_RESPONSE_NO)
  {
  	gtk_main_quit();
  }
}


void exit_enr(GtkWidget *widget,gpointer data)
{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(widget),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nVoulez Vous faire l'enregistrement avant de sortir?</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(question_reponse),widget);
}
void exit_enr_quit(GtkWidget *widget,GtkWidget *window)
{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nVoulez Vous faire l'enregistrement avant de sortir?</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(question_reponse),window);
}
/**************************************************************************************************************************************************************/

/*WINDOW INITIALISATION*/



GtkWidget * window_init()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Gestion d'un aéroport");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(exit_enr),NULL);
  	return window;
}
GtkWidget *pass_window_init()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Login Page");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(end_program),NULL);
  	return window;
}
GtkWidget * window_init_creation()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Creation de la liste ");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget * window_init_ajout()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Ajout d'un element  ");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget * window_init_supp()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Supression d'un element  ");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget * window_init_mod_pop()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Saisie d'Identifiant");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget * window_init_mod_main()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Modifier les données d'un avion  ");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget * window_init_affichage()
{
  GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

  scrolled_window=gtk_scrolled_window_new (NULL, NULL);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  gtk_container_add (GTK_CONTAINER (window), scrolled_window);

  gtk_window_set_title (GTK_WINDOW (window), "Affichage des avions");  //title for the window 
    gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window),10);

    g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
    return window;
}
GtkWidget *window_init_rech_id_pop()
{

	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Recherche par identifiant");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget *window_init_rech_com_pop()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);


	gtk_window_set_title (GTK_WINDOW (window), "Recherche par Nom du compagnie");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget *window_init_rech_id_main()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

	scrolled_window=gtk_scrolled_window_new (NULL, NULL);
 	 gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
  	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  	gtk_container_add (GTK_CONTAINER (window), scrolled_window);

	gtk_window_set_title (GTK_WINDOW (window), "Recherche par identifiant");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget *window_init_rech_com_main()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

	scrolled_window=gtk_scrolled_window_new (NULL, NULL);
  	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
  	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  	gtk_container_add (GTK_CONTAINER (window), scrolled_window);

	gtk_window_set_title (GTK_WINDOW (window), "Recherche par nom du compagnie");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget *window_init_rech_heur_main()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

	scrolled_window=gtk_scrolled_window_new (NULL, NULL);
  	gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);
  	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER (window), scrolled_window);

	gtk_window_set_title (GTK_WINDOW (window), "Recherche par Heure de decollage");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
GtkWidget *window_init_rech_heur_pop()
{
	GtkWidget *window=(GtkWidget *)malloc(sizeof(GtkWidget));
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Recherche par Heure de décollage");  //title for the window 
  	gtk_window_set_default_size (GTK_WINDOW (window), 1920, 1200);  //window size
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  	gtk_container_set_border_width(GTK_CONTAINER(window),10);
  	g_signal_connect(window,"delete_event",G_CALLBACK(destroy_window),NULL);
  	return window;
}
/****************************************************************************************************************************************/
/*Affichage des fenetres*/

void Display_affichage(GtkWidget * widget,GtkWidget * window)
{
	FILE *F=fopen("PROJECT.txt","r+");
	fseek(F, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(F);
	if(!Vide())
	{
		GtkWidget *window_crea=window_init_affichage();
		affichage_main(window_crea);
		gtk_widget_show_all(window_crea);
	}
	else
	{
		if(len>0)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">La liste est Vide !\nEssayez de faire le Chargement</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	fclose(F);
	
}
void Display_mod_pop(GtkWidget * widget,GtkWidget *window)
{
	FILE *F=fopen("PROJECT.txt","r+");
	fseek(F, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(F);
	if(!Vide())
	{
		GtkWidget *window_crea=window_init_mod_pop();
		mod_menu_pop(window_crea);
		gtk_widget_show_all(window_crea);
	}
	else
	{
		if(len>0)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">La liste est Vide !\nEssayez de faire le Chargement</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	fclose(F);
	
}

void Display_mod_main(GtkWidget * widget,GtkWidget *window)
{	
    strcpy(nom_avion,(char *)gtk_entry_get_text(GTK_ENTRY(entry_pop)));
    if(existe_pas(nom_avion))
    {
    	dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\"> \n L'identifiant n'existe pas! </span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		gtk_widget_destroy(window);
    }
    else
    {
    	gtk_widget_destroy(window);
    	GtkWidget *window_crea=window_init_mod_main();
		mod_menu_main(window_crea);
		gtk_widget_show_all(window_crea);
    }
	
}

void Display_rech_id_main(GtkWidget * widget,GtkWidget *window)
{

	strcpy(nom_avion,(char *)gtk_entry_get_text(GTK_ENTRY(entry_pop)));
    if(existe_pas(nom_avion))
    {
    	dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">\nl'identifiant n'existe pas!</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		gtk_widget_destroy(window);
    }
    else
    {
    	gtk_widget_destroy(window);
    	GtkWidget *window_crea=window_init_rech_id_main();
		rech_id_main(window_crea);
		gtk_widget_show_all(window_crea);
    }
}

void Display_rech_com_main(GtkWidget * widget,GtkWidget *window)
{
	strcpy(comp_nom,(char *)gtk_entry_get_text(GTK_ENTRY(entry_pop)));
    if(existe_pas_comp_nom(comp_nom))
    {
    	dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">\nLe nom du compagnie n'existe pas!</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		gtk_widget_destroy(window);
    }
    else
    {
    	gtk_widget_destroy(window);
    	GtkWidget *window_crea=window_init_rech_com_main();
		rech_com_main(window_crea);
		gtk_widget_show_all(window_crea);
    }
}
void Display_rech_heur_main(GtkWidget * widget,GtkWidget *window)
{
	strcpy(heur_d,(char *)gtk_entry_get_text(GTK_ENTRY(entry_pop)));
    if(existe_pas_hure(heur_d))
    {
    	dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">\nL'heure de decollage n'existe pas!</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		gtk_widget_destroy(window);
    }
    else
    {
    	gtk_widget_destroy(window);
    	GtkWidget *window_crea=window_init_rech_heur_main();
		rech_heur_main(window_crea);
		gtk_widget_show_all(window_crea);
    }
}

void Display_Supprimer(GtkWidget * widget,GtkWidget *window)
{
	FILE *F=fopen("PROJECT.txt","r+");
	fseek(F, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(F);
	if(!Vide())
	{
		window_SUP=window_init_supp();
		supp_menu(window_SUP);
		gtk_widget_show_all(window_SUP);
	}
	else
	{
		if(len>0)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">La liste est Vide !\nEssayez de faire le Chargement</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	fclose(F);
	
}
void Display_creation_menu(GtkWidget * widget,GtkWidget *window)
{
	FILE *F;
	if(F=fopen("PROJECT.txt","r+"))
	{
		fseek(F, 0, SEEK_END);
	    unsigned long len = (unsigned long)ftell(F);
	    if(len>0)
	    {
	    	if(!Vide())
			{
				dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#501015\">\nLa liste est deja crée!</span>");
				gtk_widget_show_all(dialog_ident);
				g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
			}
			else
			{
				dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#501015\">Fichier n'est pas Vide!\nEssayez de faire le Chargement</span>");
				gtk_widget_show_all(dialog_ident);
				g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
			}
	    	
	    }
		else
		{
				if(!Vide())
			{
				dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#501015\">\nLa liste est deja crée!</span>");
				gtk_widget_show_all(dialog_ident);
				g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
			}
			else
			{
				GtkWidget *window_crea=window_init_creation();
				Creation_menu(window_crea);
				gtk_widget_show_all(window_crea);
			}
	
		}
		fclose(F);
	}
	else
	{
		system("touch PROJECT.txt");
		F=fopen("PROJECT.txt","r+");
		fseek(F, 0, SEEK_END);
	    unsigned long len = (unsigned long)ftell(F);
	    if(len>0)
	    {
	    	if(!Vide())
			{
				dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#501015\">\nLa liste est deja crée!</span>");
				gtk_widget_show_all(dialog_ident);
				g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
			}
			else
			{
				dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#501015\">Fichier n'est pas Vide!\nEssayez de faire le Chargement</span>");
				gtk_widget_show_all(dialog_ident);
				g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
			}
	    	
	    }
		else
		{
			
			
				GtkWidget *window_crea=window_init_creation();
				Creation_menu(window_crea);
				gtk_widget_show_all(window_crea);
			
			
		}
		fclose(F);
	}
	
	
}
void Display_ajout_menu(GtkWidget * widget,GtkWidget *window)
{
	FILE *F=fopen("PROJECT.txt","r+");
	fseek(F, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(F);
	if(!Vide())
	{
		GtkWidget *window_crea=window_init_ajout();
		ajout_menu(window_crea);
		gtk_widget_show_all(window_crea);
	}
	else
	{
		if(len>0)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">La liste est Vide !\nEssayez de faire le Chargement</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	fclose(F);
	
}
void Display_Rech_Id_pop(GtkWidget * widget,GtkWidget *window)
{
	FILE *F=fopen("PROJECT.txt","r+");
	fseek(F, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(F);
	if(!Vide())
	{
		GtkWidget *window_crea=window_init_rech_id_pop();
		rech_id_pop(window_crea);
		gtk_widget_show_all(window_crea);
	}
	else
	{
		if(len>0)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">La liste est Vide !\nEssayez de faire le Chargement</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	fclose(F);
	
}
void Display_Rech_comp_pop(GtkWidget * widget,GtkWidget *window)
{
	FILE *F=fopen("PROJECT.txt","r+");
	fseek(F, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(F);
	if(!Vide())
	{
		GtkWidget *window_crea=window_init_rech_com_pop();
		rech_com_pop(window_crea);
		gtk_widget_show_all(window_crea);
	}
	else
	{
		if(len>0)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">La liste est Vide !\nEssayez de faire le Chargement</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	fclose(F);
	
}
void Display_Rech_heur_pop(GtkWidget * widget,GtkWidget *window)
{
	FILE *F=fopen("PROJECT.txt","r+");
	fseek(F, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(F);
	if(!Vide())
	{
		GtkWidget *window_crea=window_init_rech_heur_pop();
		rech_heur_pop(window_crea);
		gtk_widget_show_all(window_crea);
	}
	else
	{
		if(len>0)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">La liste est Vide !\nEssayez de faire le Chargement</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	fclose(F);
	
}
void Display_Tri(GtkWidget *widget,GtkWidget * window)
{
	FILE *F=fopen("PROJECT.txt","r+");
	fseek(F, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(F);
	if(!Vide())
	{
		Tri_liste();
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nLa liste à été Triée avec succèes</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	else
	{
		if(len>0)
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">La liste est Vide !\nEssayez de faire le Chargement</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	fclose(F);
		
}
void Enregistrement_call(GtkWidget * widget,GtkWidget *window)
{
	FILE *F;
	if(F=fopen("PROJECT.txt","r+"))
	{
		if(Vide())
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"<span size=\"x-large\"foreground=\"#1D1D2C\">La liste est vide !\nvoulez vous enregistrer ?</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(question_rep),window);
		}
		else
		{
			Enregistrement();
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nEnregistrement éffectuée avec succèes</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	else
	{
		system("touch PROJECT.txt");
		if(Vide())
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"<span size=\"x-large\"foreground=\"#1D1D2C\">La liste est vide !\nvoulez vous enregistrer ?</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(question_rep),window);
		}
		else
		{
			Enregistrement();
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nEnregistrement éffectuée avec succèes</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	

}
void Chargement_call(GtkWidget * widget,GtkWidget *window)
{
	FILE *F;
	if(F=fopen("PROJECT.txt","r+"))
	{
		fseek(F, 0, SEEK_END);
	    unsigned long len = (unsigned long)ftell(F);
		if(len>0)
		{
			Chargement();
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#1D1D2C\">\nChargement éffectuée avec succèes</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
		else
		{
			dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier est Vide !\nEssayez de faire la Création</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
		}
	}
	else
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_WARNING,GTK_BUTTONS_OK,"<span foreground=\"#501015\" size=\"x-large\">Le Fichier n'existe pas</span>");
			gtk_widget_show_all(dialog_ident);
			g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	
}
/****************************************************************************************************************************************/
/*L'implementation des fenetres*/

void Create_first_Menu(GtkWidget *window)
{
	box=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),box);

    
	
	mbar=gtk_menu_bar_new();
	

	
 	Creation_du_repertoire= gtk_menu_item_new_with_label (" | Création du répertoire Avion | ");
 	gtk_menu_shell_append (GTK_MENU_SHELL (mbar), Creation_du_repertoire);
 	Mise_a_jour= gtk_menu_item_new_with_label (" | Mise à jour des Avions | ");
 	gtk_menu_shell_append (GTK_MENU_SHELL (mbar), Mise_a_jour);
 	Recherche= gtk_menu_item_new_with_label (" | Recherche , Affichage et Tri | ");
 	gtk_menu_shell_append (GTK_MENU_SHELL (mbar), Recherche);
	enregistrement= gtk_menu_item_new_with_label (" | Enregistrement et chargement dans un fichier | ");
 	gtk_menu_shell_append (GTK_MENU_SHELL (mbar), enregistrement);
 	about= gtk_menu_item_new_with_label (" | About | ");
 	gtk_menu_shell_append (GTK_MENU_SHELL (mbar), about);
 	GtkWidget *enonce= gtk_menu_item_new_with_label (" | Enoncé | ");
 	gtk_menu_shell_append (GTK_MENU_SHELL (mbar), enonce);
	QUIT= gtk_menu_item_new_with_label (" | Quitter | ");
 	gtk_menu_shell_append (GTK_MENU_SHELL (mbar), QUIT);
 	

 	


	
 	MAJ= gtk_menu_new ();
 	gtk_menu_item_set_submenu (GTK_MENU_ITEM (Mise_a_jour), MAJ);
 	Rech = gtk_menu_new ();
 	gtk_menu_item_set_submenu (GTK_MENU_ITEM (Recherche), Rech);
 	Enr = gtk_menu_new ();
 	gtk_menu_item_set_submenu (GTK_MENU_ITEM (enregistrement), Enr);


 	MAJ_ajouter_text= gtk_menu_item_new_with_label ("Ajouter un nouvel avion");
 	gtk_menu_shell_append (GTK_MENU_SHELL (MAJ), MAJ_ajouter_text);
 	MAJ_Supprimer_text= gtk_menu_item_new_with_label ("supprimer un avion");
 	gtk_menu_shell_append (GTK_MENU_SHELL (MAJ), MAJ_Supprimer_text);
 	MAJ_modifier_text= gtk_menu_item_new_with_label ("modifier les donnees d'un avion");
 	gtk_menu_shell_append (GTK_MENU_SHELL (MAJ), MAJ_modifier_text);

 	Rech_cont_text= gtk_menu_item_new_with_label ("Contenu de la liste des avions");
 	gtk_menu_shell_append (GTK_MENU_SHELL (Rech), Rech_cont_text);
 	Rech_ident_text= gtk_menu_item_new_with_label ("Recherche par Identifiant avion");
 	gtk_menu_shell_append (GTK_MENU_SHELL (Rech), Rech_ident_text);
 	Rech_comp_text= gtk_menu_item_new_with_label ("Recherche par compagnie");
 	gtk_menu_shell_append (GTK_MENU_SHELL (Rech), Rech_comp_text);
 	Rech_heure_text= gtk_menu_item_new_with_label ("Recherche par heure de décollage");
 	gtk_menu_shell_append (GTK_MENU_SHELL (Rech), Rech_heure_text);
 	Rech_Tri_text= gtk_menu_item_new_with_label ("Tri");
 	gtk_menu_shell_append (GTK_MENU_SHELL (Rech), Rech_Tri_text);

 	Enr_enreg_text= gtk_menu_item_new_with_label ("Enregistrement");
 	gtk_menu_shell_append (GTK_MENU_SHELL (Enr), Enr_enreg_text);
 	Enr_charg_text= gtk_menu_item_new_with_label ("Chargement");
 	gtk_menu_shell_append (GTK_MENU_SHELL (Enr), Enr_charg_text);
 	GtkWidget *Enr_cont_text= gtk_menu_item_new_with_label ("Contenue du Fichier");
 	gtk_menu_shell_append (GTK_MENU_SHELL (Enr), Enr_cont_text);


 	gtk_widget_set_name(MAJ_ajouter_text,"creation_bar");
	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(MAJ_ajouter_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(MAJ_Supprimer_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	
    context = gtk_widget_get_style_context(MAJ_Supprimer_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(MAJ_modifier_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

    context = gtk_widget_get_style_context(MAJ_modifier_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Rech_cont_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

    context = gtk_widget_get_style_context(Rech_cont_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Rech_ident_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	context;
    context = gtk_widget_get_style_context(Rech_ident_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Rech_comp_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

    context = gtk_widget_get_style_context(Rech_comp_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Rech_heure_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

    context = gtk_widget_get_style_context(Rech_heure_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Rech_Tri_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

    context = gtk_widget_get_style_context(Rech_Tri_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Enr_enreg_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

    context = gtk_widget_get_style_context(Enr_enreg_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Enr_charg_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

    context = gtk_widget_get_style_context(Enr_charg_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Enr_cont_text,"creation_bar");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

    context = gtk_widget_get_style_context(Enr_cont_text);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(window,"window_main");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);

   context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);



		GtkWidget *image1 = gtk_image_new_from_file("airplane -01.png"); // put path to your image here
    gtk_fixed_put(GTK_FIXED(box),image1,100,50);

    GtkWidget *image2 = gtk_image_new_from_file("airplane -01.png"); // put path to your image here
		gtk_fixed_put(GTK_FIXED(box),image2,20,300);

    GtkWidget *image3 = gtk_image_new_from_file("airplane -01.png"); // put path to your image here
    gtk_fixed_put(GTK_FIXED(box),image3,-100,600);

    GtkWidget *image4 = gtk_image_new_from_file("airplane -01.png"); // put path to your image here
    gtk_fixed_put(GTK_FIXED(box),image4,50,900);

    gtk_widget_set_name(image1,"imagee");
		provider = gtk_css_provider_new ();
		gtk_css_provider_load_from_path (provider, "main.css", NULL);

   	context = gtk_widget_get_style_context(image1);
		gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

		gtk_widget_set_name(image2,"imagee");
		provider = gtk_css_provider_new ();
		gtk_css_provider_load_from_path (provider, "main.css", NULL);

   	context = gtk_widget_get_style_context(image2);
		gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

		gtk_widget_set_name(image3,"imagee");
		provider = gtk_css_provider_new ();
		gtk_css_provider_load_from_path (provider, "main.css", NULL);

   	context = gtk_widget_get_style_context(image3);
		gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

		gtk_widget_set_name(image4,"imagee");
		provider = gtk_css_provider_new ();
		gtk_css_provider_load_from_path (provider, "main.css", NULL);

   	context = gtk_widget_get_style_context(image4);
		gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);



 	/*Fonctionnalite*/

 	g_signal_connect(G_OBJECT(QUIT),"activate",G_CALLBACK(exit_enr_quit),window);
 	g_signal_connect(G_OBJECT(Creation_du_repertoire),"activate",G_CALLBACK(Display_creation_menu),NULL);
 	g_signal_connect(G_OBJECT(MAJ_ajouter_text),"activate",G_CALLBACK(Display_ajout_menu),window);
 	g_signal_connect(G_OBJECT(MAJ_Supprimer_text),"activate",G_CALLBACK(Display_Supprimer),window);
 	g_signal_connect(G_OBJECT(Enr_enreg_text),"activate",G_CALLBACK(Enregistrement_call),window);
 	g_signal_connect(G_OBJECT(Enr_charg_text),"activate",G_CALLBACK(Chargement_call),window);
 	g_signal_connect(G_OBJECT(MAJ_modifier_text),"activate",G_CALLBACK(Display_mod_pop),window);
 	g_signal_connect(G_OBJECT(Rech_cont_text),"activate",G_CALLBACK(Display_affichage),window);
 	g_signal_connect(G_OBJECT(Rech_ident_text),"activate",G_CALLBACK(Display_Rech_Id_pop),window);
 	g_signal_connect(G_OBJECT(Rech_comp_text),"activate",G_CALLBACK(Display_Rech_comp_pop),window);
 	g_signal_connect(G_OBJECT(Rech_heure_text),"activate",G_CALLBACK(Display_Rech_heur_pop),window);
 	g_signal_connect(G_OBJECT(Rech_Tri_text),"activate",G_CALLBACK(Display_Tri),window);
 	g_signal_connect(G_OBJECT(about),"activate",G_CALLBACK(about_fun),window);
 	g_signal_connect(G_OBJECT(Enr_cont_text),"activate",G_CALLBACK(contenu_fichier),NULL);
 	g_signal_connect(G_OBJECT(enonce),"activate",G_CALLBACK(affiche_enonce),NULL);

 	/********************/
	 
	
	gtk_fixed_put(GTK_FIXED(box),mbar,0,0);
	gtk_widget_set_size_request(mbar,1810,40);

}
char User_name[256];
char Password[256];

char ver_name_pass[2000];

void verif_pass(GtkWidget *widget,GtkWidget *window)
{
	int found=0;
	strcpy(User_name,(char *)gtk_entry_get_text(GTK_ENTRY(user_entry)));
	strcpy(Password,(char *)gtk_entry_get_text(GTK_ENTRY(Pass_entry)));
	char name_pass[2000];
	strcpy(name_pass,User_name);
	strcat(name_pass,"/");
	strcat(name_pass,Password);
	strcat(name_pass,"/");
	FILE *P=fopen("Password.txt","r");
	while(fscanf(P,"%[^\n]\n",ver_name_pass)!=EOF)
	{
		if(strcmp(name_pass,ver_name_pass)==0)
		{
			gtk_widget_destroy(GTK_WIDGET(window));
			GtkWidget *m_window=window_init();
			Create_first_Menu(m_window);
			gtk_widget_show_all(m_window);
			found=1;
			break;
		}
	}
	if(!found)
	{
		dialog_ident=gtk_message_dialog_new_with_markup(GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"<span size=\"x-large\"foreground=\"#501015\">\nUser Name ou mot de passe Incorrecte !</span>");
		gtk_widget_show_all(dialog_ident);
		g_signal_connect(GTK_DIALOG(dialog_ident),"response",G_CALLBACK(on_response),NULL);
	}
	fclose(P);
	

}
void show_hide_fun(GtkWidget *widget,GtkWidget *entry)
{
	gboolean boo=gtk_entry_get_visibility(GTK_ENTRY(entry));
	gtk_entry_set_visibility(GTK_ENTRY(entry),!boo);
	const gchar *but=gtk_button_get_label(GTK_BUTTON(widget));
	if(strcmp(but,"Show")==0)
		gtk_button_set_label(GTK_BUTTON(widget),"Hide");
	else
		gtk_button_set_label(GTK_BUTTON(widget),"Show");
}
void pass_page(GtkWidget *window)
{
	GtkWidget *fix=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),fix);

	GtkWidget *login_button=gtk_button_new_with_label("Sign In");
	GtkWidget *show_hide=gtk_button_new_with_label("Show");

	GtkWidget *user_frame=gtk_frame_new("User Name : ");
	GtkWidget *Pass_frame=gtk_frame_new("Password : ");
	GtkWidget *Login_label=gtk_label_new("");
	char *str=g_strdup_printf("<span  font=\"25\" color=\"#e38881\"> <b> LOGIN </b>  </span>");
	gtk_label_set_markup(GTK_LABEL(Login_label),str);

	user_entry=gtk_entry_new();
	Pass_entry=gtk_entry_new();

	gtk_entry_set_placeholder_text(GTK_ENTRY(user_entry),"User Name");
	gtk_entry_set_placeholder_text(GTK_ENTRY(Pass_entry),"Password");

	GIcon *icon;
	GFile *path; 
	path = g_file_new_for_path("user.png"); 
	icon = g_file_icon_new(path); 
	gtk_entry_set_icon_from_gicon(GTK_ENTRY(user_entry),GTK_ENTRY_ICON_PRIMARY,icon);

	path = g_file_new_for_path("password.png"); 
	icon = g_file_icon_new(path); 
	gtk_entry_set_icon_from_gicon(GTK_ENTRY(Pass_entry),GTK_ENTRY_ICON_PRIMARY,icon);

	gtk_entry_set_visibility(GTK_ENTRY(Pass_entry),FALSE);

	gtk_container_add(GTK_CONTAINER(user_frame),user_entry);
	gtk_container_add(GTK_CONTAINER(Pass_frame),Pass_entry);


	gtk_widget_set_name(window,"window");
	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);


	gtk_widget_set_name(login_button,"login_button");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	context = gtk_widget_get_style_context(login_button);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(user_entry,"user_entry");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	context = gtk_widget_get_style_context(user_entry);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Pass_entry,"Pass_entry");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	context = gtk_widget_get_style_context(Pass_entry);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(show_hide,"show_hide");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	context = gtk_widget_get_style_context(show_hide);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(user_frame,"user_frame");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	context = gtk_widget_get_style_context(user_frame);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_name(Pass_frame,"Pass_frame");
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	context = gtk_widget_get_style_context(Pass_frame);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_fixed_put(GTK_FIXED(fix),Login_label,700,300);
	gtk_widget_set_size_request(Login_label,500,75);

	gtk_fixed_put(GTK_FIXED(fix),user_frame,700,350);
	gtk_widget_set_size_request(user_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fix),Pass_frame,700,450);
	gtk_widget_set_size_request(Pass_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fix),login_button,700,600);
	gtk_widget_set_size_request(login_button,500,75);

	gtk_fixed_put(GTK_FIXED(fix),show_hide,1125,482);
	gtk_widget_set_size_request(show_hide,65,36);

	gtk_widget_show_all(window);
	g_signal_connect(G_OBJECT(login_button),"clicked",G_CALLBACK(verif_pass),window);
	g_signal_connect(G_OBJECT(show_hide),"clicked",G_CALLBACK(show_hide_fun),Pass_entry);	

	

}


void Creation_menu(GtkWidget *window)
{
	Creer_liste();
	button=gtk_button_new_with_label("AJOUTER");
	button2=gtk_button_new_with_label("Retour au menu Principal");
	identifiant_frame=gtk_frame_new("Identifiant: ");
	carburant_frame=gtk_frame_new("Niveau de carburant : ");
	consommation_frame=gtk_frame_new("Consommation(en minute) : ");
	heure_frame=gtk_frame_new("Heure de decollage(forme HH:MM:SS) : ");
	comp_nom_frame=gtk_frame_new("Nom du compagnie : ");
	comp_acro_frame=gtk_frame_new("Acronyme du compagnie : ");
	char posii[100];
	snprintf(posii,sizeof(posii),"Position de saisir : (entre 0(en tete) et %u(en queue) ",taille_liste());
	position=gtk_frame_new(posii);
	title=gtk_label_new("CREATION DU REPERTOIRE AVION");


	gtk_widget_set_name(window,"Crea_win");
	gtk_widget_set_name(button,"ajout_button");
	gtk_widget_set_name(button2,"retour_button");

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	context = gtk_widget_get_style_context(button);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	context = gtk_widget_get_style_context(button2);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);


	entry_ident=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_ident),6);
	gtk_container_add(GTK_CONTAINER(identifiant_frame),entry_ident);
	entry_carb=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(carburant_frame),entry_carb);
	entry_consom=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(consommation_frame),entry_consom);
	entry_heure=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_heure),8);
	gtk_container_add(GTK_CONTAINER(heure_frame),entry_heure);
	entry_comp_nom=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(comp_nom_frame),entry_comp_nom);
	entry_comp_acro=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_comp_acro),3);
	gtk_container_add(GTK_CONTAINER(comp_acro_frame),entry_comp_acro);
	entry_pos=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(position),entry_pos);
	gtk_entry_set_text(GTK_ENTRY(entry_pos),"0");

	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),fixed);
	/*INPUTS*/
	gtk_fixed_put(GTK_FIXED(fixed),identifiant_frame,700,300);
	gtk_widget_set_size_request(identifiant_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),carburant_frame,700,375);
	gtk_widget_set_size_request(carburant_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),consommation_frame,700,450);
	gtk_widget_set_size_request(consommation_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),heure_frame,700,525);
	gtk_widget_set_size_request(heure_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),comp_nom_frame,700,600);
	gtk_widget_set_size_request(comp_nom_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),comp_acro_frame,700,675);
	gtk_widget_set_size_request(comp_acro_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),position,700,750);
	gtk_widget_set_size_request(position,500,75);


	/*BUTTONS*/
	gtk_fixed_put(GTK_FIXED(fixed),button,1000,900);
	gtk_widget_set_size_request(button,200,75);
	gtk_fixed_put(GTK_FIXED(fixed),button2,700,900);
	gtk_widget_set_size_request(button2,200,75);

	char *str=g_strdup_printf("<span  font=\"25\" color=\"#0F6079\"> <b> CREATION DU REPERTOIRE AVION </b>  </span>");
	
	gtk_label_set_markup(GTK_LABEL(title),str);

	gtk_fixed_put(GTK_FIXED(fixed),title,665,50);
	gtk_widget_set_size_request(title,200,200);

	g_signal_connect(button,"clicked",G_CALLBACK(saisie),window);
	g_signal_connect(button2,"clicked",G_CALLBACK(destroy_wind),window);
	
	
		
}
void ajout_menu(GtkWidget *window)
{
	button=gtk_button_new_with_label("AJOUTER");
	button2=gtk_button_new_with_label("Retour au menu Principal");
	identifiant_frame=gtk_frame_new("Identifiant: ");
	carburant_frame=gtk_frame_new("Niveau de carburant : ");
	consommation_frame=gtk_frame_new("Consommation(en minute) : ");
	heure_frame=gtk_frame_new("Heure de decollage(forme HH:MM:SS) : ");
	comp_nom_frame=gtk_frame_new("Nom du compagnie : ");
	comp_acro_frame=gtk_frame_new("Acronyme du compagnie : ");
	char posii[100];
	snprintf(posii,sizeof(posii),"Position de saisir : (entre 0(en tete) et %u(en queue) ",taille_liste());
	position=gtk_frame_new(posii);
	title=gtk_label_new("Ajout du repertoire ");


	gtk_widget_set_name(window,"Crea_win");
	gtk_widget_set_name(button,"ajout_button");
	gtk_widget_set_name(button2,"retour_button");

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	context = gtk_widget_get_style_context(button);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	context = gtk_widget_get_style_context(button2);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);


	entry_ident=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_ident),6);
	gtk_container_add(GTK_CONTAINER(identifiant_frame),entry_ident);
	entry_carb=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(carburant_frame),entry_carb);
	entry_consom=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(consommation_frame),entry_consom);
	entry_heure=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_heure),8);
	gtk_container_add(GTK_CONTAINER(heure_frame),entry_heure);
	entry_comp_nom=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(comp_nom_frame),entry_comp_nom);
	entry_comp_acro=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_comp_acro),3);
	gtk_container_add(GTK_CONTAINER(comp_acro_frame),entry_comp_acro);
	entry_pos=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(position),entry_pos);

	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),fixed);
	/*INPUTS*/
	gtk_fixed_put(GTK_FIXED(fixed),identifiant_frame,700,300);
	gtk_widget_set_size_request(identifiant_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),carburant_frame,700,375);
	gtk_widget_set_size_request(carburant_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),consommation_frame,700,450);
	gtk_widget_set_size_request(consommation_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),heure_frame,700,525);
	gtk_widget_set_size_request(heure_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),comp_nom_frame,700,600);
	gtk_widget_set_size_request(comp_nom_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),comp_acro_frame,700,675);
	gtk_widget_set_size_request(comp_acro_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),position,700,750);
	gtk_widget_set_size_request(position,500,75);


	/*BUTTONS*/
	gtk_fixed_put(GTK_FIXED(fixed),button,1000,900);
	gtk_widget_set_size_request(button,200,75);
	gtk_fixed_put(GTK_FIXED(fixed),button2,700,900);
	gtk_widget_set_size_request(button2,200,75);

	char *str=g_strdup_printf("<span  font=\"25\" color=\"#0F6079\"> <b> AJOUT DU REPERTOIRE AVION </b> </span>");
	
	gtk_label_set_markup(GTK_LABEL(title),str);

	gtk_fixed_put(GTK_FIXED(fixed),title,692,50);
	gtk_widget_set_size_request(title,200,200);

	g_signal_connect(button,"clicked",G_CALLBACK(saisie),window);
	g_signal_connect(button2,"clicked",G_CALLBACK(destroy_wind),window);
	
}


void supp_menu()
{
	title=gtk_label_new("Ajout du repertoire ");
	char *str=g_strdup_printf("<span  font=\"25\" color=\"#BB1A32\"> <b> SUPRESSION D'UN AVION </b></span>");
	gtk_label_set_markup(GTK_LABEL(title),str);
	
	GtkWidget *label=gtk_label_new("aaa ");
	str=g_strdup_printf("<span  font=\"14\" color=\"#BB521A\"> <b>VOTRE CHOIX :   </b></span>");
	gtk_label_set_markup(GTK_LABEL(label),str);

	GtkWidget *radio1=gtk_radio_button_new_with_label(NULL,"Supression en tete ");
	GtkWidget *radio2=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (radio1),"Supression en queue");
	GtkWidget *radio3=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (radio1),"Supression à partir d'une position");
	GtkWidget *radio4=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (radio1),"Supression d'un avion donné ");
	GtkWidget *radio5=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON (radio1),"Supression des avions d'une compagnie ");
	GtkWidget *valider=gtk_button_new_with_label("valider");
	GtkWidget *Exit=gtk_button_new_with_label("Retour au menu Principal");


	gtk_widget_set_name(window_SUP,"supp_win");
	gtk_widget_set_name(valider,"ajout_button");
	gtk_widget_set_name(Exit,"retour_button");

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window_SUP);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	context = gtk_widget_get_style_context(valider);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	context = gtk_widget_get_style_context(Exit);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);


	char posii[100];
	if(!Vide())
		snprintf(posii,sizeof(posii),"Position de suppression : (entre 0(en tete) et %u(en queue) ",taille_liste() -1>=0?taille_liste()-1:0);
	else
		snprintf(posii,sizeof(posii),"Liste est vide !!");
	frame1=gtk_frame_new(posii);
	GtkWidget *frame2=gtk_frame_new("Nom d'avion : ");
	GtkWidget *frame3=gtk_frame_new("Nom du compagnie : ");

	entry1=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(frame1),entry1);
	entry2=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry2),6);
	gtk_container_add(GTK_CONTAINER(frame2),entry2);
	entry3=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(frame3),entry3);

	gtk_entry_set_text(GTK_ENTRY(entry1),"0");

	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window_SUP),fixed);

	gtk_fixed_put(GTK_FIXED(fixed),label,700,280);
	gtk_widget_set_size_request(label,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),radio1,700,355);
	gtk_widget_set_size_request(radio1,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),radio2,700,430);
	gtk_widget_set_size_request(radio2,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),radio3,700,505);
	gtk_widget_set_size_request(radio3,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),radio4,700,580);
	gtk_widget_set_size_request(radio4,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),radio5,700,655);
	gtk_widget_set_size_request(radio5,500,75);

	gtk_fixed_put(GTK_FIXED(fixed),Exit,700,805);
	gtk_widget_set_size_request(Exit,200,75);

	gtk_fixed_put(GTK_FIXED(fixed),valider,950,805);
	gtk_widget_set_size_request(valider,200,75);

	gtk_fixed_put(GTK_FIXED(fixed),frame1,1050,505);
	gtk_widget_set_size_request(frame1,300,75);
	gtk_fixed_put(GTK_FIXED(fixed),frame2,1050,580);
	gtk_widget_set_size_request(frame2,300,75);
	gtk_fixed_put(GTK_FIXED(fixed),frame3,1050,655);
	gtk_widget_set_size_request(frame3,300,75);

	gtk_fixed_put(GTK_FIXED(fixed),title,688,40);
	gtk_widget_set_size_request(title,200,200);

	g_signal_connect(G_OBJECT(Exit),"clicked",G_CALLBACK(destroy_wind),window_SUP);
	g_signal_connect(G_OBJECT(valider),"clicked",G_CALLBACK(Supression_call),radio1);
}




void mod_menu_main(GtkWidget *window)
{
	fixed_p=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),fixed_p);

	button=gtk_button_new_with_label("MODIFIER");
	button2=gtk_button_new_with_label("Retour au menu Principal");
	identifiant_frame=gtk_frame_new("Identifiant: ");
	carburant_frame=gtk_frame_new("Niveau de carburant : ");
	consommation_frame=gtk_frame_new("Consommation(en minute) : ");
	heure_frame=gtk_frame_new("Heure de decollage(forme HH:MM:SS) : ");
	comp_nom_frame=gtk_frame_new("Nom du compagnie : ");
	comp_acro_frame=gtk_frame_new("Acronyme du compagnie : ");
	title=gtk_label_new("Ajout du repertoire ");



	gtk_widget_set_name(window,"Crea_win");
	gtk_widget_set_name(button,"ajout_button");
	gtk_widget_set_name(button2,"retour_button");

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	context = gtk_widget_get_style_context(button);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	context = gtk_widget_get_style_context(button2);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	entry_ident=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_ident),6);
	gtk_container_add(GTK_CONTAINER(identifiant_frame),entry_ident);
	entry_carb=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(carburant_frame),entry_carb);
	entry_consom=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(consommation_frame),entry_consom);
	entry_heure=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_heure),8);
	gtk_container_add(GTK_CONTAINER(heure_frame),entry_heure);
	entry_comp_nom=gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(comp_nom_frame),entry_comp_nom);
	entry_comp_acro=gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_comp_acro),3);
	gtk_container_add(GTK_CONTAINER(comp_acro_frame),entry_comp_acro);

	
	/*INPUTS*/
	gtk_fixed_put(GTK_FIXED(fixed_p),identifiant_frame,700,300);
	gtk_widget_set_size_request(identifiant_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed_p),carburant_frame,700,375);
	gtk_widget_set_size_request(carburant_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed_p),consommation_frame,700,450);
	gtk_widget_set_size_request(consommation_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed_p),heure_frame,700,525);
	gtk_widget_set_size_request(heure_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed_p),comp_nom_frame,700,600);
	gtk_widget_set_size_request(comp_nom_frame,500,75);
	gtk_fixed_put(GTK_FIXED(fixed_p),comp_acro_frame,700,675);
	gtk_widget_set_size_request(comp_acro_frame,500,75);


	/*BUTTONS*/
	gtk_fixed_put(GTK_FIXED(fixed_p),button,1000,900);
	gtk_widget_set_size_request(button,200,75);
	gtk_fixed_put(GTK_FIXED(fixed_p),button2,700,900);
	gtk_widget_set_size_request(button2,200,75);

	char *str=g_strdup_printf("<span  font=\"25\" color=\"#181741\"> <b> MODIFICATION DU REPERTOIRE AVION </b></span>");
	
	gtk_label_set_markup(GTK_LABEL(title),str);

	gtk_fixed_put(GTK_FIXED(fixed_p),title,630,50);
	gtk_widget_set_size_request(title,200,200);

	Cellule *av=rech_ident(nom_avion);
	char ch[100];
	gtk_entry_set_text(GTK_ENTRY(entry_ident),av->cle.Identifiant);
	snprintf(ch,sizeof(ch),"%d",av->cle.carburant);
	gtk_entry_set_text(GTK_ENTRY(entry_carb),ch);
	snprintf(ch,sizeof(ch),"%d",av->cle.consommation);
	gtk_entry_set_text(GTK_ENTRY(entry_consom),ch);
	gtk_entry_set_text(GTK_ENTRY(entry_heure),av->cle.heure_decollage);
	gtk_entry_set_text(GTK_ENTRY(entry_comp_nom),av->cle.compagnie.nom);
	gtk_entry_set_text(GTK_ENTRY(entry_comp_acro),av->cle.compagnie.acronyme);


	g_signal_connect(button,"clicked",G_CALLBACK(modifie),window);
	g_signal_connect(button2,"clicked",G_CALLBACK(destroy_wind),window);
}

void mod_menu_pop(GtkWidget *window)
{
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),fixed);

	frame_pop=gtk_frame_new("L'Identifiant de l'avion : ");
	button_pop=gtk_button_new_with_label("continuer");
	entry_pop=gtk_search_entry_new();


	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_widget_set_name(button_pop,"continue_button");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(button_pop);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_widget_set_name (window,"main_win");
	context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_widget_set_name (entry_pop,"main-entry");
	context = gtk_widget_get_style_context(entry_pop);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_entry_set_max_length(GTK_ENTRY(entry_pop),6);
	gtk_container_add(GTK_CONTAINER(frame_pop),entry_pop);

	gtk_fixed_put(GTK_FIXED(fixed),frame_pop,700,300);
	gtk_widget_set_size_request(frame_pop,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),button_pop,700,400);
	gtk_widget_set_size_request(button_pop,500,75);
	
	g_signal_connect(G_OBJECT(button_pop),"clicked",G_CALLBACK(Display_mod_main),window);
	
}

void affichage_main(GtkWidget *window)
{
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
	view = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_widget_set_name(window,"win");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	provider = gtk_css_provider_new ();
	gtk_widget_set_name(view,"view");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
    context = gtk_widget_get_style_context(view);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
  	
  	gtk_text_buffer_create_tag (buffer, "heading","weight", PANGO_WEIGHT_BOLD,"size", 12 * PANGO_SCALE,NULL);
  	gtk_text_buffer_create_tag (buffer, "italic","style", PANGO_STYLE_ITALIC, NULL);
  	gtk_text_buffer_create_tag (buffer, "bold","weight", PANGO_WEIGHT_BOLD, NULL);
  	gtk_text_buffer_create_tag (buffer, "big","size", 15 * PANGO_SCALE, NULL);
  	gtk_text_buffer_create_tag (buffer, "xx-small","scale", PANGO_SCALE_XX_SMALL, NULL);
  	gtk_text_buffer_create_tag (buffer, "xx-large","scale", PANGO_SCALE_XX_LARGE, NULL);
  	gtk_text_buffer_create_tag (buffer, "monospace","family", "monospace", NULL);
 		gtk_text_buffer_create_tag (buffer, "red_foreground", "foreground", "#1D1D2C", NULL);
  	gtk_text_buffer_create_tag (buffer, "red_background","background", "blue", NULL);
  	gtk_text_buffer_create_tag (buffer, "big_gap_before_line","pixels_above_lines", 30, NULL);
  	gtk_text_buffer_create_tag (buffer, "big_gap_after_line","pixels_below_lines", 30, NULL);
  	gtk_text_buffer_create_tag (buffer, "double_spaced_line", "pixels_inside_wrap", 10, NULL);
  	gtk_text_buffer_create_tag (buffer, "not_editable","editable", FALSE, NULL);
  	gtk_text_buffer_create_tag (buffer, "word_wrap","wrap_mode", GTK_WRAP_WORD, NULL);
  	gtk_text_buffer_create_tag (buffer, "char_wrap","wrap_mode", GTK_WRAP_CHAR, NULL);
  	gtk_text_buffer_create_tag (buffer, "no_wrap","wrap_mode", GTK_WRAP_NONE, NULL);
  	gtk_text_buffer_create_tag (buffer, "center","justification", GTK_JUSTIFY_CENTER, NULL);
  	gtk_text_buffer_create_tag (buffer, "right_justify","justification", GTK_JUSTIFY_RIGHT, NULL);
  	gtk_text_buffer_create_tag (buffer, "wide_margins","left_margin", 50, "right_margin", 50,NULL);
  	gtk_text_buffer_create_tag (buffer, "strikethrough","strikethrough", TRUE, NULL);
  	gtk_text_buffer_create_tag (buffer, "underline","underline", PANGO_UNDERLINE_SINGLE, NULL);
  	gtk_text_buffer_create_tag (buffer, "double_underline","underline", PANGO_UNDERLINE_DOUBLE, NULL);
  	gtk_text_buffer_create_tag (buffer, "superscript","rise", 10 * PANGO_SCALE,"size", 8 * PANGO_SCALE,NULL);
  	gtk_text_buffer_create_tag (buffer, "subscript","rise", -10 * PANGO_SCALE,"size", 8 * PANGO_SCALE,NULL);
  	gtk_text_buffer_create_tag (buffer, "rtl_quote","wrap_mode", GTK_WRAP_WORD,"direction", GTK_TEXT_DIR_RTL,"indent", 30,"left_margin", 20,"right_margin", 20,NULL);



  gtk_text_buffer_get_iter_at_offset(buffer, &iter_title, 0);


    
    if(!Vide())
    {
      char aa[1000];
      char bb[1000];
      int i=1;
      int max=max_length_name();
      int cc=0;
      int tt=0;
      int str;
      int int_m=max_length_car();
      Cellule *aux=L.premier;
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," # |     Identifiant\t      Heure de decollage           Acronyme du compagnie\t          Nom du compagnie", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int j=0;j<max-11;j++)
      {
      		cc++;
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," ", -1,"red_foreground" ,"heading","monospace",  NULL);
      }
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"                  Carburant", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int j=0;j<int_m-5;j++)
      {
      		tt++;
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," ", -1,"red_foreground" ,"heading","monospace",  NULL);
      }
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"               Consommation \n", -1,"red_foreground" ,"heading","monospace",  NULL);

      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"______________________________________________________________________________________________________________________________________________________________________________", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int o=0;o<cc;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);

      for(int o=0;o<tt;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"\n", -1,"red_foreground" ,"heading","monospace",  NULL);
      
      while(aux)
      {

        snprintf(aa,sizeof(aa)," %d |\t  %s   \t|\t    %s     \t|\t      %s       \t|\t\t%s",i,aux->cle.Identifiant,aux->cle.heure_decollage,aux->cle.compagnie.acronyme,aux->cle.compagnie.nom);
          for(int j=0;j<max-strlen(aux->cle.compagnie.nom);j++)
            strcat(aa," ");

        snprintf(bb,sizeof(bb),"\t\t|         %d",aux->cle.carburant);
        strcat(aa,bb);

        for(int j=0;j<int_m-length_car(aux->cle.carburant);j++)
          strcat(aa," ");
        

        snprintf(bb,sizeof(bb),"\t        |         %d\t \n",aux->cle.consommation);
        strcat(aa,bb);
        gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,aa, -1,"red_foreground" ,"heading","monospace",  NULL);
        gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"______________________________________________________________________________________________________________________________________________________________________________", -1,"red_foreground" ,"heading","monospace",  NULL);
        for(int o=0;o<cc;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);
      	for(int o=0;o<tt;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);

      	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"\n", -1,"red_foreground" ,"heading","monospace",  NULL);
        aux=aux->suivant;
        i++;
      }
      
      
      
    }
    	    
    GtkWidget *button=gtk_button_new_with_label("Retour");
    gtk_fixed_put(GTK_FIXED(fixed),button,0,0);
    gtk_widget_set_size_request(button,20,10);
    g_signal_connect(button,"clicked",G_CALLBACK(retour),window);

   
    provider = gtk_css_provider_new ();
	gtk_widget_set_name(button,"ret_button");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
    context = gtk_widget_get_style_context(button);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

  	

  gtk_text_view_set_editable(GTK_TEXT_VIEW(view),FALSE) ;

  gtk_fixed_put(GTK_FIXED(fixed),view,60,60);
  gtk_widget_set_size_request(view,1700,1200);

}

void rech_id_pop(GtkWidget *window)
{
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),fixed);

	frame_pop=gtk_frame_new("L'Identifiant de l'avion : ");


	


	button_pop=gtk_button_new_with_label("CONTINUER");
	gtk_widget_set_name(button_pop,"continue_button");

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(button_pop);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);


	gtk_widget_set_name (window,"main_win");
	context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	entry_pop=gtk_search_entry_new();
	gtk_widget_set_name (entry_pop,"main-entry");
	context = gtk_widget_get_style_context(entry_pop);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_entry_set_max_length(GTK_ENTRY(entry_pop),6);
	gtk_container_add(GTK_CONTAINER(frame_pop),entry_pop);

	gtk_fixed_put(GTK_FIXED(fixed),frame_pop,700,300);
	gtk_widget_set_size_request(frame_pop,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),button_pop,700,400);
	gtk_widget_set_size_request(button_pop,500,75);
	
	g_signal_connect(G_OBJECT(button_pop),"clicked",G_CALLBACK(Display_rech_id_main),window);
}
void rech_com_pop(GtkWidget *window)
{
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),fixed);

	frame_pop=gtk_frame_new("Nom du compagnie : ");
	button_pop=gtk_button_new_with_label("continuer");
	entry_pop=gtk_search_entry_new();

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_widget_set_name(button_pop,"continue_button");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(button_pop);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_widget_set_name (window,"main_win");
	context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_widget_set_name (entry_pop,"main-entry");
	context = gtk_widget_get_style_context(entry_pop);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_container_add(GTK_CONTAINER(frame_pop),entry_pop);

	gtk_fixed_put(GTK_FIXED(fixed),frame_pop,700,300);
	gtk_widget_set_size_request(frame_pop,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),button_pop,700,400);
	gtk_widget_set_size_request(button_pop,500,75);
	
	g_signal_connect(G_OBJECT(button_pop),"clicked",G_CALLBACK(Display_rech_com_main),window);
}
void rech_heur_pop(GtkWidget *window)
{
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window),fixed);

	frame_pop=gtk_frame_new("L'heure de decollage(HH:MM:SS) : ");
	button_pop=gtk_button_new_with_label("continuer");
	entry_pop=gtk_search_entry_new();

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_widget_set_name(button_pop,"continue_button");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(button_pop);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_widget_set_name (window,"main_win");
	context = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_widget_set_name (entry_pop,"main-entry");
	context = gtk_widget_get_style_context(entry_pop);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_entry_set_max_length(GTK_ENTRY(entry_pop),8);
	gtk_container_add(GTK_CONTAINER(frame_pop),entry_pop);

	gtk_fixed_put(GTK_FIXED(fixed),frame_pop,700,300);
	gtk_widget_set_size_request(frame_pop,500,75);
	gtk_fixed_put(GTK_FIXED(fixed),button_pop,700,400);
	gtk_widget_set_size_request(button_pop,500,75);
	
	g_signal_connect(G_OBJECT(button_pop),"clicked",G_CALLBACK(Display_rech_heur_main),window);
}
void rech_id_main(GtkWidget *window)
{
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
	view = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter_title, 0);


	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_widget_set_name(window,"win");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	provider = gtk_css_provider_new ();
	gtk_widget_set_name(view,"view");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
    context = gtk_widget_get_style_context(view);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);


	char aa[1000];
	char bb[1000];
	int i;
	int max=max_length_name_id(nom_avion);
	int int_m=max_length_car_id(nom_avion);

	gtk_text_buffer_create_tag (buffer, "heading","weight", PANGO_WEIGHT_BOLD,"size", 12 * PANGO_SCALE,NULL);
	gtk_text_buffer_create_tag (buffer, "monospace","family", "monospace", NULL);
 	gtk_text_buffer_create_tag (buffer, "red_foreground", "foreground", "#1D1D2C", NULL);
	
	Cellule *aux=rech_id(nom_avion,&i);
	int cc=0,tt=0;
	

		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," #  |     Identifiant\t      Heure de decollage           Acronyme du compagnie\t          Nom du compagnie", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int j=0;j<max-11;j++)
      {
      		cc++;
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," ", -1,"red_foreground" ,"heading","monospace",  NULL);
      }
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"                  Carburant", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int j=0;j<int_m-5;j++)
      {
      		tt++;
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," ", -1,"red_foreground" ,"heading","monospace",  NULL);
      }
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"               Consommation \n", -1,"red_foreground" ,"heading","monospace",  NULL);

      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"______________________________________________________________________________________________________________________________________________________________________________", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int o=0;o<cc;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);

      for(int o=0;o<tt;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"\n", -1,"red_foreground" ,"heading","monospace",  NULL);


    snprintf(aa,sizeof(aa)," %d  |\t  %s   \t|\t    %s     \t|\t      %s       \t|\t\t%s",i,aux->cle.Identifiant,aux->cle.heure_decollage,aux->cle.compagnie.acronyme,aux->cle.compagnie.nom);
    
    for(int j=0;j<max-strlen(aux->cle.compagnie.nom);j++)
        strcat(aa," ");
    
    snprintf(bb,sizeof(bb),"\t\t|         %d",aux->cle.carburant);
    strcat(aa,bb);

    for(int j=0;j<int_m-length_car(aux->cle.carburant);j++)
       	strcat(aa," ");
        

    snprintf(bb,sizeof(bb),"\t        |         %d\t \n",aux->cle.consommation);
    strcat(aa,bb);



    

  	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,aa, -1,"red_foreground" ,"heading","monospace",  NULL);

  	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"______________________________________________________________________________________________________________________________________________________________________________", -1,"red_foreground" ,"heading","monospace",  NULL);
        for(int o=0;o<cc;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);
      	for(int o=0;o<tt;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);

      	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"\n", -1,"red_foreground" ,"heading","monospace",  NULL);

  	GtkWidget *button=gtk_button_new_with_label("Retour");

  	
  	provider = gtk_css_provider_new ();
	gtk_widget_set_name(button,"ret_button");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
    context = gtk_widget_get_style_context(button);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

    

    gtk_fixed_put(GTK_FIXED(fixed),button,0,0);
    gtk_widget_set_size_request(button,20,10);
    g_signal_connect(button,"clicked",G_CALLBACK(retour),window);

  	gtk_text_view_set_editable(GTK_TEXT_VIEW(view),FALSE) ;
  	gtk_fixed_put(GTK_FIXED(fixed),view,60,60);
  	gtk_widget_set_size_request(view,1400,1000);


}

void rech_com_main(GtkWidget *window)
{




	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
	view = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter_title, 0);
	char aa[1000];
	char bb[1000];
	int max=strlen(comp_nom);
	int int_m=max_length_car_nom(comp_nom);


	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_widget_set_name(window,"win");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	provider = gtk_css_provider_new ();
	gtk_widget_set_name(view,"view");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
    context = gtk_widget_get_style_context(view);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);


	gtk_text_buffer_create_tag (buffer, "heading","weight", PANGO_WEIGHT_BOLD,"size", 12 * PANGO_SCALE,NULL);
	gtk_text_buffer_create_tag (buffer, "monospace","family", "monospace", NULL);
 	gtk_text_buffer_create_tag (buffer, "red_foreground", "foreground", "#1D1D2C", NULL);
	
	Cellule *aux=L.premier;
	int i=1;
	int cc=0,tt=0;



	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," # |     Identifiant\t      Heure de decollage           Acronyme du compagnie\t          Nom du compagnie", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int j=0;j<max-11;j++)
      {
      		cc++;
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," ", -1,"red_foreground" ,"heading","monospace",  NULL);
      }
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"                 Carburant", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int j=0;j<int_m-2;j++)
      {
      		tt++;
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," ", -1,"red_foreground" ,"heading","monospace",  NULL);
      }
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"              Consommation \n", -1,"red_foreground" ,"heading","monospace",  NULL);

      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"______________________________________________________________________________________________________________________________________________________________________________", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int o=0;o<cc;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);

      for(int o=0;o<tt;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"\n", -1,"red_foreground" ,"heading","monospace",  NULL);
	while(aux)
	{
		if(strcmp(aux->cle.compagnie.nom,comp_nom)==0)
		{
			
    		snprintf(aa,sizeof(bb)," %d |\t  %s   \t|\t    %s     \t|\t      %s       \t|\t\t%s",i,aux->cle.Identifiant,aux->cle.heure_decollage,aux->cle.compagnie.acronyme,aux->cle.compagnie.nom);
    
    		for(int j=0;j<max-strlen(aux->cle.compagnie.nom);j++)
        		strcat(aa," ");
    		
    		snprintf(bb,sizeof(bb),"\t\t|         %d",aux->cle.carburant);
    		strcat(aa,bb);

    		for(int j=0;j<int_m-length_car(aux->cle.carburant);j++)
       			strcat(aa," ");
        

    		snprintf(bb,sizeof(bb),"\t        |         %d\t \n",aux->cle.consommation);
    		strcat(aa,bb);
			gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,aa, -1,"red_foreground" ,"heading","monospace",  NULL);
			gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"______________________________________________________________________________________________________________________________________________________________________________", -1,"red_foreground" ,"heading","monospace",  NULL);
        for(int o=0;o<cc;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);
      	for(int o=0;o<tt;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);

      	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"\n", -1,"red_foreground" ,"heading","monospace",  NULL);		
      }
		aux=aux->suivant;
		i++;
	}
    


    

  	

  	GtkWidget *button=gtk_button_new_with_label("Retour");
    gtk_fixed_put(GTK_FIXED(fixed),button,0,0);
    gtk_widget_set_size_request(button,20,10);
    g_signal_connect(button,"clicked",G_CALLBACK(retour),window);


    provider = gtk_css_provider_new ();
	gtk_widget_set_name(button,"ret_button");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
    context = gtk_widget_get_style_context(button);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);


  	gtk_text_view_set_editable(GTK_TEXT_VIEW(view),FALSE) ;
  	gtk_fixed_put(GTK_FIXED(fixed),view,60,60);
  	gtk_widget_set_size_request(view,1400,1000);


}
void rech_heur_main(GtkWidget *window)
{
	fixed=gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
	view = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter_title, 0);
	char aa[1000];
	char bb[1000];
	int max=max_length_name_heur(heur_d);
	int int_m=max_length_car_heur(heur_d);


	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_widget_set_name(window,"win");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
	GtkStyleContext *context;
    context = gtk_widget_get_style_context(window);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	provider = gtk_css_provider_new ();
	gtk_widget_set_name(view,"view");
	gtk_css_provider_load_from_path (provider, "main.css", NULL);
    context = gtk_widget_get_style_context(view);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	gtk_text_buffer_create_tag (buffer, "heading","weight", PANGO_WEIGHT_BOLD,"size", 12 * PANGO_SCALE,NULL);
	gtk_text_buffer_create_tag (buffer, "monospace","family", "monospace", NULL);
 	gtk_text_buffer_create_tag (buffer, "red_foreground", "foreground", "#1D1D2C", NULL);


	Cellule *aux=L.premier;
	int i=1;
	

	int cc=0;
      int tt=0;
gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," # |     Identifiant\t      Heure de decollage           Acronyme du compagnie\t          Nom du compagnie", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int j=0;j<max-11;j++)
      {
      		cc++;
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," ", -1,"red_foreground" ,"heading","monospace",  NULL);
      }
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"              Carburant", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int j=0;j<int_m-1;j++)
      {
      		tt++;
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title," ", -1,"red_foreground" ,"heading","monospace",  NULL);
      }
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"               Consommation \n", -1,"red_foreground" ,"heading","monospace",  NULL);

      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"______________________________________________________________________________________________________________________________________________________________________________", -1,"red_foreground" ,"heading","monospace",  NULL);
      for(int o=0;o<cc;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);

      for(int o=0;o<tt;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);
      gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"\n", -1,"red_foreground" ,"heading","monospace",  NULL);


		while(aux)
	{
		if(strcmp(aux->cle.heure_decollage,heur_d)==0)
		{
			
    		snprintf(aa,sizeof(bb)," %d |\t  %s   \t|\t    %s     \t|\t      %s       \t|\t\t%s",i,aux->cle.Identifiant,aux->cle.heure_decollage,aux->cle.compagnie.acronyme,aux->cle.compagnie.nom);
    
    		for(int j=0;j<max-strlen(aux->cle.compagnie.nom);j++)
        		strcat(aa," ");
    		
    		snprintf(bb,sizeof(bb),"\t\t|         %d",aux->cle.carburant);
    		strcat(aa,bb);

    		for(int j=0;j<int_m-length_car(aux->cle.carburant);j++)
       			strcat(aa," ");
        

    		snprintf(bb,sizeof(bb),"\t        |         %d\t \n",aux->cle.consommation);
    		strcat(aa,bb);
			gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,aa, -1,"red_foreground" ,"heading","monospace",  NULL);

			gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"______________________________________________________________________________________________________________________________________________________________________________", -1,"red_foreground" ,"heading","monospace",  NULL);
        for(int o=0;o<cc;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);
      	for(int o=0;o<tt;o++)
      		gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"_", -1,"red_foreground" ,"heading","monospace",  NULL);

      	gtk_text_buffer_insert_with_tags_by_name(buffer, &iter_title,"\n", -1,"red_foreground" ,"heading","monospace",  NULL);



		}
		aux=aux->suivant;
		i++;
	}


    

  	GtkWidget *button=gtk_button_new_with_label("Retour");
    gtk_fixed_put(GTK_FIXED(fixed),button,0,0);
    gtk_widget_set_size_request(button,20,10);

    provider = gtk_css_provider_new ();
	gtk_widget_set_name(button,"ret_button");
	gtk_css_provider_load_from_path (provider, "main.css", NULL); 
    context = gtk_widget_get_style_context(button);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);



    g_signal_connect(button,"clicked",G_CALLBACK(retour),window);

  	gtk_text_view_set_editable(GTK_TEXT_VIEW(view),FALSE) ;
  	gtk_fixed_put(GTK_FIXED(fixed),view,60,60);
  	gtk_widget_set_size_request(view,1400,1000);


}
