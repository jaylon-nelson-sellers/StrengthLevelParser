#ifndef EXERCISE_H
#define EXERCISE_H

using namespace std;

#include <algorithm>
#include <string>
#include <vector>
#include "BST.h"
#include "set.h"
#include "workingsets.h"

class Exercise {
public:
	Exercise(string exerciseName, int workingSetMin, int cycleLength);

	string getName();

	int getE1RM();

	int getA1RM();

	int getW1RM();

	void addSet(Set tempSet);

	void addWorkingSets(WorkingSets tempSets);

	string outputSets();

	void simplifySets();

	string outputWorkingSets();

	void simplifyWorkingSets();

	void getProgression();

	void setRecentRecord();

	string getAverageWorkingSet();

	friend ostream& operator<<(ostream& out, Exercise& set);

private:
	string exerciseName;
	int workingSetMin;
	int cycleLength;
	double E1RM;
	double A1RM;
	double W1RM;
	double weightProgression;
	double progression;

	Set recentRecord;

	WorkingSets WorkingAverage;
	double averageWorkoutWeight;
	double averageWorkoutVolume;

	vector<Set> allSets;
	vector<Set> RepRecord;


	vector<WorkingSets> allWorkingSets;
	vector<WorkingSets> topWorkingSets;//1-15



};

#endif