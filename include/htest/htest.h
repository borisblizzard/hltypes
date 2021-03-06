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
#define MM_CONCAT__( a, b )     a ## b
#define MM_CONCAT_( a, b )      MM_CONCAT__( a, b )
#define MM_CONCAT( a, b )       MM_CONCAT_( a, b )

#ifdef __APPLE__
	#import <Foundation/NSString.h>
	#import <XCTest/XCTest.h>

	#define HTEST_ASSERT(expression, msg) if (!(expression)) XCTFail(@"%s", __assertMsg(msg))
	#define HTEST_FAIL(msg) XCTFail(@"%s", __assertMsg(msg))
	#define HTEST_LOG(msg) printf("    [htest] %s\n", hstr(msg).cStr())

	#define HTEST_SUITE_BEGIN \
		static const char* __assertMsg(chstr msg) { return msg.cStr(); } \
		@interface MM_CONCAT(_, _HTEST_CLASS) : XCTestCase \
		@end \
		@implementation MM_CONCAT(_, _HTEST_CLASS)

	#define HTEST_SUITE_END @end

	#define HTEST_SUITE_INIT()\
		+ (void) setUp\
		{\
			try \
			{ \
				hstr dataDir = [[[NSBundle bundleForClass:[self class]] resourcePath] UTF8String]; \
				hstr tempDir = hdir::joinPath([NSTemporaryDirectory() UTF8String], "htest"); \
				[MM_CONCAT(_, _HTEST_CLASS) _setUp:dataDir tempDir:tempDir];\
			}\
			catch (hexception& e) \
			{ \
				printf("    [htest::ERROR] Error initialising test suite: %s\n", hstr(e.getMessage()).cStr());\
				exit(1);\
			} \
		}\
		+ (void) _setUp:(chstr) dataDir tempDir:(chstr) tempDir

	#define HTEST_SUITE_DESTROY() + (void) tearDown

	#define HTEST_INIT()\
		- (void) setUp\
		{\
			try \
			{ \
				[self __setUp]; \
			}\
			catch (hexception& e) \
			{ \
				printf("    [htest::ERROR] Error initialising test: %s\n", hstr(e.getMessage()).cStr());\
				exit(1);\
			} \
		}\
		- (void) __setUp

	#define HTEST_DESTROY() - (void) tearDown

	#define HTEST_CASE(name) \
		- (void) test_ ## name \
		{ \
			try \
			{ \
				[self _test_ ## name]; \
			} \
			catch (hexception& e) \
			{ \
				_XCTFailureHandler(self, YES, __FILE__, __LINE__, @"Unhandled Exception", @"%s", __assertMsg(e.getMessage())); \
			} \
		} \
		- (void) _test_ ## name

	#define HTEST_CASE_WITH_DATA(name) \
		- (void) test_ ## name \
		{ \
			try \
			{ \
				hstr dataDir = [[[NSBundle bundleForClass:[self class]] resourcePath] UTF8String]; \
				hstr tempDir = hdir::joinPath([NSTemporaryDirectory() UTF8String], "htest"); \
				hdir::createNew(tempDir); \
				[self _test_ ## name:dataDir tempDir:tempDir]; \
			} \
			catch (hexception& e) \
			{ \
				_XCTFailureHandler(self, YES, __FILE__, __LINE__, @"Unhandled Exception", @"%s", __assertMsg(e.getMessage())); \
			} \
		} \
		- (void) _test_ ## name:(chstr) dataDir tempDir:(chstr) tempDir
#else
	#include "CppUnitTest.h"
	#include <windows.h>

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	#define HTEST_ASSERT(expression, msg) Assert::IsTrue((expression), __assertMsg(msg))
	#define HTEST_FAIL(msg) Assert::Fail(__assertMsg(msg))
	#define HTEST_LOG(msg) Logger::WriteMessage(("[htest] " + hstr(msg)).cStr())

	#define HTEST_SUITE_BEGIN \
		namespace __EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## _htest \
		{ \
			static wchar_t __assertMessage[2048]; \
			static const wchar_t* __assertMsg(chstr msg) { const char* s = msg.cStr(); int i; for (i = 0; s[i] != 0; ++i) { __assertMessage[i] = s[i]; }; __assertMessage[i] = 0; return __assertMessage; } \
			TEST_CLASS(MM_CONCAT(_, _HTEST_CLASS)) \
			{ \
			public:

	#define HTEST_SUITE_END };}

	#define HTEST_SUITE_INIT() TEST_CLASS_INITIALIZE(initTestSuite)\
		{ \
			try \
			{ \
				hstr dataDir = hdir::baseDir(__FILE__); \
				wchar_t winTempPath[256]; \
				GetTempPathW(256, winTempPath); \
				hstr tempDir = hdir::joinPath(hstr::fromUnicode(winTempPath).replaced("\\", "/"), "htest"); \
				hdir::createNew(tempDir); \
				_initTestSuite(dataDir, tempDir); \
			} \
			catch (hexception& e) \
			{ \
				Assert::Fail(__assertMsg(e.getMessage())); \
			} \
		} \
		static void _initTestSuite(chstr dataDir, chstr tempDir)

	#define HTEST_SUITE_DESTROY() TEST_CLASS_CLEANUP(destroyTestSuite)

	#define HTEST_INIT() TEST_METHOD_INITIALIZE(initTestMethod)\
		{ \
			try \
			{ \
				_initTestMethod(); \
			} \
			catch (hexception& e) \
			{ \
				Assert::Fail(__assertMsg(e.getMessage())); \
			} \
		} \
		static void _initTestMethod()

	#define HTEST_DESTROY() TEST_METHOD_CLEANUP(destroyTestMethod)

	#define HTEST_CASE(name) TEST_METHOD(__EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## _ ## name) \
		{ \
			try \
			{ \
				__EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## __ ## name(); \
			} \
			catch (hexception& e) \
			{ \
				Assert::Fail(__assertMsg(e.getMessage())); \
			} \
		} \
		void __EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## __ ## name()

	#define HTEST_CASE_WITH_DATA(name) TEST_METHOD(__EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## _ ## name) \
		{ \
			try \
			{ \
				hstr dataDir = hdir::baseDir(__FILE__); \
				wchar_t winTempPath[256]; \
				GetTempPathW(256, winTempPath); \
				hstr tempDir = hdir::joinPath(hstr::fromUnicode(winTempPath).replaced("\\", "/"), "htest"); \
				hdir::createNew(tempDir); \
				__EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## __ ## name(dataDir, tempDir); \
			} \
			catch (hexception& e) \
			{ \
				Assert::Fail(__assertMsg(e.getMessage())); \
			} \
		} \
		void __EXPAND(_HTEST_LIB) ## __EXPAND(_) ## __EXPAND(_HTEST_CLASS) ## __ ## name(chstr dataDir, chstr tempDir)
	#endif
#endif
