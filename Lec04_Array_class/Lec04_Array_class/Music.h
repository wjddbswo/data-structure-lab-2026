#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Music class
class Music {
private:
	string title;
	string artist;
	string album;
	int year;

public:
	Music(string title, string artist, string album, int year) {
		this->title = title;
		this->artist = artist;
		this->album = album;
		this->year = year;
	}
	string getTitle() { return title; }
	string getArtist() { return artist; }
	string getAlbum() { return album; }
	int getYear() { return year; }

};
class MusicStreamingService {
private:
	string serviceName;
	vector<Music>musicList;

public:
	MusicStreamingService(string name) {
		this->serviceName = name;
	}
	void addMusic(string title, string artist, string album, int year) {
		Music newMusic(title, artist, album, year);
		musicList.push_back(newMusic);
		cout << title << "by" << artist << "added to" << serviceName << endl;
	}

	//search by title
	//객체 반환시는 * 필요
	Music* searchByTitle(string title) {
		for (int i = 0;i < musicList.size(); i++) {
			if (musicList[i].getTitle() == title) {
				return &musicList[i]; //반환값이 포인터->주소값 저장 - &는 주소값의미
			}
		}
		return NULL;
	}
	// search by artist
	vector<Music*> searchByArtist(string artist) {
		vector<Music*> result; //result라는 벡터를 만들었는데 그 값들이 Music*이라는 포인터이다
		for (int i = 0; i < musicList.size(); i++) {
			//artist와 muisiclist에 있는 artist가 같으면 result에 추가
			if (musicList[i].getArtist() == artist) {
				result.push_back(&musicList[i]);
			}
		}
		return result;
	}
};
