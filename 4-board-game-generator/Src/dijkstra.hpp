#ifndef parcour_H
#define parcour_H


#include <iostream>
#include <vector>
#include <map>
#include <stdint.h>
#include <iostream>
#include <queue>
#include "draw.hpp"
#include "direction.hpp"
#include "graph_tuile.hpp"
#include "coup.hpp"
#include "noeud_case.hpp"
#include<queue>

class parcour
{
	public:
		parcour();
		~parcour();

		queue<int> large ;
		void trever_lar(int start);
		int praiteprocessueur[16];
		int voisan[24];
};

#endif
