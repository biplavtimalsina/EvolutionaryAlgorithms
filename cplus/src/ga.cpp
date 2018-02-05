//============================================================================
// Name        : ga.cpp
// Author      : Sushil J Louis
//Modified BY  : Biplav Timalsina
// Version     :
// Copyright   : Copyright University of Nevada, Reno
// Description : GA in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "utils.h"
#include <population.h>
#include <ga.h>
#include <random.h>
#include <string.h>

using namespace std;
using namespace ga;

//extern double ordinates[MAX_CHROM_LENGTH][2];

int main(int argc, char *argv[]) {
	/*
	int randomSeed[]={100,200};
	float px_ar[]={0.5,0.99,0.67};
	float pm_ar[]={0.001,0.01,0.1};
	int popSize_ar[]={100,50};
	int maxGens_ar[]={300,500};
	for(int i=0;i<2;i++){
		for(int j=0;i<3;j++){
			for (int k=0;k<3;k++){
				for (int l=0;l<2;l++){
					for(int m=0;m<2;m++){
						GA ga = GA(argc, argv, randomSeed[i],px_ar[j],pm_ar[k],popSize_ar[l],maxGens_ar[m]);
						ga.init();
						ga.run();
						ga.report();
					}
				}
			}
		}
	}
	*/
						GA ga = GA(argc, argv);
						ga.init();
						ga.run();
						ga.report();
	

	return 0;
}

//GA::GA(int argc, char *argv[], int seed, float px, float pm, int popSize, int maxGens){
 GA::GA(int argc, char *argv[]){
	setupOptions(argc, argv);
	srandom(options.randomSeed);
	ofstream ofs(options.outfile, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	ofstream pofs(options.phenotypeFile, std::ofstream::out | std::ofstream::trunc);
	pofs.close();
	maxFitGen = 0;
	this->bestIndividualSoFar = new Individual(options.chromLength);
	bestFitnessSoFar = -1;


}


void GA::init(){
	//read the coordinates of different locations
	/*std::ifstream file("burma14.tsp");
	int i,x,y;
	while(!file.eof()){
		file>>i;
		file>>x;
		file>>y;
		ordinates[i][0]=x;
		ordinates[i][1]=y;
		cout<<"i="<<i<<"x="<<x<<"y="<<y<<endl;
	}
*/

	parent = new Population(options);
	child  = new Population(options);
	parent->initialize(); // evaluates, stats, and reports on initial population
	updateProgress(0, parent);
//	cout << "initialized" << endl;
}



//
//void GA::CHC(Population *p, Population *c){
//}

void GA::run(){//chc

	Population *tmp;
	for (unsigned int i = 1; i < options.maxgens; i++){
	  		parent->chc(child);
	        //parent->generation(child);

		child->statistics();
		child->report(i);

		updateProgress(i, child);

		tmp = parent;
		parent = child;
		child = tmp;
		//cout << "Generation: " << i << endl;
	}
	

}

/**
 * Update and save the best ever individual
 */
void GA::updateProgress(unsigned int gen, Population *p){

  if (p->max > bestFitnessSoFar){
    bestFitnessSoFar = p->max;
    maxFitGen = gen;
    bestIndividualSoFar->copy(p->pop[p->maxi]);
    
    char printbuf[1024];
    char chromString[MAX_CHROM_LENGTH+1];
    chromToString(bestIndividualSoFar->chrom, bestIndividualSoFar->length, chromString);
    sprintf(printbuf, "%4i \t %f \t %s\n", maxFitGen, bestFitnessSoFar, chromString);
    writeBufToFile(printbuf, options.phenotypeFile);
  }/*
  if(p->min < bestFitnessSoFar){
  	bestFitnessSoFar=p->min;
  	maxFitGen=gen;
  	bestIndividualSoFar->copy(p->pop[p->mini]);

  	char printbuf[1024];
    char chromString[MAX_CHROM_LENGTH+1];
    chromToString(bestIndividualSoFar->chrom, bestIndividualSoFar->length, chromString);
    sprintf(printbuf, "%4i \t %f \t %s\n", maxFitGen, bestFitnessSoFar, chromString);
    writeBufToFile(printbuf, options.phenotypeFile);
  }*/
  
}


void GA::report(){
  //parent->report(options.maxgens);
  cout << *(parent->pop[parent->maxi])<<"\t" << endl;
	//cout<<*(parent->pop[parent->mini])<<endl;
  /*
  for(int i=0;i<options.chromLength;i++){
  	cout<<pop[parent->maxi]->chrom[i]<<"\t";
  }
  cout<<endl;
	*/
}

void GA::configure(){
	ifstream ifs(options.infile);
	if(ifs.good()){
		ifs >> options.popSize;
		ifs >> options.chromLength;
		ifs >> options.maxgens;
		ifs >> options.px;
		ifs >> options.pm;
		ifs >> options.scaler;
		ifs >> options.lambda;
	}
	ifs.close();
}

//void GA::setupOptions(int argc, char *argv[],int seed,float px,float pm,int popsize,int maxGens){
void GA::setupOptions(int argc, char *argv[]){
	options.randomSeed =189;
	options.infile = string("infile");
	options.outfile = string("outfile_189");// append randomseed to output file names

	options.popSize = 1000;
	options.chromLength = 52;		//number of cities
	options.maxgens = 1000;
	options.px = 0.99f;
	options.pm = 0.1f;
	options.scaler = 1.05;
	options.lambda = 2;
	options.nCriteria   = 1;

	options.mutator = Mutator::Flip;
	options.xover = Xover::UX;
	options.selector = Selector::Proportionate;

	if(argc == 4){
		options.infile = string(argv[1]);
		options.outfile = string(argv[2]);
		options.randomSeed = atoi(argv[3]);
		configure();
	}
	//derived values go after configure() above
	options.phenotypeFile   = string(options.outfile + ".pheno"); //derived from options.outfile
	//options.maxgens = options.popSize * 1.5;


}


