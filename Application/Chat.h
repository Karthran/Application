#pragma once
#include "Array.h"

class Message;
class User;

class Chat
{
public:
    Chat() { std::cout << "Chat constr " << this << std::endl; }
    Chat(int max_message_num);

    ~Chat();

    void printMessages(int first_index, int number) const;
    void printMessage(int message_index) const;
    void addMessage(std::shared_ptr<User> user);
    void deleteMessage(int message_index);
    void editMessage(int message_index);

    int getMaxMessageNum() const { return _max_message_num; }
    int getCurrentMessageNum() const { return _current_message_num; }

    const std::shared_ptr<User> getFirstUser() const { return _first_user; }
    const std::shared_ptr<User> getSecondUser() const { return _second_user; }

    void setFirstUser(std::shared_ptr<User> user) { _first_user = user; }
    void setSecondUser(std::shared_ptr<User> user) { _second_user = user; }


private:
    Array<Message> _message_array;
    int _max_message_num{0};
    int _current_message_num{0};

    std::shared_ptr<User> _first_user{nullptr};
    std::shared_ptr<User> _second_user{nullptr};
};
