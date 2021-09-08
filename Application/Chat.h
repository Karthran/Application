#pragma once

class Message;
class User;

class Chat
{
public:
    Chat() {}
    Chat(int max_message_num);

    ~Chat();

    void printMessages(int first_index, int number) const;
    void printMessage(int message_index) const;
    void addMessage(const User& user);
    void deleteMessage(int message_index);
    void editMessage(int message_index);

    int getMaxMessageNum() const { return _max_message_num; }
    int getCurrentMessageNum() const { return _current_message_num; }

private:
    Message* _message_array{nullptr};
    int _max_message_num{0};
    int _current_message_num{0};
};
