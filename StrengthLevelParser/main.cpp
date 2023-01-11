#include <iostream>
#include <sstream> 
#include <fstream>
#include <string>
#include <vector>
#include "exercise.h"
#include "set.h"

using namespace std;

vector<Set> sets;
vector<WorkingSets> workingSets;
vector<Exercise> exercises;

void addSetsToExercises() {
    bool notFound = true;

    for (auto& set : sets) {
        notFound = true;
        if (exercises.size() == 0) {
            Exercise tempExercise(set.getExercise(), 3, 6);
            tempExercise.addSet(set);
            exercises.push_back(tempExercise);
        }
        for (auto& exercise : exercises) {
            if (set.getExercise() == exercise.getName()) {
                exercise.addSet(set);
                notFound = false;
            }
        }
        if (notFound) {
            Exercise tempExercise(set.getExercise(), 3, 6);
            tempExercise.addSet(set);
            exercises.push_back(tempExercise);
        }
    }

    for (auto& wSets : workingSets) {
        for (auto& exercise : exercises) {
            if (wSets.getExercise() == exercise.getName()) {
                exercise.addWorkingSets(wSets);
            }
        }
    }

    sort(exercises.begin(), exercises.end(), [](Exercise& lhs, Exercise& rhs) {
        return lhs.getName() < rhs.getName();
        });


}

void createWorkingSets() {
    WorkingSets tempSets;
    for (auto& set : sets) {
        if (set.getWarmup() == 1) {
            continue;
        }
        if (tempSets.isSame(set) && set.getWarmup() != 1) {
            tempSets.addSet(set);
        }
        else {
            if (tempSets.isEmpty() && set.getWarmup() != 1) {
                tempSets.addSet(set);
            }
            else {
                workingSets.push_back(tempSets);
                tempSets.clear();
                tempSets.addSet(set);
            }


        }

    }

}


void read_record()
{
    ifstream myFile("data.csv");

    if (!myFile.is_open()) {
        cerr << "No file" << endl;
        exit(1);
    }
    bool first = true;

    //Sets Information
    while (myFile.good()) {

        Set tempSet(false);
        string line;
        if (first) {
            getline(myFile, line);
            first = false;
            continue;
        }
        getline(myFile, line, ',');
        tempSet.setDate(line);

        getline(myFile, line, ',');
        tempSet.setExercise(line);

        getline(myFile, line, ',');

        getline(myFile, line, ',');
        tempSet.setLiftMass(line);

        getline(myFile, line, ',');
        tempSet.setRepetitions(line);

        getline(myFile, line, ',');

        getline(myFile, line, ',');
        tempSet.setBodyMass(line);

        getline(myFile, line, ',');
        tempSet.setPercentile(line);

        getline(myFile, line);
        tempSet.setWarmup(line);

        tempSet.calcE1RM();

        if (tempSet.getExercise() == "Pull Ups" ||
            tempSet.getExercise() == "Chin Ups" ||
            tempSet.getExercise() == "One Arm Pull Ups" ||
            tempSet.getExercise() == "Inverted Row" ||
            tempSet.getExercise() == "Dips") {
            tempSet.bodyweightExercises();
        }

        sets.push_back(tempSet);

    }
}


void core(bool convSumoPick) {
    for (auto& exercise : exercises) {
        bool benchFound = false;
        bool OHP2Found = false;

        bool pullUpFound = false;
        bool Row2Found = false;
        
        bool deadliftFound = false;
        bool squatFound = false;
        
       
        bool OHPFound = false;
        bool bench2Found = false;
        
        bool RowFound = false;
        bool pullUp2Found = false;

        bool squat2Found = false;
        bool deadlift2Found = false;

        if (!benchFound & exercise.getName() == "Bench Press") {
            benchFound = true;
            cout << exercise << endl;
        }

        if (!OHP2Found & exercise.getName() == "Dumbbell Shoulder Press") {
            OHP2Found = true;
            cout << exercise << endl;
        }

        if (!pullUpFound & exercise.getName() == "Pull Ups") {
            pullUpFound = true;
            cout << exercise << endl;
        }

        if (!Row2Found & exercise.getName() == "Seated Cable Row") {
            Row2Found = true;
            cout << exercise << endl;
        }

    
        if (!deadliftFound & exercise.getName() == "Sumo Deadlift") {
            deadliftFound = true;
            cout << exercise << endl; 
        }

        if (!squat2Found & exercise.getName() == "Front Squat") {
            squat2Found = true;
            cout << exercise << endl;
        }

        if (!OHPFound & exercise.getName() == "Shoulder Press") {
            OHPFound = true;
            cout << exercise << endl;
        }

        if (!bench2Found & exercise.getName() == "Incline Bench Press") {
            bench2Found = true;
            cout << exercise << endl;
        }

        if (!RowFound & exercise.getName() == "Pendlay Row") {
            RowFound = true;
            cout << exercise << endl;
        }
       
        if (!pullUp2Found & exercise.getName() == "Chin Ups") {
            pullUp2Found = true;
            cout << exercise << endl;
        }

        if (!squatFound & exercise.getName() == "Squat") {
            squatFound = true;
            cout << exercise << endl;
        }

        if (!deadlift2Found & exercise.getName() == "Deadlift") {
            deadlift2Found = true;
            cout << exercise << endl;
        }

        

    }
    cout << endl << endl << endl;
}

void outputWorkingSets() {
    ofstream myfile("wSetsResults.csv");
    int vsize = workingSets.size();

    myfile << "Date" << ",";
    myfile << "Exercise" << ",";
    myfile << "Sets" << ",";
    myfile << "Repetitions" << ",";
    myfile << "Weight Avg" << ",";
    myfile << "Working 1 Rep Max" << ",";
    myfile << "Percentile" << endl;


    for (int n = 0; n < vsize; n++)
    {
        myfile << workingSets.at(n).getDate()[0] << "/";
        myfile << workingSets.at(n).getDate()[1] << "/";
        myfile << workingSets.at(n).getDate()[2] << ",";
        myfile << workingSets.at(n).getExercise() << ",";
        myfile << workingSets.at(n).getSets() << ",";
        myfile << workingSets.at(n).getRepAverage() << ",";
        myfile << workingSets.at(n).getWeightAverage() << ",";
        myfile << workingSets.at(n).getW1RM() << ",";
        myfile << workingSets.at(n).getPercentileAverage() << ",";
        myfile << endl;
    }
}


int main()
{
    read_record();
    createWorkingSets();
    addSetsToExercises();
    core(true);
    for (auto exercise : exercises) {
        cout << exercise << endl;
    }
    outputWorkingSets();
}

