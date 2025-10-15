#include <charconv>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

#include "util.h"

using Action = std::function<void()>;
using MenuActions = std::map<int, Action>;

// =========================================================================
//  DATA STRUCTURES
// =========================================================================

struct Contacts {
  Contacts(std::string name, std::string phone, std::string mail)
      : name(std::move(name)),
        phone_number(std::move(phone)),
        email(std::move(mail)) {}

  std::string name;
  std::string phone_number;
  std::string email;
};

// =========================================================================
//  UTILITY / I/O HANDLING
// =========================================================================

std::optional<int> StringToInt(const std::string& str) {
  int result = 0;
  const auto [ptr, ec] =
      std::from_chars(str.data(), str.data() + str.size(), result);

  if (ec == std::errc() && ptr == str.data() + str.size()) {
    return result;
  }

  return std::nullopt;
}

std::optional<std::string> GetUserInput(std::string_view prompt) {
  std::string input;
  std::cout << prompt;

  if (!std::getline(std::cin, input)) {
    // Check for fatal stream error (e.g., Ctrl+D/Z)
    std::cerr << "ERROR: Fatal error in reading input stream.\n";
    return std::nullopt;
  }

  return util::trim(input);
}

bool GetMenuSelection(std::string_view prompt, int& out_selection) {
  while (true) {
    std::optional<std::string> input_opt = GetUserInput(prompt);

    if (!input_opt.has_value()) {
      return false;
    }

    if (input_opt->empty()) {
      std::cerr << "ERROR: Input cannot be empty. Please try again.\n";
      continue;
    }

    if (std::optional<int> selection_opt = StringToInt(*input_opt);
        selection_opt.has_value()) {
      out_selection = *selection_opt;
      return true;
    }

    std::cerr << "ERROR: Invalid input. Please enter a number.\n";
  }
}

// =========================================================================
//  FILE I/O (Read/Write)
// =========================================================================

// File format marker (magic number) for robust file loading
constexpr std::string_view kFileMarker = "CONTACT_MANAGER_V1";
constexpr std::string_view kFileName = "contacts.txt";

/**
 * @brief Saves the entire contact list to a file.
 * The file format is simple: Magic Marker, then (Name, Phone, Email) per line.
 * @param contact_list The vector to save.
 */
void SaveContactList(const std::vector<Contacts>& contact_list) {
  std::ofstream output_file(kFileName.data());

  if (!output_file.is_open()) {
    std::cerr << "ERROR: Failed to open file for writing: " << kFileName
              << '\n';
    return;
  }

  // Write a file marker at the start for robust loading
  output_file << kFileMarker << '\n';

  // Write the total number of contacts for robust loading
  output_file << contact_list.size() << '\n';

  // Write the data
  for (const auto& contact : contact_list) {
    // Each field on a new line for simplicity in reading
    output_file << contact.name << '\n';
    output_file << contact.phone_number << '\n';
    output_file << contact.email << '\n';
  }

  std::cout << "Successfully saved " << contact_list.size() << " contacts to "
            << kFileName << '\n';
}

/**
 * @brief Loads the contact list from a file.
 * @param contact_list The vector to populate with loaded contacts.
 * @return true if loading was successful, false otherwise.
 */
bool LoadContactList(std::vector<Contacts>& contact_list) {
  std::ifstream input_file(kFileName.data());

  if (!input_file.is_open()) {
    std::cerr << "INFO: No previous contact file found (" << kFileName
              << "). Starting fresh.\n";
    return true;  // Not a failure; just starting empty.
  }

  std::string marker;
  if (!std::getline(input_file, marker) || marker != kFileMarker) {
    std::cerr << "ERROR: File format error. Missing or invalid file marker.\n";
    return false;
  }

  size_t num_contacts = 0;
  if (!(input_file >> num_contacts)) {
    std::cerr << "ERROR: File format error. Cannot read contact count.\n";
    return false;
  }

  input_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  contact_list.clear();

  for (size_t i = 0; i < num_contacts; ++i) {
    std::string name, phone, email;

    if (!std::getline(input_file, name) || !std::getline(input_file, phone) ||
        !std::getline(input_file, email)) {
      std::cerr
          << "ERROR: File format error. Unexpected end of file at contact #"
          << i + 1 << '\n';
      return false;
    }
    contact_list.emplace_back(std::move(name), std::move(phone),
                              std::move(email));
  }

  std::cout << "Successfully loaded " << contact_list.size()
            << " contacts from " << kFileName << '\n';
  return true;
}

// =========================================================================
//  CONTACT MANAGER ACTIONS
// =========================================================================

void DisplayMenu(const std::vector<std::string>& menu_list) {
  if (menu_list.empty()) {
    std::cout << "No menu to display.\n";
    return;
  }

  std::cout << "\n--- Menu ---\n";
  for (const auto& [index, element] :
       std::ranges::views::enumerate(menu_list)) {
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
    std::cout << "\nContact #" << index + 1 << '\n';
    std::cout << "Name: " << element.name << '\n';
    std::cout << "Phone Number: " << element.phone_number << '\n';
    std::cout << "Email: " << element.email << '\n';
  }
}

void AddContact(std::vector<Contacts>& contact_list) {
  std::string name;
  std::string phone;
  std::string email;

  std::optional<std::string> name_opt = GetUserInput("Enter contact name: ");
  if (!name_opt.has_value() || name_opt->empty()) return;
  name = std::move(*name_opt);

  std::optional<std::string> phone_opt = GetUserInput("Enter phone number: ");
  if (!phone_opt.has_value() || phone_opt->empty()) return;
  phone = std::move(*phone_opt);

  std::optional<std::string> email_opt = GetUserInput("Enter email: ");
  if (!email_opt.has_value() || email_opt->empty()) return;
  email = std::move(*email_opt);

  contact_list.emplace_back(std::move(name), std::move(phone),
                            std::move(email));
  std::cout << "Contact added successfully!\n";
}

// =========================================================================
//  APPLICATION LOOP
// =========================================================================

void ContactManager(std::vector<Contacts>& contact_list,
                    const std::vector<std::string>& menu_list,
                    const MenuActions& action_map, bool& is_running) {
  // Load contacts immediately at startup
  LoadContactList(contact_list);

  while (is_running) {
    DisplayMenu(menu_list);
    int input_selection = 0;

    // Use the dedicated menu selection handler
    if (!GetMenuSelection("Option: ", input_selection)) {
      // Fatal I/O error occurred during selection (e.g., stream closed)
      return;
    }

    // Map the user input to specific actions
    if (action_map.count(input_selection)) {
      action_map.at(input_selection)();
    } else {
      std::cerr << "ERROR: Invalid option chosen. Please select a number from "
                   "the menu.\n";
    }
  }
}

// =========================================================================
//  ENTRY POINT
// =========================================================================

int main() {
  std::vector<Contacts> contact_list;

  std::vector<std::string> menu_list{"Add Contact", "View All Contacts",
                                     "Save All Contacts", "Exit"};

  bool is_running = true;

  MenuActions actions_map{
      {1, [&contact_list]() { AddContact(contact_list); }},
      {2, [&contact_list]() { ViewContacts(contact_list); }},
      {3, [&contact_list]() { SaveContactList(contact_list); }},
      {4, [&is_running, &contact_list]() {
         std::cout << "Exiting Contact Manager.\n";
         is_running = false;
       }}};

  ContactManager(contact_list, menu_list, actions_map, is_running);

  return 0;
}