import pandas as pd

def read_from_file(file_name):
    # Load the CSV data into a pandas DataFrame
    df = pd.read_csv(file_name)

    dfs = dict(tuple(df.sort_values('Exercise').groupby('Exercise')))


    return dfs