#include "dijkstra.hpp"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "case.hpp"
#include "tuile.hpp"
#include "graph_tuile.hpp"

using namespace MMaze; 

void parcour::trever_lar(int start)
{
	
	Tuile T(true, 0,0,0);
	Graph_tuile GT(T);
		
	for(int i = 0 ; i < 16 ; i++)
	{   
	    large.push(i);
	    praiteprocessueur[i] = -1 ;
	    
	}
	large.push(start);
	praiteprocessueur[start]= start ;
	while (! large.empty())
	{
	    int t=large.front();
	    int s = GT.contenue[t].nbCoupsPossible;
	    for(int i =0 ; i<s ; i++)
	    {
	       if (praiteprocessueur[i] != -1 ){
		int tmp = GT.contenue[t].predecesseur[i]->C.index();
		praiteprocessueur[tmp] = t;
		large.push(tmp);
	       }
		   if(praiteprocessueur[start]>praiteprocessueur[i])
		   {
			   praiteprocessueur[i]=voisan[i]+1;
			   int tmp1=GT.contenue[t].predecesseur[i]->C.index();
			   voisan[tmp1]=t ;
			   large.push(tmp1);
		   }
	    }
	}

	
}

