// # ifndef __DIJ_HPP
// # define __DIJ_HPP
//

# include <iostream>
# include <vector>
# include <string>
# include <algorithm>
using namespace std;

template <class C> class Graphe {
private:
  vector<C> sommets;
  vector<pair<pair<C,C>,int> > arretes;

public:
  Graphe();
  Graphe(vector<C> sommets, vector<pair<pair<C,C>,int> > arretes);

  void addSommet(C);
  void addArrete(pair<pair<C,C>,int>);
  int findSommet(C);//retourne l'indice du sommet rechercher dans le vecteur, retourne -1 si il le retrouve pas
  int findArrete(pair<C,C>);//retourne l'indice de l'arrete rechercher dans le vecteur, retourne -1 si il le retrouve pas
  bool deleteSommet(C);
  bool deleteArrete(pair<C,C>);
  void deleteArrete(C);//suprime toute les arretes qui concerne C, un sommet.
  // friend ostream& operator<<(ostream& ,const Graphe<C>&);
  void affiche();

};

template <class C> class Tas {
  private:
    vector<C> tas;

  public:
    Tas();
    Tas(vector<C> tas);

    void addCles(C c);
    C mini();
    int findCles(C c);//retourne l'indice de l'element de type C rechercher
    void permuter(C i, C j);
    void heapify(int n, int i);
    void heapSort();
    void afficherTab();//affiche le tas sous forme de tableau
};

// template <class C> class Tas {
//   private:
//     Tas* filsDroit;
//     Tas* filsGauche;
//     C cles;
//   public:
//     Tas();
//     Tas(C);
//     Tas(Tas*,Tas*,C);
//
//     void addCles(C c);
//     C mini();
//     int findCles(C c);
//     void sort();
// };
//
// #endif


//fonction de Graphe
template< class C>
Graphe<C>::Graphe(){
   // (*this).sommets=NULL;
   // (*this).arretes=NULL;
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
  }
}

