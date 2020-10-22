#pragma once

#if defined(_MSC_VER)
//Microsoft
#pragma warning(disable:4996)
#if defined(MACHINE_EXPORTS)
#define MACHINE_DLL_API __declspec(dllexport) __stdcall
#else
#define MACHINE_DLL_API __declspec(dllimport) __stdcall
#endif
#elif defined(__GNUC__)
//GCC
#if defined(MACHINE_EXPORTS)
#define MACHINE_DLL_API __attribute__((visibility("default")))
#else
#define MACHINE_DLL_API
#endif
#else

#define MACHINE_DLL_API
#pragma warning Unknown dynamic link import/export semantics.
#endif


extern "C"
{

int MACHINE_DLL_API machine_call(
	const std::string& output_filename,
	const std::string& input_filename
	);

}