/*
 * Evolution.cpp
 *
 *  Created on: 24 Eyl 2016
 *      Author: yasin
 */

#include "Evolution.h"
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <iostream>

OperationCycle::OperationCycle() {
	operation = ' ';
}

bool OperationCycle::appendOperator(char op) {
	if (operation == ' ' && !operands.empty()) {
		operation = op;
		return true;
	} else {
		return false;
	}
}

bool OperationCycle::appendOperand(int operand) {
	if (operands.size() < 2) {
		operands.push_back(operand);
		return true;
	} else {
		return false;
	}
}

bool OperationCycle::available() {
	if (operands.size() == 2) {
		if (operation == '/') {
			if (operands[1] == 0) {
				operands.pop_back();
				return false;
			} else {
				return true;
			}
		} else if (operation == ' ') {
			return false;
		} else if (operation == '*' || operation == '+' || operation == '-') {
			return true;
		}
	} else
		return false;

}

int OperationCycle::doOperation() {
	int result = 0;
	switch (operation) {
	case '+':
		result = operands[0] + operands[1];
		break;
	case '-':
		result = operands[0] - operands[1];
		break;

	case '*':
		result = operands[0] * operands[1];
		break;
	case '/':
		result = operands[0] / operands[1];
		break;
	default:
		break;
	}
	operands.clear();
	operation = ' ';
	return result;
}

OperationStack::OperationStack(){
	isOperand = false;
}

void OperationStack::pushStack(int value){
	bool isCurrOperand = (value < 10);
	bool isOperator = ( (value > 9) && (value < 14) );
	if(opStack.empty()){
		if(isCurrOperand)
		{
			this->opStack.push(value);
			return;
		}
	}
	else{
		if(opStack.size() == 1){
			if(isOperator)
			{
				this->opStack.push(value);
				return;
			}
		}
		else if(opStack.size() == 2){
			if(isCurrOperand)
			{
				this->opStack.push(value);
				try{
					this->doArithmetic();
				}
				catch(ArithmeticException &ex){
					std::cout<<ex.what()<<std::endl;
					opStack.pop();
					opStack.pop();
				}
			}
		}
	}

}

void OperationStack::doArithmetic(){
	int secondOperand = this->opStack.top();
	this->opStack.pop();
	char arithmeticOp = this->opStack.top();
	this->opStack.pop();
	int firstOperand = this->opStack.top();
	this->opStack.pop();
	int result = 0;
	if(arithmeticOp == 10){
		result = firstOperand + secondOperand;
	}
	else if(arithmeticOp == 11){
		result = firstOperand - secondOperand;
	}
	else if(arithmeticOp == 12){
		result = firstOperand * secondOperand;
	}
	else if(arithmeticOp == 13){
		if(secondOperand == 0){
			//throw ArithmeticException();
			result = firstOperand;
		}else{
			result = firstOperand / secondOperand;
		}
	}
	this->opStack.push(result);
}

int OperationStack::returnResult(){
	if(opStack.size() == 1){
		int t = this->opStack.top();
		this->opStack.pop();
		return t;
	}else{
		std::cout<<"Error: Stack operation size is not equals to one!!"<<std::endl;
		if(opStack.empty()){
			std::cout<<"Error: Stack operation is empty!!" <<std::endl;
			return 12;
		}
		std::cout<< "Error: Stack size is: "<<opStack.size()<<". And popped value is: " ;
		int x = opStack.top();
		opStack.pop();
		std::cout<< x << " ( " << ( (char) x ) << " ). "<<std::endl;
		if(opStack.size() == 1){
			int t = this->opStack.top();
			opStack.pop();
			return t;
		}

	}
}

Evolution::Evolution() {
	// TODO Auto-generated constructor stub

}

Evolution::~Evolution() {
	// TODO Auto-generated destructor stub
}

bool Evolution::testChromosome(BaseChromosome& chrm, int desired_result) {
	std::cout << "Debugging: Chromosome string: " <<chrm.toString() <<std::endl;
	int op_result = this->calculateChromosomeResult(chrm);
	std::cout << "Debugging: Chromosome result: " <<op_result <<std::endl;
	double fitnessScr = 0;
	//we found the solution, return true!
	if (desired_result == op_result) {
		fitnessScr = DBL_MAX;
		chrm.setFitnessScore(fitnessScr);
		return true;
	} else {
		fitnessScr = ((double)1.0) / fabs(desired_result - op_result);
		chrm.setFitnessScore(fitnessScr);
		return false;
	}

}

