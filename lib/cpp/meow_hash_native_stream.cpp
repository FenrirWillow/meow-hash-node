#include "meow_hash_native_stream.h"
#include "meow_hash_constants.h"

Napi::FunctionReference MeowHashNativeStream::constructor;
Napi::String ExtractHash(const Napi::Env env, meow_u128 Hash);

Napi::Object MeowHashNativeStream::Init(Napi::Env env, Napi::Object exports)
{
	Napi::HandleScope scope(env);

	Napi::Function func = DefineClass(env, NATIVE_STREAM_CLASS_NAME, {
		InstanceMethod(NATIVE_STREAM_METHOD_NAME_ABSORB, &MeowHashNativeStream::Absorb),
		InstanceMethod(NATIVE_STREAM_METHOD_NAME_END, &MeowHashNativeStream::End)
	});

	constructor = Napi::Persistent(func);
	constructor.SuppressDestruct();

	exports.Set(NATIVE_STREAM_CLASS_NAME, func);

	return exports;
}

MeowHashNativeStream::MeowHashNativeStream(const Napi::CallbackInfo& info)
	: Napi::ObjectWrap<MeowHashNativeStream>(info)
{
	MeowBegin(&State, MeowDefaultSeed);
};

Napi::Value MeowHashNativeStream::Absorb(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if((info.Length() != 1) || (!info[0].IsBuffer())) {
		Napi::TypeError::New(env, NATIVE_STREAM_ABSORB_ARGUMENTS_MESSAGE).ThrowAsJavaScriptException();
		return env.Undefined();
	}

	Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();
	MeowAbsorb(&State, buffer.Length(), buffer.Data());

	return env.Undefined();
};

Napi::Value MeowHashNativeStream::End(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	meow_u128 Hash = MeowEnd(&State, MeowDefaultSeed);
	return ExtractHash(env, Hash);
}
