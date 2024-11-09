#include "Message.h"

Message::Message(std::string msg, std::string rec, std::string snd):message(msg), recipient(rec), sender(snd) {}


std::string Message::getMessage() {
    return message;
}

std::string Message::getRecipient() {
    return recipient;
}

std::string Message::getSender() {
    return sender;
}