// # ifndef __DIJ_HPP
// # define __DIJ_HPP
//

# include <iostream>
# include <vector>
# include <string>
// # include <bool>
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
  friend ostream& operator<<(ostream& out ,const Graphe<C> &g );

};

//
// #endif
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
  (*this).sommets.push_back(c);
}

template< class C>
void Graphe<C>::addArrete(pair<pair<C,C>,int> a){
  (*this).arretes.push_back(a);
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

template< class C >
ostream & operator << ( ostream& out ,const Graphe<C> &g ) {
  out<<"Sommets:"<<endl;
  for(int i =0;i<g.sommets.size();i++){
    out<<g.sommets[i]<<";" ;
  }
  out<<endl;
  out<<"Arretes:"<<endl;
  for(int i =0;i<g.arretes.size();i++){
    out<<"sommets: "<<g.arretes.first.first<<" "<<g.arretes.first.second<<"// poid:"<<g.arretes.second<<endl;
  }
  return out;
}


// template< class C >
// Solmmet &Sommet::operator = (const vector<C*>& v ) {
// 	for (int i=0;i<v.size();i++){
//     this[i]=v[i];
//   }
//   return *this ;
// }


int main(){

  vector<int> v;
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);

  vector<pair<pair<int,int>,int> > a;
   a.push_back(make_pair(make_pair(2,3),4));
   a.push_back(make_pair(make_pair(4,3),9));
   a.push_back(make_pair(make_pair(2,4),5));

    // Graphe<int> *g= new Graphe<int>(v,a);

    Graphe<int> g (v,a);
    g.addSommet(5);
    g.addArrete(make_pair(make_pair(2,5),78));
    g.deleteSommet(5);
    Graphe<int>& refg = g;
     cout<<g<<endl;


  //  Graphe<int> *g2= new Graphe<int>();


  return 0;


}
