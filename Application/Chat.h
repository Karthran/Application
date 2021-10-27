#pragma once
#include <vector>
#include <fstream>

class Message;
class User;
class File;

class Chat
{
public:
    Chat();
    ~Chat();

    auto printMessages(int first_index, int number) const -> void;
    auto printMessage(int message_index) const -> void;
    auto addMessage(const std::shared_ptr<User>& user) -> const std::shared_ptr<Message>&;
    auto deleteMessage(const std::shared_ptr<User>& user, int message_index) -> const std::shared_ptr<Message>&;
    auto editMessage(const std::shared_ptr<User>& user, int message_index) -> const std::shared_ptr<Message>&;

    auto getCurrentMessageNum() const -> int { return static_cast<int>(_message_array.size()); }

    auto getFirstUser() const -> const std::shared_ptr<User>& { return _first_user; }
    auto getSecondUser() const -> const std::shared_ptr<User>& { return _second_user; }

    auto setFirstUser(const std::shared_ptr<User>& user) -> void { _first_user = user; }
    auto setSecondUser(const std::shared_ptr<User>& user) -> void { _second_user = user; }

    auto getMessageIndex(const std::shared_ptr<Message>& message) -> int;

    auto save(File& file) -> void;
    auto load(File& file, const std::vector<std::shared_ptr<User>>& user) -> void;

private:
    std::vector<std::shared_ptr<Message>> _message_array{};
    // int _current_message_num{0};

    /* _first_user and _second_user used only Private Chat */
    std::shared_ptr<User> _first_user{nullptr};  /*In _first_user contains the minimum of the two user IDs  */
    std::shared_ptr<User> _second_user{nullptr}; /*In _second_user contains the maximum of the two user IDs  */
};
