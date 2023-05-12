def filter_exercises(dfs, filename):
    # Read the file and extract exercises
    with open(filename, 'r') as f:
        exercises = [line.strip() for line in f]

    # Filter dfs based on exercises
    filtered_dfs = {exercise: dfs[exercise] for exercise in exercises if exercise in dfs}

    return filtered_dfs
