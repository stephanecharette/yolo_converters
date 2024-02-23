/* YOLO converters -- helper apps to convert annotations to YOLO format.
 * Copyright 2021-2024 Stephane Charette <stephanecharette@gmail.com>
 * MIT license applies.  See "license.txt" for details.
 */

#include <iostream>
#include <fstream>
#include <regex>


// Download MSCOCO 2017, and convert the JSON annotations to YOLO .txt files.

int main()
{
	int rc = 1;

	try
	{
		rc = 0;
	}
	catch (const std::exception & e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	return rc;
}
