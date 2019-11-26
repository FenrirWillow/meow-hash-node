#include <napi.h>
#include "meow_hash_node.h"
#include "meow_hash_native_stream.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	MeowHashNativeStream::Init(env, exports);
	exports.Set("CreateHash", 		Napi::Function::New(env, CreateHash));
	exports.Set("CompareBuffers", 	Napi::Function::New(env, CompareBuffers));
	return exports;
}

NODE_API_MODULE(meow_hash_node, InitAll)
