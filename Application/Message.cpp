#include "Message.h"

void Message::editedMessage(const std::string& new_message, const tm& message_editing_time)
{
    _message = new_message;
    _message_editing_time = message_editing_time;
    _is_edited = true;
}
