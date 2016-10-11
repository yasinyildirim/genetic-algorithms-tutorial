/*
 * BaseChromosome.cpp
 *
 *  Created on: 24 Eyl 2016
 *      Author: yasin
 */
#include <ctime>
#include <cstdlib>

#include "BaseChromosome.h"

Gene::Gene(char g){
	gene = g;
}

char Gene::get(){
	return this->gene;
}

void Gene::set(char g){
	this->gene = g;
}

void BaseChromosome::seedRandomGenes(){
	srand(time(NULL));
}

BaseChromosome::BaseChromosome(int length) {
	genes.reserve(length);
	this->length = length;
	probability = 0;
	fitnessScore = 0;
	// TODO Auto-generated constructor stub
	for(int i=0; i<length; i++){
		int gene = rand() % 14;
		genes.push_back(Gene( (char) gene));
	}

}

BaseChromosome::~BaseChromosome() {
	// TODO Auto-generated destructor stub
}

std::string BaseChromosome::toString(){
	std::string geneStr;
	for(int i=0; i<genes.size(); i++){
		char c = genes[i].get();
		if(c<10){
			geneStr.push_back(c + 48);
		}
		else{
			if(c==10){
				geneStr.push_back('+');
			}
			else if(c==11){
				geneStr.push_back('-');
			}
			else if(c==12){
				geneStr.push_back('*');
			}
			else if(c==13){
				geneStr.push_back('/');
			}
			else{
				//erroneous bit, put space to indicate that
				geneStr.push_back(' ');
			}


		}

	}
	return geneStr;
}

