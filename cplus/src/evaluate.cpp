/*
 * evaluate.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: sushil
 */

#include <evaluate.h>
#include <utils.h>
#include <const.h>

#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;



void evaluate(ga::Individual *ent){
//	cout << *ent << endl;
	double sum = 0;
	for(int i = 0; i < ent->length; i++){
		sum += ent->chrom[i];
	}
	ent->fit = sum;
	for(int i = 0; i < ga::MAX_CRITERIA; i++){
		ent->fitness[i] = sum;
	}

	cout << "----------------------------------------" << endl;

}

double decode(int * chrom, int start, int end){
  double prod = 0;
  for (int i = start; i < end; i++){
    prod += (chrom[i] == 0 ? 0 : pow(2.0, (double) i));
  }
  return prod;
}

void xSquared(ga::Individual *ent) {
  int value = decode(ent->chrom, 0, ent->length);
  ent->fit = value * value;
  return;

}

void total_distance(ga::Individual *ent){
/*
	 //Burma tour
	double val[14][2]= {{16.47,96.10},
						{16.47,94.44},
						{20.09,92.54},
						{22.39,93.37},
						{25.23,97.24},
						{22.00,96.05},
						{20.47,97.02},
						{17.20,96.29},
						{16.30,97.38},
						{14.05,98.12},
						{16.53,97.38},
						{21.52,95.59},
						{19.41,97.13},
						{20.09,94.55}};//
						*/
	 // berlin tour
double val[52][2]={{565.0, 575.0},
					 {25.0, 185.0},
					 {345.0, 750.0},
					 {945.0, 685.0},
					 {845.0 ,655.0},
					 {880.0 ,660.0},
					 {25.0, 230.0},
					 {525.0, 1000.0},
					 {580.0, 1175.0},
					 {650.0, 1130.0},
					 {1605.0, 620.0},
					 {1220.0, 580.0},
					 {1465.0, 200.0},
					 {1530.0, 5.0},
					 {845.0, 680.0},
					 {725.0, 370.0},
					 {145.0, 665.0},
					 {415.0, 635.0},
					 {510.0, 875.0 }, 
					 {560.0, 365.0},
					 {300.0, 465.0},
					 {520.0, 585.0},
					 {480.0, 415.0},
					 {835.0, 625.0},
					 {975.0, 580.0},
					 {1215.0, 245.0},
					 {1320.0, 315.0},
					 {1250.0, 400.0},
					 {660.0, 180.0},
					 {410.0, 250.0},
					 {420.0, 555.0},
					 {575.0, 665.0},
					 {1150.0, 1160.0},
					 {700.0, 580.0},
					 {685.0, 595.0},
					 {685.0, 610.0},
					 {770.0, 610.0},
					 {795.0 ,645.0},
					 {720.0, 635.0},
					 {760.0, 650.0},
					 {475.0, 960.0},
					 {95.0, 260.0},
					 {875.0, 920.0},
					 {700.0, 500.0},
					 {555.0, 815.0},
					 {830.0, 485.0},
					 {1170.0, 65.0},
					 {830.0, 610.0},
					 {605.0, 625.0},
					 {595.0, 360.0},
					 {1340.0, 725.0},
					{ 1740.0, 245.0}};

	/*
//eil51
	double val[51][2]={ {37, 52},
						 {49, 49},
						 {52 ,64},
						 {20, 26},
						 {40, 30},
						 {21, 47},
						 {17, 63},
						 {31, 62},
						 {52, 33},
						 {51, 21},
						 {42, 41},
						 {31, 32},
						 {5, 25},
						{12, 42},
						 {36, 16},
						 {52, 41},
						 {27, 23},
						 {17, 33},
						 {13, 13},
						 {57, 58},
						 {62, 42},
						 {42, 57},
						 {16, 57},
						 {8, 52},
						 {7, 38},
						 {27, 68},
						 {30, 48},
						 {43, 67},
						 {58, 48},
						 {58, 27},
						 {37, 69},
						 {38, 46},
						 {46, 10},
						 {61, 33},
						 {62, 63},
						 {63, 69},
						 {32, 22},
						 {45, 35},
						 {59, 15},
						 {5, 6},
						 {10, 17},
						 {21, 10},
						 {5, 64},
						 {30, 15},
						 {39, 10},
						 {32, 39},
						 {25, 32},
						 {25, 55},
						 {48, 28},
						 {56, 37},
						 {30, 40}};
*/
	/*
	//eli76
	double val[76][2]={ {22, 22},
						 {36, 26},
						 {21, 45},
						 {45, 35},
						 {55, 20},
						 {33, 34},
						 {50, 50},
						 {55, 45},
						 {26, 59},
						 {40, 66},
						 {55, 65},
						 {35, 51},
						 {62, 35},
						 {62, 57},
						 {62, 24},
						 {21, 36},
						 {33, 44},
						 {9, 56},
						 {62, 48},
						 {66, 14},
						 {44, 13},
						 {26, 13},
						 {11, 28},
						 {7, 43},
						 {17, 64},
						 {41, 46},
						 {55, 34},
						 {35, 16},
						 {52, 26},
						 {43, 26},
						 {31, 76},
						 {22, 53},
						 {26, 29},
						 {50, 40},
						 {55, 50},
						 {54, 10},
						 {60, 15},
						 {47, 66},
						 {30, 60},
						 {30, 50},
						 {12, 17},
						 {15, 14},
						 {16, 19},
						 {21, 48},
						 {50 ,30},
						 {51, 42},
						 {50, 15},
						 {48, 21},
						 {12, 38},
						 {15, 56},
						 {29, 39},
						 {54, 38},
						 {55, 57},
						 {67, 41},
						 {10, 70},
						 {6, 25},
						 {65, 27},
						 {40, 60},
						 {70, 64},
						 {64, 4},
						 {36, 6},
						 {30, 20},
						 {20, 30},
						 {15, 5},
						 {50, 70},
						 {57, 72},
						 {45, 42},
						 {38, 33},
						 {50, 4},
						 {66, 8},
						 {59, 5},
						 {35, 60},
						 {27, 24},
						 {40, 20},
						 {40, 37},
						 {40, 40}};

						 */
	/*					 
double val[105][2]={{63,	71},
					{94,	71},
					{142,	370},
					{173,	1276},
					{205,	1213},
					{213,	69},
					{244,	69},
					{276,	630},
					{283,	732},
					{362,	69},
					{394,	69},
					{449,	370},
					{480,	1276},
					{512,	1213},
					{528,	157},
					{583,	630},
					{591,	732},
					{638,	654},
					{638,	496},
					{638,	314},
					{638,	142},
					{669,	142},
					{677,	315},
					{677,	496},
					{677,	654},
					{709,	654},
					{709,	496},
					{709,	315},
					{701,	142},
					{764,	220},
					{811,	189},
					{843,	173},
					{858,	370},
					{890,	1276},
					{921,	1213},
					{992,	630},
					{1000,	732},
					{1197,	1276},
					{1228,	1213},
					{1276,	205},
					{1299,	630},
					{1307,	732},
					{1362,	654},
					{1362,	496},
					{1362,	291},
					{1425,	654},
					{1425,	496},
					{1425,	291},
					{1417,	173},
					{1488,	291},
					{1488,	496},
					{1488,	654},
					{1551,	654},
					{1551,	496},
					{1551,	291},
					{1614,	291},
					{1614,	496},
					{1614,	654},
					{1732,	189},
					{1811,	1276},
					{1843,	1213},
					{1913,	630},
					{1921,	732},
					{2087,	370},
					{2118,	1276},
					{2150,	1213},
					{2189,	205},
					{2220,	189},
					{2220,	630},
					{2228,	732},
					{2244,	142},
					{2276,	315},
					{2276,	496},
					{2276,	654},
					{2315,	654},
					{2315,	496},
					{2315,	315},
					{2331,	142},
					{2346,	315},
					{2346,	496},
					{2346,	654},
					{2362,	142},
					{2402,	157},
					{2402,	220},
					{2480,	142},
					{2496,	370},
					{2528,	1276},
					{2559,	1213},
					{2630,	630},
					{2638,	732},
					{2756,	69},
					{2787,	69},
					{2803,	370},
					{2835,	1276},
					{2866,	1213},
					{2906,	69},
					{2937,	69},
					{2937,	630},
					{2945,	732},
					{3016,	1276},
					{3055,	69},
					{3087,	69},
					{606,	220},
					{1165,	370},
					{1780,	370}};
					*/
/*
	double val[318][2]={
						{63,71},
						{94,71},
						{142,370},
						{173,1276},
						{205,1213},
						{213,69},
						{244,69},
						{276,630},
						{283,732},
						{362,69},
						{394,69},
						{449,370},
						{480,1276},
						{512,1213},
						{528,157},
						{583,630},
						{591,732},
						{638,654},
						{638,496},
						{638,314},
						{638,142},
						{669,142},
						{677,315},
						{677,496},
						{677,654},
						{709,654},
						{709,496},
						{709,315},
						{701,142},
						{764,220},
						{811,189},
						{843,173},
						{858,370},
						{890,1276},
						{921,1213},
						{992,630},
						{1000,732},
						{1197,1276},
						{1228,1213},
						{1276,205},
						{1299,630},
						{1307,732},
						{1362,654},
						{1362,496},
						{1362,291},
						{1425,654},
						{1425,496},
						{1425,291},
						{1417,173},
						{1488,291},
						{1488,496},
						{1488,654},
						{1551,654},
						{1551,496},
						{1551,291},
						{1614,291},
						{1614,496},
						{1614,654},
						{1732,189},
						{1811,1276},
						{1843,1213},
						{1913,630},
						{1921,732},
						{2087,370},
						{2118,1276},
						{2150,1213},
						{2189,205},
						{2220,189},
						{2220,630},
						{2228,732},
						{2244,142},
						{2276,315},
						{2276,496},
						{2276,654},
						{2315,654},
						{2315,496},
						{2315,315},
						{2331,142},
						{2346,315},
						{2346,496},
						{2346,654},
						{2362,142},
						{2402,157},
						{2402,220},
						{2480,142},
						{2496,370},
						{2528,1276},
						{2559,1213},
						{2630,630},
						{2638,732},
						{2756,69},
						{2787,69},
						{2803,370},
						{2835,1276},
						{2866,1213},
						{2906,69},
						{2937,69},
						{2937,630},
						{2945,732},
						{3016,1276},
						{3055,69},
						{3087,69},
						{606,220},
						{1165,370},
						{1780,370},
						{63,1402},
						{94,1402},
						{142,1701},
						{173,2607},
						{205,2544},
						{213,1400},
						{244,1400},
						{276,1961},
						{283,2063},
						{362,1400},
						{394,1400},
						{449,1701},
						{480,2607},
						{512,2544},
						{528,1488},
						{583,1961},
						{591,2063},
						{638,1985},
						{638,1827},
						{638,1645},
						{638,1473},
						{669,1473},
						{677,1646},
						{677,1827},
						{677,1985},
						{709,1985},
						{709,1827},
						{709,1646},
						{701,1473},
						{764,1551},
						{811,1520},
						{843,1504},
						{858,1701},
						{890,2607},
						{921,2544},
						{992,1961},
						{1000,2063},
						{1197,2607},
						{1228,2544},
						{1276,1536},
						{1299,1961},
						{1307,2063},
						{1362,1985},
						{1362,1827},
						{1362,1622},
						{1425,1985},
						{1425,1827},
						{1425,1622},
						{1417,1504},
						{1488,1622},
						{1488,1827},
						{1488,1985},
						{1551,1985},
						{1551,1827},
						{1551,1622},
						{1614,1622},
						{1614,1827},
						{1614,1985},
						{1732,1520},
						{1811,2607},
						{1843,2544},
						{1913,1961},
						{1921,2063},
						{2087,1701},
						{2118,2607},
						{2150,2544},
						{2189,1536},
						{2220,1520},
						{2220,1961},
						{2228,2063},
						{2244,1473},
						{2276,1646},
						{2276,1827},
						{2276,1985},
						{2315,1985},
						{2315,1827},
						{2315,1646},
						{2331,1473},
						{2346,1646},
						{2346,1827},
						{2346,1985},
						{2362,1473},
						{2402,1488},
						{2402,1551},
						{2480,1473},
						{2496,1701},
						{2528,2607},
						{2559,2544},
						{2630,1961},
						{2638,2063},
						{2756,1400},
						{2787,1400},
						{2803,1701},
						{2835,2607},
						{2866,2544},
						{2906,1400},
						{2937,1400},
						{2937,1961},
						{2945,2063},
						{3016,2607},
						{3055,1400},
						{3087,1400},
						{606,1551},
						{1165,1701},
						{1780,1701},
						{3,2733},
						{94,2733},
						{142,3032},
						{173,3938},
						{205,3875},
						{213,2731},
						{244,2731},
						{276,3292},
						{283,3394},
						{362,2731},
						{394,2731},
						{449,3032},
						{480,3938},
						{512,3875},
						{528,2819},
						{583,3292},
						{591,3394},
						{638,3316},
						{638,3158},
						{638,2976},
						{638,2804},
						{669,2804},
						{677,2977},
						{677,3158},
						{677,3316},
						{709,3316},
						{709,3158},
						{709,2977},
						{701,2804},
						{764,2882},
						{811,2851},
						{843,2835},
						{858,3032},
						{890,3938},
						{921,3875},
						{992,3292},
						{1000,3394},
						{1197,3938},
						{1228,3875},
						{1276,2867},
						{1299,3292},
						{1307,3394},
						{1362,3316},
						{1362,3158},
						{1362,2953},
						{1425,3316},
						{1425,3158},
						{1425,2953},
						{1417,2835},
						{1488,2953},
						{1488,3158},
						{1488,3316},
						{1551,3316},
						{1551,3158},
						{1551,2953},
						{1614,2953},
						{1614,3158},
						{1614,3316},
						{1732,2851},
						{1811,3938},
						{1843,3875},
						{1913,3292},
						{1921,3394},
						{2087,3032},
						{2118,3938},
						{2150,3875},
						{2189,2867},
						{2220,2851},
						{2220,3292},
						{2228,3394},
						{2244,2804},
						{2276,2977},
						{2276,3158},
						{2276,3316},
						{2315,3316},
						{2315,3158},
						{2315,2977},
						{2331,2804},
						{2346,2977},
						{2346,3158},
						{2346,3316},
						{2362,2804},
						{2402,2819},
						{2402,2882},
						{2480,2804},
						{2496,3032},
						{2528,3938},
						{2559,3875},
						{2630,3292},
						{2638,3394},
						{2756,2731},
						{2787,2731},
						{2803,3032},
						{2835,3938},
						{2866,3875},
						{2906,2731},
						{2937,2731},
						{2937,3292},
						{2945,3394},
						{3016,3938},
						{3055,2731},
						{3087,2731},
						{606,2882},
						{1165,3032},
						{1780,3032},
						{1417,-79},
						{1496,-79},
						{1693,4055}};
*/





	long double dist=0;
	double valuex1=val[ent->chrom[0]][0];		//x coordinate of first location
	double valuey1=val[ent->chrom[0]][1];		//y coordinate of first location
	double valuex=0;
	double valuey=0;
	double valuex2=0;
	double valuey2=0;
	/*
	cout<<"route======"<<endl;
	for(int i=0;i<ent->length;i++){
		cout<<ent->chrom[i]<<"\t";
	}
	cout<<endl;
	*/

	for(int i=1;i<ent->length;i++){
		valuex2=val[ent->chrom[i]][0];
		valuey2=val[ent->chrom[i]][1];
		valuex=valuex2-valuex1;
		valuey=valuey2-valuey1;
		long double temp_dist1=valuex*valuex+valuey*valuey;
		//cout<<"temp_dist="<<temp_dist1<<endl;
		dist+=pow((long double)temp_dist1,0.5);
			
		//cout<<"x1="<<valuex1<<"\t"<<"y1="<<valuey1<<"\tx2="<<valuex2<<"\ty2="<<valuey2<<"\tx="<<valuex<<"\t y="<<valuey<<"\t dist="<<dist<<endl;	
		valuex1=valuex2;
		valuey1=valuey2;
	}
	//adding distance between 14th and 1st place
	valuex2=val[ent->chrom[0]][0];
	valuey2=val[ent->chrom[0]][1];
	valuex=valuex2-valuex1;
	valuey=valuey2-valuey1;
	long double temp_dist1=valuex*valuex+valuey*valuey;
	//cout<<"temp_dist="<<temp_dist1<<endl;
	//cout<<"_____x1="<<valuex1<<"\t"<<"y1="<<valuey1<<"\tx2="<<valuex2<<"\ty2="<<valuey2<<"\tx="<<valuex<<"\t y="<<valuey<<endl;	
	//cout<<"temp_dist1=="<<pow((long double)temp_dist1,0.5)<<endl;
	dist+=pow((long double)temp_dist1,0.5);
	//cout<<"*****************distance="<<dist<<endl;
	ent->fit=1/dist;
}
