#pragma once

constexpr auto CREATE_HASH_FUNCTION_NAME = "CreateHash";

constexpr auto COMPARE_BUFFERS_FUNCTION_NAME = "CompareBuffers";

constexpr auto CREATE_HASH_ARGUMENTS_MESSAGE = "CreateHash() expects exactly 1 argument of type Buffer";

constexpr auto COMPARE_HASH_ARGUMENTS_MESSAGE = "CompareHash expects exactly 2 arguments of type Buffer";

constexpr auto NATIVE_STREAM_CLASS_NAME = "MeowHashNativeStream";

constexpr auto NATIVE_STREAM_METHOD_NAME_ABSORB = "absorb";

constexpr auto NATIVE_STREAM_METHOD_NAME_END = "end";

constexpr auto NATIVE_STREAM_ABSORB_ARGUMENTS_MESSAGE = "MeowHashNativeStream::absorb() expects exactly 1 argument of type Buffer";
