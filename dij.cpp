
# include <iostream>
# include <vector>
# include <string>
# include <algorithm>
#include <map>
using namespace std;

template <class C> class Graphe {
private:
  vector<C> sommets;
  vector<pair<pair<C,C>,int> > arretes;

public:
  Graphe();
  Graphe(vector<C> sommets, vector<pair<pair<C,C>,int> > arretes);


  void addSommet(C);//ajoute un sommet de type C passer en parametre dans la liste des arrets du Graphe appelant
  void addArrete(pair<pair<C,C>,int>);//ajoute une arrets (ainsi que sont poid) dans la liste des arretes du Graphe appelant
  int findSommet(C);//retourne l'indice du sommet rechercher dans le vecteur, retourne -1 si il le retrouve pas
  int findArrete(pair<C,C>);//retourne l'indice de l'arrete rechercher dans le vecteur, retourne -1 si il le retrouve pas
  bool deleteSommet(C);//supprime un sommet de type C passer en parametre de la liste des sommets (uniquement si le sommet existe: retourne false) retourne true
  bool deleteArrete(pair<C,C>);//supprime une arrete passer en parametre de la liste d'arrete (uniquement si l'arrete existe: retourne false) retourne true
  void deleteArrete(C);//suprime toute les arretes qui concerne C, un sommet.
  void affiche();// affiche les sommets du graphe ainsi que ses arretes.

};

template <class C> class Tas {
  private:
    vector<C> tas;

  public:
    Tas();
    Tas(vector<C> tas);
    ~Tas();

    void addCles(C c);
    C mini();
    int findCles(C c);//retourne l'indice de l'element de type C rechercher
    void permuter(int i,int j);
    void tamiser(int iPere, int iFin);
    void triTas();
    void entasser();
    void afficherTab();//affiche le tas sous forme de tableau
};

template <class C> class Tas_id{
  private:
    std::map<int,C> tas_id;

  public:
    Tas_id();
    Tas_id(std::map<int,C>);
    ~Tas_id();

    void setAllId(Tas<C> t);//prend un tas et affecte des id, on le stoque dans la teas_id appelant.
    void addVal(Tas<C> t,C c);//rajoute dans le tas l'element c, et l'ajoute dans tas_id avec la cles qui correspond a sa position
    void removeVal(Tas<C> t,C c);//supprime dans le tas t l'élement c, et le supprime de tas id.
};

//fonction de Graphe
template< class C>
Graphe<C>::Graphe(){
  (*this).sommets=std::vector<C>();
  (*this).arretes=std::vector<pair<pair<C,C>,int> > ();
}

template< class C>
Graphe<C>::Graphe(vector<C> sommets, vector<pair<pair<C,C>,int> > arretes){
  (*this).sommets=sommets;
  (*this).arretes=arretes;
}

template< class C>
void Graphe<C>::addSommet(C c){
  if (findSommet(c)==-1){
    (*this).sommets.push_back(c);
  }else{
    cout<<"Sommet deja présent"<<endl;
  }
}

template< class C>
void Graphe<C>::addArrete(pair<pair<C,C>,int> a){
  if (findArrete(a.first)==-1){
    (*this).arretes.push_back(a);
  }else{
    cout<<"Arrete deja présente"<<endl;
  }
}

template< class C>
int Graphe<C>::findSommet(C c){
  for(int i =0;i<(*this).sommets.size();i++){
    if((*this).sommets[i]==c){
      return i;
    }
  }
    return -1;
}

template< class C>
int Graphe<C>::findArrete(pair<C,C> p){
  for(int i = 0; i<(*this).arretes.size();i++){
    if((*this).arretes[i].first.first==p.first){
      if((*this).arretes[i].first.second==p.second){
       return i;
     }
   }else{
     if((*this).arretes[i].first.first==p.second){
       if((*this).arretes[i].first.second==p.first){
         return i;
       }
     }
   }
  }
  return -1;
}

template< class C>
bool Graphe<C>::deleteSommet(C c){
  int indice=(*this).findSommet(c);
  if(indice!=-1){
    (*this).sommets.erase((*this).sommets.begin()+indice);
    (*this).deleteArrete(c);
    return true;
  }else{return false;}
}

template< class C>
bool Graphe<C>::deleteArrete(pair<C,C> p){
  int indice=(*this).findArrete(p);
  if(indice!=-1){
    (*this).arretes.erase((*this).arretes.begin()+indice);
    return true;
  }else{return false;}
}

template< class C>
void Graphe<C>::deleteArrete(C s){
  for(int i = 0; i<(*this).arretes.size();i++){
    if((*this).arretes[i].first.first==s||(*this).arretes[i].first.second==s){
      (*this).deleteArrete((*this).arretes[i].first);
      i--;
    }
  }
}

