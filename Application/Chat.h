#pragma once
#include "Array.h"

class Message;
class User;

class Chat
{
public:
    Chat();
    ~Chat();

    void printMessages(int first_index, int number) const;
    void printMessage(int message_index) const;
    void addMessage(const std::shared_ptr<User>& user);
    void deleteMessage(const std::shared_ptr<User>& user, int message_index);
    void editMessage(const std::shared_ptr<User>& user, int message_index);

    int getCurrentMessageNum() const { return _current_message_num; }

    const std::shared_ptr<User>& getFirstUser() const { return _first_user; }
    const std::shared_ptr<User>& getSecondUser() const { return _second_user; }

    void setFirstUser(const std::shared_ptr<User>& user) { _first_user = user; }
    void setSecondUser(const std::shared_ptr<User>& user) { _second_user = user; }

private:
    Array<Message> _message_array{};
    int _current_message_num{0};

    /* _first_user and _second_user used only Private Chat */
    std::shared_ptr<User> _first_user{nullptr}; /*In _first_user contains the minimum of the two user IDs  */
    std::shared_ptr<User> _second_user{nullptr}; /*In _second_user contains the minimum of the two user IDs  */
};
