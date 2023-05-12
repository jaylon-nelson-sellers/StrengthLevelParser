class workout_set:
    def __init__(self, date=None, exercise=None, weight=None, reps=None, bodyweight=None, percentile=None):
        # Initializer / Instance attributes (default to None)
        self.__date = date
        self.__exercise = exercise
        self.__weight = weight  # Default: lbs
        self.__reps = reps
        self.__bodyweight = bodyweight  # Default: lbs
        self.__percentile = percentile

    # Getters
    def get_date(self):
        return self.__date

    def get_exercise(self):
        return self.__exercise

    def get_weight(self):
        return self.__weight

    def get_reps(self):
        return self.__reps

    def get_bodyweight(self):
        return self.__bodyweight

    def get_percentile(self):
        return self.__percentile

    # Setters
    def set_date(self, date):
        self.__date = date

    def set_exercise(self, exercise):
        self.__exercise = exercise

    def set_weight(self, weight):
        self.__weight = weight

    def set_reps(self, reps):
        self.__reps = reps

    def set_bodyweight(self, bodyweight):
        self.__bodyweight = bodyweight

    def set_percentile(self, percentile):
        self.__percentile = percentile

    # toString method
    def __str__(self):
        return f'Date: {self.__date}, Exercise: {self.__exercise}, Weight: {self.__weight} lbs, Reps: {self.__reps}, Bodyweight: {self.__bodyweight} lbs, Percentile: {self.__percentile}'