template< class C>
void Graphe<C>::affiche(){
  cout<<"Sommets:"<<endl;
    for(int i =0;i<(*this).sommets.size();i++){
      cout<<(*this).sommets[i]<<";" ;
    }
    cout<<endl;
    cout<<"Arretes:"<<endl;
    for(int i =0;i<(*this).arretes.size();i++){
      cout<<"sommets: "<<(*this).arretes[i].first.first<<" "<<(*this).arretes[i].first.second<<"// poid:"<<(*this).arretes[i].second<<endl;
    }
}

// fonction de Tas
template<class C>
Tas<C>::Tas(){
  (*this).tas=std::vector<C>();
}

template<class C>
Tas<C>::Tas(vector<C> tas){
  (*this).tas=tas;
}

template<class C>
C Tas<C>::mini(){
  return (*this).tas[0];
}

template<class C>
void Tas<C>::addCles(C c){
  (*this).tas.push_back(c);
}

template<class C>
void Tas<C>::permuter(int i, int j){
	C temp;
	temp = (*this).tas[i];
	(*this).tas[i]=(*this).tas[j];
	(*this).tas[j]=temp;
}

template <class C>
void Tas<C>::tamiser(int iPere, int iFin){
  int iFils = 2*iPere;
  if((iFils<iFin) && ((*this).tas[iFils+1]>(*this).tas[iFils])){
    iFils++;
  }
  if ((iFils<=iFin) && ((*this).tas[iPere]<(*this).tas[iFils])){
    (*this).permuter(iPere, iFils);
    (*this).tamiser(iFils, iFin);
  }
}

template <class C>
void Tas<C>::triTas(){
  (*this).entasser();
  int k= (*this).tas.size();
  while(k>0){
    (*this).permuter(1,k);
    (*this).tamiser(1,k-1);
    k--;
  }
}

template <class C>
void Tas<C>::entasser(){
  int i=(*this).tas.size()/2;
  while(i>0){
    tamiser(i,(*this).tas.size());
    i--;
  }
}


template<class C>
void Tas<C>::afficherTab(){
  cout<<"Tableau du tas: "<<endl;
    for(int i =0;i<(*this).tas.size();i++){
      cout<<(*this).tas[i]<<";" ;
    }
    cout<<""<<endl;
}

//fonction de tas_id

template<class C>
Tas_id<C>::Tas_id(){
  (*this).tas_id=std::map<int,C>();
}

template<class C>
Tas_id<C>::Tas_id(std::map<int,C> tas_id){
  (*this).tas_id=tas_id;
}

template<class C>
void Tas_id<C>::setAllId(Tas<C> t){
  int i=1;
  int taille=t.tas.size();
  while (taille>0){
    (*this).tas_id[i]=t.tas[i-1];
    i++;
    taille--;
  }
}

template<class C>
void Tas_id<C>::addVal(Tas<C> t,C c){
  t.addCles(c);
  (*this).setAllid(t);
}

template<class C>
void Tas_id<C>::removeVal(Tas<C> t,C c){
  t.addCles(c);
  (*this).setAllid(t);
}




int main(){

  char user='w';
  while(user!='q'){
    cout<<"g: crée un Graphe."<<endl;
    cout<<"q: quit."<<endl;
    cin>>user;
    if(user=='g'){
      Graphe<int> g=Graphe<int> ();
      cout<<"taper les sommets:"<<endl;
      cout<<"pour arreter taper q si vous avez choisie char, -2 si vous avez choisie int "<<endl;
      


      while(b){
			  int e;
			  cin>>e;
			  if(e==-2){
				  b=false;
			  }else{
				  g.addSommet(e);
			  }
      }
	  b=true;
	  cout<<"taper les couples des sommets en choisissant entre les disponibles (taper -1 -1 pour quitter):"<<endl;
	  for(int i=0; i<g.sommets.size(); i++){
		  cout<<g.sommets[i]<<";".
	  }
	  cout<<endl;
	  int aa=1;
	  while(b){
		  cout<<"arrete n°"<<aa<<" : "<<endl;
		  
			  int s1, s2;
			  cin>>s1>>s2;
			  if(s1==-1&&s2==-1){
				  b=false;
			  }else{
				  cout<<"saisir la valeur de l'arrete: "<<endl;
				  int va;
				  cin>>va;
				  g.addArrete(((s1,s2),va));
			  }
		  
	  }
	  g.affiche();
	  vector<int> v;
	  for(j=0; j<g.arretes.size();j++){
		  v.push_back(g.arretes[j]);
	  }
	  Tas<int> t (v);
	  cout<<"Tas non ordonnee: "<<endl;
	  t.afficherTab();
	  t.triTas();
	  cout<<"Tas ordonnee: "<<endl;
	  t.afficherTab();
	  Tas_id<int> tid ();
	  tid.setAllId(t);
    }
  }
  return 0;
}
