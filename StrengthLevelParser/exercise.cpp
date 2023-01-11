#include "exercise.h"



Exercise::Exercise(string exerciseName, int workingSetMin, int cycleLength) {
	this->exerciseName = exerciseName;
	this->workingSetMin = workingSetMin;
	this->cycleLength = cycleLength;
	E1RM = 0;
	A1RM = 0;
	W1RM = 0;
}

string Exercise::getName() {
	return exerciseName;
}

int Exercise::getE1RM() {
	return E1RM;
}

int Exercise::getA1RM() {
	return A1RM;
}

int Exercise::getW1RM() {
	if (allWorkingSets.size() == 0) return 0;
	this->W1RM = 0;
	
	int minWorkingSet = cycleLength;

	if (allWorkingSets.size() < cycleLength) {
		minWorkingSet = allWorkingSets.size() - 1;
	}


	for (int i = 0; i < minWorkingSet; i++)
	{
		
		this->W1RM += allWorkingSets[i].getW1RM();
	
		
	}
	return W1RM/ minWorkingSet;
}

void Exercise::addSet(Set tempSet) {
	allSets.push_back(tempSet);


	if (tempSet.getLiftMass() > A1RM) {
		A1RM = tempSet.getLiftMass();
	}
	
	if(tempSet.getE1RM() > E1RM) {
		E1RM = tempSet.getE1RM();
	}

	if (RepRecord.size() == 0) {
		RepRecord.push_back(tempSet);
		return;
	}

	bool notFound = true;
	bool smaller = false;
	for (auto& repSet : RepRecord) {
		if (repSet.getRepetitions() == tempSet.getRepetitions()) {
			if (repSet < tempSet) {
				repSet = tempSet;
				notFound = false;
			}
			else
				smaller = true;
			continue;
		}
		else {
		}

	}
	if (notFound && !smaller) {
		RepRecord.push_back(tempSet);
	}
}


void Exercise::simplifySets() {
	sort(RepRecord.begin(), RepRecord.end(), [](Set& lhs, Set& rhs) {
		return lhs.getRepetitions() < rhs.getRepetitions();
		});

	for (unsigned int i = 0; i < RepRecord.size(); i++) {
		if (i == 0) {
			continue;
		}

		for (int j = i - 1; j >= 0; j--) {
			if ((RepRecord.at(i).getLiftMass() > RepRecord.at(j).getLiftMass()) &&
				(RepRecord.at(i).getRepetitions() > RepRecord.at(j).getRepetitions())) {

				RepRecord.erase(RepRecord.begin() + j);
				i--;
				continue;
			}

			if ((RepRecord.at(i).getLiftMass() == RepRecord.at(j).getLiftMass() &&
				(RepRecord.at(i).getRepetitions() > RepRecord.at(j).getRepetitions()))) {
				RepRecord.erase(RepRecord.begin() + j);
				i--;
				continue;
			}
		}
	}
}

void Exercise::simplifyWorkingSets() {
	sort(topWorkingSets.begin(), topWorkingSets.end(), [](WorkingSets& lhs, WorkingSets& rhs) {
		return lhs.getRepAverage() < rhs.getRepAverage();
		});

	for (unsigned int i = 0; i < topWorkingSets.size(); i++) {
		if (i == 0) {
			continue;
		}

		for (int j = i - 1; j >= 0; j--) {
			if ((topWorkingSets.at(i).getWeightAverage() > topWorkingSets.at(j).getWeightAverage()) &&
				(topWorkingSets.at(i).getRepAverage() > topWorkingSets.at(j).getRepAverage())) {

				topWorkingSets.erase(topWorkingSets.begin() + j);
				i--;
				continue;
			}

			if ((topWorkingSets.at(i).getWeightAverage() == topWorkingSets.at(j).getWeightAverage() &&
				(topWorkingSets.at(i).getRepAverage() > topWorkingSets.at(j).getRepAverage()))) {
				topWorkingSets.erase(topWorkingSets.begin() + j);
				i--;
				continue;
			}
		}
	}
}


void Exercise::addWorkingSets(WorkingSets tempSets) {
	if (tempSets.getSets() < workingSetMin) {
		return;
	}

	allWorkingSets.push_back(tempSets);
	bool notFound = true;
	bool smaller = false;
	for (auto& repSets : topWorkingSets) {
		if (repSets.getRepAverage() == tempSets.getRepAverage()) {
			if (repSets < tempSets) {
				repSets = tempSets;
				notFound = false;
			}
			else
				smaller = true;
			continue;
		}
		else {
		}

	}
	if (notFound && !smaller) {
		topWorkingSets.push_back(tempSets);
	}
}


void Exercise::getProgression() {
	int workouts = cycleLength;
	vector<double> delta;
	vector<double> weightDelta;
	int sizeOf = allWorkingSets.size();
	if (workouts > sizeOf) {
		workouts = sizeOf;
	}


	int i = sizeOf - 1;

	for (unsigned int k = 0; k < workouts; k++) {
		if (k + 1 >= sizeOf) {
			continue;
		}
		double tempWeight = allWorkingSets.at(k).getW1RM() - allWorkingSets.at(k + 1).getW1RM();

		double tempDelta = (allWorkingSets.at(k).getW1RM() - 
			allWorkingSets.at(k+1).getW1RM()) /
			allWorkingSets.at(k + 1).getW1RM();

		weightDelta.push_back(tempWeight);
		delta.push_back(tempDelta);
	}
	int deltaSize = delta.size();
	double average = 0;
	for (auto& d : delta) {
		average += d;
	}

	double weightAverage = 0;
	for (auto& d : weightDelta) {
		weightAverage += d;
	}
	progression = (average / deltaSize) * 100;
	weightProgression = weightAverage / deltaSize;
}

