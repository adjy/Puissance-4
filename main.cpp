#include <iostream>
#include <ctime>
#include <unistd.h>
using namespace std;

const int LIG = 6; // Nbres de lignes
const int COL = 7; // Nbres de colonne

// Mes Structures
struct Puissance4{
	int Grille[LIG][COL];
	int NbreJeutonAligne[2] ;
};

struct Joueur{
	string nom;
	int numero;
	string type,pion;
};

struct ListeJoueur{
	Joueur Joueurs[2];
};

//######################Fonctions######################
Puissance4 initJeu(Puissance4 Jeu);
bool colonnePlein(Puissance4 Jeu, int colonne);
int alea(int a, int b);
int saisirColonne(string type_Joueur);
int choixColonne(Puissance4 Jeu, string type_Joueur, int numeroJoueur);
int ligneNouveauJeton(Puissance4 Jeu, int colonne);
int pionsHor(Puissance4 Jeu, int ligne, int colonne, int numeroJoueur);
int pionsVert(Puissance4 Jeu, int ligne, int colonne, int numeroJoueur);
int pionsDiagGD(Puissance4 Jeu, int ligne, int colonne, int numeroJoueur);
int pionsDiagDG(Puissance4 Jeu, int ligne, int colonne, int numeroJoueur);
void MAJ_jeu(Puissance4 *Jeu, int ligne, int colonne, int numeroJoueur);
void Jouer(Puissance4 *Jeu, int numeroJoueur, string type_Joueur);
void afficher(Puissance4 Jeu);
int JouerOrdiAI(Puissance4 Jeu,int numeroJoueur);
int BloqOrdiAI(Puissance4 Jeu,int numeroJoueur);
int JouerAI(Puissance4 Jeu,int numeroJoueur);
void tirageJoueurAleatoire(ListeJoueur *J, string Joueur1, string Joueur2);



int main(){
	srand(time(NULL));
	Puissance4 Jeu;
	string Joueur1, Joueur2;
	ListeJoueur J;
	bool partie = true;
	int pleine = 0;


	

	Jeu = initJeu(Jeu); // initialise le plateau a -1

	//Force l'entrer de ordi ou humain
	
	while(Joueur1 != "ORDI" && Joueur1 !="HUMAIN"){
	 	cout<<"Type du joueur 1 <ORDI/HUMAIN> ? ";
		cin>>Joueur1;
	}

	if(Joueur1 !="ORDI"){
		cout<<"Votre nom? ";
		cin>>J.Joueurs[0].nom;
	}
	else{
		J.Joueurs[0].nom = "ORDI";
	}
	
	cout<<endl;
	while(Joueur2 != "ORDI" && Joueur2 !="HUMAIN"){
	 	cout<<"Type du joueur 2 <ORDI/HUMAIN> ? ";
		cin>>Joueur2;
	}

	if(Joueur2 !="ORDI"){
		cout<<"Votre nom? ";
		cin>>J.Joueurs[1].nom;
	}
	else{
		J.Joueurs[1].nom = "ORDI";
	}



	afficher(Jeu); // Affiche le plateau

	
 tirageJoueurAleatoire(&J, Joueur1,  Joueur2);
	
	while(partie){
		int p = 0;
		while(p<2){
			
			Jouer( &Jeu,  J.Joueurs[p].numero, J.Joueurs[p].type); // Jouer par un joueur
			afficher(Jeu); // Affiche le plateau

		 	usleep(310000); // Faire une pause
			

			if( (Jeu.NbreJeutonAligne[p]==4) || (Jeu.NbreJeutonAligne[p]>4) ){
				cout<<"Le gagnant est le joueur: "<<J.Joueurs[p].numero<<endl;
				p = 10000;
				partie = false;
				break;
			}

			pleine = 0;
			for(int k =0; k<COL; k++){ // verification colonne pleine
				if(colonnePlein( Jeu, k) == true){ // verifie si une colonne est pleine
					pleine++;
				}
				if(pleine>=COL){ // Verifie si toutes les colonnes sont pleines
					cout<<"Partie Nul"<<endl;
					partie = false;
					break;
				}
			}
				
			if(partie == true ){
				p++;
			}
			if(partie == false){
				break;
			}
		}
	}

		
	} 
	


