#include "contact_manager.h"

#include <fstream>
#include <iostream>
#include <ranges>

#include "util_io.h"

// =========================================================================
//  JSON Serialization Helpers
// =========================================================================

/**
 * Implementation of to_json
 */
void to_json(json& j, const Contact& c) {
  j = json{
      {"name", c.name}, {"phone_number", c.phone_number}, {"email", c.email}};
}

/**
 * Implementation of from_json
 */
void from_json(const json& j, Contact& c) {
  c.name = j.at("name").get<std::string>();
  c.phone_number = j.at("phone_number").get<std::string>();
  c.email = j.value("email", "");
}

// =========================================================================
//  Class Definition
// =========================================================================

/**
 * Implementation of ContactManager::ContactManager construct
 */
ContactManager::ContactManager() {
  menu_list_ = {"Add Contact", "View All Contacts", "Delete Contact",
                "Save All Contacts", "Exit"};
  action_map_ = {{1, std::bind(&ContactManager::AddContact, this)},
                 {2, std::bind(&ContactManager::ViewContacts, this)},
                 {3, std::bind(&ContactManager::DeleteContact, this)},
                 {4, std::bind(&ContactManager::SaveContactList, this)},
                 {5, std::bind(&ContactManager::Exit, this)}};
  LoadContactList();
}

/**
 * Implementation of ContactManager::Run
 */
void ContactManager::Run() {
  while (is_running_) {
    DisplayMenu();
    int input_selection = util::io::get_numeric_input<int>("Option: ");

    if (action_map_.count(input_selection)) {
      action_map_.at(input_selection)();
    } else {
      std::cerr << "ERROR: Invalid option chosen. Please select a number from "
                   "the menu.\n";
    }
  }
}
/**
 * Implementation of ContactManager::DisplayMenu
 */
void ContactManager::DisplayMenu() const {
  if (menu_list_.empty()) {
    std::cerr << "ERROR: Menu list is empty. Nothing to show.\n";
    return;
  }

  std::cout << '\n';
  for (const auto& [index, element] :
       std::ranges::views::enumerate(menu_list_)) {
    std::cout << index + 1 << ". " << element << '\n';
  }
}

/**
 * Implementation of ContactManager::ViewContacts
 */
void ContactManager::ViewContacts() const {
  if (contact_list_.empty()) {
    std::cerr << "ERROR: Contact list is empty. Nothing to view.\n";
    return;
  }

  for (const auto& [index, contact] :
       std::ranges::views::enumerate(contact_list_)) {
    std::cout << "\nContact #" << index + 1 << '\n';
    std::cout << "Name: " << contact.name << '\n';
    std::cout << "Phone Number: " << contact.phone_number << '\n';
    std::cout << "Email: " << contact.email << '\n';
  }
}

/**
 * Implementation of ContactManager::AddContact
 */
void ContactManager::AddContact() {
  std::string name;
  std::string phone_number;
  std::string email;

  std::string name_opt = util::io::get_line_input("Enter your name: ");
  if (name_opt.empty()) {
    std::cerr << "ERROR: Name is empty. Aborting action.\n";
    return;
  }
  name = std::move(name_opt);

  std::string phone_number_opt =
      util::io::get_line_input("Enter your phone number: ");
  if (phone_number_opt.empty()) {
    std::cerr << "ERROR: Phone number is empty. Aborting action.\n";
    return;
  }
  phone_number = std::move(phone_number_opt);

  std::string email_opt = util::io::get_line_input("Enter your email: ");
  if (email_opt.empty()) {
    std::cerr << "ERROR: Email is empty. Aborting action.\n";
    return;
  }
  email = std::move(email_opt);

  contact_list_.emplace_back(std::move(name), std::move(phone_number),
                             std::move(email));
  std::cout << "Contact added successfully!\n";
}

/**
 * Implementation of ContactManager::DeleteContact
 */
void ContactManager::DeleteContact() {
  if (contact_list_.empty()) {
    std::cerr << "ERROR: The contact list is empty. Nothing to delete.\n";
    return;
  }

  ViewContacts();

  int selection_index =
      util::io::get_numeric_input<int>("Choose a contact to delete: ");

  const int zero_based_index = selection_index - 1;

  if (zero_based_index < 0 ||
      zero_based_index >= static_cast<int>(contact_list_.size())) {
    std::cerr << "ERROR: Invalid contact number selected (" << selection_index
              << "). Deletion aborted.\n";
    return;
  }

  const std::string deleted_name = contact_list_[zero_based_index].name;
  char user_input;

  std::cout << "Are you sure you want to delete: " << deleted_name
            << " (y/N)? ";
  if (!std::cin >> user_input) {
    std::cerr << "ERROR: Invalid input. Abording action.\n";
    return;
  }

  if (user_input == 'Y' || user_input == 'y') {
    contact_list_.erase(contact_list_.begin() + zero_based_index);
    std::cout << "Successfully deleted contact: " << deleted_name << ".\n";
  } else {
    std::cout << "Aborting deletion of contact: " << deleted_name << ".\n";
  }
}

/**
 * Implementation of ContactManager::SaveContactList
 */
void ContactManager::SaveContactList() const {
  if (contact_list_.empty()) {
    std::cerr << "ERROR: Contact list is empty. Nothing to save.\n";
    return;
  }

  std::ofstream output_file(kFileName.data());

  if (!output_file.is_open()) {
    std::cerr << "ERROR: Failed to open file for writing: " << kFileName
              << '\n';
    return;
  }

  json output_json;

  output_json["file_marker"] = kFileMarker;
  output_json["contact_count"] = contact_list_.size();
  output_json["contacts"] = contact_list_;

  try {
    output_file << output_json.dump(2);
  } catch (const json::exception& e) {
    std::cerr << "ERROR: JSON serialization failed: " << e.what() << '\n';
    return;
  }
}

/**
 * Implementation of ContactManager::LoadContactList
 */
void ContactManager::LoadContactList() {
  std::ifstream input_file(kFileName.data());

  if (!input_file.is_open()) {
    std::cerr << "INFO: No previous contact file found (" << kFileName
              << "). Starting fresh.\n";
    return;
  }

  int contact_count = 0;

  try {
    json input_json;
    input_file >> input_json;

    if (input_json.at("file_marker").get<std::string>() != kFileMarker) {
      std::cerr
          << "ERROR: File format error. Missing or invalid file marker.\n";
      return;
    }

    contact_count = input_json.at("contact_count").get<int>();
    contact_list_ = input_json.at("contacts").get<std::vector<Contact>>();

    std::cout << "INFO: Successfully loaded " << contact_count
              << " contacts from the save file.\n";
  } catch (const json::exception& e) {
    std::cerr << "ERROR: Failed to load contacts (JSON ERROR): " << e.what()
              << ". Starting fresh.\n";
    return;
  }
}

/**
 * Implementation of ContactManager::Exit
 */
void ContactManager::Exit() {
  std::cout << "Exiting Contact Manager.\n";
  is_running_ = false;
}