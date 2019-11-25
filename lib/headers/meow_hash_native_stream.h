#include <napi.h>
#include "meow_hash_x64_aesni.h"

class MeowHashNativeStream : public Napi::ObjectWrap<MeowHashNativeStream> {
public:
	static Napi::Object Init(Napi::Env env, Napi::Object exports);

	MeowHashNativeStream(const Napi::CallbackInfo& info);

	Napi::Value Absorb(const Napi::CallbackInfo& info);

	Napi::Value End(const Napi::CallbackInfo& info);

private:

	static Napi::FunctionReference constructor;

	meow_state State;
};
