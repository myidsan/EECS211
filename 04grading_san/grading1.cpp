#include <iostream>
#include <vector>

struct Weighted_grade
{
	double grade;
	double weight;
};

std::vector<Weighted_grade> read_grades()
{
	std::vector<Weighted_grade> result;
	Weighted_grade wg;

	while (std::cin >> wg.grade && std::cin >> wg.weight)
	{
		result.push_back(wg);
	}

	return result;
}

double weighted_sum(std::vector<Weighted_grade> grades)
{
	double sum = 0.0;

	for (Weighted_grade wg : grades)
	{
		sum += wg.grade * wg.weight;
	}

	return sum;
}

double total_weight(std::vector<Weighted_grade> grades)
{
	double sum = 0.0;

	for (Weighted_grade wg: grades)
	{
		sum += wg.weight;
	}

	return sum;
}

double averaged_weight(std::vector<Weighted_grade> grades)
{
	double numerator = weighted_sum(grades);
	double denominator = total_weight(grades);

	if (denominator == 0) {
		std::cout << "Average cannot be represented since the total weight is 0\n";
	} else {
		return numerator/denominator;
	}
}


int main (void)
{
	std::vector<Weighted_grade> grade = read_grades();
	double average = averaged_weight(grade);

	std::cout << "Average: " << average << '\n';

}
