#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>

#include "DeductionService.grpc.pb.h"

#include "DeductionUtil.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using DeductionService::Deduction;
using DeductionService::UserId;
using DeductionService::ServiceId;
using DeductionService::AddReq;
using DeductionService::RemoveReq;
using DeductionService::Empty;
using DeductionService::ServiceInfo;
using DeductionService::ServiceInfoList;

class WeChatClient {
public:
	WeChatClient(int id, std::shared_ptr<Channel> channel)
		: user_id_(id)
		, stub_(Deduction::NewStub(channel))
	{}

	std::vector<DeductionInfo> GetList();
	bool AddService(int svr_id);
	bool RemoveService(int svr_id);

	bool login() { return true; }
private:
	std::unique_ptr<Deduction::Stub> stub_;
	int user_id_;
};

int main(int argc, char** argv) {
	std::string target_str;
	std::string arg_str("--target");
	if (argc > 1) {
		std::string arg_val = argv[1];
		size_t start_pos = arg_val.find(arg_str);
		if (start_pos != std::string::npos) {
			start_pos += arg_str.size();
			if (arg_val[start_pos] == '=') {
				target_str = arg_val.substr(start_pos + 1);
			}
			else {
				std::cout << "The only correct argument syntax is --target=" << std::endl;
				return 0;
			}
		}
		else {
			std::cout << "The only acceptable argument is --target=" << std::endl;
			return 0;
		}
	}
	else {
		target_str = "localhost:50051";
	}
	auto channel = grpc::CreateChannel(
		target_str, grpc::InsecureChannelCredentials());
	//auto channel = grpc::CreateChannel(
	//	target_str, grpc::SslCredentials(grpc::SslCredentialsOptions()));
	WeChatClient client(333, channel);
	if (client.login())
	{
		auto print_list = [&]() {
			auto dd_list = client.GetList();
			std::cout << "DD list:" << std::endl;
			for (auto e : dd_list)
			{
				std::cout << e.id << " " << e.name << "\n";
			}
			std::cout << "List end." << std::endl;
		};

		print_list();

		client.AddService(1);
		client.AddService(2);
		print_list();

		auto dd_list = client.RemoveService(3);
		print_list();

	}

	return 0;
}

std::vector<DeductionInfo> WeChatClient::GetList()
{
	UserId request;
	request.set_userid(user_id_);

	ServiceInfoList reply;
	ClientContext context;

	Status status = stub_->GetList(&context, request, &reply);
	if (status.ok()) {
		std::vector<DeductionInfo> result;
		int len = reply.service_size();
		for (int i = 0; i < len; i++)
		{
			auto service_info = reply.service(i);
			result.push_back(DeductionInfo{ service_info.id().serviceid(), service_info.name() });
		}
		return result;
	}
	else {
		std::cout << status.error_code() << ": " << status.error_message()
			<< std::endl;
		return std::vector<DeductionInfo>();
	}
}

bool WeChatClient::AddService(int svr_id)
{
	AddReq request;
	request.mutable_id()->set_userid(user_id_);
	request.set_serviceid(svr_id);

	Empty reply;
	ClientContext context;

	Status status = stub_->AddService(&context, request, &reply);
	if (status.ok()) {
		return true;
	}
	else {
		std::cout << status.error_code() << ": " << status.error_message()
			<< std::endl;
		return false;
	}
}

bool WeChatClient::RemoveService(int svr_id)
{
	RemoveReq request;
	request.mutable_id()->set_userid(user_id_);
	request.set_serviceid(svr_id);

	Empty reply;
	ClientContext context;

	Status status = stub_->RemoveService(&context, request, &reply);
	if (status.ok()) {
		return true;
	}
	else {
		std::cout << status.error_code() << ": " << status.error_message()
			<< std::endl;
		return false;
	}
}

