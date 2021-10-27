#pragma once
#include <iostream>
#include <map>
#include <vector>

class Message;

const int BAD_INDEX = -1;
class NewMessages
{
public:
    NewMessages() { std::cout << "NewMessages constr " << this << std::endl; }
    ~NewMessages() { std::cout << "NewMessages destr " << this << std::endl; }

    auto isNewMessagesExists() const -> bool { return isNewMsgExists; }
    auto addNewMessage(const std::shared_ptr<Message>& message) -> void;
    auto removeNewMessage(const std::shared_ptr<Message>& message) -> void;
    auto usersNumber() const -> size_t { return _userIDmap.size(); }
    auto newMessageNumber(int userID) -> size_t { return _newMessagesMap[userID].size(); }
    auto getUserID(int index) -> int { return _userIDmap[index]; }
    auto getMessages(int userID) -> const std::vector<std::shared_ptr<Message>>& { return _newMessagesMap[userID]; }
    auto isUserIDExists(int userID) const -> int;
    auto setLastVisitTime(const tm& tm) -> void;
    auto getLastVisitTime() -> const tm& { return _lastVisitTime; }

private:
    std::map<int, int> _userIDmap{}; // key - index ; value userID
    std::map<int, std::vector<std::shared_ptr<Message>>> _newMessagesMap{}; // key userID; value Message
    bool isNewMsgExists{false};
    tm _lastVisitTime{};

    auto eraseUserID(int userID) -> void;
};

