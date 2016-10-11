/*
 * Environment.h
 *
 *  Created on: 3 Eki 2016
 *      Author: yasin
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_
#include <vector>
#include "BaseChromosome.h"

#define DEFAULT_CHROMOSOME_COUNT 3000
#define DEFAULT_CHROMOSOME_LENGTH 11
#define DEFAULT_MUTATION_RATE 0.003
#define DEFAULT_CROSSOVER_RATE 0.7
class Environment {
public:
	Environment();
	~Environment();
	std::vector<BaseChromosome> getChromosomes();
	int size(){
		return chromosomeNumber;
	}
	void setChromosomes(const std::vector<BaseChromosome>&);

private:
	int chromosomeNumber;
	std::vector<BaseChromosome> chrmsmList;
	double crossover_rate;
	double mutation_rate;
	int chromosome_length;


};

#endif /* ENVIRONMENT_H_ */
