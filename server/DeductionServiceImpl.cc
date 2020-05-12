#include "DeductionServiceImpl.h"

using ::grpc::StatusCode;
using ::grpc::Status;

DeductionServiceImpl::DeductionServiceImpl(DataStorage* db)
	:db_(db)
{
}

DeductionServiceImpl::~DeductionServiceImpl()
{
	//db_
}

::grpc::Status DeductionServiceImpl::GetList(::grpc::ServerContext* context, const::DeductionService::UserId* request, ::DeductionService::ServiceInfoList* response)
{
	auto infos = db_->GetDedctList(request->userid());
	for (auto& info : infos)
	{
		auto* svr = response->add_service();
		svr->set_name(info.name);
		svr->mutable_id()->set_serviceid(info.id);
	}

	return Status();
}

::grpc::Status DeductionServiceImpl::AddService(::grpc::ServerContext* context, const::DeductionService::AddReq* request, ::DeductionService::Empty* response)
{
	bool stat = db_->AddDeduction(request->id().userid(), request->serviceid());

	return stat ? Status() : Status(StatusCode::INVALID_ARGUMENT, "INVALID_ARGUMENT");
}

::grpc::Status DeductionServiceImpl::RemoveService(::grpc::ServerContext* context, const::DeductionService::RemoveReq* request, ::DeductionService::Empty* response)
{
	bool stat = db_->RemoveDeduction(request->id().userid(), request->serviceid());

	return stat ? Status() : Status(StatusCode::INVALID_ARGUMENT, "INVALID_ARGUMENT");
}
