#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <stdio.h>

#include "../AStar.h"
#include "../Graph/Node.h"


// https://aiandgames.com/romania-graph1/
TEST_CASE("Romania Graph")
{
	AStar* pathFinder = new AStar();

	// Construct the romania graph nodes
	Node* ara = new Node("Arad", 366);
	Node* buc = new Node("Bucharest", 0);
	Node* cra = new Node("Craiova", 160);
	Node* dob = new Node("Dobreta", 242);
	Node* efo = new Node("Eforie", 161);
	Node* fag = new Node("Fagaras", 178);
	Node* giu = new Node("Giurgiu", 77);
	Node* hir = new Node("Hirsova", 151);
	Node* ias = new Node("Iasi", 226);
	Node* lug = new Node("Lugoj", 244);
	Node* meh = new Node("Mehadia", 241);
	Node* nea = new Node("Neamt", 234);
	Node* ora = new Node("Oradea", 380);
	Node* pit = new Node("Pitesti", 98);
	Node* rim = new Node("Rimnicu Vilcea", 193);
	Node* sib = new Node("Sibiu", 253);
	Node* tim = new Node("Timisoara", 329);
	Node* urz = new Node("Urziceni", 80);
	Node* vas = new Node("Vaslui", 199);
	Node* zer = new Node("Zerind", 374);

	ara->paths.push_back(Edge(ara, zer, 75));
	ara->paths.push_back(Edge(ara, tim, 118));
	ara->paths.push_back(Edge(ara, sib, 140));

	buc->paths.push_back(Edge(buc, giu, 90));
	buc->paths.push_back(Edge(buc, urz, 85));
	buc->paths.push_back(Edge(buc, fag, 211));
	buc->paths.push_back(Edge(buc, pit, 101));

	cra->paths.push_back(Edge(cra, pit, 138));
	cra->paths.push_back(Edge(cra, rim, 146));
	cra->paths.push_back(Edge(cra, dob, 120));

	dob->paths.push_back(Edge(dob, cra, 120));
	dob->paths.push_back(Edge(dob, meh, 75));

	efo->paths.push_back(Edge(efo, hir, 86));

	fag->paths.push_back(Edge(fag, buc, 211));
	fag->paths.push_back(Edge(fag, sib, 99));

	giu->paths.push_back(Edge(giu, buc, 90));

	hir->paths.push_back(Edge(hir, efo, 86));
	hir->paths.push_back(Edge(hir, urz, 98));

	ias->paths.push_back(Edge(ias, vas, 92));
	ias->paths.push_back(Edge(ias, nea, 87));

	lug->paths.push_back(Edge(lug, meh, 70));
	lug->paths.push_back(Edge(lug, tim, 111));

	meh->paths.push_back(Edge(meh, dob, 75));
	meh->paths.push_back(Edge(meh, lug, 70));

	nea->paths.push_back(Edge(nea, ias, 87));

	ora->paths.push_back(Edge(ora, zer, 71));
	ora->paths.push_back(Edge(ora, sib, 151));

	pit->paths.push_back(Edge(pit, buc, 101));
	pit->paths.push_back(Edge(pit, rim, 97));
	pit->paths.push_back(Edge(pit, cra, 138));

	rim->paths.push_back(Edge(rim, cra, 146));
	rim->paths.push_back(Edge(rim, pit, 97));
	rim->paths.push_back(Edge(rim, sib, 80));

	sib->paths.push_back(Edge(sib, rim, 80));
	sib->paths.push_back(Edge(sib, fag, 99));
	sib->paths.push_back(Edge(sib, ora, 151));
	sib->paths.push_back(Edge(sib, ara, 140));

	tim->paths.push_back(Edge(tim, lug, 111));
	tim->paths.push_back(Edge(tim, ara, 118));

	urz->paths.push_back(Edge(urz, buc, 85));
	urz->paths.push_back(Edge(urz, hir, 98));
	urz->paths.push_back(Edge(urz, vas, 142));

	vas->paths.push_back(Edge(vas, urz, 142));
	vas->paths.push_back(Edge(vas, ias, 92));

	zer->paths.push_back(Edge(zer, ara, 75));
	zer->paths.push_back(Edge(zer, ora, 71));

	SECTION ("Bucharest to Bucharest")
	{
		pathFinder->Clear();		

		std::vector<Node*> expectedResult = {buc};

		REQUIRE(pathFinder->FindPath(buc, buc) == expectedResult);

	}

	SECTION ("Craiova to Bucharest")
	{
		pathFinder->Clear();

		std::vector<Node*> expectedResult = {cra, pit, buc};

		REQUIRE(pathFinder->FindPath(cra, buc) == expectedResult);
	}

	SECTION ("Arad to Bucharest")
	{
		pathFinder->Clear();

		std::vector<Node*> expectedResult = {ara, sib, rim, pit, buc};

		REQUIRE(pathFinder->FindPath(ara, buc) == expectedResult);
	}	

	SECTION ("Eforie to Bucharest")
	{
		pathFinder->Clear();

		std::vector<Node*> expectedResult = {efo, hir, urz, buc};

		REQUIRE(pathFinder->FindPath(efo, buc) == expectedResult);
	}
}