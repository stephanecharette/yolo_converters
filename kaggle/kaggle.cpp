/* YOLO converters -- helper apps to convert annotations to YOLO format.
 * Copyright 2021-2022 Stephane Charette <stephanecharette@gmail.com>
 * MIT license applies.  See "license.txt" for details.
 */

#include <iostream>
#include <fstream>
#include <regex>


/* This was written to convert the annotations for the Great Barrier Reef project in November 2021.
 * The project has a single class, so everything is hard-coded to use id #0.
 * https://www.kaggle.com/c/tensorflow-great-barrier-reef/
 */
 
int main()
{
	const auto input_filename = "train.csv";

	std::ifstream ifs(input_filename);
	if (not ifs.good())
	{
		std::cout << "cannot open " << input_filename << std::endl;
		return 1;
	}

	const std::regex line_rx("^(\\d+),(\\d+),(\\d+),(\\d+),([^,]+),(\\[\\]|\".+\")$");
	const std::regex value_rx("'x': (\\d+), 'y': (\\d+), 'width': (\\d+), 'height': (\\d+)(.+)");

	std::string line;
	while (std::getline(ifs, line))
	{
		std::smatch m;
		bool success = std::regex_match(line, m, line_rx);
		if (not success)
		{
			std::cout << "Skipping: " << line << std::endl;
			continue;
		}

		// negative sequences look like this:
		//
		//		0,45518,1260,387,0-1260,[]
		//
		// where:
		//			0 = video id
		//			45518 = sequence id
		//			1260 = frame id
		//			387 = sequence frame (!?)
		//			0-1260 = image id
		//			[] = empty image

		const std::string txt = "video_" + m.str(1) + "/" + m.str(3) + ".txt";
		std::ofstream ofs(txt);

		if (m.str(6) == "[]")
		{
			// this will create an empty file
			continue;
		}

		// if we get here, then we have a complex set of annotations, such as:
		//
		//		"[{'x': 509, 'y': 3, 'width': 36, 'height': 37}, {'x': 485, 'y': 25, 'width': 33, 'height': 31}, {'x': 468, 'y': 46, 'width': 34, 'height': 32}]"

		while (true)
		{
			success = std::regex_search(line, m, value_rx);
			if (not success)
			{
				break;
			}

			const double x = stod(m.str(1));
			const double y = stod(m.str(2));
			const double w = stod(m.str(3));
			const double h = stod(m.str(4));
			line = m.str(5);
			const double cx = x + w / 2.0;
			const double cy = y + h / 2.0;
			const double normalized_cx = cx / 1280.0;
			const double normalized_cy = cy / 720.0;
			const double normalized_w = w / 1280.0;
			const double normalized_h = h / 720.0;

			ofs << "0 " << normalized_cx << " " << normalized_cy << " " << normalized_w << " " << normalized_h << std::endl;
		}
	}

	return 0;
}

