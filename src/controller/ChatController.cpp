#include "ChatController.h"
#include <drogon/HttpResponse.h>
#include <json/json.h>
void ChatController::chat(
    const drogon::HttpRequestPtr& request,
    std::function<void(
        const drogon::HttpResponsePtr&)>&& callback)
{
    auto jsonBody = request->getJsonObject();
    if (!jsonBody || !jsonBody->isMember("message"))
    {
        Json::Value response;
        response["success"] = false;
        response["message"] = "Please provide a message.";
        auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
        resp->setStatusCode(drogon::k400BadRequest);
        callback(resp);
        return;
    }
    std::string message =
        (*jsonBody)["message"].asString();
    std::string reply =
        chatService.getResponse(message);
    Json::Value response;
    response["success"] = true;
    response["reply"] = reply;
    auto resp =
        drogon::HttpResponse::newHttpJsonResponse(response);
    callback(resp);
}
