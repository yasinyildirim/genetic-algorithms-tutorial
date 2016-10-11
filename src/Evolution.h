/*
 * Evolution.h
 *
 *  Created on: 24 Eyl 2016
 *      Author: yasin
 */

#ifndef EVOLUTION_H_
#define EVOLUTION_H_

#include "BaseChromosome.h"
#include "Environment.h"
#include <stack>
#include <exception>

class OperationCycle{
public:
	std::vector<int> operands;
	char operation;
	OperationCycle();
	bool appendOperator(char op);
	bool appendOperand(int operand);
	bool available();
	int doOperation();
private:

};


class ArithmeticException : public std::exception{
public:
	virtual const char* what() const throw()
	  {
	    return "Arithmetic Exception happened";
	  }
};


class OperationStack{
public:
	OperationStack();
	void pushStack(int value);
	int returnResult();
private:
	void doArithmetic();
	bool isOperand;
	std::stack<int> opStack;
};

class Evolution {
public:
	Evolution();
	virtual ~Evolution();
	bool testChromosome(BaseChromosome& chrm, int desired_result);
	void calculateChromosomeProbabilities(Environment& chrm);
	std::pair<BaseChromosome, BaseChromosome> RouletteWheelSelection(Environment& env);
	void applyCrossover(std::pair<BaseChromosome, BaseChromosome>& chrpair);
	void applyMutation(BaseChromosome& bc);

private:
	int parseChromosomeResult(BaseChromosome& bc);
	int calculateChromosomeResult(BaseChromosome& bc);


};

#endif /* EVOLUTION_H_ */