/*######################### Mes fonctions #########################*/
int alea(int a, int b){
	/*Fonction qui retourne une valeur aleatoire entre 2 nombres
	Parametre attendu : a, b : entier
	Valeur de retour rand()% (b-a+1)+a : entier*/
	return  rand()% (b-a+1)+a ;
}

Puissance4 initJeu(Puissance4 Jeu){
	/*Fonction qui renvoie le plateau de jeu initialisé avec les éléments de la grille à -1 et le tableau max à 0.
	Parametre attendu : Puissance4 Jeu;
	Valeur de retour: Puissance4 Jeu */ 
	 
	for(int i=0; i<LIG; i++){
		for(int j=0; j<COL;j++){
			Jeu.Grille[i][j]=-1;
		}
	}
	for(int i = 0; i< 2; i++){
		Jeu.NbreJeutonAligne[i]=0;
	}
	return Jeu;
}

bool colonnePlein(Puissance4 Jeu, int colonne){ 
	/*Fonction qui retourne vrai si la colonne est pleine et faux sinon.
	Parametre attendu : Puissance4 Jeu, int colonne
	Valeur de retour: true, false*/
	if(colonne <COL){
		for(int i=0; i<LIG;i++){
			if(Jeu.Grille[i][colonne] == -1){ // Verifie si la colonne un -1 comme valeur, alors elle n'est pas pleine
				return false;
				
			}
		}return true;	
	}
	else{
		return false;
	}
}


int saisirColonne(string type_Joueur){
	/*Fonction qui retourne la colonne choisie par le joueur
	Parametre attendu : string type_Joueur
	Valeur de retour: col: int */

	int col;
	if(type_Joueur == "HUMAIN"){ // demande la colonne a l'utilisateur
		cout<<"Dans quelle colonne voulez-vous jouer ? <0-"<<COL-1<<"> ";
		cin>>col;
	}
	else{
		col = alea(0, COL-1); // envoie un nombre entre 0 et 6 si c un ordi
	}
	return col;
}

int choixColonne(Puissance4 Jeu, string type_Joueur, int numeroJoueur){
	/*Fonction qui retourne la colonne choisie par le joueur qui recommencera jusqu’à ce que la colonne existe
	Parametre attendu:  Puissance4 Jeu, string type_Joueur
	Valeur de retour col: int*/
	int col; 

	if(type_Joueur == "HUMAIN"){ // Colonne entree par l'utilisateur
		col = saisirColonne("HUMAIN");

		while((col<0) || (col>6) || colonnePlein( Jeu, col)){ // Rcommence la saisie tant que la colonne est pleinne
			//cout<<"La colonne est pleinne! "<<endl;
			cout<<"Reesayer"<<endl;
			col = saisirColonne("HUMAIN"); 
		
			
		}
	}

	else{ //Colonne choisie au hasard par l'ordi
		// col = saisirColonne("ORDI");
		col= JouerAI(Jeu, numeroJoueur);

		while( colonnePlein( Jeu, col)){ // Rcommence la saisie tant que la colonne est pleinne
			col = saisirColonne("ORDI");
			// col = JouerAI(Jeu, numeroJoueur);
		}
	}
	return col;
}

int ligneNouveauJeton(Puissance4 Jeu, int colonne){
	/*Fonction qui retourne le numéro de la ligne dans laquelle le jeton va tomber.
	Parametre attendu: Puissance4 Jeu, int colonne
	Valeur de retour i : int*/

		for(int i=0; i<LIG;i++){
			if(Jeu.Grille[i][colonne] ==-1){ // Regarde si la ligene est vide (=-1)
				return i;
			
		}
	}
}

