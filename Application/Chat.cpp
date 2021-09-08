#include "Chat.h"
#include "Message.h"

Chat::Chat(int max_message_num) : _max_message_num(max_message_num), _current_message_num(0)
{
    _message_array = new Message[_max_message_num];
}
