#pragma once
#include "Array.h"

class Message;
class User;

class Chat
{
public:
    Chat();
    ~Chat();

    auto printMessages(int first_index, int number) const -> void;
    auto printMessage(int message_index) const -> void;
    auto addMessage(const std::shared_ptr<User>& user) -> void;
    auto deleteMessage(const std::shared_ptr<User>& user, int message_index) -> void;
    auto editMessage(const std::shared_ptr<User>& user, int message_index) -> void;

    auto getCurrentMessageNum() const -> int { return _current_message_num; }

    auto getFirstUser() const -> const std::shared_ptr<User>& { return _first_user; }
    auto getSecondUser() const -> const std::shared_ptr<User>& { return _second_user; }

    auto setFirstUser(const std::shared_ptr<User>& user) -> void { _first_user = user; }
    auto setSecondUser(const std::shared_ptr<User>& user) -> void { _second_user = user; }

private:
    Array<Message> _message_array{};
    int _current_message_num{0};

    /* _first_user and _second_user used only Private Chat */
    std::shared_ptr<User> _first_user{nullptr}; /*In _first_user contains the minimum of the two user IDs  */
    std::shared_ptr<User> _second_user{nullptr}; /*In _second_user contains the minimum of the two user IDs  */
};
