#ifndef CONTACT_MANAGER_H_
#define CONTACT_MANAGER_H_

#include <functional>
#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "json.hpp"

using Action = std::function<void()>;
using MenuActions = std::map<int, Action>;

using json = nlohmann::json;

constexpr std::string_view kFileMarker = "ContactManagerV2";
constexpr std::string_view kFileName = "contacts.json";

// =========================================================================
//  DATA STRUCTURES / Contact Object Structure
// =========================================================================

struct Contact {
  // Constructor definitions
  Contact() = default;

  Contact(std::string name, std::string phone, std::string mail)
      : name(std::move(name)),
        phone_number(std::move(phone)),
        email(std::move(mail)) {}

  // Properties of the Contact Object
  std::string name{};
  std::string phone_number{};
  std::string email{};
};

/**
 * @brief Converts a Contact object to a JSON object (Serialization).
 * This function must be in the same namespace/scope as Contacts to work.
 * @param j The JSON object to populate.
 * @param c The Contact object to serialize.
 */
void to_json(json& j, const Contact& c);

/**
 * @brief Converts a Json object to a Contact object (Deserialization).
 * This function must be in the same namespace/scope as Contacts to work.
 * @param j The JSON object to read from.
 * @param c The Contact object to populate.
 */
void from_json(const json& j, Contact& c);

// =========================================================================
//  DATA STRUCTURES / ContactManager Class
// =========================================================================

class ContactManager {
 public:
  /**
   * @brief Construct a new Contact Manager object
   */
  ContactManager();

  /**
   * @brief Run the whole Contact Manager process
   */
  void Run();

 private:
  std::vector<Contact> contact_list_;
  std::vector<std::string> menu_list_;

  MenuActions action_map_;
  bool is_running_ = true;

  /**
   * @brief Display the menu list to the console
   */
  void DisplayMenu() const;

  /**
   * @brief Display the contact list to the console
   */
  void ViewContacts() const;

  /**
   * @brief Add a Contact object to the contact list of the Contact Manager
   * object
   */
  void AddContact();

  /**
   * @brief Delete a Contact object from the contact list of the Contact Manager
   * object
   */
  void DeleteContact();

  /**
   * @brief Save the contact list to a json file, including a kFileMarker and
   * contact count
   */
  void SaveContactList() const;

  /**
   * @brief Load the contact list from a json file
   */
  void LoadContactList();

  /**
   * @brief The function to exit from the process loop of Contact Manager
   */
  void Exit();
};

#endif