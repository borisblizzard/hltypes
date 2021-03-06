/// @file
/// @version 4.2
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Contains some configuration definitions for Rapid XML.

#ifndef HLXML_RAPID_XML_CONFIG_H
#define HLXML_RAPID_XML_CONFIG_H

#define RAPIDXML_STATIC_POOL_SIZE (1024 * 1024)
#define RAPIDXML_DYNAMIC_POOL_SIZE (256 * 1024)
#define RAPIDXML_NO_STDLIB
#ifdef assert
	#undef assert
#endif
#define assert(arg)

#endif
