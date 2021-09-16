#pragma once
#include <iostream>
#include <string>

class User;

class Message
{
public:
    Message() { /*std::cout << "Message constr " << this << std::endl;*/ };
    Message(const std::string& message, const std::shared_ptr<User>& user, const tm& message_creation_time)
        : _message(message), _user(user), _message_creation_time(message_creation_time)
    {
        /*std::cout << "Message constr " << this << std::endl;*/ 
    }
    ~Message() { /*std::cout << "Message destr " << this << std::endl; */}
    void setMessage(const std::string& message) { _message = message; }
    void setUser(const std::shared_ptr<User>& user) { _user = user; }
    void setMessageCreationTime(const tm& time) { _message_creation_time = time; }
    void setMessageEditingTime(const tm& time) { _message_editing_time = time; }
    void setEdited(bool edit) { _is_edited = edit; }

    const std::string& getMessage() const { return _message; }
    const std::shared_ptr<User>& getUser() const { return _user; }
    const tm& getMessageCreationTime() const { return _message_creation_time; }
    const tm& getMessageEditingTime() const { return _message_editing_time; }
    bool isEdited() const { return _is_edited; }

    void editedMessage(const std::string& new_message, const tm& message_editing_time);

private:
    std::string _message{};
    std::shared_ptr<User> _user{nullptr};
    tm _message_creation_time{};
    bool _is_edited = false;
    tm _message_editing_time{};
};
