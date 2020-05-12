#pragma once

#include "DeductionService.grpc.pb.h"

#include "database.h"

using DeductionService::Deduction;



class DeductionServiceImpl final : public Deduction::Service
{
public:
	DeductionServiceImpl(DataStorage* db);
	virtual ~DeductionServiceImpl();

	virtual ::grpc::Status GetList(::grpc::ServerContext* context, 
		const ::DeductionService::UserId* request, ::DeductionService::ServiceInfoList* response) override;
	virtual ::grpc::Status AddService(::grpc::ServerContext* context,
		const ::DeductionService::AddReq* request, ::DeductionService::Empty* response) override;
	virtual ::grpc::Status RemoveService(::grpc::ServerContext* context,
		const ::DeductionService::RemoveReq* request, ::DeductionService::Empty* response) override;

private:
	DataStorage* db_;
};