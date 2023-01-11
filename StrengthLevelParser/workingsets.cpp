#include "workingsets.h"
WorkingSets::WorkingSets() {
	date[0] = 0;
	date[1] = 0;
	date[2] = 0;
	exercise = " ";
	weightAverage = 0;
	repAverage = 0;
	W1RM = 0;
	percentileAverage = 0;
	empty = true;
	lbkg = 0;
}


WorkingSets::WorkingSets(Set& initSet) {
	date = initSet.getDate();
	exercise = initSet.getExercise();
	setsAcross.push_back(initSet);
	maxWeight = initSet.getLiftMass();
	volume = initSet.getLiftMass() * initSet.getRepetitions();
	weightAverage = initSet.getLiftMass();
	repAverage = initSet.getRepetitions();
	W1RM = initSet.getE1RM();
	percentileAverage = initSet.getPercentile();
	lbkg = initSet.getLbKg();
	empty = false;
}

WorkingSets::~WorkingSets() {
	clear();
}

string WorkingSets::getExercise() {
	return exercise;
}

bool WorkingSets::isEmpty() {
	return empty;
}

bool WorkingSets::isSame(Set tempSet) {
	if (tempSet.getDate() == getDate() && tempSet.getExercise() == getExercise())
		return true;

	return false;
}

array<int,3> WorkingSets::getDate() {
	array<int,3> copyDate;
	std::copy(std::begin(date), std::end(date), std::begin(copyDate));
	return copyDate;
}

void WorkingSets::setDate(array<int,3> tempDate) {
	date = tempDate;
}

double WorkingSets::getWeightAverage() {
	return weightAverage;
}

double WorkingSets::getRepAverage() {
	return repAverage;
}

int WorkingSets::getSets() {
	return setsAcross.size();
}

double WorkingSets::getMaxWeight() {
	return maxWeight;
}

double WorkingSets::getVolume() {
	return volume;
}

double WorkingSets::getW1RM() {
	return W1RM;
}

double WorkingSets::getPercentileAverage() {
	return percentileAverage;
}

int WorkingSets::getLbKg()
{
	return lbkg;
}

void WorkingSets::addSet(Set tempSet) {
	if (!isEmpty() && !(exercise == tempSet.getExercise())) return;
	if (tempSet.getLbKg() != lbkg) tempSet.swapLbKg();
	
	setsAcross.push_back(tempSet);
	exercise = tempSet.getExercise();
	setDate(tempSet.getDate());

	repAverage = 0;
	percentileAverage = 0;
	weightAverage = 0;
	W1RM = 0;
	volume = 0;
	if (tempSet.getLiftMass() > maxWeight) {
		maxWeight = tempSet.getLiftMass();
	}

	for (auto& set : setsAcross) {
		
		weightAverage += set.getLiftMass();
		W1RM += set.getE1RM();
		
		repAverage += set.getRepetitions();
		percentileAverage += set.getPercentile();
		volume += set.getLiftMass() * set.getRepetitions();
	}

	weightAverage = floor(weightAverage / setsAcross.size());
	repAverage = floor(repAverage / setsAcross.size());
	W1RM = floor(W1RM / setsAcross.size());
	percentileAverage = percentileAverage / setsAcross.size();
	empty = false;
}

void WorkingSets::clear() {
	int date[3] = { -1,-1,-1 };
	exercise = " ";
	setsAcross.clear();
	weightAverage = -1;
	repAverage = -1;
	W1RM = -1;
	percentileAverage = -1;
	maxWeight = -1;
	volume = -1;
	empty = true;
}

int WorkingSets::checkDate(WorkingSets tempSet)
{
	if (date[0] > tempSet.date[0])
		return 1;

	if (date[0] == tempSet.date[0]) {
		if (date[1] > tempSet.date[1]) {
			return 1;
		}
	}

	if (date[0] == tempSet.date[0]) {
		if (date[1] == tempSet.date[1]) {
			if (date[2] > tempSet.date[2]) {
				return 1;
			}
		}
	}

	if (date[0] == tempSet.date[0]) {
		if (date[1] == tempSet.date[1]) {
			if (date[2] == tempSet.date[2]) {
				return 0;
			}
		}
	}

	return -1;



}

bool WorkingSets::operator< (const WorkingSets& tempSet) const
{
	return (W1RM < tempSet.W1RM);
}

ostream& operator<<(ostream& out, const WorkingSets& sets) {

	out << "Date: ";
	out << sets.date[0] << "/" << sets.date[1] << "/";
	std::cout << sets.date[2] << " | ";

	out << "Workout: ";
	out << sets.weightAverage;
	if (sets.lbkg) out << " kg. ";
	else out << " lb.";
	out << " x " << sets.setsAcross.size() << " Sets";
	out << " x " << sets.repAverage << " Reps | ";

	out << "Volume: " << sets.volume << " | ";

	out << "Working 1RM: " << sets.W1RM << " @ ";
	out << sets.percentileAverage << "%";

	return out;
}