int pionsHor(Puissance4 Jeu, int ligne, int colonne, int numeroJoueur){
	/*Fonction qui à partir de cette position compte le nombre de pions lui appartenant consécutifs sur la ligne .
	parametre attendu: Puissance4 Jeu, int ligne, int colonne, int numeroJoueur
	Valeur de retourn: som: entier*/
	
	int somme = 0;
	if (Jeu.Grille[ligne][colonne]==numeroJoueur){ // Si le pion existe c'est a dire elle vaut la valeur d'un pion

		for(int j = colonne; j<COL; j++){
			if(Jeu.Grille[ligne][j] ==numeroJoueur){ 
				// Si la case suivante ne quitte pas la grille
					somme++;
				
			}
			else{
				break; // Si la case suivante quitte la grille, elle sort de la boucle
			}
		}
		somme--;
	}

	if (Jeu.Grille[ligne][colonne]==numeroJoueur){ // Si le pion existe c'est a dire elle vaut la valeur d'un pion

		for(int j=colonne; j>=0; j--){
			if(Jeu.Grille[ligne][j]==numeroJoueur){ 
			 
					somme++;	
			}
			else {
				break; // Si la case precedente quitte la grille, elle sort de la boucle
			}
		}
		somme--;
	}

	if (Jeu.Grille[ligne][colonne]==numeroJoueur){ // Si le pion existe c'est a dire elle vaut la valeur d'un pion

		somme++; // Ajoute 1 pour compter le pion principal
	}
	return somme;
}

int pionsVert(Puissance4 Jeu, int ligne, int colonne, int numeroJoueur){
	/*Fonction qui à partir de cette position compte le nombre de pions lui appartenant consécutifs sur la colonne.
	parametre attendu: Puissance4 Jeu, int ligne, int colonne, int numeroJoueur
	Valeur de retourn: som: entier*/
	int somme=0;

	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ // Si le pion existe c'est a dire elle vaut la valeur d'un pion
		for(int i = ligne; i<LIG; i++){ 
			if(Jeu.Grille[i][colonne]==numeroJoueur){  // Si la case suivante est egal au pion
				somme++;
			}
			else{
				break; // Si la case suivante quitte la grille, elle sort de la boucle
			}
		}
		somme--;
	}
	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ // Si le pion existe c'est a dire elle vaut la valeur d'un pion
		
		for(int i = ligne; i>=0; i--){
			if(Jeu.Grille[i][colonne]==numeroJoueur){  // Si la case precedente est egal au pion
					somme++;
				}
			else{
				break; // Si la case precedente quitte la grille, elle sort de la boucle
			}
		}
		somme--;
	}
	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ 

		somme++;
	}
	return somme;
}



int pionsDiagGD(Puissance4 Jeu, int ligne, int colonne, int numeroJoueur){
	/*Fonction qui à partir de cette position compte le nombre de pions lui appartenant consécutifs sur la  diagonale allant de haut-gauche à bas-droit.
	parametre attendu: Puissance4 Jeu, int ligne, int colonne, int numeroJoueur
	Valeur de retourn: som: entier*/
	int somme=0;	
	int i  = ligne; 
	int j = colonne;

	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ // Verifie si le pion existe
		while(i<LIG && j <COL){
			if(Jeu.Grille[i][j]==numeroJoueur){ 
				somme++;
			}
			else {
				break;
			}
			i++;
			j++;
		}
		somme--;
	}


	i = ligne;  
	j = colonne;
	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ // Verifie si le pion existe

		while(i>=0 && j>=0){
			if(Jeu.Grille[i][j] ==numeroJoueur){
				somme++;
			}
			else{
				break;
			}
			i--;
			j--;
		}
		somme--;
		}

	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ // Verifie si le pion existe
		somme++;
	}
		
	return somme ;

}

