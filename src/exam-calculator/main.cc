#include <format>
#include <iostream>

#include "score_const.h"
#include "util_io.h"

int main() {
  float assignment_score =
      util::io::get_numeric_input<float>("Enter you assignment score: ");
  float midterm_score =
      util::io::get_numeric_input<float>("Enter you assignment score: ");
  float final_score =
      util::io::get_numeric_input<float>("Enter you assignment score: ");

  float total_score = assignment_score + midterm_score + final_score;
  float average_score = total_score / kNumScores;
  char letter_grade;

  if (average_score >= 90.0f) {
    letter_grade = 'A';
  } else if (average_score >= 80.0f) {
    letter_grade = 'B';
  } else if (average_score >= 70.0f) {
    letter_grade = 'C';
  } else if (average_score >= 60.0f) {
    letter_grade = 'D';
  } else {
    letter_grade = 'F';
  }

  std::cout << "\n--- Final Results ---" << std::endl;
  std::cout << std::format("Total Score: %.2f / 300.00\n", total_score);
  std::cout << std::format("Average Score: %.2f / 100.00\n", average_score);
  std::cout << "Letter Grade: " << letter_grade << std::endl;

  return 0;
}