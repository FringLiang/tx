#include "server.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>


#include "DeductionServiceImpl.h"

using grpc::ServerBuilder;

WeChatSever::WeChatSever(const std::string& server_address)
	:data_()
{
	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();

	auto svr_ = new DeductionServiceImpl(&data_);


	//auto client_ca_pem = get_file_contents(argv[1]); // for verifying clients
	//auto my_key_pem = get_file_contents(argv[2]);
	//auto my_cert_pem = get_file_contents(argv[3]);

	//grpc::SslServerCredentialsOptions::PemKeyCertPair pkcp = {
	//  my_key_pem.c_str(), my_cert_pem.c_str()
	//};

	//grpc::SslServerCredentialsOptions ssl_opts(GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY);
	//ssl_opts.pem_root_certs = client_ca_pem;
	//ssl_opts.pem_key_cert_pairs.push_back(pkcp);
	//std::cout << "pem_root_certs length: " << ssl_opts.pem_root_certs.length() << std::endl;

	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	//builder.AddListeningPort(server_address, grpc::SslServerCredentials(grpc::SslServerCredentialsOptions(GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE)));
	builder.RegisterService(svr_);
	grpc_server_ = builder.BuildAndStart();
}

WeChatSever::~WeChatSever()
{
	data_.FlushData();
	delete svr_;
}

void WeChatSever::Exec()
{
	grpc_server_->Wait();
}
