#include <napi.h>
#include "meow_hash_x64_aesni.h"
#include "meow_hash_native_stream.h"

Napi::String CreateHash(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if(!info[0].IsBuffer()) {
		// TODO: (Stefan) Make the error message constexpr string.
		Napi::TypeError::New(env, "Buffer expected").ThrowAsJavaScriptException();
	}

	Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();
	meow_u128 Hash = MeowHash(MeowDefaultSeed, buffer.Length(), buffer.Data());

	char hashStringBuffer[36];
	snprintf(
		hashStringBuffer,
		sizeof(hashStringBuffer),
		"%08X-%08X-%08X-%08X",
		MeowU32From(Hash, 3),
		MeowU32From(Hash, 2),
		MeowU32From(Hash, 1),
		MeowU32From(Hash, 0)
	);
	return Napi::String::New(env, hashStringBuffer, 36);
}

Napi::Boolean CompareBuffers(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if(info.Length() < 2 || !info[0].IsBuffer() || !info[1].IsBuffer()) {
		// TODO: (Stefan) Make the error message a little nicer
		Napi::TypeError::New(env, "Two buffers expected").ThrowAsJavaScriptException();
	}

	Napi::Buffer<uint8_t> bufferA = info[0].As<Napi::Buffer<uint8_t>>();
	Napi::Buffer<uint8_t> bufferB = info[0].As<Napi::Buffer<uint8_t>>();

	meow_u128 hashA = MeowHash(MeowDefaultSeed, bufferA.Length(), bufferA.Data());
	meow_u128 hashB = MeowHash(MeowDefaultSeed, bufferB.Length(), bufferB.Data());
	return Napi::Boolean::New(env, MeowHashesAreEqual(hashA, hashB));
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	MeowHashNativeStream::Init(env, exports);
	exports.Set("CreateHash", 		Napi::Function::New(env, CreateHash));
	exports.Set("CompareBuffers", 	Napi::Function::New(env, CompareBuffers));
	return exports;
}

NODE_API_MODULE(meow_hash_node, InitAll)
