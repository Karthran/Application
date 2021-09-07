#pragma once
#include <string>

class Message
{
public:
    Message(){};
    Message(const std::string& message, int user_ID, const tm& message_creation_time)
        : _message(message), _user_ID(user_ID), _message_creation_time(message_creation_time){}

    void setMessage(const std::string& message) { _message = message; }
    void setUserID(int user_ID) { _user_ID = user_ID; }
    void setMessageCreationTime(const tm& time) { _message_creation_time = time; }
    void setMessageEditingTime(const tm& time) { _message_editing_time = time; }
    void setEdited(bool edit) { _is_edited = edit; }

    const std::string& getMessage() const { return _message; }
    int getUserID() const { return _user_ID; }
    const tm& getMessageCreationTime() const { return _message_creation_time; }
    const tm& getMessageEditingTime() const { return _message_editing_time; }
    bool isEdited() const { return _is_edited; }

    void editedMessage(const std::string& new_message, const tm& message_editing_time);

private:
    std::string _message{};
    int _user_ID{0};
    tm _message_creation_time{};
    tm _message_editing_time{};
    bool _is_edited = false;
};
