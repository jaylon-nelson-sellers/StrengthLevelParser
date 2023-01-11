#include <sstream> 
#include "set.h"

Set::Set() {
	date;
	exercise = " ";
	liftMass = 0;
	repetitions = 0;
	bodyMass = 0;
	percentile = 0;
	E1RM = 0;
	warmup = 0;
	lbKg = 0;
}

Set::Set(bool lbkg) {
	date;
	exercise = " ";
	liftMass = 0;
	repetitions = 0;
	bodyMass = 0;
	percentile = 0;
	E1RM = 0;
	warmup = 0;
	this->lbKg = lbkg;
}

void Set::setDate(string sDate) {
	stringstream ss(sDate);
	string substr;
	for (int i = 0; i < 3; i++) {
		getline(ss, substr, '-');
		date[i] = stoi(substr);
	}
}

array<int,3> Set::getDate() {
	array<int,3> copyDate;
	std::copy(std::begin(date), std::end(date), std::begin(copyDate));
	return copyDate;
}


void Set::setExercise(string exercise) {
	this->exercise = exercise;
}

string Set::getExercise() {
	return exercise;
}

void Set::swapLbKg() {

}

int Set::getLbKg() {
	return lbKg;
}

string Set::printLbKg() {
	if (lbKg == 0) return "lbs.";
	else return "kg.";
}


void Set::setLiftMass(string liftMass) {
	this->liftMass = stoi(liftMass);
}

double Set::getLiftMass() {
	return liftMass;
}

void Set::setRepetitions(string repetitions) {
	this->repetitions = stoi(repetitions);
}

int Set::getRepetitions() {
	return repetitions;
}

void Set::setBodyMass(string bodyMass) {
	this->bodyMass = stoi(bodyMass);
}

double Set::getBodyMass() {
	return bodyMass;
}

void Set::setPercentile(string percentile) {
	this->percentile = stoi(percentile);
}

double Set::getPercentile() {
	return percentile;
}

void Set::setWarmup(string warmup) {
	this->warmup = stoi(warmup);
}

int Set::getWarmup() {
	return warmup;
}

void Set::bodyweightExercises() {
	liftMass = abs(bodyMass + liftMass);
	calcE1RM();
}

void Set::calcE1RM() {
	if (repetitions == -1) {
		E1RM = -1;
	}

	if (repetitions == 1) {
		E1RM = liftMass;
	}
	else {
		E1RM = liftMass / (1.0278 - (0.0278 * repetitions));
	}
}

int Set::getE1RM() {
	calcE1RM();
	return E1RM;
}

int Set::checkDate(Set tempSet) {
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

bool Set::operator< (const Set& tempSet) const
{
	return (E1RM< tempSet.E1RM);
}

bool Set::operator==(const Set set1) {
	if (date[0] == set1.date[0] &&
		date[1] == set1.date[1] &&
		date[2] == set1.date[2] &&
		exercise == set1.exercise &&
		lbKg == set1.lbKg &&
		liftMass == set1.liftMass &&
		repetitions == set1.repetitions &&
		bodyMass == set1.bodyMass &&
		percentile == set1.percentile &&
		E1RM == set1.E1RM &&
		warmup == set1.warmup)
		return true;
}

ostream& operator<<(ostream& out, const Set& set) {
	out << "Date" << ": ";
	out << set.date[0] << "/" << set.date[1] << "/";
	out << set.date[2] << " |";

	out << " Set: " << set.liftMass;
	if (set.lbKg) out << " kg. ";
	else out << " lbs." << " x ";

	out << set.repetitions << " Reps |";
	if (set.lbKg) out << " kg. |";

	out << " Estimated 1RM: " << set.E1RM;
	out << " @ " << set.percentile << "%";
	
	return out;
}