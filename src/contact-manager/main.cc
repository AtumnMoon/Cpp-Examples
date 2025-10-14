#include <charconv>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "util.h"

using Action = std::function<void()>;
using MenuActions = std::map<int, Action>;

struct Contacts {
  Contacts(std::string name, std::string phone)
      : name(std::move(name)), phone_number(std::move(phone)) {}

  std::string name;
  std::string phone_number;
};

std::optional<int> StringToInt(const std::string& str) {
  int result = 0;

  const auto [ptr, ec] =
      std::from_chars(str.data(), str.data() + str.size(), result);

  if (ec == std::errc() && ptr == str.data() + str.size()) {
    return result;
  }

  std::string error_detail;
  if (ec == std::errc::result_out_of_range) {
    error_detail = "Value is out of range for an integer.";
  } else if (ec == std::errc::invalid_argument) {
    error_detail = "Invalid argument for conversion.";
  } else if (ec == std::errc()) {
    error_detail = "Input contains non-integer characters.";
  }

  std::cerr << "ERROR: Failed to convert string to integer: " << error_detail
            << " Input: " << str << '\n';
  return std::nullopt;
}

std::optional<std::string> GetUserInput(std::string_view prompt) {
  std::string input;

  std::cout << prompt;

  if (!std::getline(std::cin, input)) {
    std::cerr << "ERROR: error in reading the input.\n";
    return std::nullopt;
  }
  return util::trim(input);
}

bool GetInputLoop(std::string_view prompt, std::string& out_input) {
  while (true) {
    std::optional<std::string> input_opt = GetUserInput(prompt);

    if (!input_opt.has_value()) {
      return false;
    }

    if (input_opt->empty()) {
      std::cerr << "ERROR: Input cannot be empty. Please try again.\n";
      continue;
    }

    out_input = std::move(*input_opt);
    return true;
  }
}

void DisplayMenu(const std::vector<std::string>& menu_list) {
  if (menu_list.empty()) {
    std::cout << "No menu to display.\n";
    return;
  }

  std::cout << "\n--- Menu ---\n";
  for (const auto& [index, element] :
       std::ranges::views::enumerate(menu_list)) {
    // FIX: Replaced std::endl with '\n'
    std::cout << index + 1 << ". " << element << '\n';
  }
}

void ViewContacts(const std::vector<Contacts>& contact_list) {
  if (contact_list.empty()) {
    std::cout << "The contact list is empty.\n";
    return;
  }

  std::cout << "\n--- Contacts ---\n";
  for (const auto& [index, element] :
       std::ranges::views::enumerate(contact_list)) {
    std::cout << "Contact #" << index + 1 << '\n';
    std::cout << "Name: " << element.name << '\n';
    std::cout << "Phone Number: " << element.phone_number << '\n';
  }
}

void AddContact(std::vector<Contacts>& contact_list) {
  std::string name;
  std::string phone;

  if (!GetInputLoop("Enter contact name: ", name) ||
      !GetInputLoop("Enter phone number: ", phone)) {
    std::cerr << "ERROR: Adding contact aborted due to fatal I/O error.\n";
    return;
  }

  contact_list.emplace_back(std::move(name), std::move(phone));
  std::cout << "Contact added successfully!\n";
}

void ContactManager(const std::vector<std::string>& menu_list,
                    const MenuActions& action_map) {
  bool isRunning = true;

  while (isRunning) {
    DisplayMenu(menu_list);
    std::string user_input;

    if (!GetInputLoop("Option: ", user_input)) {
      std::cerr << "ERROR: Fatal I/O error. Exiting.\n";
      return;
    }

    if (std::optional<int> input_opt = StringToInt(user_input);
        input_opt.has_value()) {
      int input = *input_opt;

      if (action_map.count(input)) {
        action_map.at(input)();
      } else {
        std::cerr << "ERROR: Invalid option chosen. \n";
      }
    }
  }
}

int main() {
  std::vector<std::string> menu_list{"Add Contacts", "View Contacts", "Exit"};
  std::vector<Contacts> contact_list;
  bool isRunning = true;
  bool& running_ref = isRunning;

  MenuActions actions_map{
      {1, [&contact_list]() { AddContact(contact_list); }},
      {2, [&contact_list]() { ViewContacts(contact_list); }},
      {3, [&running_ref]() {
         std::cout << "Exiting Contact Manager. Goodbye!\n";
         running_ref = false;
       }}};

  ContactManager(menu_list, actions_map);
  return 0;
}