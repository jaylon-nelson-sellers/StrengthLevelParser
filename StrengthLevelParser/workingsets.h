#ifndef WORKING_SETS_H
#define WORKING_SETS_H

#include <string>
#include <cmath>
#include <iostream>
#include"set.h"
#include <vector>

using namespace std;

class WorkingSets {
public:

	WorkingSets();

	WorkingSets(Set& initSet);

	~WorkingSets();

	string getExercise();

	bool isEmpty();

	bool isSame(Set tempSet);

	void setDate(array<int,3> date);

	array<int, 3> getDate();

	double getWeightAverage();

	double getRepAverage();

	int getSets();

	double getMaxWeight();

	double getVolume();

	double getW1RM();

	double getPercentileAverage();

	int getLbKg();

	void addSet(Set tempSet);

	void clear();
	
	int checkDate(WorkingSets tempSet);

	bool operator< (const WorkingSets& tempSet) const;

	friend ostream& operator<<(ostream& out, const WorkingSets& set);

private:
	bool empty = true;
	array<int, 3> date;
	int lbkg;
	string exercise;
	vector<Set> setsAcross;
	double weightAverage;
	double repAverage;
	double maxWeight;
	double volume;
	double W1RM;
	double percentileAverage;

};
#endif
