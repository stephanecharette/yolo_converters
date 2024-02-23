/* YOLO converters -- helper apps to convert annotations to YOLO format.
 * Copyright 2021-2024 Stephane Charette <stephanecharette@gmail.com>
 * MIT license applies.  See "license.txt" for details.
 */

#include <iostream>
#include <fstream>
#include <regex>
#include <filesystem>
#include <opencv2/opencv.hpp>


int main(int argc, char *argv[])
{
	try
	{
		const std::filesystem::path base_dir		= (argc == 2 ? argv[1] : ".");
		const std::filesystem::path images_dir		= base_dir / "images";
		const std::filesystem::path annotations_dir	= base_dir / "annotations";

		if (not std::filesystem::exists(images_dir))
		{
			throw std::invalid_argument("images directory was not found: " + images_dir.string());
		}
		if (not std::filesystem::exists(annotations_dir))
		{
			throw std::invalid_argument("annotations directory was not found: " + annotations_dir.string());
		}

		const std::regex rx("(\\d+),(\\d+),(\\d+),(\\d+),(\\d+),(\\d+),(\\d+),(\\d+)");

		size_t file_count = 0;

		for (auto item : std::filesystem::recursive_directory_iterator(images_dir))
		{
			const auto image_fn = item.path().filename();
			const auto old_annotation_fn = (annotations_dir	/ image_fn).replace_extension(".txt");
			const auto new_annotation_fn = (images_dir		/ image_fn).replace_extension(".txt");

			if (item.path() == new_annotation_fn)
			{
				// this is a txt file, not an image, so skip it
				continue;
			}

			std::cout	<< "image: " << item.path().string()		<< std::endl
						<< "  new: " << new_annotation_fn.string()	<< std::endl
						<< "  old: " << old_annotation_fn.string()	<< std::endl;

			if (not std::filesystem::exists(old_annotation_fn))
			{
				std::cout << "  skipping image (no annotations found)" << std::endl;
				continue;
			}

			cv::Mat mat = cv::imread(item.path());
			const double iw = mat.cols;
			const double ih = mat.rows;

			if (mat.empty() or iw <= 0.0 or ih <= 0.0)
			{
				std::cout << "  not an image" << std::endl;
				continue;
			}

			file_count ++;

			size_t annotation_count = 0;
			std::ofstream ofs(new_annotation_fn);
			std::ifstream ifs(old_annotation_fn);
			std::string line;
			while (std::getline(ifs, line))
			{
				std::smatch m;
				bool success = std::regex_search(line, m, rx);
				if (not success)
				{
					std::cout << "Skipping: " << line << std::endl;
					continue;
				}

				annotation_count ++;

				double x = std::stoi(m.str(1));
				double y = std::stoi(m.str(2));
				double w = std::stoi(m.str(3));
				double h = std::stoi(m.str(4));
				const int class_id = std::stoi(m.str(6));

				x += w / 2.0;
				y += h / 2.0;
				x /= iw;
				y /= ih;
				w /= iw;
				h /= ih;
				ofs << class_id << " " << std::fixed << std::setw(8) << x << " " << y << " " << w << " " << h << std::endl;
			}
			std::cout << "  annotations: " << annotation_count << std::endl;
		}

		std::cout << "image files processed: " << file_count << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
