#ifndef CONTACT_MANAGER_H_
#define CONTACT_MANAGER_H_

#include <functional>
#include <map>
#include <string>
#include <vector>

using Action = std::function<void()>;
using MenuActions = std::map<int, Action>;

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
  std::string name {};
  std::string phone_number {};
  std::string email {};
};

// =========================================================================
//  DATA STRUCTURES / ContactManager Class
// =========================================================================

class ContactManager {
 public:
  ContactManager();
  void Run();

 private:
  std::vector<Contact> contact_list_;
  std::vector<std::string> menu_list_;

  MenuActions action_map_;
  bool is_running_ = true;

  void DisplayMenu() const;
  void ViewContacts() const;

  void AddContact();
  void DeleteContact();

  void SaveContactList() const;
  void LoadContactList();

  void Exit();
};

#endif