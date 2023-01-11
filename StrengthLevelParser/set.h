#ifndef SET_H
#define SET_H
#include <array>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;
/**Set Class
* Creates a set from a workout log
*/
class Set {
public:

	Set();

	Set(bool weight);

	void setDate(string date);

	array<int, 3> getDate();

	void setExercise(string exercise);

	string getExercise();

	int getLbKg();

	void swapLbKg();

	string printLbKg();

	void setLiftMass(string liftMass);

	double getLiftMass();

	void setRepetitions(string repetitions);

	int getRepetitions();

	void setBodyMass(string bodyMass);

	double getBodyMass();

	void setPercentile(string percentile);

	double getPercentile();

	void setWarmup(string warmup);

	int getWarmup();

	void bodyweightExercises();

	void calcE1RM();

	int getE1RM();

	int checkDate(Set tempSet);


	bool operator<(const Set& setToBeCompared) const;

	bool operator==(const Set set1);

	bool operator!=(const Set set1);

	friend ostream& operator<<(ostream& out, const Set& set);

private:
	array<int, 3> date;
	string exercise;
	int lbKg;
	double liftMass;
	int repetitions;
	double bodyMass;
	double percentile;
	double E1RM;
	int warmup;
};
#endif
