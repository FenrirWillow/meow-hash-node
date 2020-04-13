#include <napi.h>
#include "meow_hash_node.h"
#include "meow_hash_native_stream.h"
#include "meow_hash_constants.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	MeowHashNativeStream::Init(env, exports);
	exports.Set(CREATE_HASH_FUNCTION_NAME, 		Napi::Function::New(env, CreateHash));
	exports.Set(COMPARE_BUFFERS_FUNCTION_NAME, 	Napi::Function::New(env, CompareBuffers));
	return exports;
}

NODE_API_MODULE(meow_hash_node, InitAll)
