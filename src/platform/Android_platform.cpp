/// @file
/// @version 4.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#ifdef __ANDROID__
#include <android/log.h>

#include "hlog.h"
#include "hplatform.h"
#include "hstring.h"
#include "platform_internal.h"

namespace hltypes
{
	void _platformPrint(const String& tag, const String& message, int level)
	{
		if (tag != "")
		{
			__android_log_print(level, tag.cStr(), "[%s] %s", tag.cStr(), message.cStr());
		}
		else
		{
			__android_log_write(level, "", message.cStr());
		}
	}
	
	bool _platformClipboardClear()
	{
		Log::error(logTag, CLIPBOARD_ERROR);
		return false;
	}
	
	bool _platformClipboardIsString()
	{
		Log::error(logTag, CLIPBOARD_ERROR);
		return false;
	}
	
	bool _platformClipboardGetString(hstr& string)
	{
		Log::error(logTag, CLIPBOARD_ERROR);
		return false;
	}
	
	bool _platformClipboardSetString(chstr string)
	{
		Log::error(logTag, CLIPBOARD_ERROR);
		return false;
	}
	
}
#endif
