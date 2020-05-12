#pragma once
#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "DeductionService.grpc.pb.h"
#include "DeductionServiceImpl.h"
#include "database.h"

using grpc::Server;

class WeChatSever
{
public:
	WeChatSever(const std::string& server_address);
	~WeChatSever();


	void Exec();
private:

	DataStorage data_;
	DeductionServiceImpl* svr_;
	std::unique_ptr<Server> grpc_server_;
};

