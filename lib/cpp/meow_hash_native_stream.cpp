#include "meow_hash_native_stream.h"

Napi::FunctionReference MeowHashNativeStream::constructor;
Napi::String ExtractHash(const Napi::Env env, meow_u128 Hash);

Napi::Object MeowHashNativeStream::Init(Napi::Env env, Napi::Object exports)
{
	Napi::HandleScope scope(env);

	// TODO: (Stefan) Constexpr...
	Napi::Function func = DefineClass(env, "MeowHashNativeStream", {
		InstanceMethod("absorb", &MeowHashNativeStream::Absorb),
		InstanceMethod("end", &MeowHashNativeStream::End)
	});

	constructor = Napi::Persistent(func);
	constructor.SuppressDestruct();

	// TODO: (Stefan) Constexpr...
	exports.Set("MeowHashNativeStream", func);

	return exports;
}

MeowHashNativeStream::MeowHashNativeStream(const Napi::CallbackInfo& info)
	: Napi::ObjectWrap<MeowHashNativeStream>(info)
{
	MeowBegin(&State, MeowDefaultSeed);
};

Napi::Value MeowHashNativeStream::Absorb(const Napi::CallbackInfo& info) {
	// CLEANUP: (Stefan) Messages can be nicer...
	// TODO: (Stefan) Messages as constexpr...

	// if (info.Length() < 1 ) {
	// 	throw Napi::Error::New(info.Env(), "1 argument expected");
	// }

	// if (!info[0].IsBuffer()) {
	// 	throw Napi::Error::New(info.Env(), "The parameter must be a buffer");
	// }

	Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();
	MeowAbsorb(&State, buffer.Length(), buffer.Data());

	return buffer;
};

Napi::Value MeowHashNativeStream::End(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	meow_u128 Hash = MeowEnd(&State, MeowDefaultSeed);
	return ExtractHash(env, Hash);
}
