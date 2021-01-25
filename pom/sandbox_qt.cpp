#include <iostream>
#include <QImageReader>

int main() {
	std::cout << "ok" << std::endl;
	auto img = QImageReader{"D:\\dataset\\nasa_images_png\\PIA18033~small.png"}.read();
	if(img.isNull()) {
		std::cout << "No such image." << std::endl;
	} else {
		std::cout << "Found it." << std::endl;
	}
}
