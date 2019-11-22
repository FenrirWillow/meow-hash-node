#include <iostream>
#include <napi.h>
#include "meow_hash_x64_aesni.h"

Napi::BigInt GetMeowHash32(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if(!info[0].IsBuffer()) {
		Napi::TypeError::New(env, "Buffer expected").ThrowAsJavaScriptException();
	}

	Napi::Buffer<uint> buffer = info[0].As<Napi::Buffer<char>>();
	meow_u128 Hash = MeowHash(MeowDefaultSeed, buffer.Length(), buffer.Data());
	uint32_t Hash32 = MeowU32From(Hash, 0);


	printf("    %08X-%08X-%08X-%08X\n",
           MeowU32From(Hash, 3),
           MeowU32From(Hash, 2),
           MeowU32From(Hash, 1),
           MeowU32From(Hash, 0));
	// std::cout << "Hash -> " << MeowU32From(Hash, 3) << "-" << MeowU32From(Hash, 2) << "-" << MeowU32From(Hash, 1) << "-" << MeowU32From(Hash, 0) << std::endl;
	return Napi::BigInt::New(env, int64_t(Hash32));
}

Napi::Boolean CompareBuffers(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if(info.Length() < 2 || !info[0].IsBuffer() || !info[1].IsBuffer()) {
		Napi::TypeError::New(env, "Two buffers expected").ThrowAsJavaScriptException();
	}

	Napi::Buffer<int16_t> bufferA = info[0].As<Napi::Buffer<int16_t>>();
	Napi::Buffer<int16_t> bufferB = info[0].As<Napi::Buffer<int16_t>>();

	meow_u128 HashA = MeowHash(MeowDefaultSeed, bufferA.Length(), bufferA);
	meow_u128 HashB = MeowHash(MeowDefaultSeed, bufferB.Length(), bufferB);
	return Napi::Boolean::New(env, MeowHashesAreEqual(HashA, HashB));
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	exports.Set("GetMeowHash32", Napi::Function::New(env, GetMeowHash32));
	exports.Set("CompareBuffers", Napi::Function::New(env, CompareBuffers));
	return exports;
}


NODE_API_MODULE(meow_hash_node, InitAll)
