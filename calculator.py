from collections import Counter

class StatisticsCalculator:
    def __init__(self, numbers):
        self.numbers = numbers

    # function that calculates the mean of the numbers
    def mean(self):
        if not self.numbers:
            return None
        return sum(self.numbers) / len(self.numbers)

    # functions that calculates the median of the numbers
    def median(self):
        if not self.numbers:
            return None
        sorted_numbers = sorted(self.numbers)
        n = len(sorted_numbers)
        mid = n // 2
        if n % 2 == 0:
            return (sorted_numbers[mid - 1] + sorted_numbers[mid]) / 2
        else:
            return sorted_numbers[mid]

    # functions that caluates the mode of the numbers
    def mode(self):
        if not self.numbers:
            return None
        counts = Counter(self.numbers)
        max_freq = max(counts.values())
        mode = [num for num, freq in counts.items() if freq == max_freq]
        return mode


if __name__ == "__main__":
    numbers = [7,9,11,25,5,9,77,9,2,5]
   
    print("Mean:",  StatisticsCalculator(numbers).mean())
    print("Median:",  StatisticsCalculator(numbers).median())
    print("Mode:",  StatisticsCalculator(numbers).mode())
