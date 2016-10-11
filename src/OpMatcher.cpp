//============================================================================
// Name        : OpMatcher.cpp
// Author      : Yasin Yıldırım
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Evolution.h"
#include <cstdlib>

void createNextGeneration(Evolution &evolution, Environment& env){
	std::vector<BaseChromosome> nextGeneration;
	nextGeneration.reserve(env.size());
	evolution.calculateChromosomeProbabilities(env);
	while( ((double) nextGeneration.size() < (double)1.0f * env.size())){
		std::pair<BaseChromosome,BaseChromosome> chrpair = evolution.RouletteWheelSelection(env);
		evolution.applyCrossover(chrpair);
		evolution.applyMutation(chrpair.first);
		evolution.applyMutation(chrpair.second);
		nextGeneration.push_back(chrpair.first);
		nextGeneration.push_back(chrpair.second);
	}

	env.setChromosomes(nextGeneration);

}

int main(int argc, char* argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	int desired_result = 10003;
	Environment env;
	Evolution evolution;
	bool done = false;
	srand(time(NULL));
	BaseChromosome result(DEFAULT_CHROMOSOME_LENGTH);
	int generationCount = 0;
	while(!done){
		std::vector<BaseChromosome> chrList = env.getChromosomes();
		std::vector<BaseChromosome>::iterator iter = chrList.begin();
		for(; iter != chrList.end(); ++iter){

			done = evolution.testChromosome( (*iter), desired_result );
			if(done){
				result = (*iter);
				break;
			}
		}
		env.setChromosomes(chrList);
		std::cout << "Done evaluating "<<generationCount << "th Generation.."<<std::endl ;
		std::cout << "Creating "<< ++generationCount << "th Generation.."<<std::endl ;
		createNextGeneration(evolution, env);



	}

	std::cout<< "Result for input "<<  desired_result<<" is: "<<result.toString()<<std::endl;


	return 0;
}
