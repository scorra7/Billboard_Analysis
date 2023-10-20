 /* ---------------------------------------------
 Program 3: Billboard Analysis
 
 Course: CS 141, Spring 2022. Tues 3pm lab
 System: Windows and IpadOS using replit
 Author: Steve Corral and Isaac Rosales
 ---------------------------------------------
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cctype>
#include <cstring>
#include <sstream>
#include <algorithm>
using namespace std;

// This class will have the "columns" from the csv file
class infoFromCharts {
public:
	void separateDate(string newDate) {
		date = newDate;
	}
	
	void separateRank(string newRank) {
		rank = newRank;
	}
	
	void separateSong(string newSong) {
		song = newSong;
	}
	
	void separateArtist(string newArtist) {
		artist = newArtist;
	}

	void separateLastWeek(string newLastWeek) {
		lastWeek = newLastWeek;
	}
	
	void separatePeakRank(string newPeakRank) {
		peakRank = newPeakRank;
	}
	
	void separateWeeksOnBoard(string newWeeksOnBoard) {
		weeksOnBoard = newWeeksOnBoard;
	}
	
  string getDate () const {return date;}
	string getRank () const {return rank;}
	string getSong () const {return song;}
	string getArtist () const {return artist;}
	string getLastWeek () const {return lastWeek;}
	string getPeakRank () const {return peakRank;}
	string getWeeksOnBoard () const {return weeksOnBoard;}
	
private:
	string date;
	string rank;
	string song;
	string artist;
	string lastWeek;
	string peakRank;
	string weeksOnBoard;
};

// This function will get each line of the selected csv file, then separate the line from the commas and put them into the class as columns. Then the song gets appended into a vector. 
void separateInfoIntoClass(vector<infoFromCharts> &rowsInList, int timePeriod) {
	infoFromCharts currentSong;
	string currentWord;
	string currentLine;
	
	ifstream inStream;
	if (timePeriod == 1) {
		inStream.open("charts_top50_1960_1980.csv");
	}
	else if (timePeriod == 2) {
		inStream.open("charts_top50_1981_2000.csv");
	}
	else {
		inStream.open("charts_top50_2001_2020.csv");
	}
	assert( inStream.fail() == false );
	while (getline(inStream, currentLine)) {
		stringstream currentStream(currentLine);
		
		getline(currentStream, currentWord, ',');
		currentSong.separateDate(currentWord);
		
		getline(currentStream, currentWord, ',');
		currentSong.separateRank(currentWord);
		
		getline(currentStream, currentWord, ',');
		currentSong.separateSong(currentWord);
		
		getline(currentStream, currentWord, ',');
		currentSong.separateArtist(currentWord);
		
		getline(currentStream, currentWord, ',');
		currentSong.separateLastWeek(currentWord);
		
		getline(currentStream, currentWord, ',');
		currentSong.separatePeakRank(currentWord);
		
		getline(currentStream, currentWord, ',');
		currentSong.separateWeeksOnBoard(currentWord);
		
		rowsInList.push_back(currentSong);
	}
	inStream.close();
	
	rowsInList.erase(rowsInList.begin());
}

// Displays the info after selecting which csv you want to use.
int menuOption(int& choice) {
  cout << "Select a menu option: \n"
	     << "   1. Display overall information about the data\n"
	     << "   2. Display the Billboard info of the song with the most #1 occurrences for a given decade or year\n"
	     << "   3. Display the Billboard info for the most long-lasting song on the charts for a given decade or year\n"
	     << "   4. Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year\n"
	     << "   5. Artist Search - Return the Billboard info for records that matches user input for artist search\n"
	     << "   6. Exit\n"
	     << "Your choice --> ";
	cin >> choice;
  return choice;
}

// This is the function for if you choose the first option from the menuOption function. It will display the number of rows in the csv you selected (besides the first line). Also displays the number of unique songs.
void menuOptionOne (vector<infoFromCharts> &chartInfoVector,vector<string> &uniqueSongs, string currentSong) {
  cout << "Total number of rows: " << chartInfoVector.size() << endl;
	
	for (int i = 0; i < chartInfoVector.size(); i++) {
		currentSong = (chartInfoVector.at(i)).getSong();
		if (count(uniqueSongs.begin(), uniqueSongs.end(), currentSong) == 0) {
			uniqueSongs.push_back(currentSong);
		}
	}
		cout << "Number of unique songs represented in the dataset: " << uniqueSongs.size() << endl;
}

// This function will parse through the each of the three vectors, keep the number one ranked songs that it finds, and put that song into a separate vector. Finally, it will modify the date so only the year is kept.
vector<infoFromCharts> reorderVector(vector<infoFromCharts> &firstVector, vector<infoFromCharts> &secondVector, vector<infoFromCharts> &thirdVector) {
  vector<infoFromCharts> numberOneOccurances;
  infoFromCharts currentSong;
  string currentDate;
  string currentNumString;
  
  	// these three for loops will put all the number 1 ranked songs into one vector from all three files
  	for (int i = 0; i < firstVector.size(); i++) {
  		currentSong = firstVector.at(i);
  		
  		if (currentSong.getRank() == "1") {
  			numberOneOccurances.push_back(currentSong);
  		}
  	}
  	
  	for (int i = 0; i < secondVector.size(); i++) {
  		currentSong = secondVector.at(i);
  		
  		if (currentSong.getRank() == "1") {
  			numberOneOccurances.push_back(currentSong);
  		}
  	}
  	
  	for (int i = 0; i < thirdVector.size(); i++) {
  		currentSong = thirdVector.at(i);
  		
  		if (currentSong.getRank() == "1") {
  			numberOneOccurances.push_back(currentSong);
  		}
  	}
  	
  	// this will remove the day and month of the number 1 ranked songs
  	for (int i = 0; i < numberOneOccurances.size(); i++) {
  		currentDate = (numberOneOccurances.at(i)).getDate();
  		stringstream s(currentDate);
  		
  		getline(s, currentNumString, '/');
  		getline(s, currentNumString, '/');
  		getline(s, currentNumString, '/');
  		(numberOneOccurances.at(i)).separateDate(currentNumString);
  	}
    return numberOneOccurances;
}

// this will now separate the vector with all the number 1 ranked songs into three different vectors, between times periods (1960-1980), (1980-2000), (2000-2020)
void stringToInt(vector<infoFromCharts> &numberOneOccurances, vector<infoFromCharts> &firstDateVector, vector<infoFromCharts> &secondDateVector, vector<infoFromCharts> &thirdDateVector, int timePeriod) {
  for (int i = 0; i < numberOneOccurances.size(); i++) {
      int currentYear = stoi((numberOneOccurances.at(i)).getDate());
  		if (timePeriod == 1) {
  			if (currentYear >= 1960 && currentYear <= 1969) {
  				firstDateVector.push_back(numberOneOccurances.at(i));
  			}
  			if ((currentYear >= 1970) && (currentYear <= 1979)) {
  				secondDateVector.push_back(numberOneOccurances.at(i));
  			}
  			if (currentYear == 1980) {
  				thirdDateVector.push_back(numberOneOccurances.at(i));
  			}
  		}
  		else if (timePeriod == 2) {
  			if (currentYear >= 1980 && currentYear <= 1989) {
  				firstDateVector.push_back(numberOneOccurances.at(i));
  			}
  			if ((currentYear >= 1990) && (currentYear <= 1999)) {
  				secondDateVector.push_back(numberOneOccurances.at(i));
  			}
  			if (currentYear == 2000) {
  				thirdDateVector.push_back(numberOneOccurances.at(i));
  			}
  		}
  		else {
  			if (currentYear >= 2000 && currentYear <= 2009) {
  				firstDateVector.push_back(numberOneOccurances.at(i));
  			}
  			if ((currentYear >= 2010) && (currentYear <= 2019)) {
  				secondDateVector.push_back(numberOneOccurances.at(i));
  			}
  			if (currentYear == 2020) {
  				thirdDateVector.push_back(numberOneOccurances.at(i));
  			}
  		}
  	}

}


bool menuOptionTwo(vector<infoFromCharts> &firstVector, vector<infoFromCharts> &secondVector, vector<infoFromCharts> &thirdVector, int timePeriod) {
	char choice;
	vector<infoFromCharts> numberOneOccurances, firstDateVector, secondDateVector, thirdDateVector;
	vector<string> tempVector, maxSongs, tempArtistVector, maxArtist;
	string currentSongFromVector, currentArtistFromVector;
	int yearChosen, rankMax = 0, currentCount = 0;
  bool running = true;

  numberOneOccurances = reorderVector(firstVector, secondVector, thirdVector);
  while (running == true) {
    cout << "Enter D to select a decade or Y to select a year." << endl
	       << "Your choice --> ";
	  cin >> choice;
    choice = toupper(choice);
    if (choice == 'D') {
    	cout << "Enter the decade you would like to choose, as a multiple of 10 (e.g. 2010)." << endl;
    	cin >> yearChosen;
    	yearChosen = (yearChosen - (yearChosen % 10));
  
    	stringToInt(numberOneOccurances, firstDateVector, secondDateVector, thirdDateVector, timePeriod);
      
    	if (timePeriod == 1) {
    		if (yearChosen == 1960) {
    			for (int i = 0; i < firstDateVector.size(); i++) {
    				tempVector.push_back((firstDateVector.at(i)).getSong());
            tempArtistVector.push_back((firstDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
    		else if (yearChosen == 1970) {
    			for (int i = 0; i < secondDateVector.size(); i++) {
    				tempVector.push_back((secondDateVector.at(i)).getSong());
            tempArtistVector.push_back((secondDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
    		else if (yearChosen == 1980) {
    			for (int i = 0; i < thirdDateVector.size(); i++) {
    				tempVector.push_back((thirdDateVector.at(i)).getSong());
            tempArtistVector.push_back((firstDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
        else {
          cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl << endl;
          return true;
        }
    	}
      if (timePeriod == 2) {
    		if (yearChosen == 1980) {
    			for (int i = 0; i < firstDateVector.size(); i++) {
    				tempVector.push_back((firstDateVector.at(i)).getSong());
            tempArtistVector.push_back((firstDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
    		else if (yearChosen == 1990) {
    			for (int i = 0; i < secondDateVector.size(); i++) {
    				tempVector.push_back((secondDateVector.at(i)).getSong());
            tempArtistVector.push_back((firstDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
    		else if (yearChosen == 2000) {
    			for (int i = 0; i < thirdDateVector.size(); i++) {
    				tempVector.push_back((thirdDateVector.at(i)).getSong());
            tempArtistVector.push_back((firstDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
        else {
          cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl << endl;
          return true;
        }
      }
      if (timePeriod == 3) {
    		if (yearChosen == 2000) {
    			for (int i = 0; i < firstDateVector.size(); i++) {
    				tempVector.push_back((firstDateVector.at(i)).getSong());
            tempArtistVector.push_back((firstDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
    		else if (yearChosen == 2010) {
    			for (int i = 0; i < secondDateVector.size(); i++) {
    				tempVector.push_back((secondDateVector.at(i)).getSong());
            tempArtistVector.push_back((firstDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
    		else if (yearChosen == 2020) {
    			for (int i = 0; i < thirdDateVector.size(); i++) {
    				tempVector.push_back((thirdDateVector.at(i)).getSong());
            tempArtistVector.push_back((firstDateVector.at(i)).getArtist());
    			}
    			for (int i = 0; i < tempVector.size(); i++) {
    				currentSongFromVector = tempVector.at(i);
            currentArtistFromVector = tempArtistVector.at(i);
    				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
    				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
    					rankMax = max(rankMax, currentCount);
    					maxSongs.clear();
              maxArtist.clear();
    					maxSongs.push_back(currentSongFromVector);
              maxArtist.push_back(currentArtistFromVector);
    				}
    			}
    		}
        else {
          cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl << endl;
          return true;
        }
      }
      running = false;
    }
    else if (choice == 'Y') {
      cout << "Enter the year you would like to choose (e.g. 2001).";
      cin >> yearChosen;
      
      if (timePeriod == 1) {
        if (yearChosen >= 1960 && yearChosen <= 1980) {
          for (int i = 0; i < numberOneOccurances.size(); i++) {
            if (stoi((numberOneOccurances.at(i)).getDate()) == yearChosen) {
              tempVector.push_back((numberOneOccurances.at(i)).getSong());
              tempArtistVector.push_back((numberOneOccurances.at(i)).getArtist());
            }
          }
          for (int i = 0; i < tempVector.size(); i++) {
      				currentSongFromVector = tempVector.at(i);
              currentArtistFromVector = tempArtistVector.at(i);
      				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
      				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
      					maxSongs.push_back(currentSongFromVector);
                maxArtist.push_back(currentArtistFromVector);
      				}
      				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
      					rankMax = max(rankMax, currentCount);
      					maxSongs.clear();
                maxArtist.clear();
      					maxSongs.push_back(currentSongFromVector);
                maxArtist.push_back(currentArtistFromVector);
      				}
      		}
        }
        else {
          cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
          return true;
        }
      }
      if (timePeriod == 2) {
        if (yearChosen >= 1981 && yearChosen <= 2000) {
          for (int i = 0; i < numberOneOccurances.size(); i++) {
            if (stoi((numberOneOccurances.at(i)).getDate()) == yearChosen) {
              tempVector.push_back((numberOneOccurances.at(i)).getSong());
              tempArtistVector.push_back((numberOneOccurances.at(i)).getArtist());
            }
          }
          for (int i = 0; i < tempVector.size(); i++) {
      				currentSongFromVector = tempVector.at(i);
              currentArtistFromVector = tempArtistVector.at(i);
      				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
      				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
      					maxSongs.push_back(currentSongFromVector);
                maxArtist.push_back(currentArtistFromVector);
      				}
      				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
      					rankMax = max(rankMax, currentCount);
      					maxSongs.clear();
                maxArtist.clear();
      					maxSongs.push_back(currentSongFromVector);
                maxArtist.push_back(currentArtistFromVector);
      				}
      		}
        }
        else {
          cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
          return true;
        }
      }
      if (timePeriod == 3) {
        if (yearChosen >= 2001 && yearChosen <= 2020) {
          for (int i = 0; i < numberOneOccurances.size(); i++) {
            if (stoi((numberOneOccurances.at(i)).getDate()) == yearChosen) {
              tempVector.push_back((numberOneOccurances.at(i)).getSong());
              tempArtistVector.push_back((numberOneOccurances.at(i)).getArtist());
            }
          }
          for (int i = 0; i < tempVector.size(); i++) {
      				currentSongFromVector = tempVector.at(i);
              currentArtistFromVector = tempArtistVector.at(i);
      				currentCount = count(tempVector.begin(),tempVector.end(), currentSongFromVector);
      				if (max(rankMax, currentCount) == currentCount && count(maxSongs.begin(), maxSongs.end(), currentSongFromVector) == 0) {
      					maxSongs.push_back(currentSongFromVector);
                maxArtist.push_back(currentArtistFromVector);
      				}
      				else if (max(rankMax, currentCount) == currentCount && rankMax != currentCount) {
      					rankMax = max(rankMax, currentCount);
      					maxSongs.clear();
                maxArtist.clear();
      					maxSongs.push_back(currentSongFromVector);
                maxArtist.push_back(currentArtistFromVector);
      				}
      		}
        }
        else {
          cout << "No songs found in that timeframe. Be sure that the timeframe you enter is within the one covered by the dataset chosen." << endl;
          return true;
        }
      }
      running = false;
    }
    else {
      cout << "Invalid entry. Try again." << endl;
    }
  }
  cout << endl << endl << "The song(s) with the most #1 occurrences for selected time period is: " << endl;
	for (int i = 0; i < maxSongs.size(); i++) {
		cout << "        Song Title: " << maxSongs.at(i) << endl
         << "        Artist: " << maxArtist.at(i) << endl
		     << "        # of occurrences: " << rankMax << endl << endl;
	}
  cout << endl;
	tempVector.clear();
	maxSongs.clear();
return true;
}

void menuOptionThree(vector<infoFromCharts> &firstVector, vector<infoFromCharts> &secondVector, vector<infoFromCharts> &thirdVector, int timePeriod) {
  char choice;
	vector<infoFromCharts> numberOneOccurances, firstDateVector, secondDateVector, thirdDateVector;
	vector<string> tempVector, maxSongs, tempArtistVector, maxArtist;
	string currentSongFromVector, currentArtistFromVector;
	int yearChosen, rankMax = 0, currentCount = 0;
  
  reorderVector(firstVector, secondVector, thirdVector);
  
}

void menuOptionFive(vector<infoFromCharts>& chartInfoVector, string &choiceArtist) {
  
  vector<infoFromCharts> chartNames;
  cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name:" << endl;
  cin >> choiceArtist;



  for(int i = 0; i < choiceArtist.size(); i++) {
    choiceArtist.at(i) = tolower(choiceArtist.at(i));
  }

  for(int j = 0; j < chartInfoVector.size(); j++) {
    if((chartInfoVector.at(j)).getRank() == "1" || (chartInfoVector.at(j)).getPeakRank() == "1"){
      string topArtist = (chartInfoVector.at(j)).getArtist();
      for(int k = 0; k < topArtist.size(); k++) {
        topArtist.at(k) = tolower(topArtist.at(k));
      }
      if(topArtist.find(choiceArtist) != string::npos){
      chartNames.push_back(chartInfoVector.at(j));
      }
    }  
  }


  if(chartNames.size() > 0) {
    cout << "Retrieval of first 10 #1 records found based upon search by artist name: " << endl;
    for(int count = 0; count < 10; count++) {
        cout << (count + 1) << ") Song: " << chartNames.at(count).getSong() << endl
             << "    Artist: " << chartNames.at(count).getArtist() << endl
             << "    Week of: " << chartNames.at(count).getDate() << endl
             << "    Week Position: 1" << endl;
    }
  }
  else {
    cout << "No matching artists were found." << endl;
  }
  
}

void displayInfo(vector<infoFromCharts> &firstVector, vector<infoFromCharts> &secondVector, vector<infoFromCharts> &thirdVector, int timePeriod) {
	int choice;
	vector<string> uniqueSongs;
	string currentSong;
  string choiceArtist;
  bool status = true;

	while(status == true) {
    menuOption(choice);
    if (choice == 1) {
      if (timePeriod == 1) {
			  menuOptionOne(firstVector, uniqueSongs, currentSong);
  		}
  		else if (timePeriod == 2) {
  			menuOptionOne(secondVector, uniqueSongs, currentSong);
  		}
  		else {
  			menuOptionOne(thirdVector, uniqueSongs, currentSong);
  		}
		}
    else if (choice == 2) {
      menuOptionTwo(firstVector, secondVector, thirdVector, timePeriod);
	  }
    else if (choice == 3) {
      menuOptionThree(firstVector, secondVector, thirdVector, timePeriod);
    }
    else if (choice == 5) {
      if (timePeriod == 1) {
        menuOptionFive(firstVector, choiceArtist);
      }
      else if (timePeriod == 2) {
        menuOptionFive(secondVector,  choiceArtist);
      }
      else {
        menuOptionFive(thirdVector, choiceArtist);
      }
    }
    else if (choice == 6) {
		  status = false;
	  }
	 else {
	    cout << endl << "Invalid value.  Please re-enter a value from the menu options below.\n\n";
	    continue;
	 }
  }
}
/*
void menuOptionFive(vector<infoFromCharts> &chartInfoVector, vector<string> &artistNames, string &artistName) {
  cout << "Enter search text to retrieve first 10 records of #1 songs that match by artist name: " << endl;
  cin >> artistName;

  int count = 0;

  for(int i = 0; i < chartInfoVector.size(); i++) {
    artistName = (chartInfoVector.at(i).getArtist);
    if (count(uniqueSongs.begin(), uniqueSongs.end(), currentSong) == 0) {
      artistNames.push_back(artistName);
    }  
  }

  
    for(int i = 0; i < chartsInfoVector.size(); i++) {
      if(chartInfoVector.at(i).find(artistName) != npos && chartInfoVector.at(i).getRank == '1' && count <= 10)) {
        cout << (count + 1) << " Song: " << chartsInfoVector.at(i).getSong << "\n"
             << "    Artist: " << chartInfoVector.at(i).getArtist << "\n"
             << "    Week of: " << chartInfoVector.at(i).getDate << "\n"
             << "    Week Position; 1\n";
  else {
    cout << "No matching artists were found.\n"
  }
  
}
*/


