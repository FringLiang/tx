load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_cc//cc:defs.bzl", "cc_library")


cc_library(
    name = "deduction_proto",
    srcs = ["DeductionService.grpc.pb.cc"],
    hdrs = ["DeductionService.grpc.pb.h"],
	copts = ["-Iexternal/gtest/include"],
)

cc_binary(
    name = "server",
    srcs = ["server-main.cc"],
	deps = [
        ":deduction_proto",
		"@protobuf_project//:proto_lib"
    ],

)
