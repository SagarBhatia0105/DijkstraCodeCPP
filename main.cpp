#include <iostream>
#include <fstream>
#define INF 10000
#define NIL -1
using namespace std;

void ISS(int vertices, int *parent, int *d, int s){

  for(int i=0; i<vertices; i++){
    parent[i] = NIL;
    d[i] = INF;
  }

  d[s] = 0;

}

int getShortest(bool *visited, int *d, int vertices){
  int min = INF;
  int p;

  for(int i=0; i<vertices; i++){
    if(d[i]<min && visited[i] == false){
      p = i;
      min = d[i];
    }
  }

  visited[p] = true;
  return p;
}

void Relax(int *parent, int *d, int **adj, int p, int i){

  if(d[i] > d[p] + adj[p][i]){
    d[i] = d[p] + adj[p][i];
    parent[i] = p;
  }
}

void showShortest(int *parent, int *d, int vertices){

  for(int i=0; i<vertices; i++){
    cout<<"Parent of "<<i<<" is "<<parent[i]<<" and ";
    cout<<"Distance is "<<d[i]<<endl;
  }
}

void Dijsktra(int **adj, int s, int vertices){

  int *parent = new int[vertices];
  int *d = new int[vertices];
  bool *visited = new bool[vertices];
  int counter = 0, p;

  ISS(vertices, parent, d, s);

  for(int i=0; i<vertices; i++){
    visited[i] = false;
  }

  while(counter<vertices){
    p = getShortest(visited, d, vertices);
    cout<<"The visited edge now is "<<p<<endl;
    for(int i=0; i<vertices; i++){
      if(adj[p][i] != 0 && visited[i] == false){
        Relax(parent, d, adj, p, i);
      }
    }
    counter++;
  }

  showShortest(parent, d, vertices);

}

int main(int argc, char const *argv[]) {

  //number of data sets
  int n, **adj;
  //number of edges and vertices
  int vertices, edges;
  fstream input(argv[1]);
  int u, v, w;

  if(!input){
    cout<<"Unable to read input file"<<endl;
  }

  input>>n;

  for(int i=0; i<n; i++){

    input>>vertices>>edges;

    adj = new int*[vertices];

    for(int j=0; j<vertices; j++){
      adj[j] = new int[vertices];
    }

    for(int j=0; j<vertices; j++){
      for(int k=0; k<vertices; k++){
        adj[j][k] = 0;
      }
    }

    cout<<vertices<<" "<<edges<<endl;
    for(int j=0; j<edges; j++){
      input>>u>>v>>w;
      adj[u][v] = w;
    }

    Dijsktra(adj, 0, vertices);

  }
    input.close();
    return 0;
}
