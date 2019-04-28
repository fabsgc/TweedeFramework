#pragma once

#include "Prerequisites/TePrerequisitesUtility.h"
#include <istream>

namespace bs 
{
	/** Supported encoding types for strings. */
	enum class StringEncoding
	{
		UTF8 = 1,
		UTF16 = 2
	};

	/**
	 * General purpose class used for encapsulating the reading and writing of data from and to various sources using a 
	 * common interface.
	 */
	class TE_UTILITY_EXPORT DataStream
	{
	public:
		enum AccessMode
		{
			READ = 1, 
			WRITE = 2
		};
	};
}