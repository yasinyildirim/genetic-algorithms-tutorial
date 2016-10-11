/*
 * Environment.cpp
 *
 *  Created on: 3 Eki 2016
 *      Author: yasin
 */

#include "Environment.h"

Environment::Environment() {
	// TODO Auto-generated constructor stub
	chromosomeNumber = DEFAULT_CHROMOSOME_COUNT;
	chromosome_length = DEFAULT_CHROMOSOME_LENGTH;
	crossover_rate = DEFAULT_CROSSOVER_RATE;
	mutation_rate = DEFAULT_MUTATION_RATE;

	chrmsmList.reserve(chromosomeNumber);
	BaseChromosome::seedRandomGenes();
	for(int i=0; i<chromosomeNumber; i++){
		BaseChromosome b(DEFAULT_CHROMOSOME_LENGTH);
		chrmsmList.push_back(b);
	}
}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
	chrmsmList.clear();
}

std::vector<BaseChromosome> Environment::getChromosomes(){
	return this->chrmsmList;
}

void Environment::setChromosomes(const std::vector<BaseChromosome>& nextGen){
	this->chrmsmList.clear();
	this->chrmsmList = nextGen;
	this->chromosomeNumber = nextGen.size();
}