void Evolution::calculateChromosomeProbabilities(Environment& env) {
	std::vector<BaseChromosome> chromosomes = env.getChromosomes();
	long double sumOfFitnessScore = 0;
	for (int i = 0; i < env.size(); i++) {
		sumOfFitnessScore += chromosomes.at(i).getFitnessScore();

	}
	std::cout << "sumOfFitnessScore = " <<sumOfFitnessScore<<std::endl;

	for (int i = 0; i < env.size(); i++) {
		double prob = (chromosomes.at(i).getFitnessScore()
				/ sumOfFitnessScore);
		chromosomes.at(i).setProbability(prob);
	}

	env.setChromosomes(chromosomes);

}



int Evolution::parseChromosomeResult(BaseChromosome& bc) {

	int currentResult = 0;
	OperationCycle opCycle;
	for (unsigned int i = 0; i < bc.size(); i++) {
		Gene gen = bc.getGeneAt(i);
		char x = gen.get();
		if (x < 10) {
			if (!opCycle.appendOperand((int) x)) {
				if (opCycle.available()) {
					currentResult = opCycle.doOperation();
					opCycle.appendOperand(currentResult);
				}
			}

		} else {
			switch (x) {
			case 10:
				if (!opCycle.appendOperator('+')) {
					continue;
				}
				break;
			case 11:
				if (!opCycle.appendOperator('-')) {
					continue;
				}
				break;
			case 12:
				if (!opCycle.appendOperator('*')) {
					continue;
				}
				break;
			case 13:
				if (!opCycle.appendOperator('/')) {
					continue;
				}
				break;
			}
		}

	}
	return currentResult;
}

int Evolution::calculateChromosomeResult(BaseChromosome& bc) {

	int currentResult = 0;
	OperationStack operationStack;
	for (unsigned int i = 0; i < bc.size(); i++) {
		Gene gen = bc.getGeneAt(i);
		char x = gen.get();
		operationStack.pushStack(x);

	}
	currentResult = operationStack.returnResult();
	return currentResult;
}


std::pair<BaseChromosome, BaseChromosome> Evolution::RouletteWheelSelection(
		Environment& env) {
	std::vector<BaseChromosome> chromosomes = env.getChromosomes();
	double rndNumber = rand() / (double) RAND_MAX;
	double offset = 0.0;
	BaseChromosome mother(DEFAULT_CHROMOSOME_LENGTH);
	BaseChromosome father(DEFAULT_CHROMOSOME_LENGTH);
	std::vector<BaseChromosome>::iterator it = chromosomes.begin();
	for (; it != chromosomes.end(); ++it) {
		offset += (*it).getProbability();
		if (rndNumber < offset) {
			mother = (*it);
			//bad design using linked list is better option
			//chromosomes.erase(it);
			break;
		}
	}

	rndNumber = rand() / (double) RAND_MAX;
	offset = 0.0;
	int index = it - chromosomes.begin();
	for (it = chromosomes.begin(); it != chromosomes.end(); ++it) {
		offset += (*it).getProbability();
		if (rndNumber < offset) {
			//if it is chosen for mother, skip to next one
			if(index == (it - chromosomes.begin())){
				continue;
			}
			father = (*it);
			//chromosomes.erase(it);
			break;
		}
	}
	return std::make_pair(mother, father);

}

/**
 *
 */
void Evolution::applyCrossover(std::pair<BaseChromosome, BaseChromosome>& chrpair){
	double randomValue = rand() / (double) RAND_MAX;
	if(randomValue < DEFAULT_CROSSOVER_RATE){
		//swap genes after random point
		double randomGeneIndex = rand()%DEFAULT_CHROMOSOME_LENGTH;
		for(int i = randomGeneIndex; i < DEFAULT_CHROMOSOME_LENGTH; i++ ){
			//swap the ith genes between the pairs
			Gene tempFirst = chrpair.first.getGeneAt(i);
			chrpair.first.setGeneAt(i, chrpair.second.getGeneAt(i));
			chrpair.second.setGeneAt(i, tempFirst);
		}
	}

}

void Evolution::applyMutation(BaseChromosome& bc){
	for(unsigned int i=0; i<bc.size(); i++){
	double randomValue =  rand() / (double) RAND_MAX;
		if(randomValue < DEFAULT_MUTATION_RATE){
			Gene temp = bc.getGeneAt(i);
			char x = temp.get();
			//swap genes after random nth bit
			int randomGeneBitIndex = (int) (rand()%4);

			temp.set( x ^ (1<<randomGeneBitIndex) );
			bc.setGeneAt(i, temp);

		}
	}
}






