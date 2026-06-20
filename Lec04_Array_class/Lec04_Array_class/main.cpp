#include "rectangle.h"
#include "Pet.h"
#include "Music.h"
using namespace std; //std 생략

int main() {
	Rectangle rect1(4, 6);
	std::cout << "Rectangle 1:" << std:: endl;
	//printf("rectangle 1: \n");
	cout << "Area: " << rect1.getArea() << endl;
	//printf("Area: %lf\n", rect1.getArea());
	cout << "Permeter: " << rect1.getPerimeter() << endl;
	cout << "Is Square? " << boolalpha << rect1.isSquare() << endl;
	//boolalpha= 0, 1을 false, true로
	printf("-------------------------------------------\n");

	Pet myPet("Lucky", 5, "dog");
	cout << "My pet name is " << myPet.getName() << endl;
	Puppy myPuppy("kong", 13, "dog", "Puddle");
	cout << "My Puppys breed is " << myPuppy.getBreed() << endl;
	printf("-------------------------------------------\n");

	//creat a new music streaming service
	MusicStreamingService myService("Sportify");
	// add music into service
	myService.addMusic("사과 하나를 그려", "소란", "사과 하나를 그려", 2026);
	//search by title
	string music_title;
	cout << "enter the title: ";
	cin >> music_title;
	Music* result = myService.searchByTitle(music_title);
	if (result != NULL) {
		cout << "found :" << result->getTitle() << endl;
	}
	else {
		cout << "not found" << endl;
	}
	//search by artist
	string artist_name;
	cout << "Enter the name: ";
	cin >> artist_name;

	vector<Music*>artistResult = myService.searchByArtist(artist_name);
	if (artistResult.size() > 0) {
		cout << "Found" << artistResult.size() << " songs by" << artist_name << ":" << endl;
		for (int i = 0; i < artistResult.size(); i++) {
			cout << artistResult[i]->getTitle() << endl; //artistResult자체가 포인터 이므로 화살표 사용
		}
	}
	else {
		cout << "not found" << endl;
	}
	return 0;
}
