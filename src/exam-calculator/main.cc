#include <iostream>
#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/ascii.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"

#include "score_const.h"

static absl::StatusOr<float> StringToFloat(absl::string_view input_string) {
  std::size_t chars_converted = 0;
  float result = 0.0f;

  absl::string_view stripped_string = absl::StripAsciiWhitespace(input_string);

  if (stripped_string.empty()) {
    return absl::InvalidArgumentError(
        "Input string is empty or contains only whitespaces.");
  }

  std::string temp_string(stripped_string.data(), stripped_string.length());

  try {
    result = std::stof(temp_string, &chars_converted);
  } catch (const std::out_of_range &e) {
    return absl::OutOfRangeError(
        absl::StrFormat("Value '%s' is out of float range.", input_string));
  } catch (const std::invalid_argument &e) {
    return absl::InvalidArgumentError(absl::StrFormat(
        "Input string '%s' contains no valid number.", input_string));
  }

  if (chars_converted != temp_string.length()) {
    return absl::InvalidArgumentError(
        absl::StrFormat("Trailing characters found in input: '%s'",
                        temp_string.substr(chars_converted)));
  }

  return result;
}

static absl::StatusOr<float> ValidateScoreRange(float score) {
  if (score < kMinScore || score > kMaxScore) {
    return absl::InvalidArgumentError(
        absl::StrFormat("Score must be between %d and %d. Received %.2f.",
                        kMinScore, kMaxScore, score));
  }
  return score;
}

static absl::StatusOr<float> GetFloatFromUser(const std::string &prompt) {
  std::string user_input;
  absl::StatusOr<float> float_result;

  while (true) {
    std::cout << prompt << ": ";
    std::cout.flush();

    // Check if it's impossible to get the user input
    if (!std::getline(std::cin, user_input)) {
      return absl::CancelledError("Input stream is closed or cancelled.");
    }

    // Do the conversion and check for errors
    float_result = StringToFloat(user_input);
    if (!float_result.ok()) {
      std::cerr << "Invalid Input! " << float_result.status().message()
                << " Please try again." << std::endl;
      continue;
    }

    // Check if it exceed the 0-100 range value for score then report it
    absl::StatusOr<float> validated_score = ValidateScoreRange(*float_result);
    if (!validated_score.ok()) {
      std::cerr << "Invalid Input! " << validated_score.status().message()
                << " Please try again." << std::endl;
      continue;
    }

    return validated_score;
  }
}

int main() {
  absl::StatusOr<float> assignment_score = GetFloatFromUser("Enter Assignment Score (0-100)");
  if (!assignment_score.ok()) {
    std::cerr << "Program aborted: " << assignment_score.status().message()
              << std::endl;
    return 1;
  }

  absl::StatusOr<float> midterm_score = GetFloatFromUser("Enter Midterm Exam Score (0-100)");
  if (!midterm_score.ok()) {
    std::cerr << "Program aborted: " << midterm_score.status().message()
              << std::endl;
    return 1;
  }

  absl::StatusOr<float> final_score = GetFloatFromUser("Enter Final Exam Score (0-100)");
  if (!final_score.ok()) {
    std::cerr << "Program aborted: " << final_score.status().message()
              << std::endl;
    return 1;
  }

  float total_score = *assignment_score + *midterm_score + *final_score;
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
  std::cout << absl::StrFormat("Total Score: %.2f / 300.00\n", total_score);
  std::cout << absl::StrFormat("Average Score: %.2f / 100.00\n", average_score);
  std::cout << "Letter Grade: " << letter_grade << std::endl;

  return 0;
}