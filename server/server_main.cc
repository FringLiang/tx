/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "DeductionService.grpc.pb.h"

#include "server.h"
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using DeductionService::Deduction;
using DeductionService::UserId;
using DeductionService::ServiceId;
using DeductionService::AddReq;
using DeductionService::RemoveReq;
using DeductionService::ServiceInfo;
using DeductionService::ServiceInfoList;

//// Logic and data behind the server's behavior.
//class DeductionServiceImpl final : public Deduction::Service {
//	Status GetList(ServerContext* context, const UserId* request,
//		ServiceInfoList* reply) override {
//		//std::string prefix("Hello ");
//		//reply->set_message(prefix + request->name());
//		return Status::OK;
//	}
//};

//void LoadData() {
//	
//}
//
//void RunServer() {
//	std::string server_address("0.0.0.0:50051");
//	DeductionServiceImpl service;
//
//	grpc::EnableDefaultHealthCheckService(true);
//	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
//
//	ServerBuilder builder;
//	builder.AddListeningPort(server_address, grpc::SslServerCredentials(grpc::SslServerCredentialsOptions()));
//	builder.RegisterService(&service);
//	std::unique_ptr<Server> server(builder.BuildAndStart());
//
//	std::cout << "Server listening on " << server_address << std::endl;
//	server->Wait();
//}

int main(int argc, char** argv) {

	//LoadData();
	//RunServer();
    WeChatSever server("0.0.0.0:50051");
    server.Exec();

	return 0;
}