int pionsDiagDG(Puissance4 Jeu, int ligne, int colonne, int numeroJoueur){
	/*Fonction qui à partir de cette position compte le nombre de pions lui appartenant consécutifs sur la Diagonale de haut-droit à bas-gauche.
	parametre attendu: Puissance4 Jeu, int ligne, int colonne, int numeroJoueur
	Valeur de retourn: som: entier*/
	int somme=0;
	int i = ligne;
	int j = colonne;

	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ // Verifie si le pion existe

		while(i>=0 && j <COL){
			if(Jeu.Grille[i][j]==numeroJoueur){ 
				somme++;
			}
			else{
				break;
			}
			i--;
			j++;
		}
		somme--;
	}

	
	i = ligne;
	j = colonne;

	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ // Verifie si le pion existe

		while(i<LIG && j>=0){

			if(Jeu.Grille[i][j] == numeroJoueur){
				somme++;
			}

			else{
				break;
			}
			i++;
			j--;
		}
		somme--;
	}

	if(Jeu.Grille[ligne][colonne]==numeroJoueur){ // Verifie si le pion existe
		somme++;	
		}
	return somme;

}

void MAJ_jeu(Puissance4 *Jeu, int ligne, int colonne, int numeroJoueur){
	/*Fonction qui met à jour le plateau (grille et max)
	parametre attendu: Puissance4 Jeu, int ligne, int colonne, int numeroJoueur
	Valeur de retour: pas de valeur*/
	
	
	Jeu->NbreJeutonAligne[numeroJoueur-1] = 0;
	if (colonnePlein( *Jeu,  colonne)==false) {
		Jeu->Grille[ligne][colonne] =numeroJoueur ; // Met ajour la grille

		int Hor = pionsHor(*Jeu,ligne, colonne, numeroJoueur); // recupere le nbre pions alignes Horizontale
		int Vert = pionsVert(*Jeu,ligne, colonne, numeroJoueur); // recupere le nbre pions alignes Verticale
		int DiaDG = pionsDiagDG(*Jeu,ligne, colonne, numeroJoueur); // recupere le nbre pions alignes  haut-droit à bas-gauche.
		int DiaGD = pionsDiagGD(*Jeu,ligne, colonne, numeroJoueur); // recupere le nbre pions alignes  haut-gauche à bas-droit.
		
	
		int max = 0; // Recupere le nbres de pions alignes du pion 

		if(Hor > max){ 
			max = Hor; 
		}

		if(Vert > max){
			max = Vert;
		}

		if(DiaDG > max){
			max = DiaDG;
		}
		if(DiaGD > max){
			max = DiaGD;
		}

		Jeu->NbreJeutonAligne[numeroJoueur-1] = max; // Met a jour le nbre de pion alignes	
	 	cout<<"Ligne: "<<ligne<<" Col :"<<colonne<<endl;
	 // cout<<"Hor: " <<Hor<<endl;
	 // cout<<"Vert: " <<Vert<<endl;
	 // cout<<"DiaDG: " <<DiaDG<<endl;
	 // cout<<"DiaGD: " <<DiaGD<<endl;

	}
	
}


void Jouer(Puissance4 *Jeu, int numeroJoueur, string type_Joueur){
	/*Fonction qui fait jouer un des joueurs
	Parametre attendu: Puissance4 *Jeu, int numeroJoueur, string type_Joueur
	Valeur de retour: pas de valeur*/
	int colonne =choixColonne( *Jeu,  type_Joueur,  numeroJoueur); // recupere la valeur de la colonne
	int ligne = ligneNouveauJeton( *Jeu, colonne ); // Recupere la valeur de la ligne
	MAJ_jeu( Jeu,  ligne,  colonne, numeroJoueur); // Met a jour la grille
	// cout<<"\nLe joueur "<<numeroJoueur<<" a jouer dans la colonne "<<colonne<<endl;
	
}

