/*
 * individual.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: sushil
 */

#include <individual.h>
#include <stdlib.h>
#include <random.h>
#include <assert.h>

using namespace std;
using namespace ga;

Individual::Individual(){
	length    = 0;
	setup();
}

Individual::Individual(int len){
	length = len;
	setup();
}

void Individual::setup(){
	for(int i = 0; i < length; i++){
		this->chrom[i] = -1;
	}
}


void Individual::init(int len){
	assert(len <= MAX_CHROM_LENGTH);
	length = len;
	int copied_elements[length]={0};
	int elements_count=0;
	//cout<<"length="<<len<<endl;
	//generating cities' index at random, and making sure it is produced only once
	for(int i = 0; i < length;){
		//this->chrom[i] = flip(0.5);   //original code
		int temp=intInRange(0,length);
		//cout<<"temp="<<temp<<endl;
		if(copied_elements[temp]==0){
			this->chrom[i]=temp;
			copied_elements[temp]=1;
			elements_count++;
			i++;
		}
		if(elements_count==length) break;
	}
	/*
	for(int i=0;i<length;i++){
		cout<<this->chrom[i]<<"\t";
	}
	cout<<"**********************************************"<<endl;
	*/
	
}



void Individual::mutate(float prob){
	for(int i = 0; i < length; i++){
		/*if(flip(prob) == 1)
			chrom[i] = 1 - chrom[i];
	}*/
		//create swap function to implement swapping
		if(flip(prob)==1){
			int index1,index2,temp;
			index1=	intInRange(0,length);
			index2=intInRange(0,length);
			temp=chrom[index1];
			chrom[index1]=chrom[index2];
			chrom[index1]=temp;
	}
}
}

void Individual::copy(Individual *ip){
	assert(ip->length <= MAX_CHROM_LENGTH);
	this->length = ip->length;
	for(int i = 0; i < length; i++){
		this->chrom[i] = ip->chrom[i];
	}
	for(int i = 0; i < MAX_CRITERIA; i++){
		this->fitness[i] = ip->fitness[i];
		this->objectives[i] = ip->objectives[i];
	}
	this->fit = ip->fit;
	this->scaledFit = ip->scaledFit;
}