void programHeader() {
	int choice;
	vector<infoFromCharts> firstOptionVector;
	vector<infoFromCharts> secondOptionVector;
	vector<infoFromCharts> thirdOptionVector;

  separateInfoIntoClass(firstOptionVector, 1);
	separateInfoIntoClass(secondOptionVector, 2);
	separateInfoIntoClass(thirdOptionVector, 3);
	
	cout << "Program 4: BillBoard Analysis \n"
	<< "CS 141, Spring 2022, UIC \n \n"
	<< "This program will analyze weekly Billboard data spanning from 1960 - 2020.\n\n"
	<< "Select file option:\n"
	<< "   1. To analyze charts top 50: 1960 - 1980 data file\n"
	<< "   2. To analyze charts top 50: 1981 - 2000 data file\n"
	<< "   3. To analyze charts top 50: 2001 - 2020 data file\n"
	<< "Your choice --> \n";
	cin >> choice;
	if (choice == 1) {
	   cout << endl;
		displayInfo(firstOptionVector, secondOptionVector, thirdOptionVector, choice);
	}
	else if (choice == 2) {
	   cout << endl;
		displayInfo(firstOptionVector, secondOptionVector, thirdOptionVector, choice);
	}
	else if (choice == 3) {
	   cout << endl;
		displayInfo(firstOptionVector, secondOptionVector, thirdOptionVector, choice);
	}
	else {
		cout << "Invalid value. Exiting Program.";
		exit(0);
	}
}


int main() {
	
	programHeader();
	
	return 0;
}
