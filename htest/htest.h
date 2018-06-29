#ifndef HLTYPES_HTEST_H
#define HLTYPES_HTEST_H

#ifndef _HTEST_LIB
	#pragma message("WARNING! _HTEST_LIB not defined!")
#endif
#ifndef _HTEST_CLASS
	#pragma message("WARNING! _HTEST_CLASS not defined!")
#endif

#include <hltypes/hstring.h>
#include <hltypes/hdir.h>

#define __EXPAND(x) x

#ifdef __APPLE__
	#import <Foundation/NSString.h>
	#import <XCTest/XCTest.h>

	#define HTEST_ASSERT(expression, msg) if (!(expression)) XCTFail(@"%s", __assertMsg(msg))
	#define HTEST_FAIL(msg) XCTFail(@"%s", __assertMsg(msg))

	#define HTEST_SUITE_BEGIN \
		static const char* __assertMsg(chstr msg) { return msg.cStr(); }\
		@interface __EXPAND(_HTEST_CLASS) : XCTestCase \
		@end \
		@implementation __EXPAND(_HTEST_CLASS)

	#define HTEST_SUITE_END @end

	#define HTEST_CASE(name) \
		- (void) test_ ## name \
		{ \
			try\
			{\
				hstr dataDir = [[[NSBundle bundleForClass:[self class]] resourcePath] UTF8String];\
				hstr tempDir = hdir::joinPath([NSTemporaryDirectory() UTF8String], "htest");\
				hdir::createNew(tempDir);\
				[self _test_ ## name:dataDir tempDir:tempDir];\
			}\
			catch (hexception& e)\
			{\
				_XCTFailureHandler(self, YES, __FILE__, __LINE__, @"Unhandled Exception", @"%s", e.getMessage().cStr()); \
			}\
		}\
		- (void) _test_ ## name:(chstr) dataDir tempDir:(chstr) tempDir
#else
	#include "CppUnitTest.h"
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	#define HTEST_ASSERT(expression, msg) Assert::IsTrue((expression), __assertMsg(msg))

	#define HTEST_SUITE_BEGIN \
		namespace __EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## _htest \
		{ \
			static wchar_t __assertMessage[2048];\
			static const wchar_t* __assertMsg(chstr msg) { const char* s = msg.cStr(); int i; for (i = 0; s[i] != 0; ++i) { __assertMessage[i] = s[i]; }; __assertMessage[i] = 0; return __assertMessage; }\
			TEST_CLASS(__EXPAND(_HTEST_CLASS)) \
			{ \
			public:

	#define HTEST_SUITE_END };}

	#define HTEST_CASE(name) TEST_METHOD(__EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## _ ## name)

	#endif
#endif
