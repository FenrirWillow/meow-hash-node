#include <napi.h>
#include "meow_hash_x64_aesni.h"
#include "meow_hash_constants.h"

Napi::String ExtractHash(const Napi::Env env, meow_u128 Hash) {
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

Napi::String CreateHash(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if((info.Length() != 1) || (!info[0].IsBuffer())) {
		Napi::TypeError::New(env, CREATE_HASH_ARGUMENTS_MESSAGE).ThrowAsJavaScriptException();
		// NOTE: (Stefan) NAPI requires returns in all branches to function correctly.
		// This string will never be propagated to the caller's context.
		return Napi::String::New(env, "");
	}

	Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();
	meow_u128 Hash = MeowHash(MeowDefaultSeed, buffer.Length(), buffer.Data());

	return ExtractHash(env, Hash);
}

Napi::Boolean CompareBuffers(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if((info.Length() != 2) || (!info[0].IsBuffer()) || (!info[1].IsBuffer())) {
		Napi::TypeError::New(env, COMPARE_HASH_ARGUMENTS_MESSAGE).ThrowAsJavaScriptException();
		// NOTE: (Stefan) NAPI requires returns in all branches to function correctly.
		// This boolean will never be propagated to the caller's context.
		return Napi::Boolean::New(env, false);
	}

	Napi::Buffer<uint8_t> bufferA = info[0].As<Napi::Buffer<uint8_t>>();
	Napi::Buffer<uint8_t> bufferB = info[0].As<Napi::Buffer<uint8_t>>();

	meow_u128 hashA = MeowHash(MeowDefaultSeed, bufferA.Length(), bufferA.Data());
	meow_u128 hashB = MeowHash(MeowDefaultSeed, bufferB.Length(), bufferB.Data());
	return Napi::Boolean::New(env, MeowHashesAreEqual(hashA, hashB));
}
