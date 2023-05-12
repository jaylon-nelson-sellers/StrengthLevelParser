from create_sets import create_sets
from create_working_sets import create_working_sets
import workout_set
def iterate_filtered_dfs(filtered_dfs):
    for exercise, df in filtered_dfs.items():
        print(f"Exercise: {exercise}")
        print(df)  # prints the DataFrame

        temp_set = create_sets(df, 1)
        temp_working_sets = create_working_sets(temp_set)
        # You can now do something with 'exercise' and 'df'