template< class C>
void Graphe<C>::addArrete(pair<pair<C,C>,int> a){
  if (findArrete(a.first)==-1){
    (*this).arretes.push_back(a);
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


// template< class C >
// ostream & operator << ( ostream& out ,const Graphe<C> &g ) {
//   out<<"Sommets:"<<endl;
//   for(int i =0;i<g.sommets.size();i++){
//     out<<g.sommets[i]<<";" ;
//   }
//   out<<endl;
//   out<<"Arretes:"<<endl;
//   for(int i =0;i<g.arretes.size();i++){
//     out<<"sommets: "<<g.arretes.first.first<<" "<<g.arretes.first.second<<"// poid:"<<g.arretes.second<<endl;
//   }
//   return out;
// }

// fonction de Tas
template<class C>
Tas<C>::Tas(){
  (*this).tas=std::vector<C>();
  // (*this).tas=NULL;
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
  //(*this).heapSort();
}

template<class C>
void Tas<C>::permuter(C i, C j){
  //cout<<"début permuter"<<endl;
	C temp;
	temp = (*this).tas[i];
	(*this).tas[i]=(*this).tas[j];
	(*this).tas[j]=temp;
  //cout<<"fin permuter"<<endl;
}

// template<class C>
// void Tas<C>::tamiser(int noeud, int n){
//   //cout<<"début tamiset"<<endl;
// 	int k = noeud;
// 	int j = 2*k;
// 	while(j<=n)
// 	{
// 		if (j<n && (*this).tas[j]>(*this).tas[j+1])
// 		{
// 			j++;
// 		}
// 		if ((*this).tas[k]>(*this).tas[j])
// 		{
// 			(*this).permuter(k,j);
// 			k = j;
// 			j = 2*k;
// 		}
// 		else return;
//
// 	}
//   //cout<<"fin tamiser"<<endl;
//
// }

template<class C>
void Tas<C>::heapify(int n, int i)
{
    int smallest = i; // Initialize smalles as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is smaller than root
    if (l < n && (*this).tas[l] < (*this).tas[smallest])
        smallest = l;

    // If right child is smaller than smallest so far
    if (r < n && (*this).tas[r] < (*this).tas[smallest])
        smallest = r;

    // If smallest is not root
    if (smallest != i) {
        (*this).permuter(i, smallest);

        // Recursively heapify the affected sub-tree
        (*this).heapify(n,smallest);
    }
}

// main function to do heap sort
template<class C>
void Tas<C>::heapSort()
{
    int n = (*this).tas.size();
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        (*this).heapify(n,i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        (*this).permuter(0, i);

        // call max heapify on the reduced heap
        heapify(i, 0);
    }
}
//
// template<class C>
// void Tas<C>::sort(){
// //  cout<<"début sort"<<endl;
//   int n=(*this).tas.size();
// 	if (n <= 1) return;
// 	for (int i = n/2; i>=0;i--){
// 		(*this).tamiser(i,n);
// 	}
// 	for (int i=(n-1); i>0;i-- ){
// 	//	(*this).permuter(i,0);
// 		(*this).tamiser(0,i-1);
// 	}
//   //cout<<"fin sort"<<endl;
// }

template<class C>
void Tas<C>::afficherTab(){
  cout<<"Tableau du tas: "<<endl;
    for(int i =0;i<(*this).tas.size();i++){
      cout<<(*this).tas[i]<<";" ;
    }
    cout<<""<<endl;
}
// template<class C>
// Tas<C>::Tas(){
//   (*this).filsDroit=NULL;
//   (*this).filsGauche=NULL;
//   (*this).cles=0;
// }
//
// template<class C>
// Tas<C>::Tas(C c){
//   (*this).filsDroit=NULL;
//   (*this).filsGauche=NULL;
//   (*this).cles=c;
// }
//
// template<class C>
// Tas<C>::Tas(Tas* filsDroit, Tas* filsGauche, C c){
//   (*this).filsDroit=filsDroit;
//   (*this).filsGauche=filsGauche;
//   (*this).cles=c;
// }
//
// template<class C>
// void Tas<C>::sort(){
//   (*this).cles=0;
//
// }

int main(){

  // vector<int> v;
  // v.push_back(2);
  // v.push_back(3);
  // v.push_back(4);
  //
  // vector<pair<pair<int,int>,int> > a;
  //  a.push_back(make_pair(make_pair(2,3),4));
  //  a.push_back(make_pair(make_pair(4,3),9));
  //  a.push_back(make_pair(make_pair(2,4),5));

    // Graphe<int> *g= new Graphe<int>(v,a);

    // Graphe<int> g (v,a);
    // g.addSommet(5);
    // g.addArrete(make_pair(make_pair(2,5),78));
  //  g.deleteSommet(5);
    // Graphe<int>& refg = g;
    // refg.affiche();
    // cout<<g<<endl;


  //  Graphe<int> *g2= new Graphe<int>();
  //cout<<"1"<<endl;
  vector<int> v;// ici on ne peut pas fair vector<char> v {'t','i','r'}; car il faut c++11 (avec les char).
//  v.push_back(10);
  //cout<<"3"<<endl;
  //v.push_back(1);
  //cout<<"4"<<endl;
  // v.push_back(2);
//  cout<<"5"<<endl;


   //Tas<char> *t =new Tas<char>();
  // Tas<int> *t2 =new Tas<int>();
  // Tas<int> t3 (t,t2,5);

  Tas<int>* t =new Tas<int> ();
  // cout<<"6"<<endl;

   t->addCles(1);
   t->afficherTab();
   t->addCles(2);


   t->afficherTab();
    t->addCles(5);
// cout<<"1"<<endl;

//  cout<<"1"<<endl;
  t->afficherTab();
  t->addCles(3);
  t->afficherTab();
  t->addCles(4);
  t->afficherTab();
  t->heapSort();
  t->afficherTab();
//  cout<<"8"<<endl;

  return 0;

//si on veut l'indice d'un elt de pointeur de vecteur on utilise at()
}