void afficher(Puissance4 Jeu){
	/*fonction afficher qui prend en paramètre le jeu, qui affiche la grille de jeu en mettant des formes différentes
	parametre attendu: Puissance4 Jeu
	Valeur de retour: pas de valeur*/
	for(int i = LIG-1; i>=0; i--){
		for(int j=0; j<COL; j++){
			if(Jeu.Grille[i][j] == -1 ){ // Si la case est vide(=-1) affiche _
				cout<<"."<<" ";
			}
			if(Jeu.Grille[i][j] == 1){ // Si la valeur est 1, affiche 0
				cout<<"0"<<" ";
			}
			if(Jeu.Grille[i][j] == 2){ // si la valeur esr 2, affiche X
				cout<<"X"<<" ";
			}	
		}
		cout<<endl; // Saut de ligne		
	}cout<<endl;
		
	for(int i=0; i<COL; i++){ // Affiche les numeros de colonne
			cout<<i<<" ";
		}
	cout<<endl;
	for(int i = 0; i<2; i++){
	// cout<<"Le joueur "<<i+1<<" a alignés "<<Jeu.NbreJeutonAligne[i]<<" pions."<<endl;
	}
	cout<<endl;
	
}
	

int JouerOrdiAI(Puissance4 Jeu,int numeroJoueur){
	/*Fonctions qui fait jouer l'ordinateur  s’il y a pas une ligne de 3 pions à compléter pour gagner
	Parametre attendu: Puissance4 Jeu,int numeroJoueur
	Valeur de retour j;*/
	
	int   DiaDG,DiaGD, Hor, Vert;

	for(int i=0; i<LIG; i++){
		for(int j =0; j<COL; j++){
			Hor = pionsHor(Jeu,i, j, numeroJoueur); // recupere le nombres de pions consecutifs horizontales
			if(Hor ==3  ){//|| Hor ==2
				if(Jeu.Grille[i][j+1]==-1){ // Si la valeur j+1 est vide
					if(j+1<COL){ //verifie que la valeur de j+1 est dans le jeu
						return j+1; // retourne la valeur de j+1
					}
				}
				else if(Jeu.Grille[i][j-1]==-1){ // Si la valeur j-1 est vide
					if(j-1 >=0){ //verifie que la valeur de j-1 est dans le jeu
						return j-1;
					} // retourne la valeur de j-1
				}
			}
		
			Vert = pionsVert(Jeu,i, j, numeroJoueur); // recupere le nombres de pions consecutifs verticales
			if( Vert ==3){//Vert ==2 ||
				if(Jeu.Grille[i+1][j]==-1){ // Si la valeur de i+1 est vide
					if(i+1<LIG){ // Si i+1 est dans le jeu
						return j;
					}
				}
			}

			DiaGD = pionsDiagGD(Jeu,i, j, numeroJoueur); // recupere le nombres de pions consecutifs 
			if( DiaGD ==3){//DiaGD ==2 ||
				//if(Jeu.Grille[i][j+1] !=-1){ // Si la valeur juste a cote n'est pas vide, pour empecher d'etre bloquer
					if(Jeu.Grille[i+1][j+1]==-1){ //Verifie si la valeur de i+1 et j+1 est vide
						if( (j+1<COL) && (i+1<LIG) ){ // Verifie si la valeur est dans le jeu 
							return j+1;
						}				
					//}
				}
				else if(Jeu.Grille[i-1][j-1]==-1){ //Verifie si la valeur de i-1 et j-1 est  vide
					if( (j-1>=0) && (i-1>=0) ){ // Verifie si la valeur est dans le jeu
						return j-1;
					}			
				}
			}
		
			DiaDG =  pionsDiagDG(Jeu,i, j, numeroJoueur); // recupere le nombres de pions consecutifs 
			if( DiaDG ==3){//DiaDG ==2 ||
				//if(Jeu.Grille[i][j-1] !=-1){ // Si la valeur juste a cote n'est pas vide, pour empecher d'etre bloquer
					if(Jeu.Grille[i+1][j-1]==-1){
						if( (j-1>=0) && (i+1<LIG) ){ // Verifie si les valeurs restend dans le plan
							return j-1;
						}		
					}
			//	}
			}
		}
	}
			
	return -1;
}

