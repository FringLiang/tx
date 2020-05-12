set proto_file=../protos/DeductionService.proto

protoc -I ../protos --grpc_out=. --plugin=protoc-gen-grpc="C:\Program Files (x86)\grpc\bin\grpc_cpp_plugin.exe" %proto_file%
protoc -I ../protos --cpp_out=. %proto_file%