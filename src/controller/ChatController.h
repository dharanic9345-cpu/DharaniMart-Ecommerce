#pragma once
#include "../service/ChatService.h"
#include <drogon/HttpController.h>
class ChatController
    : public drogon::HttpController<ChatController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(
        ChatController::chat,
        "/api/v1/chat",
        drogon::Post
    );
    METHOD_LIST_END
    void chat(
        const drogon::HttpRequestPtr& request,
        std::function<void(
            const drogon::HttpResponsePtr&)>&& callback
    );
private:
    ChatService chatService;
};