void Exercise::setRecentRecord() {
	recentRecord = RepRecord.at(0);
	for (auto& record : RepRecord) {
		if (recentRecord.checkDate(record) == -1) {
			recentRecord = record;
		}
	}
}

string Exercise::getAverageWorkingSet() {
	if (allWorkingSets.size() == 0) {
		return "No Sets";
	}
	int averageLength = cycleLength;

	if (averageLength > allWorkingSets.size()) 
		averageLength = allWorkingSets.size();
	
	averageLength--;

	if (averageLength == 0) {
		return "Not enough Sets";
	}

	string returnValue = "Date: ";

	array<int, 3> startDate = allWorkingSets.at(averageLength).getDate();
	array<int,3> endDate = allWorkingSets.at(0).getDate();
	

	for (int i = 0; i < 3; i++) {
		returnValue += to_string((startDate[i]));
		if (i != 2)
			returnValue += "/";
	}

	returnValue += " -> ";

	for (int i = 0; i < 3; i++) {
		returnValue += to_string((endDate[i]));
		if (i != 2)
			returnValue += "/";
	}

	returnValue += " | Set: ";

	int setAvg = 0;
	double repAvg = 0;
	double weightAvg = 0;
	double percentileAvg = 0;
	double volumeAvg = 0;

	for (int i = 0; i < averageLength; i++) {
		setAvg +=allWorkingSets.at(i).getSets();
		repAvg += allWorkingSets.at(i).getRepAverage();
		weightAvg += allWorkingSets.at(i).getWeightAverage();
		percentileAvg += allWorkingSets.at(i).getPercentileAverage();
		volumeAvg += allWorkingSets.at(i).getVolume();

	}

	setAvg /= averageLength;
	repAvg /= averageLength;
	weightAvg /= averageLength;
	percentileAvg /= averageLength;
	volumeAvg /= averageLength;

	setAvg = floor(setAvg);
	repAvg = floor(repAvg);
	weightAvg = floor(weightAvg);

	returnValue += to_string(setAvg);
	returnValue += " x ";
	returnValue += to_string(int(repAvg));
	returnValue += " Reps";
	returnValue += " @ ";
	returnValue += to_string(int(weightAvg));
	if (allWorkingSets.at(0).getLbKg()) returnValue += " kgs. ";
	else  returnValue += " lb. | ";

	returnValue += "Working 1RM: ";
	returnValue += to_string(getW1RM());
	returnValue += " @ ";
	returnValue += to_string(int(percentileAvg));
	returnValue += "%";

	averageWorkoutWeight = weightAvg;
	averageWorkoutVolume = volumeAvg;


	return returnValue;
}

ostream& operator<<(ostream& out, Exercise& exercise) {
	exercise.simplifySets();
	exercise.simplifyWorkingSets();
	exercise.setRecentRecord();
	exercise.getProgression();
	out << "/--------------------------------------------------\\";
	out << endl;
	out << "Exercise: " << exercise.exerciseName << endl << endl;
	out << endl;
	out << "-----Records: " << endl;
	out << "*All Time 1RM: " << exercise.A1RM << endl;
	out << endl;
	out << "*Estimated 1RM: " << exercise.E1RM << endl;
	out << endl;

	out << "*Most Recent Record: " << endl << exercise.recentRecord << endl;
	out << endl;
	out << "*Current Average Workout: " << endl << exercise.getAverageWorkingSet() << endl;

	out << endl;
	out << endl;
	out << "-----Intensification: " << endl;
	out << endl;
	out << "*Average Workout Weight: " << to_string(int(exercise.averageWorkoutWeight));
	if (exercise.allWorkingSets.size() != 0) {
		if (exercise.allWorkingSets.at(0).getLbKg()) out << " kgs. ";
		else  out << " lb. ";
	}
	out << endl;
	out << endl;
	out << "*Rep Records " << endl;
	for (auto& repSet : exercise.RepRecord) {
		out << repSet << endl;
	}
	out << endl;

	out << endl;
	out << "-----Volumization: " << endl;
	out << endl;
	out << "*Average Workout Volume: " << to_string(int(exercise.averageWorkoutVolume)) << endl;
	out << endl;

	out << "*Progression per workout: ";
	out << exercise.weightProgression;
	if (exercise.allWorkingSets.size() != 0) {
		if (exercise.allWorkingSets.at(0).getLbKg()) out << " kgs. ";
		else  out << " lb. ";
	}
	out << ": ";
	out << exercise.progression;
	out << "%" << endl;

	int minMax = 3;
	if (exercise.allWorkingSets.size() < 3)
		minMax = exercise.allWorkingSets.size();
	out << endl;
	out << "*Last Three Workouts: " << endl;
	for (int i = 0; i < minMax; i++) {
		out << exercise.allWorkingSets.at(i) << endl;
	}

	out << endl;
	
	out << "*Working Sets " << endl;
	for (auto& repSet : exercise.topWorkingSets) {
		out << repSet << endl;
	}
	out << endl;
	out << "\\--------------------------------------------------/" << endl;

	return out;
}