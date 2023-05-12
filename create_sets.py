from workout_set import workout_set
def create_sets(df, lbs_or_kg):
    set_list = []
    for i, row in df.iterrows():
        if lbs_or_kg:
            weight = row['Weight (lb)']
            bodyweight = row['Bodyweight (lb)']
        else:
            weight = row['Weight (kg)']
            bodyweight = row['Bodyweight (kg)']
        new_set = workout_set(date=row['Date Lifted'],
            exercise=row['Exercise'],
            weight=weight,
            reps=row['Reps'],
            bodyweight=bodyweight,
            percentile=row['Percentile (%)'])
        set_list.append(new_set)
    return set_list
