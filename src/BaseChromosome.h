/*
 * BaseChromosome.h
 *
 *  Created on: 24 Eyl 2016
 *      Author: yasin
 */

#ifndef BASECHROMOSOME_H_
#define BASECHROMOSOME_H_
#include <string>
#include <vector>
using namespace std;

/*
 *
 *  Four bits are required to represent the range of characters used:

0:         0000

1:         0001

2:         0010

3:         0011

4:         0100

5:         0101

6:         0110

7:         0111

8:         1000

9:         1001

+:         1010

-:          1011

*:          1100

/:          1101
 *
 *
 * */

class Gene{
public:
	Gene(char g);
	char get();
	void set(const char g);
private:
	char gene;
};

class BaseChromosome {
public:
	BaseChromosome(int length);
	~BaseChromosome();
	static void seedRandomGenes();
	std::string toString();
	unsigned int size(){
		return this->length;
	}
	Gene getGeneAt(int i){
		return genes[i];
	}
	void setGeneAt(int i, const Gene& gen){
			genes[i] = gen;
		}
	void setFitnessScore(double f){
		this->fitnessScore = f;
	}
	double getFitnessScore(){
		return this->fitnessScore;
	}

	void setProbability(double prob){
		this->probability = prob;
	}
	double getProbability(){
		return this->probability;
	}
private:
	std::vector<Gene> genes;
	unsigned int length;
	double fitnessScore;
	double probability;
};

#endif /* BASECHROMOSOME_H_ */