int BloqOrdiAI(Puissance4 Jeu,int numeroJoueur){
		/*Fonctions qui fait jouer l'ordinateur  s’il y a pas une ligne de 3 pions à bloquer son adversaire pour
	Parametre attendu: Puissance4 Jeu,int numeroJoueur
	Valeur de retour j;*/
	int   DiaDG,DiaGD, Hor, Vert;

	// Change le numero de joueur par celui de son adversaire
	if(numeroJoueur == 1){ 
		numeroJoueur = 2;
	}
	else{
		numeroJoueur = 1;
	}
	return JouerOrdiAI( Jeu,numeroJoueur);
	

	/*
	for(int i=0; i<LIG; i++){
		for(int j =0; j<COL; j++){

			Hor = pionsHor(Jeu,i, j, numeroJoueur);
			if(Hor ==3){
			
				if(Jeu.Grille[i][j+1]==-1){
					if(j+1<COL){
						return j+1;
					}
				}
				else if(Jeu.Grille[i][j-1]==-1){
					if(j-1>=0){
						return j-1;
					}
				}
			}			
			Vert = pionsVert(Jeu,i, j, numeroJoueur);
			if(Vert ==3){
				if(Jeu.Grille[i+1][j]==-1){
					if(i+1<LIG){
						return j;
					}
				}

			}

			DiaGD = pionsDiagGD(Jeu,i, j, numeroJoueur);
			if(DiaGD == 3){
				if(Jeu.Grille[i+1][j+1]==-1){
					if( (j+1<COL) && (i+1<LIG) ){
						return j+1;
					}
				}
				else if(Jeu.Grille[i-1][j-1]==-1){
					if( (j-1>=0) && (i-1>=0) ){
						return j-1;
					}
				}
			}
			
		
			DiaDG =  pionsDiagDG(Jeu,i, j, numeroJoueur);
				if(DiaDG == 3){
					if(Jeu.Grille[i+1][j-1]==-1){
						if( (j-1>=0) && (i+1<LIG) ){
							return j-1;
						}
					}
					else if(Jeu.Grille[i-1][j+1]==-1){
						if( (j+1<COL) && (i-1>=0) ){
							return j-1;
						}
					}
				}
		}
	}*/
	// return -1;
}

int JouerAI(Puissance4 Jeu,int numeroJoueur){
	/*Fonction qui permet a l'odi de jouer
		Parametre attendu: Puissance4 Jeu,int numeroJoueur
		Valeur de retour: jouer, bloq, aea(0 a 9): int*/
	int jouer = JouerOrdiAI( Jeu, numeroJoueur);
	int bloq = BloqOrdiAI( Jeu, numeroJoueur);

	
	if(jouer !=-1){
		return jouer;
	}
	if(bloq!=-1){
		return bloq;
	}
	return alea(0, COL-1);
	
}
	
void tirageJoueurAleatoire(ListeJoueur *J, string Joueur1, string Joueur2){
	/*Fonction qui choisit un joueur aux hasard
	Parametre attendu: ListeJoueur *J, string Joueur1, string Joueur2
	Valeur de retour: pas de valeur*/
	J->Joueurs[0].numero = alea(1,2); // Choisi un numero au hasard pour le 1er joueur
	
	if(J->Joueurs[0].numero == 1){ // le numero du joueur 1 est 1
		J->Joueurs[0].type = Joueur1; // Le type du joueur 1 est Joueur1
		J->Joueurs[0].pion = "0";

		J->Joueurs[1].type = Joueur2; // le numero du joueur 2 est 2
		J->Joueurs[1].numero = 2; // Le type du joueur 2 est Joueur2
		J->Joueurs[1].pion = "X";
	}
	else{ // le numero du joueur 1 est 2
		J->Joueurs[0].type = Joueur2; // Le type du joueur 1 est Joueur2
		J->Joueurs[0].pion = "X";

		J->Joueurs[1].type = Joueur1; // le numero du joueur 2 est 1
		J->Joueurs[1].numero = 1; //Le type du joueur 2 est Joueur1
		J->Joueurs[1].pion = "0";
	}
}

