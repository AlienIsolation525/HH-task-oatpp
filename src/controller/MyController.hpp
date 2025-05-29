#ifndef MyController_hpp
#define MyController_hpp
#include "/usr/local/git_clone/HH-task-oatpp/utility/Urllib/Urllib.hpp"
#include "dto/DTOs.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"
//#include "oatpp/encoding/Percent.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

class MyController : public oatpp::web::server::api::ApiController {
public:
  MyController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers) {}

public:


 ENDPOINT("GET", "/hello/", root) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT("GET", "/asd", handleAsdRequest,
           QUERY(String, name),
           QUERY(String, message))
  {
	Urllib::Decode decode;
	std::string dd_message = decode.decodeString(message);
	std::string dd_name = decode.decodeString(name);
    OATPP_LOGd("AsdRequest", "name=%s, message=%s", dd_name, dd_message);
    oatpp::String responseMessage = oatpp::String("Имя и сообщение: " + dd_name + ", " + dd_message);
    return createResponse(Status::CODE_200, responseMessage);
  }

  ENDPOINT_INFO(getHelloByName) {
    info->summary = "Hello message";
    info->pathParams["message"].description = "Message to recruto";
    //info->addResponse<Object<UserDto>>(Status::CODE_200, "application/json");
    //info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
    //info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    info->pathParams["name"].description = "Name of recruto";
  } 
  ENDPOINT("GET", "/hello/{message}/{name}", getHelloByName,
           PATH(String, name,"name"),
	   PATH(String,message,"message")) {
	Urllib::Decode decode;
	std::string dd_message = decode.decodeString(message);
	std::string  dd_name = decode.decodeString(name);
	std::string response;
	if(message) response = dd_message + " " + dd_name + "!"; 
        else response = "Greetings, " + dd_name + "!";
    return createResponse(Status::CODE_200, response);
  }
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */

